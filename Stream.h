//
// Created by imako on 21.11.2025.
//

#ifndef LABA3_STREAM_H
#define LABA3_STREAM_H

#include <cstddef>
#include <string>
#include <functional>
#include <fstream>
#include <memory>
#include "Sequance.hpp"
#include "lazy_sequence.h"
#include "Dynamic_array.hpp"
#include "Error.hpp"

template<typename T>
using Deserializer = std::function<T(const std::string&)>;

template<typename T>
using Serializer = std::function<std::string(const T&)>;



template<typename T>
class ReadOnlyStream {
private:
    enum class SourceKind {
        None,
        SequencePtr,
        LazySequencePtr,
        StringSource,
        FileSource,
        OtherStream
    };

    SourceKind kind = SourceKind::None;


    std::shared_ptr<Sequence<T>> seqSource;
    std::shared_ptr<LazySequence<T>> lazySource;

    std::string rawString;
    std::string fileName;
    Deserializer<T> deserializer;

    std::weak_ptr<ReadOnlyStream<T>> otherStream;
    mutable size_t position = 0;
    mutable bool opened = false;
    mutable bool eof = false;

    mutable std::ifstream fileStream;

public:
    ReadOnlyStream() = default;

    explicit ReadOnlyStream(std::shared_ptr<Sequence<T>> seq)
     : kind(SourceKind::SequencePtr), seqSource(std::move(seq)) {}

    explicit ReadOnlyStream(std::shared_ptr<LazySequence<T>> lazy)
         : kind(SourceKind::LazySequencePtr), lazySource(std::move(lazy)) {}

    ReadOnlyStream(const std::string& s, Deserializer<T> deser)
        : kind(SourceKind::StringSource), rawString(s), deserializer(std::move(deser)) {}

    ReadOnlyStream(const std::string& file, Deserializer<T> deser, bool /*fromFileTag*/)
        : kind(SourceKind::FileSource), fileName(file), deserializer(std::move(deser)) {}

    explicit ReadOnlyStream(const std::shared_ptr<ReadOnlyStream<T>>& other)
        : kind(SourceKind::OtherStream), otherStream(other) {}



    void Open() {
        if (opened) return;
        opened = true;
        position = 0;
        eof = false;

        if (kind == SourceKind::FileSource) {
            fileStream.open(fileName);
            if (!fileStream.is_open()) {
                throw std::runtime_error("Cannot open file in ReadOnlyStream");
            }
        }
    }

    void Close() {
        if (!opened) return;
        opened = false;
        if (kind == SourceKind::FileSource && fileStream.is_open()) {
            fileStream.close();
        }
    }

    bool IsEndOfStream() const {
        if (!opened) return true;
        return eof;
    }

    size_t GetPosition() const {
        return position;
    }

    bool IsCanSeek() const {
        return (kind == SourceKind::SequencePtr && seqSource != nullptr) ||
               (kind == SourceKind::LazySequencePtr && lazySource != nullptr);
    }

    bool IsCanGoBack() const {
        return IsCanSeek();
    }

    size_t Seek(size_t index) {
        if (!opened) throw std::runtime_error("Stream is not opened");

        if (!IsCanSeek())
            throw std::runtime_error("Seek is not supported for this source");

        switch (kind) {
            case SourceKind::SequencePtr:
                if (!seqSource)
                    throw std::runtime_error("Sequence source is not set");
                if (index > static_cast<size_t>(seqSource->GetLength()))
                    throw IndexOutOfRange();
                break;
            case SourceKind::LazySequencePtr:
                if (!lazySource)
                    throw std::runtime_error("Lazy sequence source is not set");
                if (index > static_cast<size_t>(lazySource->GetLength()))
                    throw IndexOutOfRange();
                break;
            default:
                break;
        }

        position = index;
        eof = false;
        return position;
    }

    T Read() {
        if (!opened) throw std::runtime_error("Stream is not opened");
        if (eof) throw EndOfStream();

        T value{};

        switch (kind) {
            case SourceKind::SequencePtr: {
                int len = seqSource->GetLength();
                if (position >= static_cast<size_t>(len)) {
                    eof = true;

                    throw EndOfStream();
                }
                value = seqSource->Get(static_cast<int>(position));
                ++position;
                break;
            }
            case SourceKind::LazySequencePtr: {
                int len = lazySource->GetLength();
                if (position >= static_cast<size_t>(len)) {
                    eof = true;
                    throw EndOfStream();
                }
                value = lazySource->Get(static_cast<int>(position));
                ++position;
                break;
            }
            case SourceKind::StringSource: {
                if (rawString.empty()) {
                    eof = true;
                    throw EndOfStream();
                }
                size_t pos = rawString.find(' ');
                std::string token = rawString.substr(0, pos);
                if (pos == std::string::npos)
                    rawString.clear();
                else
                    rawString = rawString.substr(pos + 1);

                value = deserializer(token);
                ++position;
                if (rawString.empty())
                    eof = true;
                break;
            }
            case SourceKind::FileSource: {
                if (!fileStream.good()) {
                    eof = true;
                    throw EndOfStream();
                }
                std::string token;
                if (!(fileStream >> token)) {
                    eof = true;
                    throw EndOfStream();
                }
                value = deserializer(token);
                ++position;
                break;
            }
            case SourceKind::OtherStream: {
                auto other = otherStream.lock();
                if (!other)
                    throw std::runtime_error("Other stream expired");
                if (other->IsEndOfStream()) {
                    eof = true;
                    throw EndOfStream();
                }
                value = other->Read();
                ++position;
                break;
            }
            default:
                throw std::runtime_error("No source set for ReadOnlyStream");
        }

        return value;
    }
};


template<typename T>
class WriteOnlyStream {
private:
    enum class TargetKind {
        None,
        SequencePtr,
        FileTarget,
        OtherStream
    };

    TargetKind kind = TargetKind::None;

    std::shared_ptr<Sequence<T>> seqTarget;
    std::string fileName;
    Serializer<T> serializer;
    std::weak_ptr<WriteOnlyStream<T>> otherStream;

    mutable size_t position = 0;
    mutable bool opened = false;

    mutable std::ofstream fileStream;

public:
    WriteOnlyStream() = default;

    explicit WriteOnlyStream(std::shared_ptr<Sequence<T>> seq)
        : kind(TargetKind::SequencePtr), seqTarget(std::move(seq)) {}
    WriteOnlyStream(const std::string& file, Serializer<T> ser, bool /*toFileTag*/)
        : kind(TargetKind::FileTarget), fileName(file), serializer(std::move(ser)) {}

    explicit WriteOnlyStream(const std::shared_ptr<WriteOnlyStream<T>>& other)
        : kind(TargetKind::OtherStream), otherStream(other) {}
    void Open() {
        if (opened) return;
        opened = true;
        position = 0;

        if (kind == TargetKind::FileTarget) {
            fileStream.open(fileName);
            if (!fileStream.is_open())
                throw std::runtime_error("Cannot open file in WriteOnlyStream");
        }
    }

    void Close() {
        if (!opened) return;
        opened = false;
        if (kind == TargetKind::FileTarget && fileStream.is_open()) {
            fileStream.close();
        }
    }

    size_t GetPosition() const {
        return position;
    }

    size_t Write(const T& value) {
        if (!opened) throw std::runtime_error("Stream is not opened");

        switch (kind) {
            case TargetKind::SequencePtr:
                if (!seqTarget)
                    throw std::runtime_error("Sequence target is not set");
                seqTarget->Append(value);
                break;
            case TargetKind::FileTarget: {
                std::string token = serializer(value);
                fileStream << token << " ";
                break;
            }
            case TargetKind::OtherStream:
                if (auto target = otherStream.lock()) {
                    target->Write(value);
                } else {
                    throw std::runtime_error("Other stream expired");
                }
                break;
            default:
                throw std::runtime_error("No target set for WriteOnlyStream");
        }

        ++position;
        return position;
    }
};
class StringReadOnlyStream : public ReadOnlyStream<char> {
public:
    explicit StringReadOnlyStream(const std::string& data)
        : m_data(data), m_pos(0), m_open(false) {}

    void Open()  {
        m_open = true;
        m_pos = 0;
    }

    void Close()  {
        m_open = false;
    }

    bool IsOpen() const  {
        return m_open;
    }

    bool IsEndOfStream() const  {
        return !m_open || m_pos >= m_data.size();
    }

    char Read()  {
        if (!m_open) {
            throw std::runtime_error("Stream is not open");
        }
        if (IsEndOfStream()) {
            throw std::runtime_error("EndOfStream");
        }
        return m_data[m_pos++];
    }

    std::size_t GetPosition() const  {
        return m_pos;
    }

private:
    std::string m_data;
    std::size_t m_pos;
    bool m_open;
};

class StringWriteOnlyStream : public WriteOnlyStream<char> {
public:
    StringWriteOnlyStream()
        : m_pos(0), m_open(false) {}

    void Open()  {
        m_open = true;
        m_buffer.clear();
        m_pos = 0;
    }

    void Close()  {
        m_open = false;
    }

    bool IsOpen() const  {
        return m_open;
    }

    void Write(const char& value)  {
        if (!m_open) {
            throw std::runtime_error("Stream is not open");
        }
        m_buffer.push_back(value);
        ++m_pos;
    }

    std::size_t GetPosition() const  {
        return m_pos;
    }

    std::string GetResult() const {
        return m_buffer;
    }

private:
    std::string m_buffer;
    std::size_t m_pos;
    bool m_open;
};

#endif //LABA3_STREAM_H