#include <iostream>
#include <string>
#include <regex>
#include <iterator>
#include <fstream>

using namespace std;

int main (int argc, char **argv) {
	fstream fileText;
    fstream inputText;
    ofstream outputText;
    int count = atoi(argv[1])+1;
    fileText.open("data.txt");
    inputText.open("out.txt");
    outputText.open("final.xta");
    string match = "/**** Programs ****************************************************************/";
    string line,line1;
    int pos,flag=0;
    if(fileText.good()) {
    while (getline(fileText, line)) {
      if(match == line && flag==0)
      {
      	outputText << endl;
      	outputText << "const program_line_t program_202 [";
      	outputText << count << "] =";
      	outputText << endl;
      	outputText << "{" << endl;
      	 if(inputText.good()) {
      	 	while (getline(inputText, line1)) {
      	 		if(line1.length()==0)
      	 			continue;
      	 		outputText << line1 << endl;
      	 	}
      	 }
      	 outputText << "{INSTR_END,0, 0, 0}" << endl;
      	 outputText << "};" << endl;
      	 flag = 1;
      }
      else
      {
      	outputText << line << endl;
      }
  }
}
inputText.close();
fileText.close();
outputText.close();
cout << "parser done" << endl;
system("./verifyta final.xta query.q > result.txt");
ifstream outputCheck;
string check = "(.*)(NOT satisfied)(.*)";
outputCheck.open("result.txt");
    if (outputCheck.good()) {
     regex e(check); 
     while (getline(outputCheck, line1)) {
      //cout << line1 << endl;
      if (regex_match(line1, e)) {
       cout << "Prone to Timing leak" << endl;
       break;
     }
   }
 }
}