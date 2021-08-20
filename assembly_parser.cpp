#include <iostream>
#include <string>
#include <regex>
#include <iterator>
#include <fstream>
#define testcase 1

using namespace std;

int main (int argc, char **argv) {
  fstream inputText[testcase];
  ofstream outputText[testcase];
  ofstream queryText;
  string line;
  string line1;
  string strIn;
  string strOut;
  queryText.open("query.q");
  //string lw = "(lw)(.[^,]*)(\\d+)(,)(\\d+)(.*)";
  //string sw = "(sw)(.[^,]*)(\\d+)(,)(\\d+)(.*)";
  long posi,pos;
  string latest,latest1;
  int count = 0;
  regex re("(.*)(lw)(.[^,]*)(\\d+)(, )(\\d+)(.*)( 1)(.*)");
  regex re1("(.*)(sw)(.[^,]*)(\\d+)(, )(\\d+)(.*)( 1)(.*)");
  regex re2("(.*)(lb)(.[^,]*)(\\d+)(, )(\\d+)(.*)( 1)(.*)");
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
        queryText << "sup{not Test0a.Terminated}: CCTRL0.list[" << count << "]" << endl;
        count++;
        //queryText << "sup{not Test0a.Terminated}: CCTRL0.cache_local_address_infos[" << stoi(match.str(6)) << "].hit" << endl;
    }
    else if (regex_search(line, match, re1) == true) {
        outputText[i] << "{INSTR_STORE, ";
        outputText[i] << stoi(match.str(6));
        //outputText << stoi(match.str(6)) +  stoi(match.str(8));
        outputText[i] << ", 0, 0},";
        outputText[i] << std::endl;
        queryText << "sup{not Test0a.Terminated}: CCTRL0.list[" << count << "]" << endl;
        count++;
        //queryText << "sup{Test0a.Terminated}: CCTRL0.cache_local_address_infos[" << stoi(match.str(6)) << "].hit" << endl;
    }
    if (regex_search(line, match, re2) == true) {
        outputText[i] << "{INSTR_LOAD, ";
        outputText[i] << stoi(match.str(6));
       // outputText << stoi(match.str(6)) +  stoi(match.str(8));
        outputText[i] << ", 0, 0},";
        outputText[i] << std::endl;
        queryText << "sup{not Test0a.Terminated}: CCTRL0.list[" << count << "]" << endl;
        count++;
        //queryText << "sup{Test0a.Terminated}: CCTRL0.cache_local_address_infos[" << stoi(match.str(6)) << "].hit" << endl;
    }
    else {
      continue;
    }
  }
  inputText[i].close();
  outputText[i].close();
}
}
//queryText << "A[] Test0a.Terminated imply Test0a.runtime>=" << (count-1)*200 << endl;
queryText.close();
system("g++ -o parser test.cpp");
string str = "./parser " + to_string(count);
const char * c = str.c_str();
system(c);
}

