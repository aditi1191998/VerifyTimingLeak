#include <iostream>
#include <string>
#include <regex>
#include <iterator>
#include <fstream>

using namespace std;

int main (int argc, char **argv) {
  fstream inputText;
  ofstream outputText;
  string line;
  string line1;
  string filename = argv[1];
  //string lw = "(lw)(.[^,]*)(\\d+)(,)(\\d+)(.*)";
  //string sw = "(sw)(.[^,]*)(\\d+)(,)(\\d+)(.*)";
  long posi,pos;
  string latest,latest1;
  int count = 0;
  inputText.open(filename);
  cout << filename << endl;
  outputText.open("out.txt");
  if(inputText.good()) {
    while (getline(inputText, line)) {
      if(line.length()==0)
          continue;
      //regex re("(.*)(lw)(.[^,]*)(\\d+)(, )(\\d+)(.[^,]*)(\\d+)(.*)");
      //regex re1("(.*)(sw)(.[^,]*)(\\d+)(, )(\\d+)(.[^,]*)(\\d+)(.*)");
      regex re("(.*)(lw)(.[^,]*)(\\d+)(, )(\\d+)(.*)");
      regex re1("(.*)(sw)(.[^,]*)(\\d+)(, )(\\d+)(.*)");
      regex re2("(.*)(lb)(.[^,]*)(\\d+)(, )(\\d+)(.*)");
      smatch match;
    if (regex_search(line, match, re) == true) {
        outputText << "{INSTR_LOAD, ";
        outputText << stoi(match.str(6));
       // outputText << stoi(match.str(6)) +  stoi(match.str(8));
        outputText << ", 0, 0},";
        outputText << std::endl;
        count++;
    }
    else if (regex_search(line, match, re1) == true) {
        outputText << "{INSTR_STORE, ";
        outputText << stoi(match.str(6));
        //outputText << stoi(match.str(6)) +  stoi(match.str(8));
        outputText << ", 0, 0},";
        outputText << std::endl;
        count++;
    }
    if (regex_search(line, match, re2) == true) {
        outputText << "{INSTR_LOAD, ";
        outputText << stoi(match.str(6));
       // outputText << stoi(match.str(6)) +  stoi(match.str(8));
        outputText << ", 0, 0},";
        outputText << std::endl;
        count++;
    }
    else {
      continue;
    }
  }
}
inputText.close();
outputText.close();
system("g++ -o parser test.cpp");
string str = "./parser " + to_string(count);
const char * c = str.c_str();
system(c);
}

