#ifndef _NestOfClasses_H
#define _NestOfClasses_H
#pragma once
#include <iostream>

namespace ttree
{
	class BST
	{
		BST* left;
		BST* right;
		BST* parent;
		char data;
		friend class Tree;
	public:
		BST(char value);
		char get_data();	
	};

	class Tree
	{
		BST* root;
		int counter;
		char* charArray;
		int size;
	public:
		Tree();
		int insert_node(char value);
		BST* delete_node(BST *CurrentNode);
		void inorder_walk(BST *CurrentNode);
		BST* find_max(BST *CurrentNode);
		BST* find_min(BST *CurrentNode);
		BST* find_node(BST *CurrentNode, char value);
		BST* find_succsessor(char value);
		BST *get_root();
		void SetSize(int s);
		void InitList(char* &a);
	};
}

#endif

/* �������� ��� ������ - ���� � z ��� �����, �� �������� 0 � ��������������� ����
* �������� z, ���� � z ���� ���� �������, �� ����� �������� z, �������� ��� �������� �������� �
* ��� ��������. ���� �� ����� ����, �� ��������� ��������� �������������: �� ������� ���������
* (� ������ ������� �� ������) �� z ������� y; � ���� ��� ������ ������� (������). ������ �����
* ����������� ���� � �������������� ������ �� ������� y � ������� z, � ���� ������� y �������
* ��������� ���� �������� */


/*
CMyClass.h

#ifndef CMYCLASS_H
#define CMYCLASS_H
class CMyClass
#endif
CMyClass.cpp

#include "cmyclass.h"

CMyClass MyClass;
void CMyClass::
��� �� � ������ ������

#include "cmyclass.h"

extern CMyClass MyClass;
*/