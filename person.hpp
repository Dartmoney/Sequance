//
// Created by islam on 21.06.2025.
//

#ifndef LABA3_PERSON_HPP
#define LABA3_PERSON_HPP
#pragma once
#include <ctime>
#include <cstring>
#include <iostream>


struct PersonID {
    int value;

    bool operator<(const PersonID& o) const { return value < o.value; }
    bool operator==(const PersonID& o) const { return value == o.value; }
    bool operator>(const PersonID& o) const { return o < *this; }

    friend std::ostream& operator<<(std::ostream& os, const PersonID& id) {
        return os << id.value;
    }
};


class Person {
public:
    PersonID    id;
    std::string firstName;
    std::string middleName;
    std::string lastName;
    std::time_t birthDate;

    Person()
            : id{0}, firstName(), middleName(), lastName(), birthDate(0)
    {}

    Person(PersonID   id_,
           const std::string& fn,
           const std::string& mn,
           const std::string& ln,
           std::time_t bd)
            : id(id_), firstName(fn), middleName(mn), lastName(ln), birthDate(bd)
    {}

    Person(const Person&)            = default;
    Person(Person&&)                 = default;
    Person& operator=(const Person&) = default;
    Person& operator=(Person&&)      = default;

    virtual ~Person() = default;

    bool operator<(const Person& o)  const { return id < o.id; }
    bool operator==(const Person& o) const { return id == o.id; }
    bool operator>(const Person& o)  const { return o < *this; }

    friend std::ostream& operator<<(std::ostream& os, const Person& p) {
        os << "[" << p.id << "] "
           << p.lastName << " "
           << p.firstName << " "
           << p.middleName;
        return os;
    }

    virtual void Print() const {
        std::cout << *this
                  << "  (born " << std::asctime(std::localtime(&birthDate)) << ")";
    }
};


class Student : public Person {
public:
    std::string studentCard;

    Student() = default;
    Student(PersonID id_,
            const std::string& fn,
            const std::string& mn,
            const std::string& ln,
            std::time_t bd,
            const std::string& card)
            : Person(id_, fn, mn, ln, bd),
              studentCard(card)
    {}

    Student(const Student&)            = default;
    Student(Student&&)                 = default;
    Student& operator=(const Student&) = default;
    Student& operator=(Student&&)      = default;

    ~Student() override = default;

    void Print() const override {
        Person::Print();
        std::cout << "  [StudentCard: " << studentCard << "]\n";
    }
};


class Professor : public Person {
public:
    std::string employeeNo;

    Professor() = default;
    Professor(PersonID id_,
              const std::string& fn,
              const std::string& mn,
              const std::string& ln,
              std::time_t bd,
              const std::string& empNo)
            : Person(id_, fn, mn, ln, bd),
              employeeNo(empNo)
    {}

    Professor(const Professor&)            = default;
    Professor(Professor&&)                 = default;
    Professor& operator=(const Professor&) = default;
    Professor& operator=(Professor&&)      = default;

    ~Professor() override = default;

    void Print() const override {
        Person::Print();
        std::cout << "  [EmployeeNo: " << employeeNo << "]\n";
    }
};
#endif //LABA3_PERSON_HPP
