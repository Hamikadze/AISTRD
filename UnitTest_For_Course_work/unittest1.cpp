#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Course_work/CommitsUtils.h"
#include "../Course_work/CommitsUtils.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest_For_Course_work
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(IsInitializationSuccess)
		{
			auto commits = new CommitsUtils("C:\\Users\\besth\\OneDrive\\Visual Studio 2017\\Projects\\AISTRD\\UnitTest_For_Course_work\\unit_test.txt");
			Assert::IsTrue(commits->path_changed == "C:\\Users\\besth\\OneDrive\\Visual Studio 2017\\Projects\\AISTRD\\UnitTest_For_Course_work\\unit_test.txt" &&
				commits->path_commits == "C:\\Users\\besth\\OneDrive\\Visual Studio 2017\\Projects\\AISTRD\\UnitTest_For_Course_work\\unit_test_commits.bin" &&
				commits->path_original == "C:\\Users\\besth\\OneDrive\\Visual Studio 2017\\Projects\\AISTRD\\UnitTest_For_Course_work\\unit_test_original.txt");
		}

		TEST_METHOD(IsReadingFunctionsWorkForOriginal)
		{
			auto commits = new CommitsUtils("C:\\Users\\besth\\OneDrive\\Visual Studio 2017\\Projects\\AISTRD\\UnitTest_For_Course_work\\unit_test.txt");
			LinkedList<std::string> list;
			list.push_back("1");
			list.push_back("2");
			list.push_back("3");

			Assert::IsTrue(commits->original_text.equals(&list));
		}

		TEST_METHOD(IsReadingFunctionsWorkForChanged)
		{
			auto commits = new CommitsUtils("C:\\Users\\besth\\OneDrive\\Visual Studio 2017\\Projects\\AISTRD\\UnitTest_For_Course_work\\unit_test.txt");
			LinkedList<std::string> list;
			list.push_back("1");
			list.push_back("2");
			list.push_back("3");
			list.push_back("4");
			list.push_back("5");

			Assert::IsTrue(commits->changed_text.equals(&list));
		}

		TEST_METHOD(IsGetOriginalWorkAfterChange)
		{
			auto commits = new CommitsUtils("C:\\Users\\besth\\OneDrive\\Visual Studio 2017\\Projects\\AISTRD\\UnitTest_For_Course_work\\unit_test.txt");

			commits->original_text.pop_front();
			Assert::IsFalse(commits->original_text.equals(&commits->temp_text));
		}

		TEST_METHOD(IsGetOriginalMethodWork)
		{
			auto commits = new CommitsUtils("C:\\Users\\besth\\OneDrive\\Visual Studio 2017\\Projects\\AISTRD\\UnitTest_For_Course_work\\unit_test.txt");
			auto list = commits->get_original();
			Assert::IsTrue(commits->original_text.equals(&list));
		}

		TEST_METHOD(IsGetChangedMethodWork)
		{
			auto commits = new CommitsUtils("C:\\Users\\besth\\OneDrive\\Visual Studio 2017\\Projects\\AISTRD\\UnitTest_For_Course_work\\unit_test.txt");
			auto list = commits->get_changed();
			Assert::IsTrue(commits->changed_text.equals(&list));
		}

		TEST_METHOD(IsGetTempMethodWork)
		{
			auto commits = new CommitsUtils("C:\\Users\\besth\\OneDrive\\Visual Studio 2017\\Projects\\AISTRD\\UnitTest_For_Course_work\\unit_test.txt");
			auto list = commits->get_temp();
			Assert::IsTrue(commits->temp_text.equals(&list));
		}

		TEST_METHOD(IsAnalyzeChangesMethodWork)
		{
			auto commits = new CommitsUtils("C:\\Users\\besth\\OneDrive\\Visual Studio 2017\\Projects\\AISTRD\\UnitTest_For_Course_work\\unit_test.txt");
			Assert::IsTrue(commits->analyze_changes());
		}

		//1545596592 - first commit 1 2 3 4

		TEST_METHOD(IsApplyHistoryMethodWork)
		{
			auto commits = new CommitsUtils("C:\\Users\\besth\\OneDrive\\Visual Studio 2017\\Projects\\AISTRD\\UnitTest_For_Course_work\\unit_test.txt");
			auto history_list = commits->apply_commits_history(std::time_t(1545596592));
			LinkedList<std::string> list;
			list.push_back("1");
			list.push_back("2");
			list.push_back("3");
			list.push_back("4");
			Assert::IsTrue(list.equals(&history_list));
		}
	};
}