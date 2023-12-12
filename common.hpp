#pragma once

#ifndef __UTILS_HPP__
#define __LOX_HPP__

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <list>
#include <map>
#include "ErrorReporter.hpp"
#include "TokenType.hpp"

#define USGERR 64
#define SYNERR 65

[[noreturn]] void   fatal(const std::string& msg, const int& exit_status);

#endif