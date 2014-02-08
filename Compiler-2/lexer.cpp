#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>
#include <string>
#include <cctype>
using namespace std;

const int MAX = 1005;

int main()
{
	map<string,string> keyMap;
	string key,val;
	fstream fin;
	fin.open("keywords",ios::in);
	

	while(!fin.eof())
	{
		fin >> key >> val;
		keyMap[key] = val;
	}

	/*for(map<string,string>::iterator it=keyMap.begin();it!=keyMap.end();it++)
	{
		cout << it->first << " " << it->second << endl;
	}

	cout << keyMap.size() << endl;*/

	fin.close();
	
	string str;
	int len,line=0;

	while(!cin.eof())
	{
		getline(cin,str);
		//cout << str << endl;
		len = str.length();
		for(int i=0;i<len;)
		{
			if(str[i]==' ' || str[i]=='\t')	i++;

			else if(isdigit(str[i]))
			{
				int temp = i;
				while(isdigit(str[i]))	i++;
				if(str[i]=='.' && isdigit(str[i+1]))
				{
					i++;
					while(isdigit(str[i]))	i++;
				}
				if(str[i]=='E' && ( ((str[i+1]=='+' || str[i+1]=='-') && isdigit(str[i+2])) || isdigit(str[i+1]) ))
				{
					i++;
					if(str[i]=='+' || str[i]=='-')	i++;
					while(isdigit(str[i]))	i++;
				}
				cout << "Number " << str.substr(temp,i-temp) << endl;
			}
			
			else if(isalpha(str[i]))
			{
				int temp = i;
				while(isalnum(str[i]))	i++;
				string s = str.substr(temp,i-temp);
				if(keyMap.find(s) != keyMap.end())
				{
					cout << keyMap[s] << " " << s << endl;
				}
				else
				{
					cout << "Identifier " << s << endl;
				}	
			}

			else if(keyMap.find(str.substr(i,1)) != keyMap.end())
			{
				string s = str.substr(i,1);
				i++;
				while(keyMap.find(s+str[i]) != keyMap.end())
				{
					s += str[i];
					i++;
				}
				cout << keyMap[s] << " " << s << endl;
			}

			else
			{
				cout << "Illegal character " << str[i] << endl;
 				i++;
			}
		}
	}

	return 0;
}