// Project_3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "AvlTree.h"

int main()
{
	AvlTree* avl = new AvlTree(8);
	avl->Insert(3);
	avl->Insert(10);
	avl->Insert(1);
	avl->Insert(6);
	avl->Insert(14);
	avl->Insert(4);
	avl->Insert(7);
	avl->Insert(7);
	avl->Insert(13);
	avl->Print();
	//8, 3, 10, 1, 6, 14, 4, 7, 13

	std::cout << std::endl << avl->Contains(0) << std::endl << std::endl;

	auto* avl_iterator = avl->create_dft_iterator();
	while (avl_iterator->has_next())
	{
		std::cout << " " << avl_iterator->next();
	}

	std::cout << std::endl << std::endl;

	auto* avl_iterator1 = avl->create_bft_iterator();
	while (avl_iterator1->has_next())
	{
		std::cout << " " << avl_iterator1->next();
	}

	std::cout << std::endl << std::endl;

	auto* avl_iterator2 = avl->create_sft_iterator();
	while (avl_iterator2->has_next())
	{
		std::cout << " " << avl_iterator2->next();
	}

	std::cout << std::endl << std::endl;

	avl->Remove(7);
	avl->Print();

	delete avl;
	system("pause");
}