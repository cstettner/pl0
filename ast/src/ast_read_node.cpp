#include "../include/ast_read_node.h"
#include <string>
  using std::string;
#include <iostream>
  using std::cin;
#include <stdlib.h>

ASTReadNode::ASTReadNode(int delta, int number) : delta(delta), number(number) {}

void ASTReadNode::execute() {
  string tmp;
  cin >> tmp;

  memory->insertValue(delta, number, atoi(tmp.c_str()));
}