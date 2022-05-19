#include <iostream>

int main()
{
	//Задание 2.1

	short s1 = 1;
	int16_t s2 = -1;
	uint16_t s3 = 1;

	int i1 = -1;
	int32_t i2 = 1;
	uint32_t i3 = 1;

	long long l1 = -1000LL;
	int64_t l2 = -1000LL;
	uint64_t l3 = 1000LL;

	char c1 = '1';
	int8_t c2 = 'A';
	uint8_t c3 = 33; //!

	bool is_on = true;

	float f1 = -1.10f;
	
	double d1 = 1.10;

	//Задание 2.2

	enum class Status 
	{
		NOUGHT,
		CROSS,
		EMPTY
	};

	//Задание 2.3

	Status aField1[3][3] = {Status::EMPTY, Status::EMPTY, Status::EMPTY, 
						   Status::EMPTY, Status::EMPTY, Status::EMPTY,
						   Status::EMPTY, Status::EMPTY, Status::EMPTY };
	//Задание 2.4

	struct TData 
	{
		Status aField[3][3];
		char firstPlayerName[30];
		char secondPlayerName[30];

		int idFirstPlayer;
		int idSecondPlayer;

		bool firstPlayerCross;
		bool secondPlayerCross;

		bool gameIsOn;

		bool turnOfFirstPlayer;
		bool turnOfSecondPlayer;

		bool wonFirstPlayer;
		bool wonSecondPlayer;	
	};

	//TData experiment;
	//experiment.aField[3][3] = {{Status::EMPTY, Status::EMPTY, Status::EMPTY}, //пишет "слишком много значений инициализатора" не смогла разобраться почему.
	//							{Status::EMPTY, Status::EMPTY, Status::EMPTY},
	//							{Status::EMPTY, Status::EMPTY, Status::EMPTY}};

	//Задание 2.5

	union MyData
	{
		char firstLetterOfName;
		int age;
		float height;
	};

	struct MyVariant
	{
		MyData s;
		uint8_t isChar : 1;
		uint8_t isInt : 1;
		uint8_t isFloat : 1;
	};

	MyVariant Maria;

	Maria.s.age = 27;

	Maria.isChar = 0;
	Maria.isFloat = 0;
	Maria.isInt = 1;

	Maria.s.firstLetterOfName = 'M';
	
	Maria.isChar = 1;
	Maria.isInt = 0;	
}
