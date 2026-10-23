// Copyright Sorush Sabzpour 2026.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// A minimal sample of consuming the library through the C++20 module
// interface. To compile it manually, build the module interface first
// (e.g. with CMake and BOOST_PROGRAM_OPTIONS_BUILD_MODULES=ON), then use
// a command like the following:
//
//   MSVC:
//   cl /std:c++20 /EHsc ^
//      /reference boost.program_options=<path>/boost.program_options.ifc ^
//      usage_sample.cpp /link <path>/libboost_program_options*.lib
//
//   Clang:
//   clang++ -std=c++20 -fprebuilt-module-path=. usage_sample.cpp \
//           -lboost_program_options

#include <iostream>

import boost.program_options;

int main(int argc, char* argv[])
{
    namespace po = boost::program_options;

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "produce help message")
        ("compression", po::value<int>(), "set compression level")
        ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help"))
    {
        std::cout << desc;
        return 0;
    }
}
