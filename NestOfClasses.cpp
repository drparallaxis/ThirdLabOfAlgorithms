#include "NestOfClasses.h"

namespace ttree
{
	BST::BST(char value) {
		data = value;
		parent = left = right = 0;
	}
	char BST::get_data() { return data; }

	Tree::Tree() { 
		root = 0;
		counter = 0;
		size = 0;
	}

	int Tree::insert_node(char value)
	{
		BST* n = new BST(value);              
		BST* ptr;
		BST* ptr1 = NULL;

		n->parent = n->left = n->right = 0;  
		ptr = root;
		while (ptr != 0)                      
		{
			ptr1 = ptr;                      
			if (value < ptr->get_data())                             
				ptr = ptr->left;
			else
				ptr = ptr->right;            
		}
		n->parent = ptr1;
		if (ptr1 == 0)                       
			root = n;
		else
		{
			if (value < ptr1->get_data())
				ptr1->left = n;
			else
				ptr1->right = n;
		}
		return 0;
	}

	BST* Tree::delete_node(BST *CurrentNode)
	{
		BST *FirstTemp, *SecondTemp;
		if (CurrentNode->left == 0 || CurrentNode->right == 0)    
			FirstTemp = CurrentNode;
		else
			FirstTemp = find_succsessor(CurrentNode->get_data());
		if (FirstTemp->left != 0)                               
			SecondTemp = FirstTemp->left;
		else
			SecondTemp = FirstTemp->right;
		if (SecondTemp != 0)                                      
			SecondTemp->parent = FirstTemp->parent;
		if (FirstTemp->parent == 0)
			root = SecondTemp;
		else
		{
			if (FirstTemp == (FirstTemp->parent)->left)
				(FirstTemp->parent)->left = SecondTemp;
			else
				(FirstTemp->parent)->right = SecondTemp;
		}
		if (FirstTemp != CurrentNode)                             
			CurrentNode->data = FirstTemp->get_data();
		return FirstTemp;
	}

	void Tree::inorder_walk(BST *CurrentNode)
	{
		if (CurrentNode != 0)
		{
			inorder_walk(CurrentNode->left);
			std::cout << CurrentNode->get_data() << "  ";
			charArray[counter++] = CurrentNode->get_data();
			inorder_walk(CurrentNode->right);
		}
	}

	void Tree::SetSize(int s) 
	{ 
		size = s; 
		charArray = new char[s];
	}

	void Tree::InitList(char* &a)
	{
		for (int i = 0; i < size; i++)
			a[i] = charArray[i];
	}

	BST* Tree::find_max(BST *CurrentNode)
	{
		while (CurrentNode->right != 0)                          
			CurrentNode = CurrentNode->right;
		return CurrentNode;
	}

	BST* Tree::find_min(BST* CurrentNode)
	{
		while (CurrentNode->left != 0)
			CurrentNode = CurrentNode->left;
		return CurrentNode;
	}

	BST* Tree::find_node(BST *CurrentNode, char value)
	{
		if (CurrentNode == 0 || value == CurrentNode->get_data())
			return CurrentNode;
		if (value > CurrentNode->get_data())
			return find_node(CurrentNode->right, value);
		else
			return find_node(CurrentNode->left, value);
	}

	BST* Tree::find_succsessor(char value)
	{
		BST *FirstTemp = find_node(root, value);                  
		BST *SecondTemp;
		if (FirstTemp == 0)
			return 0;
		if (FirstTemp->right != 0)                               
			return find_min(FirstTemp->right);
		SecondTemp = FirstTemp->parent;
		while (SecondTemp != 0 && FirstTemp == SecondTemp->right)  
		{
			FirstTemp = SecondTemp;
			SecondTemp = SecondTemp->parent;
		}
		return SecondTemp;
	}

	BST* Tree::get_root() { return root; }
}




