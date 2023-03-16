#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
#include <optional>
#include<string>
#include <unordered_set>
#include<algorithm>




class Iterator
{
public:
	Iterator(std::istream& stream);

	void printMatrix();
	void printAnswer();

protected:
	Iterator(const Iterator& prevMatrix, const size_t& expansion_string_element_index);
	void calculate();

private:
	std::vector<std::vector<int32_t>> matrix;
	size_t size;
	std::optional<int64_t> determinant;
	std::vector<Iterator> minors;
};
template <typename Type, typename IIterator>
void printUniqueElements(const IIterator& begin, const IIterator& end)
{
	std::unordered_set<Type> elements;
	std::copy(begin, end, std::inserter(elements, elements.end()));
	std::copy(elements.begin(), elements.end(), std::ostream_iterator<Type>(std::cout, ", "));
	std::cout << std::endl;
}


template<typename T>
void printContainer(const T& cont)
{
	const size_t size = cont.size();
	std::for_each(cont.begin(), cont.end(),
		[count = 0, &size](const auto& i) mutable
	{
		count++;
		std::cout << i;
		if (count != size) std::cout << ", ";
	});
	std::cout << std::endl;
}
