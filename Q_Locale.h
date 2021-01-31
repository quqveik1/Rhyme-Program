#pragma once

#include "Windows.h"
#include <locale.h>

void setRussianLocale ();

//!	@brief Устанавливает русский язык в консолях
//!
//!
//! @return НИЧЕГО и не надо:)
//! @note Использовать его надо если твоя консоль внезапно вместо русских символов выводит дичь
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