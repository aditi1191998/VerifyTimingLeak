#include <iostream>
#include <string>
#include <regex>
#include <iterator>
#include <fstream>
#define testcase 200

using namespace std;

int main (int argc, char **argv) {
	fstream fileText;
    fstream inputText[testcase];
    fstream outputText;
    ofstream queryText;
    string strIn;
    int count = atoi(argv[1])+1;
    fileText.open("data.txt");
    outputText.open("final.xta", ios::in | ios::out);
    queryText.open("query.q");
    string match = "/**** Programs ****************************************************************/";
    string match1 = "// Programs can be found in the Core template's declaration.";
    string line,line1;
    int pos;
    if(fileText.good()) {
    while (getline(fileText, line)) {
      if(match == line)
      {
      	for(int i=0;i<testcase;i++) {
        strIn = "out" + to_string(i);
        inputText[i].open(strIn);
      	outputText << endl;
      	strIn = "const program_line_t program_" + to_string(i) + " [";
      	outputText << strIn;
      	outputText << count << "] =";
      	outputText << endl;
      	outputText << "{" << endl;
      	 if(inputText[i].good()) {
      	 	while (getline(inputText[i], line1)) {
      	 		if(line1.length()==0)
      	 			continue;
      	 		outputText << line1 << endl;
      	 	}
      	 }
      	 outputText << "{INSTR_END,0, 0, 0}" << endl;
      	 outputText << "};" << endl;
      	 inputText[i].close();
      	}
      	outputText << "program_line_t get_current_program_line ()";
      	outputText << endl << "{";
      	outputText << endl;
      	for(int i=0;i<testcase;i++) {
        outputText << " if (PROGRAM == ";
        outputText << i;
        outputText << ")" << endl << " {" << endl;
        outputText << " return program_";
        outputText << i;
        outputText << "[program_counter];" << endl << " }";
        outputText << endl;
        }
    outputText << "return program_0[program_counter];";
    outputText << endl;
    outputText << "}" << endl;
      }
      else
      {
      	outputText << line << endl;
      }
  }
}
queryText << "A[] Test0a.Terminated imply Test0a.runtime>=" << (count-1)*200;
fileText.close();
queryText.close();
outputText.close();
cout << "parser done" << endl;
char ch;
for(int i = 0;i<200;i++) {
outputText.open("final.xta", ios::in | ios::out);
cout << "aditi" << i;
outputText.seekg(-2,ios::end);
long posi = outputText.tellg();
int exit = 0;
while(1) {
 outputText.seekg(posi-1);
    if(!outputText.good()) {
      cout << "ret" << endl;
      return 1;
    }
    while (outputText.good())
    {
    while(ch != '\n')
      {
        ch=outputText.get();
        outputText.seekg(-2,ios::cur);
      }
    posi = outputText.tellp();
    outputText.seekp(posi+2);
    getline(outputText, line);
   // cout << line << endl;
    int index, post;
    if ((index = line.find("Test0a = Core(1,3", post)) != string::npos) {
    //	cout <<"Aditi" << endl;
      posi = outputText.tellp();
      outputText.seekp(posi - line.size() - 1);
      outputText << "Test0a = Core(1,3," << i << ");\nsystem\n";
      exit = 1;
      break;
    }
    outputText.seekp(posi-2);
    ch=outputText.get();
    if(ch == '\n') {
        //cout << "ch" << endl; 
        outputText.seekp(posi-2);
        ch=outputText.get();
      }
  }
  if(exit == 1) {
  outputText.flush();
  outputText.close();
  break;
}
}
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
outputCheck.close();
}
}