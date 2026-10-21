# Copyright 2018-2020 Peter Dimov
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt

include(BoostTest OPTIONAL RESULT_VARIABLE HAVE_BOOST_TEST)

# C++20 module test. Does not use Boost.Test, and is only built when the
# module interface target exists.

if(BOOST_PROGRAM_OPTIONS_BUILD_MODULES AND TARGET Boost::program_options_modules)

  add_executable(program_options_module_test module_test.cpp)
  target_link_libraries(program_options_module_test PRIVATE Boost::program_options_modules)
  set_target_properties(program_options_module_test PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_SCAN_FOR_MODULES ON)
  add_test(NAME program_options_module_test COMMAND program_options_module_test)

endif()

if(NOT HAVE_BOOST_TEST)
  return()
endif()

set(BOOST_TEST_LINK_LIBRARIES Boost::program_options)

boost_test(TYPE run SOURCES options_description_test.cpp)
boost_test(TYPE run SOURCES parsers_test.cpp ARGUMENTS ${CMAKE_CURRENT_SOURCE_DIR}/config_test.cfg)
boost_test(TYPE run SOURCES variable_map_test.cpp)
boost_test(TYPE run SOURCES cmdline_test.cpp)
boost_test(TYPE run SOURCES positional_options_test.cpp)
boost_test(TYPE run SOURCES unicode_test.cpp)
boost_test(TYPE run SOURCES winmain.cpp)
boost_test(TYPE run SOURCES exception_test.cpp)
boost_test(TYPE run SOURCES split_test.cpp)
boost_test(TYPE run SOURCES unrecognized_test.cpp)
boost_test(TYPE run SOURCES required_test.cpp ARGUMENTS ${CMAKE_CURRENT_SOURCE_DIR}/required_test.cfg)
boost_test(TYPE run SOURCES exception_txt_test.cpp)
boost_test(TYPE run SOURCES optional_test.cpp)

boost_test(TYPE run SOURCES quick.cpp ARGUMENTS --path=initial LINK_LIBRARIES Boost::core)
