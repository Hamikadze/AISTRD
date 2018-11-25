#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Project_3/AvlTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest_For_Project_3
{
	TEST_CLASS(UnitTest1)
	{
	public:
		/*node(int k);
		int key;
		node* left;
		node* right;
		node* insert(int key);
		node* remove(int key);
		void Delete();
		bool contains(int key);
		void print(string indent, bool last, bool right) const;*/
		/*void Insert(int key);
		void Remove(int key);
		bool Contains(int key) const;
		void Print() const;*/

		TEST_METHOD(node_initialize_non_empty)
		{
			auto* node = new AvlTree::node(0);
			Assert::IsTrue(node != nullptr&& node->key == 0);
		}
		TEST_METHOD(node_non_empty_insert)
		{
			auto* node = new AvlTree::node(5);
			node = node->insert(0);
			node = node->insert(10);
			Assert::IsTrue(node != nullptr && node->key == 5 && node->right != nullptr && node->right->key == 10 && node->left != nullptr && node->left->key == 0);
		}
		TEST_METHOD(node_non_empty_remove)
		{
			auto* node = new AvlTree::node(0);
			node = node->remove(0);
			Assert::IsNull(node);
		}
		TEST_METHOD(node_empty_remove)
		{
			auto* node = new AvlTree::node(0);
			node = node->remove(0);
			node = node->remove(0);
			Assert::IsNull(node);
		}
		TEST_METHOD(node_non_empty_Delete)
		{
			auto* node = new AvlTree::node(0);
			node = node->Delete();
			Assert::IsNull(node);
		}
		TEST_METHOD(node_empty_Delete)
		{
			auto* node = new AvlTree::node(0);
			node = node->remove(0);
			node = node->Delete();
			Assert::IsNull(node);
		}

		TEST_METHOD(node_empty_contains)
		{
			auto* node = new AvlTree::node(0);
			node = node->remove(0);
			Assert::IsFalse(node->contains(0));
		}

		TEST_METHOD(node_non_empty_contains_true)
		{
			auto* node = new AvlTree::node(5);
			node = node->insert(0);
			node = node->insert(10);
			Assert::IsTrue(node->contains(10));
		}

		TEST_METHOD(node_non_empty_contains_false)
		{
			auto* node = new AvlTree::node(5);
			node = node->insert(0);
			node = node->insert(10);
			Assert::IsFalse(node->contains(1));
		}

		TEST_METHOD(tree_initialize_empty)
		{
			AvlTree* avl = new AvlTree();
			Assert::IsTrue(avl != nullptr && avl->root == nullptr);
		}

		TEST_METHOD(tree_initialize_non_empty)
		{
			AvlTree* avl = new AvlTree(0);
			Assert::IsTrue(avl != nullptr&& avl->root != nullptr && avl->root->key == 0);
		}

		TEST_METHOD(tree_insert_non_empty)
		{
			AvlTree* avl = new AvlTree(5);
			avl->Insert(10);
			avl->Insert(0);
			Assert::IsTrue(avl->root != nullptr && avl->root->key == 5 && avl->root->right != nullptr && avl->root->right->key == 10 && avl->root->left != nullptr && avl->root->left->key == 0);
		}

		TEST_METHOD(tree_insert_empty)
		{
			AvlTree* avl = new AvlTree(5);
			avl->root = avl->root->Delete();
			avl->Insert(5);
			avl->Insert(10);
			avl->Insert(0);
			Assert::IsTrue(avl->root != nullptr && avl->root->key == 5 && avl->root->right != nullptr && avl->root->right->key == 10 && avl->root->left != nullptr && avl->root->left->key == 0);
		}

		TEST_METHOD(tree_stf_iterator)
		{
			AvlTree* avl = new AvlTree(5);
			avl->Insert(10);
			avl->Insert(0);
			auto* iterator = avl->create_sft_iterator();
			Assert::IsTrue(iterator->has_next() && iterator->next() == 0 && iterator->next() == 5 && iterator->next() == 10 && !iterator->has_next());
		}

		TEST_METHOD(tree_btf_iterator)
		{
			AvlTree* avl = new AvlTree(5);
			avl->Insert(10);
			avl->Insert(0);
			auto* iterator = avl->create_bft_iterator();
			Assert::IsTrue(iterator->has_next() && iterator->next() == 5 && iterator->next() == 0 && iterator->next() == 10 && !iterator->has_next());
		}

		TEST_METHOD(tree_dtf_iterator)
		{
			AvlTree* avl = new AvlTree(5);
			avl->Insert(10);
			avl->Insert(0);
			auto* iterator = avl->create_dft_iterator();
			Assert::IsTrue(iterator->has_next() && iterator->next() == 5 && iterator->next() == 0 && iterator->next() == 10 && !iterator->has_next());
		}

		TEST_METHOD(tree_empty_stf_iterator)
		{
			try {
				AvlTree* avl = new AvlTree();
				auto* iterator = avl->create_sft_iterator();
			}
			catch (std::exception error)
			{
				Assert::IsTrue(error.what() == "Tree does not exist");
			}
		}

		TEST_METHOD(tree_empty_btf_iterator)
		{
			try {
				AvlTree* avl = new AvlTree();
				auto* iterator = avl->create_bft_iterator();
			}
			catch (std::exception error)
			{
				Assert::IsTrue(error.what() == "Tree does not exist");
			}
		}

		TEST_METHOD(tree_empty_dtf_iterator)
		{
			try {
				AvlTree* avl = new AvlTree();
				auto* iterator = avl->create_dft_iterator();
			}
			catch (std::exception error)
			{
				Assert::IsTrue(error.what() == "Tree does not exist");
			}
		}

		TEST_METHOD(tree_remove_root_non_empty)
		{
			AvlTree* avl = new AvlTree(0);
			avl->Insert(1);
			avl->Insert(2);
			avl->Insert(3);
			avl->Insert(4);
			avl->Insert(5);
			avl->Remove(avl->root->key);
			auto* iterator = avl->create_sft_iterator();
			Assert::IsTrue(avl->root != nullptr &&
				iterator->next() == 0 &&
				iterator->next() == 1 &&
				iterator->next() == 2 &&
				iterator->next() == 4 &&
				iterator->next() == 5);
		}

		TEST_METHOD(tree_remove_leaf_non_empty)
		{
			AvlTree* avl = new AvlTree(0);
			avl->Insert(1);
			avl->Insert(2);
			avl->Insert(3);
			avl->Insert(4);
			avl->Insert(5);
			avl->Remove(4);
			auto* iterator = avl->create_sft_iterator();
			Assert::IsTrue(iterator->next() == 0 &&
				iterator->next() == 1 &&
				iterator->next() == 2 &&
				iterator->next() == 3 &&
				iterator->next() == 5);
		}

		TEST_METHOD(tree_remove_non_exist_non_empty)
		{
			AvlTree* avl = new AvlTree(0);
			avl->Insert(1);
			avl->Insert(2);
			avl->Insert(3);
			avl->Insert(4);
			avl->Insert(5);
			avl->Remove(10);
			auto* iterator = avl->create_sft_iterator();
			Assert::IsTrue(avl->root != nullptr &&
				iterator->next() == 0 &&
				iterator->next() == 1 &&
				iterator->next() == 2 &&
				iterator->next() == 3 &&
				iterator->next() == 4 &&
				iterator->next() == 5);
		}
		TEST_METHOD(tree_contains_non_exist_non_empty)
		{
			AvlTree* avl = new AvlTree(0);
			avl->Insert(1);
			avl->Insert(2);
			avl->Insert(3);
			avl->Insert(4);
			avl->Insert(5);
			Assert::IsFalse(avl->Contains(10));
		}
		TEST_METHOD(tree_contains_exist_non_empty)
		{
			AvlTree* avl = new AvlTree(0);
			avl->Insert(1);
			avl->Insert(2);
			avl->Insert(3);
			avl->Insert(4);
			avl->Insert(5);
			Assert::IsTrue(avl->Contains(5));
		}
	};
}