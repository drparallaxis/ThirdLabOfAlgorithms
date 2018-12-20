#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <random>
#include <ctime>
#include <unordered_map>
#include <map>
#include <string>
#include "NestOfClasses.h"
using namespace std;
using ttree::BST;
using ttree::Tree;

struct CounterOfLetters
{
	int key, keyForHash;
	char letter;
	CounterOfLetters()
	{
		key = 1, keyForHash = 0;
	    letter = ' ';
	}
};

void InitTable(CounterOfLetters *table, int size)
{
	for (int i = 0; i < size; i++)
		table[i].keyForHash = -999;
}
void insert(CounterOfLetters *table, int size, int no)
{
	bool inserted = false;
	int k = no % size;

	while (!inserted)
	{
		if (table[k].keyForHash == -999)
		{
			table[k].keyForHash = no;
			inserted = true;
		}
		else {
			k++;
			k %= size;
		}
	}
}
void printTable(CounterOfLetters *table, int size)
{
	for (int i = 0; i < size; i++)
		if (!(table[i].keyForHash == -999))
			cout << "Hash: " << table[i].keyForHash << "\tletter: " << table[i].letter << "\tNumber of entries: " << table[i].key << endl;
}
void SearchForHashTable(CounterOfLetters *table, int size, char ltr)
{
	for (int i = 0; i < size; i++)
	{
		if (table[i].letter == ltr)
		{
			cout << "\nHash: " << table[i].keyForHash << "\tletter: " << table[i].letter << "\tNumber of entries: " << table[i].key << endl;
			return;
		}
	}
}


void ForBalanceTree(CounterOfLetters *C2, int iter)
{
	//Ѕалансировка дерева
	map<char, int> Balance;

	for (int i = 0; i < iter; i++)
		Balance.insert(pair<char, int>(C2[i].letter, i));
	cout << endl << "Balanced BST: ";
	for (auto it = Balance.begin(); it != Balance.end(); ++it)
		cout << (*it).first << "  ";
}
void ForHashTable(CounterOfLetters *C1, int strSize)
{
	cout << "\n\n\n";
	unsigned int start_time = 0, end_time = 0;
	InitTable(C1, strSize);

	int no = 0;

	for (int i = 0; i < strSize; i++)
	{
		no = rand();
		insert(C1, strSize, no);
	}
	printTable(C1, strSize);
	cout << "\nSearh letter in Hash-table\nInput letter for search: ";
	char ltr = ' ';
	cin >> ltr;
	start_time = clock();
	SearchForHashTable(C1, strSize, ltr);
	end_time = clock();
	cout << "\nTime of search: " << end_time - start_time << " milliseconds\n";
}

void Color(CounterOfLetters *C1, int strSize)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	cout << "\nBacklight of repeating letters of BST: ";
	for (int i = 0; i < strSize; i++)
	{
		if (C1[i].key >= 2)
		{
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 4));  //4 - red
			cout << C1[i].letter << "  ";
		}
		else
		{
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15)); //15 - white
			cout << C1[i].letter << "  ";
		}
	}
	cout << endl;
}

int main()
{
	srand(time(NULL));
	unsigned int start_time = 0, end_time = 0;
	
	Tree Object;           
	string arr = " ";
	arr = "abcfgdeaff"; 
	//cout << "input string: " << endl;  
	//getline(cin, arr);
	int strSize = arr.size();
	//arr.erase(arr.find(' '), 1);

	//strSize = arr.size();
	Object.SetSize(strSize);
	system("cls");
	cout << "Your string: " << arr << endl;

	for (int i = 0; i<strSize; i++)
		Object.insert_node((char)arr[i]); 

	char* buffer = new char[strSize];
	for (int i = 0; i < strSize; i++)
		buffer[i] = (char)arr[i];

	cout << endl << "BST: ";              
	Object.inorder_walk(Object.get_root()); cout << endl;

	Object.InitList(buffer);

	CounterOfLetters* C1 = new CounterOfLetters[strSize];

	for (int i = 0; i < strSize; i++)
		C1[i].letter = buffer[i];

	for (int i = 0; i < strSize; i++)
		for (int j = 0; j < strSize; j++)
			if (j != i)
				if (C1[i].letter == C1[j].letter)
					C1[i].key++;

	int iter = 0; 
	for (int i = 0; i < strSize; i++)
		if (C1[i].key < 2)
			iter++;

	Color(C1, strSize);

	CounterOfLetters* C2 = new CounterOfLetters[iter];
	int bufferCounter = 0;


	//”даление повтор€ющихс€ букв
	for (int i = 0; i < strSize; i++)
		if (C1[i].key < 2)
			C2[bufferCounter++].letter = C1[i].letter;
	for (int i = 0; i < strSize; i++)
		if (C1[i].key >= 2)
			Object.delete_node(Object.find_node(Object.get_root(), C1[i].letter));

	cout << endl << "After erase repeated letters of BST: ";
	Object.inorder_walk(Object.get_root()); cout << endl;

	cout << "\nSearch node of BST\n";
	cout << "Input letter for search node of BST: ";
	char l = ' ';
	cin >> l;
	start_time = clock();
	Object.find_node(Object.get_root(), l);
	end_time = clock();
	cout << "Your letter was searched!\nTime of search: " << end_time - start_time << endl;
	
	ForBalanceTree(C2, iter); //Ѕалансировка дерева
	ForHashTable(C1, strSize); //’эш-таблица


	cin.get();
	_getch();
}






//Object.delete_node(Object.find_node(Object.get_root(), (char)a));    


//void InitTable(int *table, int size)
//{
//	for (int i = 0; i < size; i++)
//		table[i] = -999;
//}
//void insert(int *table, int size, int no)
//{
//	bool inserted = false;
//	int k = no % size;
//
//	while (!inserted)
//	{
//		if (table[k] == -999)
//		{
//			table[k] = no;
//			inserted = true;
//		}
//		else
//		{
//			k++;
//			k %= size;
//		}
//	}
//}
//void printTable(int *table, int size)
//{
//	for (int i = 0; i < size; i++)
//	{
//		if (!(table[i] == -999))
//		{
//			//cout << "Table [" << i << "]\t---\n";
//			cout << "Table [" << i << "]\t" << table[i] << "\t" << table[i] % size << endl;
//		}
//		/*else
//		{
//		cout << "Table [" << i << "]\t" << table[i] << "\t" << table[i] % size << endl;
//		}*/
//	}
//}

//int N = 11, K = 8;
//int *table = new int[N];
//InitTable(table, N);
//
//int no = 0;
//
//for (int i = 0; i < K; i++)
//{
//	no = rand();
//	insert(table, N, no);
//}
//printTable(table, N);




//BST* Tree::find_max(BST *CurrentNode)
//{
//	while (CurrentNode->right != 0)                           /* здесь все очевидно - самыое максимальное значение у самого правого */
//		CurrentNode = CurrentNode->right;
//	return CurrentNode;
//}
//
//BST* Tree::find_min(BST* CurrentNode)
//{
//	while (CurrentNode->left != 0)
//		CurrentNode = CurrentNode->left;
//	return CurrentNode;
//}