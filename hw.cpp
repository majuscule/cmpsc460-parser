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

enum query {
  IF_STATEMENT,
  EXPRESSION
};

class expression {
  public: 
    int operands[2];
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
        case 'x':
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

struct command {
  query type;
  expression operands[4];
};

string read() {
  cout << prompt;
  string command = "";
  getline(cin, command);
  return command;
}

int parse(string input, command *cmd) {
  int operand = 0;
  if (input[0] == '(' && input[input.length()-1] == ')') {
    input = input.substr(1, input.length()-2);
    cmd->type = EXPRESSION;
  } else if (input.substr(0, 2) == "IF") {
    cmd->type = IF_STATEMENT;
  } else {
    fprintf(stderr, "scan error: expected EXPRESSION or IF_STATEMENT\n");
    return 1;
  }
  istringstream split(input); 
  string word = "";
  int exp_operand = 0;
  while (getline(split, word, ' ')) {
    if (word == "") continue;
    switch (cmd->type) {
      case EXPRESSION:
        if (operand < 2) {
          if (stringstream(word) >> cmd->operands[0].operands[operand]) {
            operand++;
          } else {
              fprintf(stderr, "scan error: parsing EXPRESSION, found illegal OPERAND\n");
              return 1;
          }
        } else {
          if (isdigit(word[0])) {
            fprintf(stderr, "parse error: too many OPERANDs\n");
            return 1;
          } else if (cmd->operands[0].set_op(word)) {
            fprintf(stderr, "scan error: parsing EXPRESSION, found illegal OPERATION\n");
            return 1;
          }
        }
        break;
      case IF_STATEMENT:
        if (word == "IF") break;
        if (exp_operand == 0) { word = word.substr(1, word.length()); }
        if (exp_operand == 2) {
            word = word.substr(0, word.length()-1);
            cmd->operands[operand].set_op(word);
        } else {
          stringstream(word) >> cmd->operands[operand].operands[exp_operand];
        }
        exp_operand++;
        if (exp_operand == 3) {
          operand++;
          exp_operand = 0;
        }
        break;
    }
  }
  return 0;
}

int evaluate(expression *exp) {
  int result = 0;
  switch (exp->op) {
    case ADDITION:
      result = exp->operands[0] + exp->operands[1];
      break;
    case SUBTRACTION:
      result = exp->operands[0] - exp->operands[1];
      break;
    case MULTIPLICATION:
      result = exp->operands[0] * exp->operands[1];
      break;
    case DIVISION:
      result = exp->operands[0] / exp->operands[1];
      break;
    case MODULO:
      result = exp->operands[0] % exp->operands[1];
      break;
  }
  return result;
}


int main(int argc, char *argv[]) {
  while (1) {
    command cmd;
    string input = read();
    if (input == "" || parse(input, &cmd)) continue;
    int result = evaluate(&cmd.operands[0]);
    if (cmd.type == EXPRESSION)
      printf("%d\n", result);
    else if (cmd.type == IF_STATEMENT) {
      int jump = (result < 0 ? 1 : (result == 0 ? 2 : 3));
      printf("%d\n", evaluate(&cmd.operands[jump]));
    }
  }
}

