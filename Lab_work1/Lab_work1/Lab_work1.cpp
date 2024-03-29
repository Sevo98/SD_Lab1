#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
//#include <windows.h>
#include <ctime>
//#include <algorithm>
using namespace std;

//структура массива
struct DinMas
{
	int Length = 0;
	int Capacity = 8;
	int* Arr;
};

//создание массива
void Creating(DinMas *storage)
{
	storage->Arr = new int[storage->Capacity];

	for (int i = 0; i < storage->Capacity / 2; i++)
	{
		storage->Arr[i] = rand() % 999;
		storage->Length++;
	}
}

//Увеличение размера массива
void Increase(DinMas *storage)
{
	int *tempArr;
	storage->Length++;
	tempArr = new int[storage->Length - 1];
	for (int i = 0; i < storage->Length - 1; i++)
	{
		tempArr[i] = storage->Arr[i];
	}
	delete[] storage->Arr;

	storage->Capacity = storage->Capacity + 8;
	storage->Arr = new int[storage->Capacity];
	for (int i = 0; i < storage->Length - 1; i++)
	{
		storage->Arr[i] = tempArr[i];
	}
	delete[] tempArr;
	storage->Length--;
}


//Вывод значений массива
void Output(DinMas* storage)
{
	system("cls");
	cout << "Значение массива:" << endl;
	for (int i = 0; i < storage->Length; i++)
	{
		cout << "\t" << storage->Arr[i] << "\t" << endl;
		cout << endl;
	}
}

/*
//добавление элемента в начало 
void PushFirst(DinMas *storage, const int value)
{
	for (int i = storage->Length; i >= 0; i--)
	{
		if (i != 0)
		{
			storage->Arr[i] = storage->Arr[i - 1];
		}
		else
		{
			storage->Arr[0] = value;
		}
	}
	storage->Length++;
}

//добавление элемента в конец 
void PushBack(DinMas *storage, const int value)
{
	if (storage->Length == storage->Capacity + 2)
	{
		Increase(*&storage);
	}
	storage->Arr[storage->Length++] = value;
}*/


//добавление элемента после определенного значения
void PushAfter(DinMas *storage, int index, const int value)
{
	for (int i = storage->Length; i >= 0; i--)
	{
		if (i != index)
		{
			storage->Arr[i] = storage->Arr[i - 1];
		}
		else {
			storage->Arr[index] = value;
			i = -1;
		}
	}
	storage->Length++;
}


//удаление элемента из массива
void DelElement(DinMas *storage, int index)
{
	for (int i = 0, j = 0; i < storage->Length; i++)
	{
		if (i != index)
		{
			storage->Arr[i - j] = storage->Arr[i];
		}
		else
		{
			storage->Arr[index] = 0;
			j++;
		}
	}
	storage->Length--;
}


//сортировка массива
void Sort(DinMas * storage)
{
	int temp;
	for (int i = 0; i < storage->Length - 1; i++)
	{
		for (int j = 0; j < storage->Length - i - 1; j++) 
		{
			if (storage->Arr[j] > storage->Arr[j + 1]) 
			{
				temp = storage->Arr[j];
				storage->Arr[j] = storage->Arr[j + 1];
				storage->Arr[j + 1] = temp;
			}
		}
	}
/*int temp;
	for (int i = 0; i < storage->Length - 1; i++)
	{
		if (storage->Arr[i] > storage->Arr[i + 1]) 
		{
			temp = storage->Arr[i];
			storage->Arr[i] = storage->Arr[i + 1];
			storage->Arr[i + 1] = temp;
		}
	}*/
}

//линейный поиск
int LinSearch(DinMas *storage, const int requiredKey)
{
	int length = storage->Length;
	int *tempArr = new int[length];
	for (int i = 0; i < storage->Length; i++)
	{
		tempArr[i] = storage->Arr[i];
	}

	for (int i = 0; i < length; i++)
	{
		if (tempArr[i] == requiredKey)
		return i;
	}
	tempArr = nullptr;
	delete[] tempArr;
	return -1;
}


//бинарный поиск
int BinSearch(DinMas *storage, const int index)
{
	bool flag = true;
	int left = 0;
	int right = storage->Length;
	int mid;
	while (left <= right && flag) {
		mid = (left + right) / 2;
		if (storage->Arr[mid] == index) {
			flag = false;
		}
		if (storage->Arr[mid] > index) {
			right = mid - 1;
		}
		else {
			left = mid + 1;
		}
	}
	system("cls");
	if (!flag) {
		return mid;
	}
	else {
		return -1;
	}
	system("pause");
}

//Проверка вводимого значения
void Check(int *number)
{
	int index;
	bool correct = false;
	while (!correct) {
		cin >> index;
		if (cin.fail()) {
			cin.clear();
			while (cin.get() != '\n');
			cout << "Пожалуйста, введите допустимое значение." << endl;
			correct = false;
		}
		else {
			cin.ignore();
			*number = index;
			correct = true;
		}
	}
}


int main()
{
	setlocale(LC_ALL, "ru");
	DinMas storage;
	storage.Arr = new int[storage.Capacity];
	Creating(&storage);
	//проверка размера массива
	if (storage.Length == storage.Capacity - 2)
	{
		Increase(&storage);
	}
	Output(&storage);
	system("pause");
	//меню
	while (true)
	{
		int number = 0;
		cout << "\n            Введите от 0 до 6: \n" << endl;
		cout << "Для вывода массива введите 1\n" << endl;
		cout << "Для добавления элемента в массив введите 2\n" << endl;
		cout << "Для удаление элемента массива введите 3\n" << endl;
		cout << "Для сортировки массива по возрастанию введите 4\n" << endl;
		cout << "Для линейного поиска по элементам в массиве введите 5\n" << endl;
		cout << "Для бинарного поиска элемента в массиве введите 6\n" << endl;
		cout << "Для выхода из программы введите 0\n" << endl;
		
		Check(&number);
		{
			switch (number)
			{
			//вывод массива
			case 1: 
			{
				Output(&storage);
			}
			break;
			//добавление
			case 2: 
			{
				cout << "Для добавления элемента в начало массива введите 1" << endl;
				cout << "Для добавления элемента в конец массива введите 2" << endl;
				cout << "Для добавления элемента после определенного элемента введите 3" << endl;
				int caseNum;
				Check(&caseNum);
				switch (caseNum)
				{
				case 1:
				{
					//функция добавления элемента в начало
					int value;
					cout << "Введите добавляемое значение" << endl;
					
					Check(&value);
					PushAfter(&storage, 0, value);
					//PushFirst(&storage, value);
					Output(&storage);
					break;
				}
				case 2:
				{
					//функция добавления элемента в конец
					if (storage.Length == 0)
					{
						system("cls");
						cout << "Массив пуст! Выберите добавление элемента в начало массива." << endl;
						system("pause");
						break;
					}
					int value;
					cout << "Введите добавляемое значение" << endl;
					Check(&value);
					int index = storage.Length;
					PushAfter(&storage, index, value);
					Output(&storage);
					break;
				}
				case 3:
				{
					//функция добавления элемента после элемента
					int value;
					int index;
					if (storage.Length == 0)
					{
						system("cls");
						cout << "Массив пуст! Выберите добавление элемента в начало массива." << endl;
						system("pause");
						break;
					}
					cout << "Введите добавляемое значение" << endl;
					Check(&value);
					cout << "Введите адрес элемента, после которого необходимо вставить значение" << endl;
					Check(&index);
					while (index > storage.Length || index <= -1)
					{
						cout << "Введите правильный адрес" << endl;
						Check(&index);
					}
					PushAfter(&storage, index, value);
					Output(&storage);
				}
				}
			}
			break;
			//удаление элемента
			case 3:
			{
				cout << "Введите номер удаляемого элемента" << endl;
				int index;
				Check(&index);
				while (index > storage.Length || index <= -1)
				{
					cout << "Введите правильный адрес" << endl;
					Check(&index);
				}
				if (storage.Length == 0)
				{
					system("cls");
					cout << "Массив пуст" << endl;
					system("pause");
					break;
				}
				else 
				{
					DelElement(&storage, index);
					Output(&storage);
					break;
				}
			}
			break;
			//сортировка
			case 4:
			{
				Sort(&storage);
				Output(&storage);
			}
			break;
			//линейный поиск
			case 5:
			{
				system("cls");
				cout << "Введите число, которое необходимо найти" << endl;
				int requiredKey = 0;
				Check(&requiredKey);
				int nElement = 0;
				nElement = LinSearch(&storage, requiredKey);

				if (nElement != -1)
				{
					cout << "Значение " << requiredKey << " находится в ячейке с индексом: " << nElement  << endl;
					cout << endl;
				}
				else cout << "В массиве нет такого значения" << endl;
				system("pause");
				Output(&storage);
			}
			break;
			//бинарный поиск
			case 6:
			{
				int index = 0;
				cout << "Введите число для поиска" << endl;
				//cin >> n;
				Check(&index);
				Sort(&storage);
				Output(&storage);
				int nElement = 0;
				nElement = BinSearch(&storage, index);
				if (nElement != -1)
				{
					cout << "Значение " << index << " находится в ячейке с индексом: " << nElement << endl;
					cout << endl;
				}
				else cout << "В массиве нет такого значения" << endl;
				system("pause");
				Output(&storage);
			}
			break;
			//функция увеличения массива
			case 12:
			{
				Increase(&storage);
				Output(&storage);
			}
			break;
			//выход из программы
			case 0: 
			{
				delete[] storage.Arr;
				return -1;
			}
			break;
			}
		}
	}
}