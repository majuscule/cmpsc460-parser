#include <iostream>
#include <stdio.h>
#include <sstream>
#include <string>
#include <vector>


using namespace std;

const string prompt = "> ";

enum operation {
  ADDITION,
  SUBTRACTION,
  MULTIPLICATION,
  DIVISION,
  MODULO
};

class expression {
  public: 
    int a;
    int b;
    operation op;
    int set_op(string op) {
      if (op.length() > 1) { return 0; }
      switch (op.c_str()[0]) {
        case '+':
          this->op = ADDITION;
          break;
        case '-':
          this->op = SUBTRACTION;
          break;
        case '*':
          this->op = MULTIPLICATION;
          break;
        case '/':
          this->op = DIVISION;
          break;
        case '%':
          this->op = MODULO;
          break;
        default:
          return 1;
      }
      return 0;
    }
};

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
  if (exp->set_op(op)) {
    fprintf(stderr, "expected OPERATOR (one of +-*/%\n)");
  };
  return 0;
}

void evaluate(expression *exp) {
    int result;
    switch (exp->op) {
      case ADDITION:
        result = exp->a + exp->b;
        break;
      case SUBTRACTION:
        result = exp->a - exp->b;
        break;
      case MULTIPLICATION:
        result = exp->a * exp->b;
        break;
      case DIVISION:
        result = exp->a / exp->b;
        break;
      case MODULO:
        result = exp->a % exp->b;
        break;
    }
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

