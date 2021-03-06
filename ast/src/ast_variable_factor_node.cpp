#include "../include/ast_variable_factor_node.h"

ASTVariableFactorNode::ASTVariableFactorNode(int delta, int number, MemoryManagement * m) : delta(delta), number(number), ASTFactorNode(m) {}

int ASTVariableFactorNode::eval() {
  return memory->getValue(delta, number);
}