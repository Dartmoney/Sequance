//
// Created by islam on 24.04.2025.
//

#ifndef ARRAYLIST_HPP
#define ARRAYLIST_HPP
#include "Sequance.hpp"
#include "Linked_List.hpp"
template <typename T>
class ListSequence : public Sequence<T> {
private:
    List<T>* list;
public:

    ListSequence() : list(new List<T>()) {}
    ListSequence(T* items, int count) : list(new List<T>(items, count)) {}
    ListSequence(const ListSequence<T>& other) : list(new List<T>(*other.list)) {}

    ~ListSequence() override { delete list; }

    T GetFirst() const override { return list->GetFirst(); }
    T GetLast() const override { return list->GetLast(); }
    T Get(int index) const override { return list->Get(index); }

    Sequence<T>* GetSubsequence(int start, int end) const override {
        List<T>* subList;
        if ((start < 0) || (end>list->GetLength()))
            throw IndexOutOfRange();
        for (int i=start;i<end;i++)
        {
            subList->insertEnd(list->Get(i));
        }
        return new ListSequence<T>(subList);
    }

    int GetLength() const override { return list->GetLength(); }

    Sequence<T>* Append(T item) override {
        list->insertEnd(item);
    }

    Sequence<T>* Prepend(T item) override
    {
        list->insertEnd(item);
    }
    Sequence<T>* InsertAt(T item, int index)
    {
        list->InsertAt(item,index);
    }
    Sequence<T>* Concat(Sequence<T>* other)
    {
        for (int i=0;i<other->GetLength();i++)
        {
            list->insertEnd(other->Get(i));
        }
    }
};
#endif //ARRAYLIST_HPP
