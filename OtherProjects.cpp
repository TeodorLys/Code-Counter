#include "OtherProjects.h"
#include "Variables.h"
#include <iostream>
#include <boost\filesystem\operations.hpp>

using namespace std;

std::vector<std::string> toExclude;

string numList = "0123456789";

struct Range
{
 Range(boost::filesystem::path dir) : project_Dir(dir) {}

 boost::filesystem::recursive_directory_iterator begin() { return boost::filesystem::recursive_directory_iterator(project_Dir); }
 boost::filesystem::recursive_directory_iterator end() { return boost::filesystem::recursive_directory_iterator(); }

 boost::filesystem::path project_Dir;
};

void foundDir(boost::filesystem::path _p) {
 for (auto it : Range(_p)) {
  if (it.path().filename().string().find(".cpp") != string::npos || it.path().string().find(".h") != string::npos) {
   allCpp.push_back(it.path().string());
  }
 }
}

//Converts the char to a number, probably exist a standard way to do this...
int ctoi(char c) {
 if (isalnum(c)) {
  switch (c)
  {
  case '0':
   return 0;
   break;

  case '1':
   return 1;
   break;

  case '2':
   return 2;
   break;

  case '3':
   return 3;
   break;

  case '4':
   return 4;
   break;

  case '5':
   return 5;
   break;

  case '6':
   return 6;
   break;

  case '7':
   return 7;
   break;

  case '8':
   return 8;
   break;

  case '9':
   return 9;
   break;

  default:
   return 0;
  }

 }
}

//Checks if a string contains a number
bool ContainsNumber(string s) {
 bool buff = false;
 for (char c : s) {
  printf("%c", c);
  if (numList.find(c) != string::npos) {
   buff = true;
  }
 }

 return buff;
}

string OtherProjects::GetExclution(string s) {
 string buff;
 
 //goes through every char in the answer.
 for (char c : s) {
  if (isalnum(c)) {
   toExclude.push_back(dirOnly[ctoi(c)].string());
  }
 }
 return buff;
}

void OtherProjects::OtherFiles() {
 string answer;

 //If it finds any directories in the project folder.
 if (dirOnly.size() > 0) {

  std::printf("Anything to Exclude? -- ex. (0, 1, 2) \n");
  
  for (int a = 0; a < dirOnly.size(); a++) {
   std::printf("%i. %s\n", a, dirOnly[a].filename().string().c_str());
  }

  std::printf("> ");
  getline(cin, answer);   //Select any exclution folder?

  if (!ContainsNumber(answer))   //Checks is if the answer contains a number
   answer = "";

  if (answer != "")
   GetExclution(answer);   //Saves the exclution folders to a vector.
 }

 bool found = false;
 boost::filesystem::directory_iterator itrfiles;

 if (answer != "") {

  for (boost::filesystem::directory_iterator itr(path); itr != itrfiles; itr++) {
   if (boost::filesystem::is_directory(itr->path())) {
	//Check if the current directory is an exclution folder
	for (int a = 0; a < toExclude.size(); a++) {
	 if (itr->path().string().find(toExclude[a]) != string::npos)
	  found = true;
	}

	//If it finds an exclution folder, skip the directory check.
	if (!found)
	 foundDir(itr->path());

	found = false;   //Reset the exclution checking.
   }
   else {
	//Saves the path of all, wanted, .cpp/.h files
	if (itr->path().filename().string().find(".cpp") != string::npos || itr->path().string().find(".h") != string::npos)
	 allCpp.push_back(itr->path().string());
   }
  }

 }
  else {
   //If the user doesnt select any exclution folders, it will just check everything.
   for (auto it : Range(path))
	if (it.path().filename().string().find(".cpp") != string::npos || it.path().string().find(".h") != string::npos)
	 allCpp.push_back(it.path().string());
  }


 fstream f;   //Variable for all of the .cpp/.h files

 //Iterates through all of the elements in allCpp
 for (int a = 0; a < allCpp.size(); a++) {

  f.open(allCpp[a].string());

  if (!f.is_open())
   exit(-1);

  printf("%s", allCpp[a].filename().string().c_str());
  //Iterates through all of the lines in the current opened file
  for (string b; getline(f, b);) {
   //Character count
   for (char c : b) {
	char_Count++;   //Cumulative character count for all files.
	each_Char_Count++;   //Character count for each file.
   }
   line_count++;   //Cumulative line count for all files.
   each_Count++;   //Line count for current file.
  }

  distanceBuff = distanceConst - allCpp[a].filename().string().length();
  setDistance.resize(distanceBuff, ' ');

  numDistanceStringBuff = to_string(each_Count);

  if (numDistanceStringBuff.length() == 1)
   numDistance.resize(4, ' ');
  else if (numDistanceStringBuff.length() == 2)
   numDistance.resize(3, ' ');
  else if (numDistanceStringBuff.length() == 3)
   numDistance.resize(2, ' ');
  else
   numDistance.resize(1, ' ');

  printf("%s Line: %s%i   Charachter: %i\n", setDistance.c_str(), numDistance.c_str(), each_Count, each_Char_Count);
  each_Count = 0;
  each_Char_Count = 0;
  f.close();
 }

}
