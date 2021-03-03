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


char *readText (FILE *Onegin, char *text, gnirts ptext[]);
void printText (const gnirts ptext[], int len);
void deleteEOL (char text [LineSize]);
void sortStart (const char *ptext[NLines]);
void strcpy_ (char m1[], char m2[], const int Size);
int strncmp_ (gnirts str1, gnirts str2);
void swapStr (char str1[], char str2[]);

int strcmpBack (const gnirts &str1, const gnirts &str2);
void rhymeSort (char *ptext[NLines]);
void textSort (gnirts ptext[NLines], int (*cmp)(const gnirts &str1, const gnirts &str2));
void findLen (gnirts ptext[NLines]);
long fileSize (const char *nameOfFile);
long fileSize (FILE *File);
void findEOLs (char *text, gnirts ptext[], int len);
int findnEOLs (const char *text, int len);

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

	int nlines = findnEOLs (text, fSize);
	gnirts *ptext = new gnirts[nlines + 1] {};

	printf ("nlines: %d\n", nlines);

	//ptext[0].str = "asdas";


	//printf ("\n%ld\n", __cplusplus);

	readText (Onegin, text, ptext);
	fclose (Onegin);
    //cout << text << endl;



	//findLen (ptext);
	//strncmp_ (text[0], text[2], -1);


	printText (ptext, nlines + 1);
	printf ("printTextIsEnded\n");
	//printf ("%d||isPunct: %d; isalpha: %d isnum^ %d\n", unsigned char ('«'), ispunct (unsigned char ('М')) || !isalnum(unsigned char ('М')), isalpha ('Ь'), !isalnum(unsigned char ('«')));

	char t1[] = "когда не в шутку занемог,";
	char t2[] = "он уважать себя заставил";

	//printf ("strncmp_: %d\n", strncmp_ (t1, t2, LineSize));

	textSort (ptext, &strcmpBack);
	printText (ptext, nlines + 1);


   //bubleUnittest ();


}

void findLen (gnirts ptext[NLines])
{
	for (int i = 0; i < NLines; i++)
	{
		ptext[i].len = strlen (ptext[i].str);
	}
}


char *readText (FILE *Onegin, char *text, gnirts ptext[])
{
	//int c = 0;
	long fSize = fileSize (Onegin);

	int nofchar = fread (text, sizeof (char), fSize, Onegin);
	if (nofchar >= 0)
	{
		text[nofchar] = '\0';
	}
	findEOLs (text, ptext, nofchar + 1);

	//ptext[1].str = (char *) text[c];
	//c += strlen ((char *)text[c]);
	 /*
	for (int i = 0; i < NLines; i++)
	{

	}
	findLen (ptext);
		*/

	return (char *) text;
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

void bubleUnittest ()
{
	char arr[][LineSize] = {"4", "3", "5", "1", "2"};
	bubleCheck (arr, 5);
	//printText (arr);
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
			printf ("||%s||\n", ptext[i].str);
		}
	}
	printf ("end\n");
}

void sortStart (const char *ptext[NLines])
{
	//equating (sortText[0], text[0], NLines);
	for (int j = 0; j < NLines; j ++)
	{
		for (int i = 0; i < NLines - j - 1; i++)
		{
			int delta = 3;//strncmp_ (ptext[i + 1], ptext[i]);

			if (delta < 0)
			{

				const char *temp = ptext[i];
				ptext[i] = ptext[i + 1];
				ptext[i + 1] = temp;

				//swapStr ((char *)ptext[i], (char *)ptext[i + 1]);
			}
			//sortText [i] = sortText[i + 1];
			//sortText [i] = copy;

			//printText (text);
			//printf ("\n");
		}
	}
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

				//swapStr ((char *)ptext[i], (char *)ptext[i + 1]);
			}
			//sortText [i] = sortText[i + 1];
			//sortText [i] = copy;

			//printText (text);
			//printf ("\n");
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
			int delta = 3; //strcmpBack (ptext[i], ptext[i + 1]);

			if (delta < 0)
			{

				char *temp = ptext[i];
				ptext[i] = ptext[i + 1];
				ptext[i + 1] = temp;

				//swapStr ((char *)ptext[i], (char *)ptext[i + 1]);
			}
		}
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

		/*
		if (str1[l1 - n1] == '\0' && str2[l2 - n2] == '\0')
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
		*/
		//if (n1 > l1)   return -1;
		//if (n2 > l2)   return 1;

		if (str1.str[str1.len - n1] != str2.str[str2.len - n2])
		{
			//printf ("str1[%d]: , str2[%d]: ", n1, n2);
			//printf ("%d", l1 - i);
			return str1.str[str1.len - n1] - str2.str[str2.len - n2];
		}
		n1++;

		n2++;

	}

}

void bubleCheck (char arr[][LineSize], size_t size)
{
	for (int j = 0; j < NLines - 1; j ++)
	{
		bool sorted = true;
		for (int i = 0; i < NLines - j - 1; i++)
		{
			//if (strncmp_ (arr[i], arr[i + 1]))
			{
				swapStr (arr[i], arr[i+1]);
			}
		}
		if (sorted == true) break;
	}
}

int strncmp_ (gnirts str1, gnirts str2)
{
	VerifyPtr (str1.str);
	VerifyPtr (str2.str);

	//int l1 = strlen (str1);
	//int l2 = strlen (str2);

	int n1 = 0;
	int n2 = 0;

	for (int n = 0; n < NLines; n++)
	{
		while (!isalnum ( char (str1.str[n1])) && str1.str[n1] != '\0')
        {


			if (n1 < str1.len)
			{
				n1++;
			}

		}
	}
		while (!isalnum ( char (str2.str[n2])) && str2.str[n2] != '\0')
		{
			if (n2 < str2.len)
				n2++;
		}



		if (str1.str[n1] == '\0' && str2.str[n2] == '\0')
		{
			return 0;
		}
		if (str1.str[n1] == '\0')
		{
			return -1;
		}
		if (str2.str[n2] == '\0')
		{
			return 1;
		}

		if (str1.str[n1] != '\0')
		{

			if (str1.str[n1] != str2.str[n2])
			{
				//printf ("str1[%d]: , str2[%d]: ", n1, n2);
				//printf ("%d", n);
				return str1.str[n1] - str2.str[n2];
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

int findnEOLs (const char *text, int len)
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
		    //text[i] = '\0';
			ptext[nlines].str = & (text [i + 1]);
			nlines++;

		}

	}
}


