#include <iostream>
#include "Dynamic_array.hpp"
#include "Linked_List.hpp"
#include "ListNode.h"
template <typename T>
class Sequence {
public:
    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
    virtual Sequence<T>* GetSubsequence(size_t start, size_t end) const = 0;
    virtual ~Sequence() = default;
};
template <typename T>
class ArraySequence : public Sequence<T> {
private:
    Dynamic_array<T> array;
public:
    T GetFirst() const override {
        return array[0];
    }
};
class ListSequnce
        {

};

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
    std::cout << "C++ is a general-purpose programming language with a bias towards systems programming that";
    List<int> s;
    s.insertBegin(8);
    s.insertEnd(2);
    s.insertEnd(3);
    s.print();
    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.