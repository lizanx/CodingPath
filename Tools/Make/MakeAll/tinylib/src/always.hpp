// *****************************************************************************
// header guard 
// *****************************************************************************
#ifndef _ALWAYS_HPP
#define _ALWAYS_HPP

// *****************************************************************************
// include
// *****************************************************************************
#include <cstdint>   // extra integer related types, specific bit widths, and limits
#include <cstdlib>   // general utilities library
#include <cmath>
#include <algorithm>

#include <iostream>  // I/O facilities, e.g. cin, cout, cerr
#include <iomanip>   // I/O manipulators, e.g. setfill, setprecision, setbase
#include <fstream>   // file   stream facilities
#include <sstream>   // string stream facilities

#include <string>
#include <vector>
#include <array>

#include <stdexcept> // defines standard exception classes to report exception

// *****************************************************************************
// using
// *****************************************************************************
using std::istream;
using std::ostream;
using std::fstream;

using std::string;

using std::cin;
using std::cout;
using std::cerr;
using std::clog;

using std::setw;
using std::setfill;
using std::dec;
using std::hex;

using std::endl;

// *****************************************************************************
// typedef
// *****************************************************************************
// shorter definitions for unsigned types
// -- int types --
typedef unsigned short     int ushort;
typedef unsigned           int uint;
typedef unsigned long      int ulong;
typedef unsigned long long int ulonglong;   // new in c++11

// -- char type --
typedef unsigned char          uchar;

// *****************************************************************************
// define
// *****************************************************************************
// Remember: there should be no space between macro name and the opening bracket of the argument list.

// -------------
// code_location
// -------------

#define code_location __FILE__ << ": " << __FUNCTION__ << ": " << __LINE__ << ": "

// *****************************************************************************
// defaultfloat
// *****************************************************************************
// From: http://www.stroustrup.com/Programming/std_lib_facilities.h
#if __GNUC__ && __GNUC__ < 5
inline ios_base& defaultfloat(ios_base& b)   // to augment fixed and scientific as in C++11
{
    b.setf(ios_base::fmtflags(0), ios_base::floatfield);
    return b;
}
#endif

// *****************************************************************************
// header guard
// *****************************************************************************
#endif   // _ALWAYS_HPP
