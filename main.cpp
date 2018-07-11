#include <iostream>
#include <fstream>
#include "MyList.h"
#include <set>
#include <algorithm>

using namespace std;


template<class T>
void show(const List<T>& ml);

void fill(List<Student>& ml, string path);


int main()
{
	setlocale(LC_ALL, "rus");
	List<Student> list;

	fill(list, "students.txt");

	show(list);

	try
	{
		cout << "------------------------\n";
		Student a{ "Boy", "M", 2005 };
		list.removeAt(7);
		list.insertAt(a, 7);
		show(list);



		list.pop_back();
		list.pop_front();
		cout << list.front() << endl;
		cout << list.back() << endl;
		
		cout << "size: " << list.size() << endl;
	}
	catch (const std::exception& ex) { cout << ex.what() << endl; }




	return 0;
}




template<class T>
void show(const List<T>& ml)
{
	for (int i = 0; i < ml.size(); i++)
		cout << setw(5) << i + 1 << ml[i] << endl;
}

void fill(List<Student>& ml, string path)
{
	Student temp;
	ifstream fcin;
	fcin.open(path);
	while (!fcin.eof())
	{
		fcin >> temp.name >> temp.group >> temp.year;
		ml.push_back(temp);
	}
}

/***
Node
List()
~List()
get_size
empty
front / front const
back  / back const
push_back
push_front
pop_back
pop_front
clear
insert
removeAt
operator[] / operator[] const






*/