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
  expression operands[3];
};

string read() {
  cout << prompt;
  string command = "";
  getline(cin, command);
  return command;
}

query parse(string input, command *cmd){
  expression *exp = &(cmd->operands[0]);
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
          if (stringstream(word) >> exp->operands[operand]) {
            operand++;
          } else {
            if (exp->set_op(word)) {
              fprintf(stderr, "expected OPERATOR (one of +-*/%\n)");
            };
          }
          break;
//        case IF_STATEMENT:
//          exp
//          exp_operand++;
//          if (exp_operand == 2) {
//            operand++;
//            exp_operand = 0;
//          }
//          break;
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
    if (query type = parse(input, &cmd)) {
      int result = evaluate(&(cmd.operands[0]));
      if (type = EXPRESSION)
        printf("%d\n", result);
      else if (type = IF_STATEMENT) {
        int jump = (result < 0 ? 1 : (result == 0 ? 2 : 3));
        printf("%d\n", evaluate(&(cmd.operands[jump])));
      }
    }
  }
}

