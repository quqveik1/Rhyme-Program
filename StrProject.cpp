#define _CRT_SECURE_NO_WARNINGS

#include "TXLib.h"
#include <stdio.h>
#include "Q_Locale.h"
#include <assert.h>
#include "Stuck.h"
#include <ctype.h>
#include <sys\stat.h>
//#include "TXLib.h"




struct gnirts
{
	const char * str = "";
	int len = 0;

};


const int LineSize = 100;
const int NLines = 200;


int readText (FILE *Onegin, char *text);
void writeArrText (char *text, gnirts ptext[], FILE *Onegin);

void printText (const gnirts ptext[], int len);
void printLine (const char * text);

void deleteEOL (char text [LineSize]);
void sortStart (const char *ptext[NLines]);
void strcpy_ (char m1[], char m2[], const int Size);
int strncmp_ (const gnirts &str1, const gnirts &str2);
void swapStr (char str1[], char str2[]);

int strcmpBack (const gnirts &str1, const gnirts &str2);
void rhymeSort (char *ptext[NLines]);
void textSort (gnirts ptext[NLines], int (*cmp)(const gnirts &str1, const gnirts &str2));
void findLen (gnirts ptext[NLines]);
long fileSize (const char *nameOfFile);
long fileSize (FILE *File);
void findEOLs (char *text, gnirts ptext[], int len);
int findEOLsN_ (const char *text, int len);
void findLen (gnirts ptext[NLines], int textLen);

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

	FILE *Onegin = fopen ("Onegin.txt", "r");

	int fSize = fileSize (Onegin);


	char *text = new char[fSize + 1] {0};

	int nlines = readText (Onegin, text);
	gnirts *ptext = new gnirts[nlines + 1] {};
    writeArrText (text, ptext, Onegin);
	printf ("nlines: %d\n", nlines);


	fclose (Onegin);


	printText (ptext, nlines + 1);
	printf ("printTextIsEnded\n");


	char t1[] = "когда не в шутку занемог,";
	char t2[] = "он уважать себя заставил";


	textSort (ptext, &strncmp_);
	printText (ptext, nlines + 1);
}


void textSort (gnirts ptext[NLines], int (*cmp)(const gnirts &str1, const gnirts &str2))
{
	for (int j = 0; j < NLines; j ++)
	{
		for (int i = 0; i < NLines - j - 1; i++)
		{
			int delta = (*cmp) (ptext[i + 1], ptext[i]);

			if (delta < 0)
			{

				auto temp = ptext[i].str;
				ptext[i].str = ptext[i + 1].str;
				ptext[i + 1].str = temp;
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int strncmp_ (const gnirts &str1, const gnirts &str2)
{
	VerifyPtr (&str1);
	VerifyPtr (&str2);
	VerifyPtr (str1.str);
	VerifyPtr (str2.str);

	int n1 = 0;
	int n2 = 0;

	for (int n = 0; n < NLines; n++)
	{
		while (!isalnum ( char (str1.str[n1])) && str1.str[n1] != '\n')
        {


			if (n1 < str1.len)
			{
				n1++;
			}

        }
		while (!isalnum ( char (str2.str[n2])) && str2.str[n2] != '\n')
		{
			if (n2 < str2.len)
				n2++;
		}



		if (str1.str[n1] == '\n' && str2.str[n2] == '\n')


		{
			return 0;
		}
		if (str1.str[n1] == '\n')
		{
			return -1;
		}
		if (str2.str[n2] == '\n')
		{
			return 1;
		}

		if (str1.str[n1] != '\n')
		{

			if (str1.str[n1] != str2.str[n2])
			{
				return str1.str[n1] - str2.str[n2];
			}
		}

			n1++;

			n2++;
	}





}

int strcmpBack (const gnirts &str1, const gnirts &str2)
{
	VerifyPtr (str1.str);
	VerifyPtr (str2.str);



	int n1 = 0;
	int n2 = 0;

	for (int i = 0; i < LineSize; i++)
	{
        printf ("%d", i);
		while (!isalnum ( char (str1.str[str1.len - n1])) && n1 < str1.len)
		{
			n1++;

		}
		while (!isalnum ( char (str2.str[str2.len - n2])) && n2 < str2.len)
		{
			n2++;
		}

		if (str1.str[str1.len - n1] != str2.str[str2.len - n2])
		{
			return str1.str[str1.len - n1] - str2.str[str2.len - n2];
		}
		n1++;

		n2++;

	}

}


void writeArrText (char *text, gnirts ptext[], FILE *Onegin)
{
    findEOLs (text, ptext, fileSize (Onegin));
    findLen (ptext, fileSize (Onegin));

}


int readText (FILE *Onegin, char *text)
{
	long fSize = fileSize (Onegin);

	int nofchar = fread (text, sizeof (char), fSize, Onegin);
	if (nofchar >= 0)
	{
		text[nofchar] = '\0';
	}

	return findEOLsN_ (text, fileSize (Onegin) + 1);
}



int findEOLsN_ (const char *text, int len)
{
	int nStr = 0;
	for (int i = 0; i < len; i++)
	{
		if (text[i] == '\n')
		{
			nStr++;


		}
		if (text[i] == '\0')
        {
            return nStr;
        }
	}
	return nStr;
}

void findEOLs (char *text, gnirts ptext[], int len)
{
    ptext[0].str = text;
	int nlines = 1;

	for (int i = 0; i < len; i++)
	{
	    if (text[i] == '\0')
        {
            return;
        }
		if (text[i] == '\n')
		{
			ptext[nlines].str = & (text [i + 1]);
			nlines++;

		}

	}
}




void printText (const gnirts ptext[], int len)
{
	for (int i = 0; i < len; i++)
	{
		if (ptext[i].str[0] != 0)
		{
		    if (ptext[i].str)
			printf ("%d:", i);
			printf (" [%p]::", ptext[i].str);
			VerifyPtr (ptext[i].str);
			printf ("|| ");
			printLine (ptext[i].str);
			printf (" ||\n");
		}
	}
	printf ("end\n");
}

void printLine (const char * text)
{

    for (int i = 0; ;i ++)
    {
        if (text[i] == '\n') break;
        if (text[i] == '\0') break;

        printf ("%c", text[i]);

    }

}



void findLen (gnirts ptext[NLines], int textLen)
{
	for (int i = 0; i < findEOLs (text, ptext, textLen); i++)
	{
		ptext[i].len = ptext[i + 1].str - ptext[i].str;
	}
}




long fileSize (const char *nameOfFile)
{
	struct stat buff = {};
	buff.st_size = -1;

	stat (nameOfFile, &buff);

	return buff.st_size;

}

long fileSize (FILE *File)
{
	struct stat buff = {};
	buff.st_size = -1;

	fstat (_fileno (File), &buff);

	return buff.st_size;

}

void sortStart (const char *ptext[NLines])
{
	for (int j = 0; j < NLines; j ++)
	{
		for (int i = 0; i < NLines - j - 1; i++)
		{
			int delta = 3;

			if (delta < 0)
			{

				const char *temp = ptext[i];
				ptext[i] = ptext[i + 1];
				ptext[i + 1] = temp;
			}
		}
	}
}




void rhymeSort (char *ptext[NLines])
{
	int l1 = 0;
	int l2 = 0;

	for (int j = 0; j < NLines - 1; j ++)
	{
		for (int i = 0; i < NLines - j - 1; i++)
		{
			l1 = strlen (ptext[i]);
			l2 = strlen (ptext[i + 1]);
			int delta = 3;
			if (delta < 0)
			{

				char *temp = ptext[i];
				ptext[i] = ptext[i + 1];
				ptext[i + 1] = temp;
			}
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
			{
				swapStr (arr[i], arr[i+1]);
			}
		}
		if (sorted == true) break;
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

	for (int i = 0; i < Size; i++)
	{
		m1[i] = m2[i];
	}
}


void deleteEOL (char text [LineSize])
{
	int len = strlen (text);
	if (len - 1 >= 0)
	{
		if (text[len-1] == '\n')
		{
			text[len - 1] = '\0';
		}
	}
}



void bubleUnittest ()
{
	char arr[][LineSize] = {"4", "3", "5", "1", "2"};
	bubleCheck (arr, 5);
}


