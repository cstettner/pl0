#include "../include/symbol_table.h"
#include <iostream>
	using std::cout;

SymbolTable::SymbolTable() {
	level = -1;
	max_number = 0;
}

void SymbolTable::level_up() {
	level++;
	// Vector vergrößern, falls zu klein
	if(symbol_table.size() <= level) {
		symbol_table.push_back(map<string, SymbolTableEntry>());
	}
}

void SymbolTable::level_down() {
	symbol_table[level].clear();
	level--;
}

void SymbolTable::insert(string key, int type) {
	// only insert if key not inserted yet in this level
	if(symbol_table[level].find(key) == symbol_table[level].end()) {
		// calculate running number
		int number = symbol_table[level].size();
		// update max_number for print
		if(number > max_number) max_number = number;
		// Insert Element
		symbol_table[level].insert(pair<string, SymbolTableEntry>(key, SymbolTableEntry(type, number)));
	}
}

SymbolTableEntry * SymbolTable::getSymbolTableEntry(string key, int type) {
	// start in highest level
	int tmp_level = level + 1;
	// Search for symbol
	while(--tmp_level >= 0 && symbol_table[tmp_level].find(key) == symbol_table[tmp_level].end());

	if(tmp_level >= 0) {
		SymbolTableEntry * symbol = &(symbol_table[tmp_level].find(key)->second);
		if(symbol->getType() == type) {
			// lookup successful
			return symbol;
		}
	}
}

ASTProcedureNode * SymbolTable::getProcedureNode(string key, int type) {
	// start in highest level
	int tmp_level = level + 1;
	// Search for symbol
	while(--tmp_level >= 0 && symbol_table[tmp_level].find(key) == symbol_table[tmp_level].end());

	if(tmp_level >= 0) {
		SymbolTableEntry symbol = symbol_table[tmp_level].find(key)->second;
		if(symbol.getType() == type) {
			// lookup successful
			return symbol.getProcedureNode();
		}
	}
}

ASTProcedureNode * SymbolTable::getProcedureNode(int level, string key) {
	return symbol_table[level].find(key)->second.getProcedureNode();
}

int SymbolTable::lookup(string key, int type, int& p_level, int& number) {
	// start in highest level
	int tmp_level = level + 1;
	// Search for symbol
	while(--tmp_level >= 0 && symbol_table[tmp_level].find(key) == symbol_table[tmp_level].end());

	if(tmp_level >= 0) {
		SymbolTableEntry symbol = symbol_table[tmp_level].find(key)->second;
		if(symbol.getType() != type) {
			return IDENTIFIER_WRONG_TYPE;
		}
		else {
			// lookup successful
			p_level = tmp_level;
			number = symbol.getNumber();
			return IDENTIFIER_FOUND;
		}
	}
	else {
		return IDENTIFIER_NOT_FOUND;
	}
}

int SymbolTable::getCurrentLevel() {
	return level;
}

void SymbolTable::print() {
	cout << "Start - Print\n";
	cout << "Current Level: " << level << "\n";
	for(int i = 0; i < symbol_table.size(); i++) {
		for(map_iter iter = symbol_table[i].rbegin(); iter != symbol_table[i].rend(); iter++) {
			cout << "Ebene: " << i << "\t";
			cout << "Nummer: " << iter->second.getNumber() << "\t";
			cout << "Bez.: " << iter->first << "\t";
			cout << "Typ: " << iter->second.getType() << "\n";
		}
	}
	cout << "End - Print\n";
}
