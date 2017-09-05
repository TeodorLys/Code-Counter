#include "stdafx.h"
#include "MainVars.h"
#include "VisualStudio.h"
#include "OtherProjects.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <boost\filesystem\operations.hpp>

using namespace std;

void toClip(const string &s) {
 OpenClipboard(0);
 EmptyClipboard();
 HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size() + 1);
 if (!hg) {
  CloseClipboard();
  return;
 }
 memcpy(GlobalLock(hg), s.c_str(), s.size());
 GlobalUnlock(hg);
 SetClipboardData(CF_TEXT, hg);
 CloseClipboard();
 GlobalFree(hg);
}

void Parse_Arguments(char* arg[]) {
 path = arg[0];
 path.erase(path.find_last_of("\\"), path.length());
}

void LookForProjects() {
 boost::filesystem::directory_iterator itrfiles;  //As a reference for the finding the end of the lookup directory

 printf("Looking for Project...");

 //Iterates through the project folder.
 for (boost::filesystem::directory_iterator itr(path); itr != itrfiles; itr++) {
  //Saves all of the directories in the project folder.
  if (boost::filesystem::is_directory(itr->path()))
   dirOnly.push_back(itr->path());

  //If it finds a visual studio project
  if (itr->path().string().find(".vcxproj.filters") != string::npos) {
   //hasVisualProject = true;
   name = itr->path().filename().string();
  }

 }
}

void Parse_TimeStamp() {
 string mon = __DATE__;
 mon.erase(3, mon.length());
 //ex. Sep  5 2017
//	   <-------

 transform(mon.begin(), mon.end(), mon.begin(), ::tolower);   //The first letter of the month is uppercase

 string year = __DATE__;
 year.erase(0, year.length() - 4);
 //ex. Sep  5 2017
//    ------>

 string day = __DATE__;
 day.erase(0, 4);
 day.erase(2, day.length());
 //ex. Sep  5 2017
//    --->  <----

 int arraySize = sizeof(month) / sizeof(month[0]);
 string newMonth;
 //Converts the month letters(Sep) to numbers(09).
 for (int a = 0; a < arraySize; a++) {
  if (mon.find(month[a]) != string::npos) {
   if (a > 10)
	newMonth = to_string(a + 1);
   else
	newMonth = "0" + to_string(a + 1);
   break;
  }
 }

 string timeS = __TIME__;   //gets the current time
 timeS.erase(5, timeS.length());   //Removes the seconds.
 string date = year + "-" + newMonth + "-" + day + " " + timeS;  //Combines all of this convertion shenanigans
 printf("Presentable Version : \n");
 string present = "//" + date + ", Currently: " + to_string(line_count) + " lines of code";
 printf("%s\n", present.c_str());
 printf("Copy to clipboard?(Y/N): ");
 string answer;
 getline(cin, answer);
 if (answer.find("y") != string::npos)
  toClip(present);   //"ctrl+c" this does not happen automatically, because... reasons...
}

//MAIN
int main(int argc, char* argv[]) {

 Parse_Arguments(argv);  //Removes some of the access fat from the current directory.

 LookForProjects();


 if (path == "")   //Error checking for an empty path.
  exit(-1);

 //Just getting the .cpp/.h files from the .vcxproj file
 if (hasVisualProject) {
  printf("Found Visual Studio Project\n");
  path += "\\";
  VisualStudio::VisualProject();
  name.erase(name.find_first_of("."), name.length());
 }
 else {
  printf("Did not find any project, looking for .cpp/.h Files  -- %i\n", dirOnly.size());
  OtherProjects::OtherFiles();
 }

 cout << "--------------------------" << endl;
 printf("Final count for %s  =  Line: %i   Characters: %i\n\n", name.c_str(), line_count, char_Count);

 Parse_TimeStamp();
}
