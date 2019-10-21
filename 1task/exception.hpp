#include <exception>

#pragma once
#ifndef CSV_READER_EXCEPTION_H
#define CSV_READER_EXCEPTION_H

class BadLine: virtual public std::exception {
};

#endif
