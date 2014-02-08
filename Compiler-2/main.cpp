
#include <iostream>
#include <map>
#include "regex.h"
using namespace std;

struct entry{
	int type;
	string val;
	
};

class SymbolTable
{
public:
	SymbolTable();
	~SymbolTable();
	int insert(string key, entry value);
	bool lookup(string key,entry &val);

private:
	map<string, entry> table;
};

SymbolTable::SymbolTable()
{
}

SymbolTable::~SymbolTable()
{
}

int SymbolTable::insert(string key,entry value){
	if (table.find(key) != table.end()){
		return 0;
	}
	else{
		table[key] = value;
		return 1;
	}
}

bool SymbolTable::lookup(string key, entry &val){
	if (table.find(key) != table.end()){
		val = table[key];
		return true;
	}
	else{
		return false;
	}
}

  
int main(int argc, char** argv){
	
	char string[100], re[100];
	while (1){
		cin >> string >> re;
		cout << re2post(re) << endl;
		cout << regMatch(string, re) << endl;;
	}
	return 0;
}