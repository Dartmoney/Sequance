//
// Created by imako on 21.11.2025.
//

#ifndef LABA3_READONLYSTREAM_H
#define LABA3_READONLYSTREAM_H

#include <cstddef>
#include <string>
#include <fstream>
#include <functional>
#include "Sequance.hpp"
#include "lazy_sequence.h"
#include "Error.hpp"

template<typename T>
using Deserializer = std::function<T(const std::string&)>;

class EndOfStream : public std::exception {
public:
    const char* what() const noexcept override {
        return "End of stream";
    }
};

template <class T>
class ReadOnlyStream {
private:
    Sequence<T>* seq = nullptr;
    LazySequence<T>* lazySeq = nullptr;

    std::ifstream inFile;
    std::string buffer;
    Deserializer<T> deserializer;

    bool fromFile = false;
    bool fromString = false;
    bool fromSeq = false;
    bool fromLazy = false;

    size_t position = 0;
    size_t length = 0;
    bool canSeek = false;

    bool isOpen = false;

public:
    explicit ReadOnlyStream(Sequence<T>* s)
        : seq(s), fromSeq(true), position(0)
    {
        if (!seq) throw std::invalid_argument("Sequence is null");
        length = seq->GetLength();
        canSeek = true;
    }

    explicit ReadOnlyStream(LazySequence<T>* ls)
        : lazySeq(ls), fromLazy(true), position(0)
    {
        if (!lazySeq) throw std::invalid_argument("LazySequence is null");
        try {
            length = lazySeq->GetLength();
            canSeek = true;
        } catch (...) {
            length = static_cast<size_t>(-1);
            canSeek = false;
        }
    }

    ReadOnlyStream(const std::string& filename, Deserializer<T> deser)
        : deserializer(std::move(deser)), fromFile(true), position(0)
    {
        inFile.open(filename);
        if (!inFile.is_open()) {
            throw std::runtime_error("Cannot open file: " + filename);
        }
        length = 0;
        canSeek = false;
    }

    ReadOnlyStream(const std::string& data, Deserializer<T> deser, bool fromStringFlag)
        : buffer(data), deserializer(std::move(deser)), fromString(true), position(0)
    {
        (void)fromStringFlag;
        length = 0;
        canSeek = false;
    }

    ReadOnlyStream(const ReadOnlyStream&) = delete;
    ReadOnlyStream& operator=(const ReadOnlyStream&) = delete;

    ~ReadOnlyStream() {
        try {
            Close();
        } catch (...) {
        }
    }


    bool IsEndOfStream() const {
        if (!isOpen) return true;

        if (fromSeq || fromLazy) {
            if (length == static_cast<size_t>(-1)) {
                return false;
            }
            return position >= length;
        }

        if (fromFile || fromString) {
            return false;
        }

        return true;
    }

    T Read() {
        if (!isOpen) {
            throw EndOfStream();
        }

        if (fromSeq) {
            if (position >= length)
                throw EndOfStream();
            T value = seq->Get(static_cast<int>(position));
            ++position;
            return value;
        }

        if (fromLazy) {
            if (length != static_cast<size_t>(-1) && position >= length)
                throw EndOfStream();
            T value = lazySeq->Get(static_cast<int>(position));
            ++position;
            return value;
        }

        if (fromFile) {
            std::string line;
            if (!std::getline(inFile, line)) {
                throw EndOfStream();
            }
            ++position;
            if (!deserializer) {
                throw std::logic_error("Deserializer is not set for file stream");
            }
            return deserializer(line);
        }

        if (fromString) {
            throw std::logic_error("Read from string is not implemented yet");
        }

        throw EndOfStream();
    }

    size_t GetPosition() const {
        return position;
    }

    bool IsCanSeek() const {
        return canSeek;
    }

    size_t Seek(size_t index) {
        if (!canSeek)
            throw std::logic_error("Seek is not supported for this stream");

        if (!isOpen)
            throw std::logic_error("Stream is not open");

        if (fromSeq || fromLazy) {
            if (length != static_cast<size_t>(-1) && index > length)
                throw IndexOutOfRange();
            position = index;
            return position;
        }

        throw std::logic_error("Seek not implemented for this source type");
    }

    bool IsCanGoBack() const {
        if (fromSeq || fromLazy) return true;
        return false;
    }


    void Open() {
        if (isOpen) return;
        isOpen = true;
    }

    void Close() {
        if (!isOpen) return;

        if (fromFile && inFile.is_open()) {
            inFile.close();
        }
        isOpen = false;
    }
};



#endif //LABA3_READONLYSTREAM_H