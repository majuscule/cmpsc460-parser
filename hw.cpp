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

void error(string msg) {
  fprintf(stderr, "  error: %s\n", msg.c_str());
}

string read() {
  cout << prompt;
  string command = "";
  cin >> command;
  return command;
}

int parse(string command){
  if (command[0] != '(') {
    error("expected a '(' character to begin the expression");
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
            error("expected 'IF' conditional");
            return 0;
          }
      }
    } else if (last_seen == NUMBER) {

    } else if (last_seen == OPERATOR) {
      if (command[i] != ')') {
        error("expected a ')' character to end the expression");
        return 0;
      }
    }
    i++;
  }
  printf("  read command %s\n", command.c_str());
}

int main() {
  while (1) {
    string command = read();
    parse(command);
  }
}

