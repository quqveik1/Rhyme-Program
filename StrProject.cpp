#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "Q_Locale.h"
#include <assert.h>
#include "Stuck.h"
#include <ctype.h>
//#include "TXLib.h"




const int LineSize = 200;
const int NLines = 10;


char *readText (FILE *Onegin, char text[NLines][LineSize], char *ptext[NLines]);	 
void printText (char *ptext[NLines]);
void deleteEOL (char text [LineSize]);
void sortStart (char *ptext[NLines]);
void strcpy_ (char m1[], char m2[], const int Size);
int strncmp_ (const char str1[], const char str2[], const size_t size);
void swapStr (char str1[], char str2[]);

void bubleCheck (char arr[][LineSize], size_t size);
void bubleUnittest ();

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
	char *ptext[NLines];

	
	
	readText (Onegin, text, ptext);

	

	//strncmp_ (text[0], text[2], -1);
	printText (ptext);
	printf ("%d||isPunct: %d; isalpha: %d\n", unsigned char ('«'), ispunct ('«'), isalpha ('«'));

	char t1[] = "когда не в шутку занемог,";
	char t2[] = "он уважать себя заставил";

	//printf ("strncmp_: %d\n", strncmp_ (t1, t2, LineSize));
	
	sortStart (ptext);
	printText (ptext);
	
	
   //bubleUnittest ();


}


char *readText (FILE *Onegin, char text[NLines][LineSize], char *ptext[NLines])
{
	for (int i = 0; i < NLines; i++)
	{
		if (!fgets (text[i], LineSize, Onegin)) break;
		deleteEOL (text[i]);
	}
	for (int i = 0; i < NLines; i++)
	{
		ptext[i] = text[i];	
	}

	return (char *) text;
}

void bubleUnittest ()
{
	char arr[][LineSize] = {"4", "3", "5", "1", "2"};
	bubleCheck (arr, 5);
	//printText (arr);
}

void printText (char *ptext[NLines])
{
	for (int i = 0; i < NLines; i++)
	{
		if (ptext[i][0] != 0)
		{
			printf ("%d: ||%s||\n", i, ptext[i]);
		}
	}
}

void sortStart (char *ptext[NLines])
{
	//equating (sortText[0], text[0], NLines);
	for (int j = 0; j < NLines; j ++)
	{
		for (int i = 0; i < NLines - j - 1; i++)
		{
			int delta = strncmp_ (ptext[i + 1], ptext[i], LineSize);

			if (delta < 0)
			{
				char *temp = ptext[i];
				ptext[i] = ptext[i + 1];
				ptext[i + 1] = temp;
			}
			//sortText [i] = sortText[i + 1];
			//sortText [i] = copy;

			//printText (text);
			//printf ("\n");
		}
	}
}

void bubleCheck (char arr[][LineSize], size_t size)
{
	for (int j = 0; j < NLines - 1; j ++)
	{
		bool sorted = true;
		for (int i = 0; i < NLines - j - 1; i++)
		{
			if (strncmp_ (arr[i], arr[i + 1], 5))
			{
				swapStr (arr[i], arr[i+1]);
			}			
		}
		if (sorted == true) break;
	}
}

int strncmp_ (const char str1[], const char str2[], const size_t size)
{
	VerifyPtr (str1);
	VerifyPtr (str2);

	int n1 = 0;
	int n2 = 0;

	for (int n = 0; n < size; n++)
	{
		while (ispunct (str1[n1]))
		{
			n1++;
		}
		while (ispunct (str2[n2]))
		{
			n2++;
		}



		if (str1[n1] == '\0' && str2[n2] == '\0')
		{
			return 0;	
		}
		if (str1[n1] == '\0')
		{
			return -1;	
		}
		if (str2[n2] == '\0')
		{
			return 1;	
		}

		if (str1[n1] != '\0')
		{

			if (str1[n1] != str2[n2])
			{
				//printf ("str1[%d]: , str2[%d]: ", n1, n2);
				printf ("%d", n);
				return str1[n1] - str2[n2];
			}
		}

			n1++;

			n2++;
		
		/*
		if (str1[n] == '\0')
		{
			return -1;
		}
		if (str2[n] == '\0')
		{
			return 1;
		}
		 */
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

void swapStr (char str1[], char str2[])
{
	VerifyPtr (str1);
	VerifyPtr (str2);

	for (int n = 0; ; n++)
	{
		if (str1[n] == '\0' && str2[n] == '\0') break;
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


																										  