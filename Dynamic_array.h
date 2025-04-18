//
// Created by islam on 18.04.2025.
//

#ifndef LABA_2_DYNAMIC_ARRAY_H
#define LABA_2_DYNAMIC_ARRAY_H


#include<iostream>

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
    ~Dynamic_array();
    int resize(int size);
    void push_back(T val) {
        resize(m_size + 1);
        m_data[m_size - 1] = val;
    }
    int size() const;
    T & operator[] (int i){
        return m_data[i];
    }
};



#endif //LABA_2_DYNAMIC_ARRAY_H
