#pragma once

#ifndef __ERROR_REPORTER_HPP__
#define __ERROR_REPORTER_HPP__

#include "common.hpp"

class   ErrorReporter {
public:
    static void error(int line, const std::string& message);
    static void report(int line, const std::string& where,
                        const std::string& message);
    
    static bool hadError;
};

#endif