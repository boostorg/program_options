// Copyright Sorush Sabzpour 2026.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Checks that the C++20 module interface exports a usable library.
// No Boost header is included on purpose: everything must come from
// 'import boost.program_options;'.

// Standard library: textual includes by default; when the module was built
// with 'import std' (BOOST_PROGRAM_OPTIONS_USE_STD_MODULE), the standard
// module comes with the module and the textual includes would clash with it.
#ifdef BOOST_PROGRAM_OPTIONS_USE_STD_MODULE
import std;
#else
#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#endif

import boost.program_options;

// The test is built in both Debug and Release configurations, so plain
// assert() would be a no-op in Release. Use an always-active check.
// (Uses only facilities provided by 'import std', no macros.)
#define CHECK(cond) \
    do { \
        if (!(cond)) { \
            std::cerr << "CHECK failed: " << #cond << " (" << __FILE__ \
                      << ":" << __LINE__ << ")\n"; \
            std::abort(); \
        } \
    } while (0)

static void test_command_line()
{
    using namespace boost::program_options;

    options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "produce help message")
        ("compression", value<int>()->default_value(5), "set compression level")
        ("email", value<std::vector<std::string> >()->composing(), "email address")
        ("output,o", value<std::string>()->implicit_value("default"), "output file")
        ("verbose", bool_switch(), "verbose output")
        ("input", value<std::vector<std::string> >(), "input file")
        ;

    positional_options_description positional;
    positional.add("input", 2);

    char arg0[] = "program";
    char arg1[] = "--compression";
    char arg2[] = "7";
    char arg3[] = "--email";
    char arg4[] = "a@example.com";
    char arg5[] = "-ovalue";
    char arg6[] = "file1";
    char arg7[] = "file2";
    char* argv[] = { arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7 };

    variables_map vm;
    store(
        command_line_parser(sizeof(argv) / sizeof(argv[0]), argv)
            .options(desc)
            .positional(positional)
            .style(command_line_style::unix_style)
            .run(),
        vm);
    notify(vm);

    CHECK(vm.count("compression") == 1);
    CHECK(vm["compression"].as<int>() == 7);
    CHECK(!vm["compression"].defaulted());

    CHECK(vm.count("email") == 1);
    CHECK(vm["email"].as<std::vector<std::string> >().size() == 1);

    CHECK(vm.count("output") == 1);
    CHECK(vm["output"].as<std::string>() == "value");

    // bool_switch registers a default value of false, which store() applies.
    CHECK(vm.count("verbose") == 1);
    CHECK(vm["verbose"].defaulted());
    CHECK(!vm["verbose"].as<bool>());
    CHECK(vm.count("input") == 1);
    CHECK(vm["input"].as<std::vector<std::string> >().size() == 2);
    CHECK(vm.count("help") == 0);

    // Description printing exercises the ADL-found operator<<.
    std::ostringstream os;
    os << desc;
    CHECK(os.str().find("Allowed options") != std::string::npos);
    CHECK(os.str().find("compression") != std::string::npos);

    // parse_command_line and defaulted values.
    char* argv2[] = { arg0 };
    variables_map vm2;
    store(parse_command_line(1, argv2, desc), vm2);
    notify(vm2);
    CHECK(vm2["compression"].as<int>() == 5);
    CHECK(vm2["compression"].defaulted());

    // Unregistered options.
    char unknown[] = "--no-such-option";
    char* argv3[] = { arg0, unknown };
    parsed_options parsed
        = command_line_parser(2, argv3).options(desc).allow_unregistered().run();
    std::vector<std::string> tokens
        = collect_unrecognized(parsed.options, exclude_positional);
    CHECK(tokens.size() == 1 && tokens[0] == unknown);

    // Exceptions.
    bool caught = false;
    try
    {
        store(parse_command_line(2, argv3, desc), vm2);
    }
    catch (const unknown_option& e)
    {
        caught = true;
        std::string message = e.what();
        CHECK(message.find("no-such-option") != std::string::npos);
    }
    CHECK(caught);

    char badValue[] = "--compression";
    char notANumber[] = "not-a-number";
    char* argv4[] = { arg0, badValue, notANumber };
    caught = false;
    try
    {
        store(parse_command_line(3, argv4, desc), vm2);
    }
    catch (const invalid_option_value& e)
    {
        caught = true;
        // Reachability of the error hierarchy.
        const error_with_option_name& base = e;
        CHECK(base.what() != 0);
    }
    CHECK(caught);
}

static void test_config_file()
{
    using namespace boost::program_options;

    const char* configPath = "program_options_module_test.cfg";
    {
        std::ofstream config(configPath);
        config << "# a comment\n"
               << "compression = 9\n"
               << "email = x@example.com\n"
               << "email = y@example.com\n";
    }

    options_description desc("Allowed options");
    desc.add_options()
        ("compression", value<int>(), "set compression level")
        ("email", value<std::vector<std::string> >()->composing(), "email address")
        ;

    variables_map vm;
    store(parse_config_file(configPath, desc), vm);
    notify(vm);

    CHECK(vm.count("compression") == 1);
    CHECK(vm["compression"].as<int>() == 9);
    CHECK(vm.count("email") == 1);
    CHECK(vm["email"].as<std::vector<std::string> >().size() == 2);

    std::remove(configPath);
}

// Every toolchain with C++20 modules support provides std::wstring, so the
// wide-character interface (including the basic_parsed_options<wchar_t>
// specialization) is tested unconditionally.
static void test_wide_command_line()
{
    using namespace boost::program_options;

    options_description desc("Allowed options");
    desc.add_options()
        ("compression", value<int>(), "set compression level")
        ;

    wchar_t arg0[] = L"program";
    wchar_t arg1[] = L"--compression";
    wchar_t arg2[] = L"3";
    wchar_t* argv[] = { arg0, arg1, arg2 };

    // Uses basic_parsed_options<wchar_t>, an explicit specialization that
    // must be exported by the module.
    variables_map vm;
    store(wcommand_line_parser(3, argv).options(desc).run(), vm);
    notify(vm);

    CHECK(vm.count("compression") == 1);
    CHECK(vm["compression"].as<int>() == 3);
}

int main()
{
    test_command_line();
    test_config_file();
    test_wide_command_line();

    // Small namespace-level utilities.
    using boost::program_options::strip_prefixes;
    CHECK(strip_prefixes("--foo-bar") == "foo-bar");
    CHECK(strip_prefixes("foo") == "foo");

    CHECK(boost::program_options::split_unix("a b c").size() == 3);

    std::cout << "program_options module test: PASS\n";
    return 0;
}
