#include <iostream>
#include <gtest/gtest.h>
#include "M_1.h"

//1. Установить фреймворк Google Test.
//2. Добавить unit - тесты в проект домашнего задания из седьмого или первого урока.


class TestPhoneBook : public testing::Test {
protected:
	void SetUp() override {
		ifstream file("PhoneBook.txt");
		book = new PhoneBook(file);
	}
	void TearDown() override {
		delete book;
	}
	PhoneBook* book;
};

TEST_F(TestPhoneBook, checkGetPhoneNumber) {
	Person testExistPerson{ "Ilin", "Petr", "Artemovich" };
	PhoneNumber testExistNumber{ 7, 17, "4559767" };
	auto number = book->GetPhoneNumber(testExistPerson.surname);
	ASSERT_EQ(testExistNumber, get<1>(number));
	Person testNoPerson{ "Perinova", "Lena", "Ivanovna" }; 
	number = book->GetPhoneNumber(testNoPerson.surname);
	ASSERT_EQ("not found", get<0>(number));
}

TEST_F(TestPhoneBook, checkChangePhoneNumber) {
	Person testExistPerson{ "Ilin", "Petr", "Artemovich" };
	PhoneNumber testNewNumber{ 9, 99, "9999999" };
	book->ChangePhoneNumber(testExistPerson, testNewNumber);
	auto number = book->GetPhoneNumber(testExistPerson.surname);
	ASSERT_EQ(testNewNumber, get<1>(number));
}

int main()
{
	testing::InitGoogleTest();
	return RUN_ALL_TESTS();

}


