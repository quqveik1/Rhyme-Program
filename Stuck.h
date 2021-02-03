// | firstCanary | | name        | | MaxSize     | | stack                         | | lastPos     | | structPos | | lastCanary |
//   07 9D F7 7E	 07 EE FF 00	 05 00 00 00	 78-9E 6F-1C 00-00 00-00 00-00	   02 00 00 00

#pragma once

#include <assert.h>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
#include <stdint.h>



#define _ASSERT_                          \
{										  \
	if (checkup () != _OK_)				  \
	{									  \
		dump ();						  \
		assert ("checkup failed:(" == 0); \
	}									  \
}										  \


#define POSINFO {__FILE__, __LINE__, __FUNCSIG__}
#define VAR(type, name, ...)  type name (POSINFO, #name, ##__VA_ARGS__)


#define Verificator 								 \
{												     \
	if (checkup () != 0)							 \
	{												 \
		dump (POSINFO, "Verificator check failure"); \
		assert (_OK_);							     \
	}											     \
}													 \
														   
#define VerifyPtr(adress)								         \
{														         \
	if (!checkPtr ((const int *) adress))			             \
	{													         \
		printf (" (Invalid adress {%s} = %p)", #adress, adress); \
		abort ();	                                             \
	}															 \
	                                                             \
}														   		 \
															   
#define safePrint(text, adress)								                               \
{															                               \
	if (!checkPtr (adress))							                                       \
	{														                               \
        printf ("(Returnable val = %d)::", checkPtr (adress));                             \
		printf ("(Invalid adress {%s} = %p(%d))\n", #adress, adress, checkPtr (adress));   \
	}															                           \
	else 														                           \
	{															                           \
		printf (text, adress);									                           \
	}															                           \
}																                           \

//printf (" (checkOk = %x)\n ", checkOk);

void statText (const char *text, int stat[256]);
void tenTo2 (unsigned int n);
void charToAscii (char c);
void setConsoleColor (unsigned color);
void clearConsoleColor ();
uint64_t hashCalc (const void *address, const size_t size);
uint64_t hashing2 (int array, uint64_t HASH);
int checkPtr (const void *adress);

//! @brief Специальная структура для хранения местоположения классов
//! @code PositionInfo structPos = {};
//! @endcode
struct PositionInfo
{
   const char *file = NULL;
   const int line = NULL;
   const char *function = NULL;

   void dump ();
};

//! @mainpage
//!			 Это описание библиотеки Stack

struct Stack
{
	//!	@brief Пространство имен ошибок
	//!
	//!
	//! @note Если у вас вылезла ошибка гляньте сюда и поймите где вы накосячили
	//! 
	//! @usage @code dump (_OVERFLOW_);
	//!
	//!@endcode

	enum errors
	{
		_OK_ = 0,
		_OVERFLOW_ = 1,
		_MINUSARRELEMENT_ = 2, 
		_CANARYERROR_ = 3, 
		_NULLPTR_ = 4,
		_HASHERROR_ = 5, 
		_INVALIDPTR_ = 6
	};

	//!	@brief Пространство имен цветов
	//!
	//!
	//! @note Подобранные цвета
	//! 
	//!
	//!@endcode

	enum Colors
	{
		_BLUE_ = 0x1,
		_RED_  = 0xc, 
		_CYAN_ = 0b00000011,
		_LIGHTCYAN_ = 0b00001011,
		_GRAY_ = 0b00001000, 
		_GREEN_ = 0xa, 
		_ERROR_ = 0x3
	};

	//!	@brief Конструктор класса Stack
	//! @param _structPos Это нужно для запоминания места создания структуры и печати этого в dump()

	Stack (PositionInfo _structPos, const char *_name);

	void pop ();
	void push (int num);
	void add ();
	void mul ();
	void sub ();
	void div ();

	void print ();
	void change (int num1, int num2);
	void dumpOld (/*const char *name*/);
	void dumpOld (const int cause);
	void dump (PositionInfo posinfo = {}, const char *cause = NULL);
	//void dump2 ();

	void unittest (int kOfPush = 1);
	void unittestCanary (int kOfPush);
	void unittestHash ();
	int checkup ();
	//bool hashCheck ();
	uint64_t reHash ();
	uint64_t checkHash ();

	//! @brief Максимальный размер Стека
	static const int MaxSize = 5;

	//! @brief Передняя канарейка [0]
	const int firstCanary = 0x7EF79D07;

	//! @brief Хэш класса [1, 2]
	uint64_t hash;

	//! @brief Кол-во переменных, которые будут выведены в dump () вне существующих элементов [3]
	const int addPrintSize = 5;

	//! @brief Название класса [4]
	const char *name;

	//! @brief Позиция последнего элемента [5]
	int lastPos = -1;

	//! @brief Это и есть главная чать Стека массив, где все хранится [6 - 10]
	int stack[MaxSize] = {};

	//! @brief Информация о позиции и названии Стека для аварийной отладочной распечтки dump (); [11 - 13]
	PositionInfo structPos = {};
	
	//! @brief Задняя канарейка [14]
	const int lastCanary =  0x12345E84;	 
};

void Stack::add ()
{
	if (lastPos < 2) 
	{
		printf ("add () не вохможен из-за недостатка кол-ва элементов\n");
		return;
	}

	int lastNum   = stack [lastPos - 1];
	int prelastNum = stack [lastPos - 2];

	pop ();
	pop ();

	push (lastNum + prelastNum);
}

void Stack::mul ()
{
	if (lastPos < 2) 
	{
		printf ("add () не вохможен из-за недостатка кол-ва элементов\n");
		return;
	}

	int lastNum   = stack [lastPos - 1];
	int prelastNum = stack [lastPos - 2];

	pop ();
	pop ();

	push (lastNum * prelastNum);
}

void Stack::sub ()
{
	if (lastPos < 2) 
	{
		printf ("add () не вохможен из-за недостатка кол-ва элементов\n");
		return;
	}

	int lastNum   = stack [lastPos - 1];
	int prelastNum = stack [lastPos - 2];

	pop ();
	pop ();

	push (lastNum - prelastNum);
}

void Stack::div ()
{
	if (lastPos < 2) 
	{
		printf ("add () не вохможен из-за недостатка кол-ва элементов\n");
		return;
	}

	int lastNum   = stack [lastPos - 1];
	int prelastNum = stack [lastPos - 2];

	pop ();
	pop ();

	push (lastNum / prelastNum);
}



//!	@brief Структура для теста канареек
//!
//!
//! 
//! @code StackTest st1 {{}, {POSINFO(st1)}, {}};
//!
//!@endcode

struct StackTest
{
	int mLeft[1] = {};	
	Stack data;
	int mRight[1] = {};

	//StackTest (PositionInfo _structPos);
};

//!	@brief Функция которыя тестирует Хэшфункции
//!
//!
//! 
//! 
//! @code VAR (Stack, S1);
//!		  S1.unittestHash ()
//!
//!@endcode

void Stack::unittestHash ()
{
	/*
	StackTest testData {{}, {POSINFO, "testData.data"}, {}};
	
	testData.data.push (1);
	//testData.data.pop ();
	testData.data.push (10);
	testData.data.pop ();
	testData.data.push (4538);
	testData.mRight[7] = 1000;
	testData.data.push (12);
	//Verificator
	//testData.data.push (12);
	*/

	

}

//!	@brief Функция для теста канареек
//!
//! @param kOfPush Кол-во раз, которое нужно подождать перед запретной операцией
//! 
//! @code s1.unittestCanary
//!
//!@endcode
void Stack::unittestCanary (int kOfPush)
{

	StackTest testData {{}, {POSINFO, "testData.data"}, {}};
	//st1.m1[0] = 2;
	testData.mRight[1] = 1000;
	testData.data.push (3);
	kOfPush = 0;
	

	//st1.m2[-1] = 4;

	//testData.data.dump ();

}
/*
StackTest::StackTest (PositionInfo _structPos) :
	s1 (_structPos)
{

}
	*/


//!	@brief Конструктор класса
//!
//!	@param _structPos Это объект PositionInfo  
//! @param _name Это название структуры
//!
//! @return НИЧЕГО и не надо:)
//! 
//! @code VAR (Stack, S1);
//!				S1.unittestHash ()
//!@endcode

Stack::Stack (PositionInfo _structPos, const char *_name) :
	 structPos (_structPos),
	 name	   (_name)
{ 
	reHash ();	

}

//!	@brief Функция для правильного подсчета и изменения хеша для класса
//!
//! 
//! @code s1.reHash ();
//!
//!@endcode


uint64_t Stack::reHash ()
{
	uint64_t oldHash = hash;
	hash = 0;
	hash = hashCalc (this, sizeof (*this));
	return oldHash;
}

//!	@brief Функция для правильного подсчета, но не его изменения хеша для класса
//!
//! 
//! @code s1.checkHash ();
//!
//!@endcode

uint64_t Stack::checkHash ()
{
	uint64_t hashCopy = hash;
	hash = 0;
	uint64_t newHash = hashCalc (this, sizeof (*this));
	hash = hashCopy;
	return newHash;
}


//!	@brief Проверяет на банальные ошибки с lastPos, да канарейки посмотрит
//!
//! @return _OK_ Если все хорошо, вызывает ассерт если кто-то накосячил:(
//! @warning Эта защита защищает только от самых бональных ошибок, полностью надеятся на ее не нужно
//! 
//! @usage @code checkup()
//!
//!@endcode
 

int Stack::checkup ()
{
	if (this == nullptr)
	{
		return _NULLPTR_; 	
	}

	if (!checkPtr (this))
	{
		return _INVALIDPTR_;
	}

	if (lastPos > MaxSize -1)
	{
		return _OVERFLOW_;
		//assert (0 == 1);
	}

	if (lastPos < -1)
	{
		return _MINUSARRELEMENT_;
		//assert (0 == 1);
		
	}

	if (firstCanary != 0x7EF79D07)
	{
		return _CANARYERROR_;
		//assert (0 == 1);	
	}
	if (lastCanary != 0x12345E84)
	{
		return _CANARYERROR_;
		//assert (0 == 1);
	}

	//unsigned int oldHash = reHash ();
	if (hash != checkHash ())
	{
		//hash = oldHash;
		return _HASHERROR_;
	}
	//hash = hashCopy;

	return _OK_;

}

//!	@brief Удаляет последний элемент в стеке
//!
//! @return НИЧЕГО
//! @warning При удалении элементов из пустого массива вызывается assert
//! 
//! @usage @code s1.pop ();
//!
//!@endcode

void Stack::pop ()
{
	//assert (-1 < lastPos && lastPos < MaxSize);
	assert (stack);

	//assert (checkup () == _OK_);
	//checkup ();
	Verificator
	stack[lastPos]  = NULL;
	lastPos--;

	reHash ();
	//changes = true;
	Verificator
	//checkup ();
}

//!	@brief Добавляет новый элемент в стек
//!
//!	@param num - число которое будет добавлено
//!
//! @return НИЧЕГО
//! @warning При добавлении элементов в полный массив вызывается assert
//! 
//! @usage @code s1.push (2);
//!
//!@endcode

void Stack::push (int num)
{
	//assert (num != NULL);
	assert (stack);
	//assert (-2 < lastPos && lastPos < MaxSize - 1);

	//checkup ();
	Verificator
	lastPos++;
	stack[lastPos] = num;

	reHash ();
	Verificator

	//lastPos++;

}

/*
push 10
push 20
add	 //push (pop + pop)
push -1
mul //push (pop * pop)
push 2
push 5
sub // push (pop - pop)
div // push (pop / pop)

in пушит число
out//последнее число из стэжка
hlt

* /


//!	@brief Печатает наш Стек для непрошаренных пользователей
//!
//! @return НИЧЕГО
//! @note Для отладки лучше использовать dump ();
//! 
//! @usage @code s1.print ();
//!
//!@endcode
  /*
Stack [0x004C80] (OK) "s" "main.cpp (20)"
{
	firstCanary = 0xB84C

	MaxSize     = 5
	lastPos     = 3
	stack [0x004CA0]
	{
       * [0] = 10
	   * [1] = 20
	   * [2] = 30
		 [3] = -13
		 [4] = 15
	}

	lastCanary = 0xB8CC
}
*/

  /*
Stack [0x004C80] (_LASTPOSNEGATIVE_) "s" "main.cpp (20)"
{
	firstCanary = 0xB84C

	MaxSize     = 5
	lastPos     = -1
	stack [0x004CA0]
	{
		 [0] = 10
	     [1] = 20
	     [2] = 30
		 [3] = -13
		 [4] = 15
	}

	lastCanary = 0xB8CC

*/

//!	@brief Функция для детального вывода информации о стеке
//!
//!	@param posinfo где вызвался dump
//! @param cause причина вызова
//!
//! 
//! @code s1.dump (POSINFO, "Canary");
//!
//!@endcode

void Stack::dump (PositionInfo posinfo, const char *cause)
{
	if (cause != NULL)
	{
		safePrint ("Cause: %s\n", cause);
		//printf ("Cause: %s\n", cause);
	}
	if (posinfo.line != NULL)
	{
		printf ("Called: ");
		posinfo.dump ();

	}

	int errorCode = checkup ();
	safePrint ("\nStack [0x%p] ", this);
	//printf ("\nStack [0x%p] ", this);
	switch (errorCode)
	{
	case _OK_:
		setConsoleColor (_GREEN_);
		printf ("(_OK_) ");
		break;
	case _OVERFLOW_:
		setConsoleColor (_ERROR_);	
		printf ("(_OVERFLOW_) ");
		break;
	case _MINUSARRELEMENT_:
		setConsoleColor (_ERROR_);
		printf ("(_MINUSARRELEMENT_) ");
		break;
	case _CANARYERROR_:
		setConsoleColor (_ERROR_);
		printf ("(_CANARYERROR_) ");
		break;
	case _NULLPTR_:
		setConsoleColor (_ERROR_);
		printf ("(_NULLPTR_)\n");
		break;
	case _HASHERROR_:
		setConsoleColor (_ERROR_);
		printf ("(_HASHERROR_)");
		break;
	case _INVALIDPTR_:
		setConsoleColor (_ERROR_);
		printf ("(_INVALIDPTR_)\n");
		break;
	}
	clearConsoleColor ();

	if (errorCode == _INVALIDPTR_) return; //!!!!!!Все выход из дампа дальше распечатка невозможна
	if (errorCode == _INVALIDPTR_) return; //!!!!!!Все выход из дампа дальше распечатка невозможна

	safePrint ("{%s} ", name);
	//printf ("{%s} ", name);
	structPos.dump ();
	//VerifyPtr (stack);
	printf ("\n");
	printf ("{\n"
			"	firstCanary =  0x%x (%s)\n\n"
			"	MaxSize = %d\n"
			"	lastPos = %d\n"
			"	stack [0x%p]\n"
			"	{\n",
		    firstCanary, (firstCanary == 0x7EF79D07)? "ok" : "ERROR", 
			MaxSize,
			lastPos,
			stack
		   );
	for (int i = 0; i <= lastPos + addPrintSize; i++)
	{
		if (i >= MaxSize) break;

		assert (0 <= i && i < MaxSize);

		if (i < MaxSize)
		{
			if (i < lastPos)
			{
				printf ("		*[%d] = %d\n", i, stack[i]);
			}
			else 
			{
				printf ("		 [%d] = %d\n", i, stack[i]);
			}
		}
	}

	printf ("	}\n\n");
	printf ("	lastCanary = 0x%x (%s)\n\n", lastCanary, (lastCanary == 0x12345E84)? "ok" : "ERROR");
	printf ("   hash (class) = %llx\n", hash);
	printf ("   hash (now)   = %llx\n", checkHash ());
	//int hash

	printf ("}\n");



}

/*
	hash    = 0000 0000 0000 0000
	data[i] =           0110 0101
			^ 0000 0000 0110 0101
         1 >> 0000 0000 0011 0010 | 1
			  1000 0000 0011 0010

	data[i]	=			1110 0100
			^ 1000 0000 1101 0110
		 1 >> 0100 0000 0110 1011 | 0
		      0100 0000 0110 1011



*/

//!	@brief Функция для подсчета хеша ЛЮБОГО объекта
//!
//!	@param adress адресс первого элемента стуктуры
//! @param size размер этого объекта
//!
//! 
//! @code s1.hashCalc (&s1, sizeof (*this));
//!
//!@endcode

uint64_t hashCalc (const void *address, const size_t size)
{
	/*
	hashing (MaxSize, hashCopy);
	hashing (addPrintSize, hashCopy);
	//hashing (name);
	for (int i = 0; i < MaxSize; i++)
	{
		assert (i < MaxSize && 0 <= i);
		hashing (stack[i], hashCopy);
	}
	hashing (lastPos, hashCopy);
	hashing (structPos.line, hashCopy);
	 */
	uint64_t HASH = 0;

	const unsigned char *addr = (const unsigned char*)(address);
	
	for (size_t i = 0; i < size; i++)
	{
		assert (i < size && 0 <= i);
		HASH ^= addr[i];

		uint64_t lastBit = HASH & 0b1;
		//1000000000000000000000000000000000   << 31
		//0000000000000000000000000000000000   << 1


		HASH >>= 1;
		
		HASH |= lastBit << 63;		
	}

	return HASH;

		/*
	if (hash == hashCopy)
	{
		if (changes == false)
		{
			return false;
		} 
		else 
		{
			changes = false;
			return true;
		}
	}

	if (hash != hashCopy)
	{
		if (changes == false)
		{
			return true;
		} 
		else 
		{
			changes = false;
			return false;
		}
	}
	*/

}


uint64_t hashing2 (int array, uint64_t HASH)
{
	unsigned int Hashlast2Bit = HASH & 0b11;
	HASH >>= 2;
	HASH |= Hashlast2Bit << 62;
	HASH ^= array;
	Hashlast2Bit = HASH & 0b11;
	HASH >>= 2;
	HASH |= Hashlast2Bit << 62;
	return HASH;
}




/*
void Stack::dumpNew (const int cause)
{
	printf ("\nStack [0x%p] () ", this);
	/*
	switch (cause)
	{
	case _OK_:
		printf ("(_OK_) ");
		break;
	case _OVERFLOW_:
		printf ("(_OVERFLOW_) ");
		break;
	case _MINUSARRELEMENT_:
		printf ("(_MINUSARRELEMENT_) ");
		break;
	case _CANARYERROR_:
		printf ("(_CANARYERROR_) ");
		break;
	case _NULLPTR_:
		printf ("(_NULLPTR_) ");
		break;

	}
	

	printf ("{%s} {%s (%d)} \n", structPos.name, structPos.function, structPos.line);
	printf ("{\n"
			"	firstCanary =  0x%x\n\n"
			"	MaxSize = %d\n"
			"	lastPos = %d\n"
			"	stack [0x%p]\n"
			"	{\n",
			(firstCanary == 0x7EF79D07)? "ok" : "ERROR", firstCanary,
			MaxSize,
			lastPos,
			stack
		   );
	for (int i = 0; i <= lastPos + addPrintSize; i++)
	{
		if (i < MaxSize)
		{
			if (i < lastPos)
			{
				printf ("		*[%d] = %d\n", i, stack[i]);
			}
			else 
			{
				printf ("		 [%d] = %d\n", i, stack[i]);
			}
		}
	}

	printf ("	}\n\n");
	printf ("	lastCanary (%s) = 0x%x\n", (lastCanary == 0x12345E84)? "ok" : "ERROR", lastCanary);
	printf ("}\n");



}
*/
  /*
Stack [0x004C80] (_LASTPOSNEGATIVE_) "s" "main.cpp (20)"
{
	firstCanary = 0xB84C

	MaxSize     = 5
	lastPos     = -1
	stack [0x004CA0]
	{
         [0] = 10
	     [1] = 20
	     [2] = 30
		 [3] = -13
		 [4] = 15
	}

	lastCanary = 0xB8CC

*/

//!	@brief Функция для простого изменеия цвета консоли
//!
//!	@param color это цвет его можно передавать например ввиде пространств имен Colors, которые я объвлял на верху
//!
//! 
//! @code setConsoleColor (_RED_);
//!
//!@endcode

void setConsoleColor (unsigned color)
{
	SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), (WORD) color);
}
//!	@brief Функция для сброса цвета консоли к начальному черному
//!
//!
//! 
//! @code setConsoleColor ();
//!
//!@endcode

void clearConsoleColor ()
{
	SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 7);
}

//!	@brief Функция для простого вывода для новичков
//!
//!
//! 
//! @code print ();
//!
//!@endcode

void Stack::print ()
{
	//scheckup ();
	setConsoleColor (_CYAN_);	
	assert (stack);
	assert (this);
	
	//printf ("\n%s = [ ", structPos);
	structPos.dump ();
	for (int i = 0; i <= lastPos; i++)
	{
		assert (0 <= i && i < MaxSize);
		setConsoleColor (_CYAN_);
		printf ("[%d] = ",  i);

		setConsoleColor (_LIGHTCYAN_);
		printf ("%d", stack[i]);

		setConsoleColor (_CYAN_);
		printf ("%s", (i != lastPos)? ", " : " ");
	}
	printf ("]\n");


	//lastPos++;

} 

//!	@brief Меняет два элемента массива между собой
//!
//!	@param num1 - позиция первого элемента (отсчет от 0)
//!	@param num2 - позиция второго элемента (отсчет от 0)
//!
//! @return НИЧЕГО
//! @warning При замене несуществующих элементов вызывается assert
//! 
//! @usage @code s1.change (2, 3);
//!
//!@endcode

void Stack::change (int num1, int num2)
{
	checkup ();
	assert (stack);
	//assert (num1 != NULL);
	//assert (num2 != NULL);

	assert (0 <= num1 && num1 <= lastPos);
	assert (0 <= num2 && num2 <= lastPos);

	int copy = stack[num1];
	stack[num1] = stack[num2];
	stack[num2] = copy;
	checkup ();

}


void Stack::dumpOld (/*const char *name*/)
{
	//printf ("%s = ", "sth:(");
	checkup ();
	print ();

	printf ("Adress: %p\n", this);
	structPos.dump ();
	checkup ();

	

}

//!	@brief Детальный вывод информации о структуре
//!
//!	@param cause необязательный системный параметр, нужен для вывода ошибок в checkup()
//!
//! @return НИЧЕГО
//! @note Он может вам много что рассказать
//! 
//! @usage @code s1.dump ();
//!				 s1.dump (_OverFlow_);
//!
//!@endcode

void Stack::dumpOld (const int cause)
{
	setConsoleColor (_RED_);
	printf ("ERROR:((((((((\n");
	printf ("Cause: %d\n", cause);
	//printf ("%s = ", "sth:(");
	print ();

	printf ("Adress: %p\n", this);
	printf ("Canary1: %x, Canary2: %x\n", firstCanary, lastCanary);
	structPos.dump ();


	

}

//!	@brief Сначало заполняет Стек kOfPush кол-вом элементами
//!
//!	@param kOfPush кол-во элементов, которое будет передано в стек 
//!
//! @return НИЧЕГО
//! @note Он может проверить на наличе ошибок в стеке
//! 
//! @usage @code s1.unittest
//!
//!@endcode

void Stack::unittest (int kOfPush)
{
	checkup ();
	pop ();
	/*
	for (int i = 0; i < kOfPush; i++)
	{
		push (1);
	}
	checkup ();

	for (int i = 0; i < kOfPush; i++)
	{
		//pop ();
	}

	checkup ();

	printf ("\nTest was succesfull\n");
	*/

	checkup ();

}


//!	@brief Функция для вычисления самой популярнойй буквы текста
//!
//!	@param text это текст в котором нужно посчитать статистику
//! @param stat Это масив размером 256 который содержит статистику каждой буквы
//!
//! 
//! @code statText ("abbc", stat);
//!
//!@endcode

void statText (char *text, int stat[256])
{
	for (int i = 32; i < 256; i++)
	{
		//printf ("[%c] == %d\n", i, i);	
	}

	
	for (int i = 0; text[i] != 0; i++)
	{
		//printf ("[%c] == %d\n", text[i], (unsigned char) text[i]);
		assert (0 <= i && i <= 256);
		assert (-128 <= text[i] && text[i] < 128);
		stat[ (unsigned char) text[i] ]++;

	}

	for (int i = 0; i < 256; i++)
	{
		if (stat[i] != 0)
		{
			printf ("[%c] == %d\n", i, stat[i]);
		}

	}
	/*
	192	  96  48  24   12	6 3	1 0
	  0	   0   0   0	0	0 1	1
		   11000000
	
  */
}

//!	@brief Функция для вывода данного числа в двоичной формате
//!
//! @param n данное число для перевода
//!
//! 
//! @code tenTo2 ();
//!
//!@endcode

void tenTo2 (unsigned int n)
{
	for (int i = 7; i >= 0; i--)
	{	
		//printf ("%d ", 1 << i);
				    
		printf ("%d", (n & (1 << i)) >> i);
		//printf ("\n");
	}
}

void charToAscii (char c)
{
	printf ("[%c] == (%+03d; ", c, c);
	tenTo2 (c);
	printf (")\n");

}

//!	@brief Функция для вывода информации о позиции об объекте
//!
//!
//! 
//! @code s1.structPos.dump ();
//!
//!@endcode

void PositionInfo::dump ()
{
	//!!!!!!if (name != NULL)
	//!!!!!!	printf ("Name: [%s]\n",     name);

	//printf     ("{File: [%p], Func: [%p], Line: [%d]}", file, function, line);
	VerifyPtr (file);
	VerifyPtr (function);
	
	printf     ("{File: [%s], Func: [%s], Line: [%d]}", file, function, line);
}

int checkPtr (const void *adress)
{
	MEMORY_BASIC_INFORMATION MBI = {};

	if (!VirtualQuery (adress, &MBI, sizeof (MBI))) return 0;

	DWORD readRights = PAGE_READONLY | PAGE_READWRITE;

	//printf ("( %x )", MBI.Protect);
	//printf (" (Returnable val = %d)\n", MBI.Protect & readRights);
	return (MBI.Protect & readRights);
}