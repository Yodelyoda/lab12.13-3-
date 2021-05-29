#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <Windows.h> 
using namespace std;

#pragma once


class HashClass {

public:
	HashClass();
	int HashFunc(string key);
	void AddItems(string name, string surname, string zod, string dd, string mm, string yy);
	int NumItemsInIndex(int index);
	void PrintTable();
	void PrintIndex(int index);
	void RemoveValue(string name);
private:

	static const int tableSize_ = 40;

	struct zodiac {
		string name;
		string surname;
		string zod;
		string dd;
		string mm;
		string yy;
		zodiac* next;
	};
	zodiac* HashTable[tableSize_];



};
HashClass::HashClass()
{
	for (int i = 0; i < tableSize_; i++)
	{
		HashTable[i] = new zodiac;
		HashTable[i]->name = "";
		HashTable[i]->surname = "";
		HashTable[i]->zod = "";
		HashTable[i]->dd = "";
		HashTable[i]->mm = "";
		HashTable[i]->yy = "";
		HashTable[i]->next = nullptr;
	}
}

int HashClass::HashFunc(string key)
{

	return stoi(key);

}

void HashClass::AddItems(string name, string surname, string zod, string dd, string mm, string yy)
{
	int index = HashFunc(mm);
	int numItems = NumItemsInIndex(index);
	zodiac* iter = HashTable[index];
	if (numItems == 0)
	{
		HashTable[index]->name = name;
		HashTable[index]->surname = surname;
		HashTable[index]->zod = zod;
		HashTable[index]->dd = dd;
		HashTable[index]->mm = mm;
		HashTable[index]->yy = yy;
	}
	else
	{
		zodiac* ptr = HashTable[index];
		zodiac* newPtr = new zodiac;
		newPtr->name = name;
		newPtr->surname = surname;
		newPtr->zod = zod;
		newPtr->dd = dd;
		newPtr->mm = mm;
		newPtr->yy = yy;
		newPtr->next = NULL;
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		ptr->next = newPtr;
	}
}
int HashClass::NumItemsInIndex(int index)
{
	int numItems = 0;
	zodiac* iter = HashTable[index];

	if (iter->name == "")
	{
		return numItems;
	}
	else
	{
		while (iter != NULL)
		{
			iter = iter->next;
			numItems++;
		}
	}

	return numItems;
}
void HashClass::PrintTable()
{
	int numItems = 0;

	for (int i = 0; i < tableSize_; i++)
	{
		if (HashTable[i]->mm != "")
		{
			numItems = NumItemsInIndex(i);
			if (numItems == 1)
			{
			
				cout << "Ім'я: " << HashTable[i]->name << " ";
				cout << "Прізвище: " << HashTable[i]->surname << " ";
				cout << "Знак Зодіаку: " << HashTable[i]->zod << " ";
				cout << "День народження: " << HashTable[i]->dd << " ";
				cout << "Місяць народження: " << HashTable[i]->mm << " ";
				cout << "Рік народження: " << HashTable[i]->yy << endl;
			}
			else
			{
				PrintIndex(i);
			}

		}

	}
}

void HashClass::PrintIndex(int index)
{
	int numItems = NumItemsInIndex(index);
	zodiac* iter = HashTable[index];
	for (int i = 0; i < numItems; i++)
	{
		cout << "Ім'я: " << iter->name << " ";
		cout << "Прізвище: " << iter->surname << " ";
		cout << "Знак Зодіаку: " << iter->zod << " ";
		cout << "День народження: " << iter->dd << " ";
		cout << "Місяць народження: " << iter->mm << " ";
		cout << "Рік народження: " << iter->yy << endl;

		iter = iter->next;
	}



}
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	HashClass testObj;
	string name;
	string surname;
	string zod;
	string dd;
	string mm;
	string yy;


	ifstream myFile("zodiac.txt");
	if (myFile.is_open())
	{
		while (myFile >> name >> surname >> zod >> dd >> mm >> yy)
		{
			testObj.AddItems(name, surname, zod, dd, mm, yy);
		}
		myFile.close();
	}
	else
	{
		cout << "Помилка відкриття файлу" << endl;
		system("pause");
		return 0;
	}
	testObj.PrintTable();
	string search;
	cout << "Ведіть місяць народження людини дані якої ви прагнете знайти :";
	cin >> search;
	int searchIndex = testObj.HashFunc(search);
	if (searchIndex != 0 && searchIndex<13)
	{
		testObj.PrintIndex(searchIndex);
	}
	else
	{
		cout << "  Шукану людину не знайдено. Ви ввели помилкове значення. Шукану людину не знайдено " << endl;
	}

	system("pause");

	return 0;
}