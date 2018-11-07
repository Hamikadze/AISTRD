#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Project2/LinkedList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest_For_Project_2
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(LinkedList_isEmpty_true)
		{
			LinkedList list;
			Assert::IsTrue(list.isEmpty());
		}

		TEST_METHOD(get_size_true_1)
		{
			LinkedList list;
			Assert::IsTrue(list.get_size() == 0);
		}

		TEST_METHOD(get_size_true_2)
		{
			LinkedList list;
			list.push_back(1);
			list.push_back(2);
			list.push_back(3);
			list.push_back(4);
			Assert::IsTrue(list.get_size() == 4);
		}

		TEST_METHOD(at)
		{
			LinkedList list;
			list.push_back(1);
			list.push_back(2);
			list.push_back(3);
			list.push_back(4);

			Assert::IsTrue(list.at(0) == 1 && list.at(1) == 2 && list.at(2) == 3 && list.at(3) == 4);
		}

		TEST_METHOD(at_empty)
		{
			try {
				LinkedList list;

				Assert::IsTrue(list.at(0) == 1);
			}
			catch (std::out_of_range o_ex)
			{
				Assert::AreEqual(o_ex.what(), "Index is greater than list size");
			}
		}
		//push back

		TEST_METHOD(LinkedList_isEmpty_false)
		{
			LinkedList list;
			list.push_front(0);
			Assert::IsFalse(list.isEmpty());
		}

		TEST_METHOD(push_back_is_valid_1)
		{
			LinkedList list;
			list.push_back(1);
			Assert::IsTrue(list.at(0) == 1 && list.get_size() == 1); // 1 2 3 4
		}

		TEST_METHOD(push_back_is_valid_2)
		{
			LinkedList list;
			list.push_front(2);
			list.push_front(1);
			list.push_back(3);
			list.push_back(4);
			Assert::IsTrue(list.at(3) == 4); // 1 2 3 4
		}

		TEST_METHOD(push_front_is_valid_1)
		{
			LinkedList list;
			list.push_front(2);
			list.push_front(1);
			list.push_back(3);
			list.push_back(4);
			Assert::IsTrue(list.at(0) == 1); // 1 2 3 4
		}

		TEST_METHOD(push_front_is_valid_2)
		{
			LinkedList list;
			list.push_front(1);

			Assert::IsTrue(list.at(0) == 1 && list.get_size() == 1);
		}

		TEST_METHOD(equals_true)
		{
			LinkedList list1;
			list1.push_back(1);
			list1.push_back(2);
			list1.push_back(3);
			list1.push_back(4);

			LinkedList list2;
			list2.push_back(1);
			list2.push_back(2);
			list2.push_back(3);
			list2.push_back(4);

			Assert::IsTrue(list1.equals(&list2));
		}

		TEST_METHOD(equals_false_1)
		{
			LinkedList list1;
			list1.push_back(1);
			list1.push_back(2);
			list1.push_back(3);
			list1.push_back(4);

			LinkedList list2;
			list2.push_back(1);
			list2.push_back(3);
			list2.push_back(3);
			list2.push_back(4);

			Assert::IsFalse(list1.equals(&list2));
		}

		TEST_METHOD(equals_false_2)
		{
			LinkedList list1;
			list1.push_back(1);
			list1.push_back(2);
			list1.push_back(3);
			list1.push_back(4);

			LinkedList list2;
			list2.push_back(1);
			list2.push_back(2);

			Assert::IsFalse(list1.equals(&list2));
		}

		TEST_METHOD(pop_front_empty)
		{
			LinkedList list1;

			LinkedList list2;

			list1.pop_front();

			Assert::IsTrue(list1.equals(&list2));
		}

		TEST_METHOD(pop_front)
		{
			LinkedList list1;
			list1.push_back(1);
			list1.push_back(2);
			list1.push_back(3);
			list1.push_back(4);

			LinkedList list2;
			list2.push_back(2);
			list2.push_back(3);
			list2.push_back(4);

			list1.pop_front();

			Assert::IsTrue(list1.equals(&list2));
		}

		TEST_METHOD(pop_empty)
		{
			LinkedList list1;

			LinkedList list2;

			list1.pop_back();

			Assert::IsTrue(list1.equals(&list2));
		}

		TEST_METHOD(pop_back)
		{
			LinkedList list1;
			list1.push_back(1);
			list1.push_back(2);
			list1.push_back(3);
			list1.push_back(4);

			LinkedList list2;
			list2.push_back(1);
			list2.push_back(2);
			list2.push_back(3);

			list1.pop_back();

			Assert::IsTrue(list1.equals(&list2));
		}

		TEST_METHOD(insert_empty)
		{
			LinkedList list1;

			LinkedList list2;
			list2.push_back(1);

			list1.insert(0, 1);

			Assert::IsTrue(list1.equals(&list2));
		}

		TEST_METHOD(insert_empty_middle_index)
		{
			try
			{
				LinkedList list1;

				list1.insert(5, 1);
			}
			catch (std::out_of_range o_ex)
			{
				Assert::AreEqual(o_ex.what(), "Index is greater than list size and more than the index for teoretical last element");
			}
		}

		TEST_METHOD(insert_middle)
		{
			LinkedList list1;
			list1.push_back(1);
			list1.push_back(3);
			list1.push_back(4);

			LinkedList list2;
			list2.push_back(1);
			list2.push_back(2);
			list2.push_back(3);
			list2.push_back(4);

			list1.insert(1, 2);

			Assert::IsTrue(list1.equals(&list2));
		}

		//сверять размер после уменьшения

		TEST_METHOD(insert_front)
		{
			LinkedList list1;
			list1.push_back(2);
			list1.push_back(3);
			list1.push_back(4);

			LinkedList list2;
			list2.push_back(1);
			list2.push_back(2);
			list2.push_back(3);
			list2.push_back(4);

			list1.insert(0, 1);

			Assert::IsTrue(list1.equals(&list2));
		}
		TEST_METHOD(insert_back)
		{
			LinkedList list1;
			list1.push_back(1);
			list1.push_back(2);
			list1.push_back(3);

			LinkedList list2;
			list2.push_back(1);
			list2.push_back(2);
			list2.push_back(3);
			list2.push_back(4);

			list1.insert(3, 4);

			Assert::IsTrue(list1.equals(&list2));
		}

		TEST_METHOD(remove_empty)
		{
			try
			{
				LinkedList list1;

				list1.remove(3);
			}
			catch (std::out_of_range o_ex)
			{
				Assert::AreEqual(o_ex.what(), "Index is greater than list size");
			}
		}
		TEST_METHOD(remove_back)
		{
			LinkedList list1;
			list1.push_back(1);
			list1.push_back(2);
			list1.push_back(3);
			list1.push_back(4);

			LinkedList list2;
			list2.push_back(1);
			list2.push_back(2);
			list2.push_back(3);

			list1.remove(3);

			Assert::IsTrue(list1.equals(&list2));
		}

		TEST_METHOD(remove_front)
		{
			LinkedList list1;
			list1.push_back(1);
			list1.push_back(2);
			list1.push_back(3);
			list1.push_back(4);

			LinkedList list2;
			list2.push_back(2);
			list2.push_back(3);
			list2.push_back(4);

			list1.remove(0);

			Assert::IsTrue(list1.equals(&list2));
		}
		TEST_METHOD(remove)
		{
			LinkedList list1;
			list1.push_back(1);
			list1.push_back(2);
			list1.push_back(3);
			list1.push_back(4);

			LinkedList list2;
			list2.push_back(1);
			list2.push_back(2);
			list2.push_back(4);

			list1.remove(2);

			Assert::IsTrue(list1.equals(&list2));
		}

		TEST_METHOD(get_size_false)
		{
			LinkedList list;
			list.push_back(1);
			list.push_back(4);
			Assert::IsFalse(list.get_size() == 3);
		}

		TEST_METHOD(clear_1)
		{
			LinkedList list;
			list.push_back(1);
			list.push_back(2);
			list.push_back(3);
			list.push_back(4);

			list.clear();
			Assert::IsTrue(list.isEmpty());
		}

		TEST_METHOD(clear_2)
		{
			LinkedList list;
			list.clear();
			Assert::IsTrue(list.isEmpty());
		}

		TEST_METHOD(set)
		{
			LinkedList list1;
			list1.push_back(1);
			list1.push_back(1);

			LinkedList list2;
			list2.push_back(1);
			list2.push_back(2);

			list1.set(1, 2);

			Assert::IsTrue(list1.equals(&list2));
		}

		TEST_METHOD(isEmpty_true)
		{
			LinkedList list;
			Assert::IsTrue(list.isEmpty());
		}

		TEST_METHOD(isEmpty_false)
		{
			LinkedList list;
			list.push_back(1);

			Assert::IsFalse(list.isEmpty());
		}

		TEST_METHOD(contains_with_empty_list)
		{
			LinkedList list1;
			list1.push_back(1);
			list1.push_back(2);
			list1.push_back(3);
			list1.push_back(4);

			LinkedList list2;

			Assert::IsTrue(list1.contains(&list2));
		}

		TEST_METHOD(contains_with_fill_list_true_1)
		{
			LinkedList list1;
			list1.push_back(1);
			list1.push_back(2);
			list1.push_back(3);
			list1.push_back(4);

			LinkedList list2;
			list2.push_back(1);

			Assert::IsTrue(list1.contains(&list2));
		}

		TEST_METHOD(contains_with_fill_list_true)
		{
			LinkedList list1;
			list1.push_back(1);
			list1.push_back(2);
			list1.push_back(3);
			list1.push_back(4);

			Assert::IsTrue(list1.contains(&list1));
		}

		TEST_METHOD(contains_with_fill_list_false)
		{
			LinkedList list1;
			list1.push_back(1);
			list1.push_back(2);
			list1.push_back(3);
			list1.push_back(4);

			LinkedList list2;
			list2.push_back(4);
			list2.push_back(3);

			Assert::IsFalse(list1.contains(&list2));
		}
	};
}