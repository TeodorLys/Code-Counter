#include "VisualStudio.h"
#include "Variables.h"
#include <algorithm>
#include <fstream>

using namespace std;

void VisualStudio::VisualProject() {
 ifstream file(path + name);   //Opens the *.vcxproj.filters
 ifstream f;  //variable to open all of the .cpp/.h files to count lines.

 for (string s; getline(file, s);) {

  transform(s.begin(), s.end(), s.begin(), ::tolower);

  if (s.find("include") != string::npos && s.find(".cpp") != string::npos || s.find(".h") != string::npos) {
   string buff = s;
   buff.erase(0, s.find_first_of('"') + 1);  //ex. <clinclude include="src\*.cpp">
											 //    -------------------> 

   buff.erase(buff.find_last_of('"'), buff.find_last_of('>'));  //ex. src\*.cpp">
																//			   <-

   f.open(path + buff);   //Opens the parsed file

   if (!f.is_open())
	exit(-1);

   printf("%s: ", buff.c_str());

   //Iterates through every line in .cpp/.h file
   for (string b; getline(f, s);) {
	for (char c : s) {   //Character counter
	 char_Count++;
	 each_Char_Count++;
	}
	line_count++;   //Cumulative line count
	each_Count++;   //Current file's line count
   }

   //Just for visual appeal
   {
	distanceBuff = distanceConst - buff.length();   //For ease of reading the console logging
	setDistance.resize(distanceBuff, ' ');

	numDistanceStringBuff = to_string(each_Count);

	//Count number distance... not very good, only counts upp to 1000
	switch (numDistanceStringBuff.length()) {
	case 1:
	 numDistance.resize(4, ' ');
	 break;

	case 2:
	 numDistance.resize(3, ' ');
	 break;

	case 3:
	 numDistance.resize(2, ' ');
	 break;

	case 4:
	 numDistance.resize(1, ' ');
	 break;

	default:
	 numDistance.resize(0, ' ');
	 break;
	}
   }
   printf("%s Line: %s%i   Charachter: %i\n", setDistance.c_str(), numDistance.c_str(), each_Count, each_Char_Count);
   each_Count = 0;
   each_Char_Count = 0;
   f.close();
  }
 }

 //Just to be safe
 f.close();
 file.close();
}