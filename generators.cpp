#include "generators.h"
#include "person.h"
#include <coroutine>
#include <filesystem>
#include <fstream>

template<>
std::experimental::generator<Person_t> Generate(int count)
{
	if (count < 0)
	{
		co_return;
	}

	std::filesystem::path dataset_path = std::filesystem::current_path();
	dataset_path.append("dataset\\");

	std::ifstream names_file(dataset_path.string() + "names.txt");
	std::ifstream surnames_file(dataset_path.string() + "surnames.txt");
	std::ifstream addresses_file(dataset_path.string() + "addresses.txt");

	if (!names_file.is_open() || !surnames_file.is_open() || !addresses_file.is_open())
	{
		co_return;
	}

	auto seekg_random_line = [](std::ifstream& file) -> void
		{
			file.seekg(0);
			int line_count = std::count(std::istreambuf_iterator(file), std::istreambuf_iterator<char>(), '\n');
			int line_number = rand() % line_count;
			file.seekg(std::ios::beg);
			for (int i = 0; i < line_number; ++i)
			{
				file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		};

	for (int i = 0; i < count; ++i)
	{
		seekg_random_line(names_file);
		seekg_random_line(surnames_file);
		seekg_random_line(addresses_file);

		Person_t person;

		std::getline(names_file, person.name);
		std::getline(surnames_file, person.surname);
		person.age = rand() % 100 + 1;
		std::getline(addresses_file, person.address);
		person.phone_number = std::format("+{} ({}) {}-{}-{}",
			rand() % 1000, rand() % 1000, rand() % 1000, rand() % 100, rand() % 100);

		co_yield person;
	}

	names_file.close();
	surnames_file.close();
	addresses_file.close();
}
