// Project_3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "AvlTree.h"

int main()
{
	AvlTree* avl = new AvlTree(13);
	avl->root = avl->root->Insert(9);
	avl->root = avl->root->Insert(5);
	avl->root = avl->root->Insert(6);
	avl->root = avl->root->Insert(2);
	avl->root = avl->root->Insert(8);
	avl->root = avl->root->Insert(1);
	avl->root->Balance();
	avl->root->Print(0);
	system("pause");
}