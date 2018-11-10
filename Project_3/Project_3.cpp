// Project_3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "AvlTree.h"

int main()
{
	AvlTree* avl = new AvlTree(0);
	avl->root = avl->root->Insert(9);
	avl->root = avl->root->Insert(5);
	avl->root = avl->root->Insert(6);
	avl->root = avl->root->Insert(2);
	avl->root = avl->root->Insert(8);
	avl->root = avl->root->Insert(1);
	avl->root = avl->root->Insert(10);
	avl->root = avl->root->Insert(31);
	avl->root = avl->root->Insert(41);
	avl->root = avl->root->Insert(15);
	avl->root = avl->root->Insert(16);
	avl->root = avl->root->Insert(111);
	avl->root = avl->root->Insert(12);
	avl->root = avl->root->Insert(11);
	avl->root = avl->root->Insert(7);
	avl->root->Balance();
	avl->root->Print(0);
	std::cout << avl->root->Contains(0) << std::endl;
	system("pause");
}