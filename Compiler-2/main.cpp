#include "lex.h"
#include "symbolTable.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>
#include <string>
#include <cctype>
#include <conio.h>
map<string, string> keyMap;
SymbolTable st;

void genTokenMap()
{
	string key, val;
	fstream fin;
	fin.open("keywords.txt", ios::in);

	while (!fin.eof())
	{
		fin >> key >> val;
		keyMap[key] = val;
	}

	fin.close();

	/*for (auto it = keyMap.begin(); it != keyMap.end(); it++)
	{
		cout << it->first << "\t" << it->second << endl;
	}*/
}
int main()
{
	
	genTokenMap();
	lex();
	cout << "---------------------------------------\n\n SYMBOL TABLE\n\n";
	st.printSymbolTable();
	_getch();
	return 0;
}