#pragma once
#include <string>

struct Person_t
{
	Person_t()
		: name(), surname(), age(0), address(), phone_number()
	{
	}

	Person_t(std::string_view name, std::string_view surname, int age, std::string_view address, std::string_view phone_number)
		: name(name), surname(surname), age(age), address(address), phone_number(phone_number)
	{
	}

	std::string name;
	std::string surname;
	int age;
	std::string address;
	std::string phone_number;
};
