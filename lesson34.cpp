// lesson34.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
/*
1. Реализовать собственный класс итератора, с помощью которого можно будет проитерироваться по диапазону целых чисел в цикле for-range-based.

2. Создать шаблонную функцию, которая принимает итераторы на начало и конец последовательности слов,
и выводящую в консоль список уникальных слов (если слово повторяется больше 1 раза, то вывести его надо один раз).
Продемонстрировать работу функции, передав итераторы различных типов.

3. Реализовать класс итератора для вектора.

*/

#include <iostream>
#include "Matrix.h"
#include"MyIterator.h"



int main()

{
	setlocale(LC_ALL, "rus");
	std::cout << "Задание 1" << std::endl;
	std::cout << "Работа с Классом Matrix:" << std::endl << std::endl;
	Iterator mtrx(std::cin);
	std::cout << std::endl;
	mtrx.printMatrix();
	mtrx.printAnswer();

	//-----------------------------------------------------------------------------

	std::cout << "Задание 2" << std::endl;
	std::cout << "Работа с Функцией printUniqueElements:" << std::endl << std::endl;

	std::vector<std::string> strings{ "one", "three", "two", "four", "six", "five", "seven", "one", "three", "six" };
	std::cout << "Исходный контейнер Vector:" << std::endl;
	printContainer(strings);

	std::cout << std::endl << "Результат:" << std::endl;
	printUniqueElements<std::string>(strings.begin(), strings.end());
	std::cout << std::endl;

	std::list<std::string> stringsL{ "one", "three", "two", "four", "six", "five", "seven", "eleven", "three", "ten" };
	std::cout << "Исходный контейнер List:" << std::endl;
	printContainer(stringsL);

	std::cout << std::endl << "Результат:" << std::endl;
	printUniqueElements<std::string>(stringsL.begin(), stringsL.end());
	std::cout << std::endl;
	//----------------------------------------------------------------------------------

	std::cout << "Задание номер 3 , класс итератора для класса вектора" << std::endl;

	try
	{
		Simple::Vector<int> vector;
		vector.insert(8);
		vector.insert(3);
		vector.insert(1);
		vector.insert(7);
		vector.insert(2);
		

		for (auto i : vector)
			std::cout << i << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	std::cout << "Запишем и выведем новый  вектор" << std::endl;

	Simple::Vector<int> v_vector;
	for (int i = 6; i > 0; i--)
	{
		v_vector.insert(i);
		

	}
	for (int i = 0; i < 6; i++)
	{
		
		std::cout << v_vector[i] << std::endl;

	}

	

	
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
