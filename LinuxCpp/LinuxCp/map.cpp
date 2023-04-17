#pragma once 
#include <iostream> 
#include <vector>
#include <list>
#include <deque>
#include <map>
using namespace std;

int main()
{
	map<int, string> MPA;
	MPA.insert(pair<int, string>(10, "danny"));
	MPA.insert(pair<int, string>(2, "wang"));
	MPA.insert(pair<int, string>(3, "li"));
	MPA.insert(pair<int, string>(4, "zhang"));
	MPA.insert(make_pair<int, string>(4, "zhang"));//¡Ÿ ±
	map<int, string>::const_iterator X = MPA.find(2);


	for (; X != MPA.end(); X++)
	{
		cout << X->first << X->second << endl;
	}
	return 0;
}