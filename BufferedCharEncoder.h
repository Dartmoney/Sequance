//
// Created by imako on 22.11.2025.
//

#ifndef LABA3_BUFFEREDCHARENCODER_H
#define LABA3_BUFFEREDCHARENCODER_H

#include <cstddef>
#include <string>
#include <stdexcept>
#include "Stream.h"
#include "Dynamic_array.hpp"
#include "Error.hpp"

class BufferedCharEncoder {
public:
    explicit BufferedCharEncoder(std::size_t bufSize = 1024)
        : bufferSize(bufSize ? bufSize : 1), buffer()
    {
        buffer.resize(static_cast<int>(bufferSize));
    }

    template <typename ReadStream, typename WriteStream>
    void Encode(ReadStream& input, WriteStream& output) {
        input.Open();
        output.Open();

        bool hasPrev = false;
        char prevChar = 0;
        std::size_t runCount = 0;

        while (!input.IsEndOfStream()) {
            int n = ReadToBuffer(input);
            if (n <= 0) break;

            for (int i = 0; i < n; ++i) {
                char c = buffer[i];
                if (!hasPrev) {
                    prevChar = c;
                    runCount = 1;
                    hasPrev = true;
                } else if (c == prevChar) {
                    ++runCount;
                } else {
                    FlushRun(prevChar, runCount, output);
                    prevChar = c;
                    runCount = 1;
                }
            }
        }

        if (hasPrev && runCount > 0) {
            FlushRun(prevChar, runCount, output);
        }

        input.Close();
        output.Close();
    }

private:
    std::size_t bufferSize;
    Dynamic_array<char> buffer;

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
    void FlushRun(char ch, std::size_t cnt, WriteStream& out) {
        out.Write(ch);

        std::string num = std::to_string(cnt);
        for (char d : num) out.Write(d);
    }
};

#endif //LABA3_BUFFEREDCHARENCODER_H