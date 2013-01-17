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

int parse(string command, expression *exp){
  string op = "";
  int operand = 0;
  int operands[2];
  if (command[0] != '(') {
    error(0, "expected SEPARATOR");
    return 1;
  } else if (command[command.length()-1] != ')') {
    error(command.length(), "expected trailing ')' to end expression");
    return 1;
  }
  command = command.substr(1, command.length()-2);
  istringstream split(command); 
  string word = "";
  while (getline(split, word, ' ')) {
      if (stringstream(word) >> operands[operand]) {
        operand++;
      } else {
        op = word;
      }
  }

  exp->a = operands[0];
  exp->b = operands[1];
  exp->op = op;
  return 0;
}

void evaluate(expression *exp) {
    int result = exp->a + exp->b;
    printf("%d\n", result);
}

int main() {
  while (1) {
    string input = read();
    expression exp;
    if (!parse(input, &exp)) {
        evaluate(&exp);
    }
  }
}

