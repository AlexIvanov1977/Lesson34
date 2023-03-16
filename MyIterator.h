#pragma once
#include <stdexcept>
#include <cstddef>
#include <algorithm>

namespace Simple
{

    template <typename T>
    class Vector
    {
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

    public:
        /* The iterator */
        class MyIterator
        {
            using value_type = T;
            using difference_type = std::ptrdiff_t;
            using pointer = T*;
            using reference = T&;
            using iterator_category = std::random_access_iterator_tag;

        public:
            MyIterator() = default;
            MyIterator(T* pData) : m_ptr(pData) {}

            reference       operator*() { return *m_ptr; }
            const reference& operator*()            const { return *m_ptr; }
            pointer         operator->() { return m_ptr; }
            const pointer   operator->()            const { return m_ptr; }
            reference       operator[](int offset) { return m_ptr[offset]; }
            const reference operator[](int offset)  const { return m_ptr[offset]; }

            MyIterator& operator++() { ++m_ptr; return *this; }
            MyIterator& operator--() { --m_ptr; return *this; }
            MyIterator operator++(int) { MyIterator it(*this); ++m_ptr; return *this; }
            MyIterator operator--(int) { MyIterator it(*this); --m_ptr; return *this; }

            MyIterator& operator+=(int offset) { m_ptr += offset; return *this; }
            MyIterator& operator-=(int offset) { m_ptr -= offset; return *this; }

            MyIterator operator+(int offset) const { MyIterator it(*this); return it += offset; }
            MyIterator operator-(int offset) const { MyIterator it(*this); return it -= offset; }

            difference_type operator-(const MyIterator& other) const { return m_ptr - other.m_ptr; }

            bool operator<  (const MyIterator& other) const { return m_ptr < other.m_ptr; }
            bool operator<= (const MyIterator& other) const { return m_ptr <= other.m_ptr; }
            bool operator>  (const MyIterator& other) const { return m_ptr > other.m_ptr; }
            bool operator>= (const MyIterator& other) const { return m_ptr >= other.m_ptr; }
            bool operator== (const MyIterator& other) const { return m_ptr == other.m_ptr; }
            bool operator!= (const MyIterator& other) const { return m_ptr != other.m_ptr; }

        private:
            T* m_ptr{ nullptr };
        };

    public:
        // constructors
        Vector() = default;
        explicit Vector(std::size_t nCapacity);

        void insert(value_type value);

        std::size_t size() const;

        reference operator[](std::size_t nIndex);
        const reference operator[](std::size_t nIndex) const;

        MyIterator begin();
        MyIterator end();

    private:
        void resizeIfRequired();
        void detectCapacity();
        void allocateMemory();

    private:
        std::shared_ptr<value_type[]> m_pData{ nullptr };
        std::size_t m_nSize = 0;
        std::size_t m_nCapacity = 0;
    };

    /*
     * Vector methods
     **/
    template <typename T>
    Vector<T>::Vector(std::size_t nCapacity)
    {
        if (nCapacity > 0)
        {
            m_nCapacity = nCapacity;
            m_pData = std::make_unique<value_type[]>(nCapacity);
        }
    }

    template <typename T>
    void Vector<T>::insert(value_type value)
    {
        resizeIfRequired();

        
        m_pData[m_nSize] = std::move(value);
        ++m_nSize;
    }

    template <typename T>
    std::size_t Vector<T>::size() const
    {
        return m_nSize;
    }

    template <typename T>
    typename Vector<T>::reference Vector<T>::operator[](std::size_t nIndex)
    {
        if (nIndex >= m_nSize)
            throw std::exception("Index out of range");

        return m_pData[nIndex];
    }

    template <typename T>
    typename const Vector<T>::reference Vector<T>::operator[](std::size_t nIndex) const
    {
        return operator[](nIndex);
    }

    template <typename T>
    typename Vector<T>::MyIterator Vector<T>::begin()
    {
        return Vector<T>::MyIterator{ m_pData.get() };
    }

    template <typename T>
    typename Vector<T>::MyIterator Vector<T>::end()
    {
        return Vector<T>::MyIterator{ m_pData.get() + m_nSize };
    }

    template <typename T>
    void Vector<T>::resizeIfRequired()
    {
        if (m_nSize == m_nCapacity)
        {
            detectCapacity();
            allocateMemory();
        }
    }

    template <typename T>
    void Vector<T>::detectCapacity()
    {
        if (m_nCapacity == 0)
        {
            m_nCapacity = 1;
            m_pData = std::make_unique<T[]>(m_nCapacity);
        }
        else
            m_nCapacity *= 2;
    }

    template <typename T>
    void Vector<T>::allocateMemory()
    {
        // allocate new memory
        auto pNewMemory = new T[m_nCapacity];

        // move data to there
        std::move(m_pData.get(), m_pData.get() + m_nSize, pNewMemory);

        m_pData.reset(pNewMemory);
    }

} // namespace Simple