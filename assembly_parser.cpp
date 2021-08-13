#include <iostream>
#include <string>
#include <regex>
#include <iterator>
#include <fstream>
#define testcase 200

using namespace std;

int main (int argc, char **argv) {
  fstream inputText[testcase];
  ofstream outputText[testcase];
  string line;
  string line1;
  string strIn;
  string strOut;
  //string lw = "(lw)(.[^,]*)(\\d+)(,)(\\d+)(.*)";
  //string sw = "(sw)(.[^,]*)(\\d+)(,)(\\d+)(.*)";
  long posi,pos;
  string latest,latest1;
  int count = 0;
  regex re("(.*)(lw)(.[^,]*)(\\d+)(, )(\\d+)(.*)");
  regex re1("(.*)(sw)(.[^,]*)(\\d+)(, )(\\d+)(.*)");
  regex re2("(.*)(lb)(.[^,]*)(\\d+)(, )(\\d+)(.*)");
  smatch match;
  for(int i=0;i<testcase;i++) {
  count = 0;
  strIn = "output" + to_string(i);
  strOut = "out" + to_string(i);
  inputText[i].open(strIn);
  outputText[i].open(strOut);
  if(inputText[i].good()) {
    while (getline(inputText[i], line)) {
      if(line.length()==0)
          continue;
      //regex re("(.*)(lw)(.[^,]*)(\\d+)(, )(\\d+)(.[^,]*)(\\d+)(.*)");
      //regex re1("(.*)(sw)(.[^,]*)(\\d+)(, )(\\d+)(.[^,]*)(\\d+)(.*)");
    if (regex_search(line, match, re) == true) {
        outputText[i] << "{INSTR_LOAD, ";
        outputText[i] << stoi(match.str(6));
       // outputText << stoi(match.str(6)) +  stoi(match.str(8));
        outputText[i] << ", 0, 0},";
        outputText[i] << std::endl;
        count++;
    }
    else if (regex_search(line, match, re1) == true) {
        outputText[i] << "{INSTR_STORE, ";
        outputText[i] << stoi(match.str(6));
        //outputText << stoi(match.str(6)) +  stoi(match.str(8));
        outputText[i] << ", 0, 0},";
        outputText[i] << std::endl;
        count++;
    }
    if (regex_search(line, match, re2) == true) {
        outputText[i] << "{INSTR_LOAD, ";
        outputText[i] << stoi(match.str(6));
       // outputText << stoi(match.str(6)) +  stoi(match.str(8));
        outputText[i] << ", 0, 0},";
        outputText[i] << std::endl;
        count++;
    }
    else {
      continue;
    }
  }
  inputText[i].close();
  outputText[i].close();
}
}
system("g++ -o parser test.cpp");
string str = "./parser " + to_string(count);
const char * c = str.c_str();
system(c);
}

