#include <vector>
#include <fstream>
#include <sstream>
#include "tuple.hpp"

#pragma once
#ifndef CSV_READER_READER_H
#define CSV_READER_READER_H

template<typename T, typename... Args>
class csvreader
{
public:
    csvreader()
    { }
    ~csvreader()
    { }

    void push(T arg, Args... args) {
        return m_strings.emplace_back(arg, args...);
    }

    void pop() {
        return m_strings.pop;
    }

    const Tuple<T, Args...>& operator [](const size_t index) const {
        if (m_strings.size() <= index)
            throw std::range_error("invalid index");
        return m_strings[index];
    }

    bool read_file(const char* const src);

    std::vector<Tuple<T, Args...>> copy_data() {
        return m_strings;
    }

private:
    std::vector<Tuple<T, Args...>> m_strings;
};

template<typename T, typename... Args>
bool csvreader<T, Args...>::read_file(const char* const src) {
    std::ifstream file(src);
    std::string line;

    size_t line_number = 0;
    while (file.good()) {
        std::getline(file, line);
        const size_t size = line.size();
        if (0 == size)
            continue;

        for (size_t i = 0; i < size; ++i) {
            if (',' == line[i])
                line[i] = ' ';
        }
        std::istringstream line_stream(line);

        try {
            m_strings.push_back(Tuple<T, Args...>::from_istringstream(line_stream));
        }
        catch(BadLine) {
            printf("Invalid line %zu\n", line_number);
            file.close();
            return false;
        }

        if (!line_stream.eof()) {
            printf("Invalid template %zu\n", line_number);
            //std::cout << line_stream.get() << std::endl;
            file.close();
            return false;
        }

        ++line_number;
    }

    file.close();
    return file.eof();
}

template<typename T, typename... Args>
std::vector<Tuple<T, Args...>> ReadCSV(const char* const src) {
    csvreader<T, Args...> csv{};
    if (!csv.read_file(src)) {
        throw BadLine();
    }
    return csv.copy_data();
}

#endif // CSV_READER_READER_H
