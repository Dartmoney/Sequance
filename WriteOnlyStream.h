//
// Created by imako on 21.11.2025.
//

#ifndef LABA3_WRITEONLYSTREAM_H
#define LABA3_WRITEONLYSTREAM_H


#include <cstddef>
#include <string>
#include <fstream>
#include <functional>
#include "Sequance.hpp"
#include "Error.hpp"

template<typename T>
using Serializer = std::function<std::string(const T&)>;

template <class T>
class WriteOnlyStream {
private:
    Sequence<T>* seq = nullptr;

    std::ofstream outFile;
    Serializer<T> serializer;

    bool toSeq = false;
    bool toFile = false;

    size_t position = 0;
    bool isOpen = false;

public:
    explicit WriteOnlyStream(Sequence<T>* s)
        : seq(s), toSeq(true), position(0)
    {
        if (!seq) throw std::invalid_argument("Sequence is null");
    }

    WriteOnlyStream(const std::string& filename, Serializer<T> ser)
        : serializer(std::move(ser)), toFile(true), position(0)
    {
        outFile.open(filename);
        if (!outFile.is_open()) {
            throw std::runtime_error("Cannot open file: " + filename);
        }
    }

    WriteOnlyStream(const WriteOnlyStream&) = delete;
    WriteOnlyStream& operator=(const WriteOnlyStream&) = delete;

    ~WriteOnlyStream() {
        try {
            Close();
        } catch (...) {
        }
    }


    size_t GetPosition() const {
        return position;
    }

    size_t Write(T value) {
        if (!isOpen)
            throw std::logic_error("Stream is not open");

        if (toSeq) {
            seq->Append(value);
            ++position;
            return position;
        }

        if (toFile) {
            if (!serializer) {
                throw std::logic_error("Serializer is not set for file stream");
            }
            outFile << serializer(value) << "\n";
            if (!outFile.good()) {
                throw std::runtime_error("Error writing to file");
            }
            ++position;
            return position;
        }

        throw std::logic_error("Unknown write target");
    }

    void Open() {
        if (isOpen) return;
        isOpen = true;
    }

    void Close() {
        if (!isOpen) return;
        if (toFile && outFile.is_open()) {
            outFile.close();
        }
        isOpen = false;
    }
};


#endif //LABA3_WRITEONLYSTREAM_H