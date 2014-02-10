#include "lex.h"
#include "symbolTable.h"
using namespace std;


void lex()
{
	string str;
	int len, line = 0;
	while (!cin.eof())
	{
		getline(cin, str);
		line++;
		len = str.length();
		for (int i = 0; i < len;)
		{
			if (str[i] == ' ' || str[i] == '\t')	i++;

			else if (i == 0 && str[i] == '#')
			{
				string s;
				while (i != len)
				{
					s += str[i];
					i++;
				}
				
				st.insert(s,"preDir");
				cout << "preDir " << s << endl;
			}

			else if (str[i] == '\"')
			{
				string s = str.substr(i, 1);
				i++;
				bool fileEnd = false;
				while (1)
				{
					while (i == len)
					{
						if (!cin.eof())
						{
							getline(cin, str);
							line++;
							len = str.length();
							i = 0;
						}
						else
						{
							fileEnd = true;
							break;
						}
					}
					if (!fileEnd && (str[i] != '\"' || (i > 0 && str[i - 1] == '\\')))
					{
						if(str[i]!='\t')	s += str[i];
						i++;
					}
					else
					{
						s += str[i];
						i++;
						break;
					}
				}
				st.insert(s, "string");
				cout << "string " << s << endl;
			}

			else if (str[i] == '\'')
			{
				string s = str.substr(i, 1);
				i++;
				bool fileEnd = false;
				while (1)
				{
					while (i == len)
					{
						if (!cin.eof())
						{
							getline(cin, str);
							line++;
							len = str.length();
							i = 0;
						}
						else
						{
							fileEnd = true;
							break;
						}
					}
					if (!fileEnd && (str[i] != '\'' || (i > 0 && str[i - 1] == '\\')))
					{
						if (str[i] != '\t')	s += str[i];
						i++;
					}
					else
					{
						s += str[i];
						i++;
						break;
					}
				}
				st.insert(s, "charLit");
				cout << "charLit " << s << endl;
			}

			else if (i + 1 < len && str[i] == '/' && str[i + 1] == '*')
			{
				string s = str.substr(i, 2);
				i += 2;
				bool fileEnd = false;
				while (1)
				{
					while (i == len)
					{
						if (!cin.eof())
						{
							getline(cin, str);
							line++;
							len = str.length();
							i = 0;
						}
						else
						{
							fileEnd = true;
							break;
						}
					}
					if (!fileEnd && !(i + 1 < len && str[i] == '*' && str[i + 1] == '/'))
					{
						s += str[i];
						i++;
					}
					else
					{
						s += str[i];
						i++;
						if (!fileEnd)
						{
							s += str[i];
							i++;
						}
						break;
					}
				}
				st.insert(s,"blockComment");
				cout << "blockComment " << s << endl;
			}

			else if (i + 1 < len && str[i] == '/' && str[i + 1] == '/')
			{
				string s;
				while (i != len)
				{
					s += str[i];
					i++;
				}
				st.insert(s,"lineComment");
				cout << "lineComment " << s << endl;
			}

			else if (isdigit(str[i]))
			{
				int temp = i;
				while (i < len && isdigit(str[i]))	i++;
				if (i + 1 < len && str[i] == '.' && isdigit(str[i + 1]))
				{
					i++;
					while (i < len && isdigit(str[i]))	i++;
				}
				if (str[i] == 'E' && ((i + 2 < len && (str[i + 1] == '+' || str[i + 1] == '-') && isdigit(str[i + 2])) || (i + 1 < len && isdigit(str[i + 1]))))
				{
					i++;
					if (str[i] == '+' || str[i] == '-')	i++;
					while (i < len && isdigit(str[i]))	i++;
				}
				bool illegal = false;
				while (isalnum(str[i]))
				{
					illegal = true;
					i++;
				}
				if (!illegal)
				{
					st.insert(str.substr(temp, i - temp), "number");
					cout << "number " << str.substr(temp, i - temp) << endl;
				}
				else cout << "Illegal identifier <" << str.substr(temp, i - temp) << "> at line no. " << line << endl;
				
			}

			else if (isalpha(str[i]))
			{
				int temp = i;
				while (i < len && isalnum(str[i]))	i++;
				string s = str.substr(temp, i - temp);
				if (keyMap.find(s) != keyMap.end())
				{
					st.insert(s, keyMap[s]);
					cout << keyMap[s] << " " << s << endl;
				}
				else
				{
					st.insert(s, "id");
					cout << "id " << s << endl;
				}
			}

			else if (keyMap.find(str.substr(i, 1)) != keyMap.end())
			{
				string s = str.substr(i, 1);
				i++;
				while (i < len && keyMap.find(s + str[i]) != keyMap.end())
				{
					s += str[i];
					i++;
				}
				st.insert(s, keyMap[s]);
				cout << keyMap[s] << " " << s << endl;
			}

			else
			{
				cout << "Illegal character <" << str[i] << "> at line no. " << line << endl;
				i++;
			}
		}
	}
}