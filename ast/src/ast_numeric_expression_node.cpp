#include "../include/ast_numeric_expression_node.h"

ASTNumericExpressionNode::ASTNumericExpressionNode(ASTTermNode * term) {
  terms = new TermList;
  terms->push_back(term);
}

void ASTNumericExpressionNode::insert(ASTTermNode * term) {
  terms->push_back(term);
}

int ASTNumericExpressionNode::eval() {
	int val = 0;

	for(TermList::iterator it = terms->begin(); it != terms->end(); ++it) {
		val += (*it)->eval();
	}

	return val;
}
