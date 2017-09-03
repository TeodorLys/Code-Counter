#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

string path;
string name;
string setDistance = "";
string numDistance = "";
string numDistanceStringBuff = "";
const int distanceConst = 45;
int distanceBuff;
int numDistanceBuff;


void Parse_Arguments(char* arg[]){
path = arg[0];
path.erase(path.find_last_of("\\"), path.length());

name = path;
name.erase(0, name.find_last_of("\\") + 1);
name += ".vcxproj.filters";

path += "\\";
}

//MAIN
int main(int argc, char* argv[]){

Parse_Arguments(argv);

if(path == "")
  exit(-1);

ifstream file(path + name);

ifstream f;
int count = 0;
int each_Count = 0;
int char_Count = 0;
int each_Char_Count = 0;

for(string s; getline(file, s);){

transform(s.begin(), s.end(), s.begin(), ::tolower);

if(s.find("include") != string::npos && s.find(".cpp") != string::npos || s.find(".h") != string::npos){
  string buff = s;
  buff.erase(0, s.find_first_of('"') + 1);
  buff.erase(buff.find_last_of('"'), buff.find_last_of('>'));

  f.open(path + buff);
  if(!f.is_open())
  exit(-1);

  printf("%s: ", buff.c_str());
  for(string b; getline(f, s);){
    for(char c : s){
      char_Count++;
      each_Char_Count++;
    }
    count++;
    each_Count++;
  }
  distanceBuff = distanceConst - buff.length();
  setDistance.resize(distanceBuff, ' ');

  numDistanceStringBuff = to_string(each_Count);

  if(numDistanceStringBuff.length() == 1)
  numDistance.resize(4, ' ');
  else if(numDistanceStringBuff.length() == 2)
  numDistance.resize(3, ' ');
  else if(numDistanceStringBuff.length() == 3)
  numDistance.resize(2, ' ');
  else
  numDistance.resize(1, ' ');

  printf("%s Line: %s%i   Charachter: %i\n", setDistance.c_str(), numDistance.c_str(), each_Count, each_Char_Count);
  each_Count = 0;
  each_Char_Count = 0;
  f.close();
}

}

f.close();
file.close();
name.erase(name.find_first_of("."), name.length());
cout << "--------------------------" << endl;
printf("Final count for %s  =  Line: %i   Characters: %i", name.c_str(), count, char_Count);
}
