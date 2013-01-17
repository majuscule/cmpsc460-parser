#include <iostream>
#include <stdio.h>
#include <sstream>
#include <string>
#include <vector>


using namespace std;

const string prompt = "> ";

struct expression {
  int a;
  int b;
  string op;
};

void error(int charNum, string msg) {
  fprintf(stderr, "  error at char #%d: %s\n", charNum, msg.c_str());
}

string read() {
  cout << prompt;
  string command = "";
  getline(cin, command);
  return command;
}

int* parse(string command, int operands[]){
  expression exp;
  int operand = 0;
  if (command[0] != '(') {
    error(0, "expected SEPARATOR");
    return 0;
  } else if (command[command.length()-1] != ')') {
    error(command.length(), "expected trailing ')' to end expression");
    return 0;
  }
  command = command.substr(1, command.length()-2);
  istringstream split(command); 
  string word = "";
  while (getline(split, word, ' ')) {
      if (stringstream(word) >> operands[operand]) {
        operand++;
      } else {
        exp.op = word;
      }
  }

  return operands;
}

int evaluate(int operands[]) {
    int result = operands[0] + operands[1];
    printf("  got result: %d\n", result);
}

int main() {
  while (1) {
    string input = read();
    int operands[2] = {0, 0};
    int *command = parse(input, operands);
    if (command != 0) {
        evaluate(operands);
    }
  }
}

