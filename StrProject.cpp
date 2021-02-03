#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "Q_Locale.h"
#include <assert.h>
#include "Stuck.h"
//#include "TXLib.h"



const int LineSize = 200;
const int NLines = 4;


char *readText (FILE *Onegin, char text[NLines][LineSize]);	 
void printText (char text[NLines][LineSize]);
void deleteEOL (char text [LineSize]);
void sortStart (char text[NLines][LineSize]);
void strcpy_ (char m1[], char m2[], const int Size);
int strncmp_ (char str1[], char str2[], size_t size);
void swapStr (char str1[], char str2[], size_t size);

int main()
{
	setRussianLocale ();

/*
«Мой дядя самых честных правил,
Когда не в шутку занемог,
Он уважать себя заставил
И лучше выдумать не мог

И лучше выдумать не мог
Когда не в шутку занемог,
«Мой дядя самых честных правил,
Он уважать себя заставил

Его пример другим наука;
Но, боже мой, какая скука
Когда не в шутку занемог,	
И лучше выдумать не мог
«Мой дядя самых честных правил,
Он уважать себя заставил
Какое низкое коварство
Печально подносить лекарство,
Полуживого забавлять,
Ему подушки поправлять,
С больным сидеть и день и ночь,
Не отходя ни шагу прочь!
Вздыхать и думать про себя:
Когда же черт возьмет тебя!»
*/

	FILE *Onegin = fopen ("onegin.txt", "r");

	char text[NLines][LineSize] = {""};

	

	readText (Onegin, text);

	//strncmp_ (text[0], text[2], -1);
	printText (text);
	printf ("\n");
	//char sortText [NLines][LineSize] = {};
	sortStart (text);
	printf ("М: %d\n", 'М');
	printf ("К: %d\n", 'К');
	printf ("strncmp_: %d\n", strncmp_ (text[0], text[1], LineSize));
	//swapStr (text[0], text[1], LineSize);
	printText (text);

	



}


char *readText (FILE *Onegin, char text[NLines][LineSize])
{
	for (int i = 0; i < NLines; i++)
	{
		if (!fgets (text[i], LineSize, Onegin)) break;
		deleteEOL (text[i]);
	}

	return (char *) text;
}

void printText (char text[NLines][LineSize])
{
	for (int i = 0; i < NLines; i++)
	{
		if (text[i][0] != 0)
		{
			printf ("%d: ||%s||\n", i, text[i]);
		}
	}
}

void sortStart (char text[NLines][LineSize])
{
	//equating (sortText[0], text[0], NLines);
	for (int j = 0; j < NLines - 1; j ++)
	{
		for (int i = 0; i < NLines - j - 1 ; i++)
		{
			if (strncmp_ (text[i + 1], text[i], LineSize) < 0)
			{
				swapStr (text[i], text[i+1], LineSize);
				break;
			}
			//sortText [i] = sortText[i + 1];
			//sortText [i] = copy;

			//printText (text);
			//printf ("\n");
		}
	}
}

int strncmp_ (char str1[], char str2[], size_t size)
{
	VerifyPtr (str1);
	VerifyPtr (str2);

	for (int n = 0; n < size; n++)
	{
		if (str1[n] != '\0')
		{
			if (str1[n] != str2[n])
			{
				return str1[n] - str2[n];
			}
		}
		/*
		if (str1[n] == str2[n])
		{
			return 0;
		}
		if (str1[n] > str2[n])
		{
			return 1;
		}
		if (str1[n] < str2[n])
		{
			return -1;
		}
		abcd\0 yrtfg
		abcd\0 fghfghf
		*/
	}


}

void swapStr (char str1[], char str2[], size_t size)
{
	VerifyPtr (str1);
	VerifyPtr (str2);

	for (int n = 0; n < size; n++)
	{
		char copy = str1[n];
		str1[n] = str2[n];
		str2[n] = copy;
	}

}

void strcpy_ (char m1[], char m2[], const int Size)
{
	//m1 = m2;
	
	for (int i = 0; i < Size; i++)
	{
		m1[i] = m2[i];
	}
}


/*
void compare2LinesFromStart (const char *line1, const char *line2)
{
	for (int n = 0; n < LineSize; n++)
	{
		if (line1[n] > line2[n])
		{
			char copy[LineSize];
			copy = line1; 
			sortText [i] = sortText[i + 1];
			sortText [i] = copy;
		}
	}

}
*/

void deleteEOL (char text [LineSize])
{
	int len = strlen (text);
	if (len - 1 >= 0)
	{

		//const char *nul = "\0";
		if (text[len-1] == '\n')
		{
			text[len - 1] = '\0';
		}
	}
}


																										  