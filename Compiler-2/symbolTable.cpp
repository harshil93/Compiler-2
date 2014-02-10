#include "symbolTable.h"

SymbolTable::SymbolTable()
{
}

SymbolTable::~SymbolTable()
{
}

int SymbolTable::insert(string key, string value){
	if (table.find(key) != table.end()){
		return 0;
	}
	else{
		table[key] = value;
		return 1;
	}
}


void SymbolTable::printSymbolTable()
{
	for (auto it = table.begin(); it != table.end(); it++)
	{
		cout << it->first << "\t" << it->second << endl;
	}
}
