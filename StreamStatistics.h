
#ifndef LABA3_STREAMSTATISTICS_H
#define LABA3_STREAMSTATISTICS_H

#include "Stream.h"   // здесь лежит StringReadOnlyStream<char>
#include <stdexcept>

class StringStreamStatistics {
private:
    StringReadOnlyStream stream;

    size_t count = 0;
    long double sum = 0.0L;
    char minVal = 0;
    char maxVal = 0;
    bool hasValue = false;

public:
    explicit StringStreamStatistics(const std::string& data)
        : stream(data) {}


    void ConsumeAll() {
        if (!stream.IsOpen())
            stream.Open();

        while (!stream.IsEndOfStream()) {
            char c = stream.Read();
            AddValue(c);
        }
    }

    void AddValue(char c) {
        if (!hasValue) {
            minVal = maxVal = c;
            hasValue = true;
        } else {
            if (c < minVal) minVal = c;
            if (c > maxVal) maxVal = c;
        }
        count++;
        sum += static_cast<unsigned char>(c); // чтобы не было проблем с signed char
    }

    // ===== геттеры =====
    size_t GetCount() const { return count; }
    long double GetSum() const { return sum; }

    long double GetMean() const {
        if (count == 0)
            throw std::logic_error("Mean undefined for empty stream");
        return sum / count;
    }

    char GetMin() const {
        if (!hasValue)
            throw std::logic_error("Min undefined for empty stream");
        return minVal;
    }

    char GetMax() const {
        if (!hasValue)
            throw std::logic_error("Max undefined for empty stream");
        return maxVal;
    }
};



#endif //LABA3_STREAMSTATISTICS_H