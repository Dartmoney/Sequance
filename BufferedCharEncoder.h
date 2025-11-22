//
// Created by imako on 22.11.2025.
//

#ifndef LABA3_BUFFEREDCHARENCODER_H
#define LABA3_BUFFEREDCHARENCODER_H
#include <cstddef>
#include "Dynamic_array.hpp"
#include "Stream.h"
#include "Error.hpp"

class BufferedCharEncoder {
private:
    size_t bufferSize;
    Dynamic_array<char> buffer;

public:
    explicit BufferedCharEncoder(size_t bufSize = 1024)
        : bufferSize(bufSize), buffer()
    {
        buffer.resize(static_cast<int>(bufferSize));
    }

    template <typename ReadStream, typename WriteStream>
    void Encode(ReadStream& input, WriteStream& output) {
        input.Open();
        output.Open();

        try {
            RLEEncode(input, output);
        } catch (...) {
            input.Close();
            output.Close();
            throw;
        }

        input.Close();
        output.Close();
    }

private:
    template <typename ReadStream, typename WriteStream>
    void RLEEncode(ReadStream& input, WriteStream& output) {
        bool first = true;
        char currentChar = 0;
        int runLength = 0;

        while (!input.IsEndOfStream()) {
            int readCount = ReadToBuffer(input);
            if (readCount == 0)
                break;

            for (int i = 0; i < readCount; ++i) {
                char c = buffer[i];

                if (first) {
                    currentChar = c;
                    runLength = 1;
                    first = false;
                } else if (c == currentChar && runLength < 9) {
                    ++runLength;
                } else {
                    FlushRun(currentChar, runLength, output);
                    currentChar = c;
                    runLength = 1;
                }
            }
        }

        if (!first && runLength > 0) {
            FlushRun(currentChar, runLength, output);
        }
    }

    template <typename ReadStream>
    int ReadToBuffer(ReadStream& input) {
        int count = 0;
        for (; count < static_cast<int>(bufferSize) && !input.IsEndOfStream(); ++count) {
            try {
                buffer[count] = input.Read();
            } catch (...) {
                break;
            }
        }
        return count;
    }

    template <typename WriteStream>
    void FlushRun(char c, int runLength, WriteStream& output) {
        char digit = static_cast<char>('0' + runLength);
        output.Write(digit);
        output.Write(c);
    }
};

#endif //LABA3_BUFFEREDCHARENCODER_H