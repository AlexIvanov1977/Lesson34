#include "Matrix.h"
void clearStream(std::istream& stream)
{
	stream.clear();
	stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

template <typename T>
std::optional<T> getUserInput(std::istream& stream, bool allowZero = false, bool allowNegative = false, bool checkAllinput = false, bool needClearStream = true);
template <typename T>
std::optional<T> getUserInput(std::istream& stream, bool allowZero, bool allowNegative, bool checkAllinput, bool needClearStream)
{
	while (true)
	{
		T input;
		stream >> input;
		if (stream.fail() || (input < 0) && !allowNegative || (input == 0) && !allowZero)
		{
			std::cout << "Ошибка ввода, повторите ввод: ";
			stream.clear();
			stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return std::nullopt;
		}
		else
		{
			if ((stream.peek() != stream.widen('\n')) && checkAllinput)
			{
				std::cout << "Ошибка ввода, повторите ввод: ";
				stream.clear();
				stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				return std::nullopt;
			}
			else
			{
				if (needClearStream)
				{
					stream.clear();
					stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
				return input;
			}
		}
	}
}

Iterator::Iterator(const Iterator& prevMatrix, const size_t& expansion_string_element_index) : determinant(std::nullopt), size(prevMatrix.size - 1)
{
	matrix.reserve(size);
	for (size_t i = 0; i < size; i++)
	{
		matrix.push_back(std::vector<int32_t>());
		matrix[i].reserve(size);
		for (size_t j = 0; j < prevMatrix.size; j++)
		{
			if (expansion_string_element_index != j) matrix[i].push_back(prevMatrix.matrix[i + 1][j]);
		}
	}
	calculate();
}

void Iterator::calculate()
{
	switch (size)
	{
	case 1:
		determinant = matrix[0][0];
		break;
	case 2:
		determinant = matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
		break;
	default:
		minors.reserve(size);
		determinant = 0;
		for (size_t i = 0; i < size; i++)
		{
			minors.push_back(Iterator(*this, i));
			determinant.emplace() = determinant.value() + matrix[0][i] * minors[i].determinant.value() * (i % 2 == 0 ? 1 : (-1));
		}
		break;
	}
}

Iterator::Iterator(std::istream& stream) : determinant(std::nullopt)
{
	std::cout << "Введите размер  матрицы: ";
	size = getUserInput<int32_t>(std::cin).value_or(0);
	std::cout << "Заполните матрицу цифрами: " <<std::endl;;
	matrix.reserve(size);
	for (size_t i = 0; i < size; i++)
	{
		matrix.push_back(std::vector<int32_t>());
		matrix[i].reserve(size);
		for (size_t j = 0; j < size; j++)
		{
			std::optional a = getUserInput<int32_t>(stream, true, true, false, false);
			if (a) matrix[i].push_back(a.value());
			else
			{
				std::cout << std::endl;
				for (size_t ii = 0; ii <= i; ii++)
				{
					for (size_t jj = 0; jj < ((ii < i) ? size : j); jj++)
					{
						std::cout << std::setw(3) << matrix[ii][jj] << std::setw(2) << "";
					}
					if (ii < i) std::cout << std::endl;
				}
				j--;
			}
		}
	}
	clearStream(stream);
	calculate();
}

void Iterator::printMatrix()
{
	for (const auto& i : matrix)
	{
		for (const auto& j : i)
		{
			std::cout << std::setw(3) << j << std::setw(2) << "";
		}
		std::cout << std::endl;
	}
}

void Iterator::printAnswer()
{
	if (determinant) std::cout << "Определитель матрицы = " << determinant.value();
	else std::cout << "Определитель не найден";
	std::cout << std::endl;
}



