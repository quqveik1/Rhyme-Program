#pragma once

#include "Windows.h"
#include <locale.h>

void setRussianLocale ();

//!	@brief ������������� ������� ���� � ��������
//!
//!
//! @return ������ � �� ����:)
//! @note ������������ ��� ���� ���� ���� ������� �������� ������ ������� �������� ������� ����
//! 
//! @usage @code
//!				setRussianLocale ();
//!@endcode

void setRussianLocale ()
{
	SetConsoleCP       (1251);
    SetConsoleOutputCP (1251);
	setlocale (LC_ALL,     "Russian");
	setlocale (LC_NUMERIC, "C");
}