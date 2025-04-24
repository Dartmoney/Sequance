//
// Created by islam on 18.04.2025.
//

#ifndef LABA_2_DYNAMIC_ARRAY_HPP
#define LABA_2_DYNAMIC_ARRAY_HPP


#include<iostream>
#include "Error.hpp"
using namespace std;

template <typename T>
class Dynamic_array
{
private:
    int m_size;
    int m_capacity;
    T * m_data;

public:
    Dynamic_array();
    Dynamic_array(const Dynamic_array<T> & a);
    Dynamic_array(int size);
    void DynamicArray(T* items, int count);
    ~Dynamic_array();
    void resize(int size);
    void Set(int index, T value);
    void push_back(T val) {
        resize(m_size + 1);
        m_data[m_size - 1] = val;
    }
    int size() const;
    T & operator[] (int i){
        if ((i>=m_size) || (i<0))
            throw IndexOutOfRange();
        return m_data[i];
    }
};


template <typename T>
Dynamic_array<T>::Dynamic_array() {
    m_size = 0;
    m_capacity = 0;
    m_data = NULL;
}
template <typename T>
Dynamic_array<T>::Dynamic_array(const Dynamic_array<T> &a) {
    m_size = a.m_size;
    m_capacity = m_size;
    m_data = NULL;
    if (m_size != 0)
        m_data = new T[m_size];
    else
        m_data = 0;
    for (int i = 0; i < m_size; ++i)
        m_data[i] = a.m_data[i];
}
template <typename T>
Dynamic_array<T>::Dynamic_array(int size) {
    m_size = size;
    m_capacity = size;
    if (size != 0)
        m_data = new T[size];
    else
        m_data = 0;
}

template <typename T>
void Dynamic_array<T>::resize(int size) {
    if (size > m_capacity) {
        int new_capacity = max(size, m_size * 2);
        T *new_data = new T[new_capacity];
        for (int i = 0; i < m_size; ++i)
            new_data[i] = m_data[i];
        delete[] m_data;
        m_data = new_data;
        m_capacity = new_capacity;
    }
    m_size = size;
}
template <typename T>
Dynamic_array<T>::~Dynamic_array()
{
    if (m_data)
        delete[] m_data;
}
template <typename T>
int Dynamic_array<T>::size() const{
    return m_size;
}
template <typename T>
void Dynamic_array<T>::DynamicArray(T* items, int count)
{
    m_size = count;
    m_capacity = m_size;
    m_data = NULL;
    if (m_size != 0)
        m_data = new T[m_size];
    else
        m_data = 0;
    for (int i=0;i<m_size;++i)
    {
        m_data[i] = items[i];
    }

}
template <typename T>
void Dynamic_array<T>::Set(int index, T value)
{
    if (index >= m_size)
        throw IndexOutOfRange();
    m_data[index] = value;
}
template<typename T>
ostream &operator<<(ostream &out, Dynamic_array<T> a) {
    for (int i = 0; i < a.size(); ++i)
        out << a[i] << " ";
    return out;
}

#endif //LABA_2_DYNAMIC_ARRAY_HPP
