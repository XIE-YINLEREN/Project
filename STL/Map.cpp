#include "main.h"

void Map_Insert()
{
	map<int, string> People;
	People.insert(pair<int, string>(001, "1"));
	People[003] = "3";
	People.insert(map<int, string>::value_type(002, "2"));

	auto it = People.find(004);
	if (it != People.end())
	{
		People.erase(it);
	}
	
	for (auto it = People.begin(); it != People.end(); it++)
	{
		if (it->second == "2")
		{
			it = People.erase(it);
		}
		cout << it->second << endl;
	}
	cout << "SIZE = " << People.size();
}

