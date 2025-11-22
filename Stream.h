//
// Created by imako on 21.11.2025.
//

#ifndef LABA3_STREAM_H
#define LABA3_STREAM_H

#include <cstddef>
#include <fstream>
#include <string>
#include <functional>

#include "Sequance.hpp"
#include "LazySequence.hpp"
#include "Error.hpp"


template <typename T>
class ReadOnlyStream {
public:
    virtual ~ReadOnlyStream() = default;

    virtual void Open() = 0;

    virtual void Close() = 0;

    virtual bool IsEndOfStream() const = 0;

    virtual T Read() = 0;

    virtual std::size_t GetPosition() const = 0;

    virtual bool IsCanSeek() const = 0;

    virtual std::size_t Seek(std::size_t index) = 0;

    virtual bool IsCanGoBack() const = 0;
};

template <typename T>
class WriteOnlyStream {
public:
    virtual ~WriteOnlyStream() = default;

    virtual void Open() = 0;

    virtual void Close() = 0;

    virtual std::size_t GetPosition() const = 0;

    virtual std::size_t Write(const T& value) = 0;
};


template <typename T>
class SequenceReadOnlyStream : public ReadOnlyStream<T> {
private:
    Sequence<T>* seq;
    bool ownSequence;
    std::size_t pos;
    bool opened;

public:
    explicit SequenceReadOnlyStream(Sequence<T>* sequence, bool own = false)
        : seq(sequence), ownSequence(own), pos(0), opened(false) {}

    ~SequenceReadOnlyStream() override {
        if (ownSequence) {
            delete seq;
        }
    }

    void Open() override {
        pos = 0;
        opened = true;
    }

    void Close() override {
        opened = false;
    }

    bool IsEndOfStream() const override {
        if (!opened) return true;
        return pos >= static_cast<std::size_t>(seq->GetLength());
    }

    T Read() override {
        if (!opened) {
            throw std::logic_error("Stream is not opened");
        }
        if (IsEndOfStream()) {
            throw EndOfStream();
        }
        T value = seq->Get(static_cast<int>(pos));
        ++pos;
        return value;
    }

    std::size_t GetPosition() const override {
        return pos;
    }

    bool IsCanSeek() const override {
        return true;
    }

    std::size_t Seek(std::size_t index) override {
        if (!opened) {
            throw std::logic_error("Stream is not opened");
        }
        if (index > static_cast<std::size_t>(seq->GetLength())) {
            index = static_cast<std::size_t>(seq->GetLength());
        }
        pos = index;
        return pos;
    }

    bool IsCanGoBack() const override {
        return true;
    }
};


template <typename T>
class LazySequenceReadOnlyStream : public ReadOnlyStream<T> {
private:
    LazySequence<T>* lazy;
    bool ownSequence;
    std::size_t pos;
    bool opened;

public:
    explicit LazySequenceReadOnlyStream(LazySequence<T>* sequence, bool own = false)
        : lazy(sequence), ownSequence(own), pos(0), opened(false) {};

    ~LazySequenceReadOnlyStream() override {
        if (ownSequence) {
            delete lazy;
        }
    }

    void Open() override {
        pos = 0;
        opened = true;
    }

    void Close() override {
        opened = false;
    }

    bool IsEndOfStream() const override {
        if (!opened) return true;


        int length = lazy->GetLength();
        return pos >= static_cast<std::size_t>(length);
    }

    T Read() override {
        if (!opened) {
            throw std::logic_error("Stream is not opened");
        }
        if (IsEndOfStream()) {
            throw EndOfStream();
        }
        T value = lazy->Get(static_cast<int>(pos));
        ++pos;
        return value;
    }

    std::size_t GetPosition() const override {
        return pos;
    }

    bool IsCanSeek() const override {
        return true;
    }

    std::size_t Seek(std::size_t index) override {
        if (!opened) {
            throw std::logic_error("Stream is not opened");
        }
        int length = lazy->GetLength();
        if (index > static_cast<std::size_t>(length)) {
            index = static_cast<std::size_t>(length);
        }
        pos = index;
        return pos;
    }

    bool IsCanGoBack() const override {
        return true;
    }
};


class FileReadOnlyCharStream : public ReadOnlyStream<char> {
private:
    std::string filename;
    std::ifstream file;
    std::size_t pos;
    bool opened;

public:
    explicit FileReadOnlyCharStream(const std::string& path)
        : filename(path), pos(0), opened(false) {}

    void Open() override {
        if (opened) return;
        file.open(filename, std::ios::binary);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file for reading: " + filename);
        }
        pos = 0;
        opened = true;
    }

    void Close() override {
        if (!opened) return;
        file.close();
        opened = false;
    }

    bool IsEndOfStream() const override {
        if (!opened) return true;
        return file.eof();
    }

    char Read() override {
        if (!opened) {
            throw std::logic_error("Stream is not opened");
        }
        char c;
        if (!file.get(c)) {
            throw EndOfStream();
        }
        ++pos;
        return c;
    }

    std::size_t GetPosition() const override {
        return pos;
    }

    bool IsCanSeek() const override {
        return true;
    }

    std::size_t Seek(std::size_t index) override {
        if (!opened) {
            throw std::logic_error("Stream is not opened");
        }
        file.clear();
        file.seekg(0, std::ios::beg);
        pos = 0;

        char c;
        for (std::size_t i = 0; i < index; ++i) {
            if (!file.get(c)) {
                break;
            }
            ++pos;
        }
        return pos;
    }

    bool IsCanGoBack() const override {
        return true;
    }
};


class FileWriteOnlyCharStream : public WriteOnlyStream<char> {
private:
    std::string filename;
    std::ofstream file;
    std::size_t pos;
    bool opened;

public:
    explicit FileWriteOnlyCharStream(const std::string& path)
        : filename(path), pos(0), opened(false) {}

    void Open() override {
        if (opened) return;
        file.open(filename, std::ios::binary | std::ios::trunc);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file for writing: " + filename);
        }
        pos = 0;
        opened = true;
    }

    void Close() override {
        if (!opened) return;
        file.close();
        opened = false;
    }

    std::size_t GetPosition() const override {
        return pos;
    }

    std::size_t Write(const char& value) override {
        if (!opened) {
            throw std::logic_error("Stream is not opened");
        }
        file.put(value);
        if (!file) {
            throw std::runtime_error("Write error");
        }
        ++pos;
        return pos;
    }
};
#endif //LABA3_STREAM_H