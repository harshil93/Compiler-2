#include "iostream"
#include "map"
#include "string"
using namespace std;

/*struct entr{
	string tokenClass;
	string lexeme;
	/*entr(string token, string lexemeName)
	{
		tokenClass = token;
		lexeme = lexemeName;
	}

};*/

class SymbolTable
{
public:
	SymbolTable();
	~SymbolTable();
	int insert(string key, string value);
	void printSymbolTable();

private:
	map<string, string> table;
};

extern SymbolTable st;