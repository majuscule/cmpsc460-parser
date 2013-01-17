#include <iostream>
#include <stdio.h>

using namespace std;

const string prompt = "> ";

enum token {
  SEPARATOR,
  SPACE,
  NUMBER,
  OPERATOR,
  CONDITIONAL
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

int parse(string command){
  if (command[0] != '(') {
    error(0,command);
    return 0;
  }
  token last_seen = SEPARATOR;
  int i = 1;
  while (i < command.length()) {
    if (last_seen == SEPARATOR) {
      if (isdigit(command[i])) {
        last_seen = NUMBER;
      } else if (command[i] == 'I') {
          if ( i+1 < command.length()
                  && command[i+1] == 'F') {
            last_seen = CONDITIONAL;
            i++;
          } else {
            error(i, "expected 'IF' conditional");
            return 0;
          }
      } else {
        error(i, "expected a DIGIT or an IF statement");
        return 0;
      }
    } else if (last_seen == NUMBER) {
        if (command[i] == ' ') {
            last_seen = SPACE;
        } else if (!isdigit(command[i])) {
            error(i, "expected a SPACE or a DIGIT");
            return 0;
        }
    } else if (last_seen == OPERATOR) {
      if (command[i] != ')') {
        error(i, "expected a ')' character to end the expression");
        return 0;
      }
    } else if (last_seen == SPACE) {
      if (! (isdigit(command[i])
                || command[i] == ')'
                || command[i] == '+')) {
          fprintf(stderr, "  warn: =%c=\n", command[i]);
          error(i, "expected DIGIT, SEPARATOR, or OPERATOR");
          return 0;
      }
      if (isdigit(command[i])) {
        last_seen = NUMBER;
      }
    } else {
      error(i, "expected SEPARATOR, DIGIT, or IF statement");
      return 0;
    }
    i++;
  }
  printf("  read command %s\n", command.c_str());
}

int main() {
  while (1) {
    string input = read();
    parse(input);
  }
}

