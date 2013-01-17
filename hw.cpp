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

query parse(string input, command *cmd){
  int operand = 0;
  query query_type;
  if (input[0] == '(' && input[input.length()-1] == ')') {
    input = input.substr(1, input.length()-2);
    query_type = EXPRESSION;
  } else if (input.substr(0, 2) == "IF") {
    query_type = IF_STATEMENT;
  } else {
    fprintf(stderr, "expected EXPRESSION or IF_STATEMENT");
  }
  istringstream split(input); 
  string word = "";
  int exp_operand = 0;
  while (getline(split, word, ' ')) {
    switch (query_type) {
        case EXPRESSION:
          if (stringstream(word) >> cmd->operands[0].operands[operand]) {
            operand++;
          } else {
            if (cmd->operands[0].set_op(word)) {
              fprintf(stderr, "expected OPERATOR (one of +-*/%\n)");
            };
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
  return query_type;
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


int main() {
  while (1) {
    command cmd;
    string input = read();
    query type = parse(input, &cmd);
    int result = evaluate(&(cmd.operands[0]));
    if (type == EXPRESSION)
      printf("%d\n", result);
    else if (type == IF_STATEMENT) {
      int jump = (result < 0 ? 2 : (result == 0 ? 3 : 4));
      printf("%d\n", evaluate(&(cmd.operands[jump])));
    }
  }
}

