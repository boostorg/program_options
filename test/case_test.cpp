// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/program_options.hpp>
using namespace boost::program_options;

#include "minitest.hpp"

void test_long_name_case_default()
{
    bool adamSelected = false;
    bool aliceSelected = false;
    bool bertilSelected = false;

    options_description desc;
    desc.add_options()
        ("Adam", value<bool>(&adamSelected)->default_value(false)->implicit_value(true), "Choose Adam")
        ("Alice", value<bool>(&aliceSelected)->default_value(false)->implicit_value(true), "Choose Alice")
        ("Bertil", value<bool>(&bertilSelected)->default_value(false)->implicit_value(true), "Choose Bertil")
        ;

    int ac = 4;
    char appname[] = "test";
    char option1[] = "--Adam";
    char option2[] = "--Alice";
    char option3[] = "--Bertil";
    const char* av[] = { appname , option1, option2, option3 };

    variables_map vm;
    auto parsed = command_line_parser(ac, av)
	.options(desc)
	.run();
    store(parsed, vm);
    notify(vm);

    BOOST_CHECK(adamSelected);
    BOOST_CHECK(aliceSelected);
    BOOST_CHECK(bertilSelected);
}

void test_long_name_case_default_bad_input()
{
    bool adamSelected = false;

    options_description desc;
    desc.add_options()
        ("Adam", value<bool>(&adamSelected)->default_value(false)->implicit_value(true), "Choose Adam")
        ;

    int ac = 2;
    char appname[] = "test";
    char option1[] = "--adam";
    const char* av[] = { appname , option1 };

    auto parser = command_line_parser(ac, av).options(desc);
    BOOST_CHECK_THROW(parser.run(), std::exception);
}

void test_short_name_case_default()
{
    bool adamSelected = false;
    bool bertilSelected = false;

    options_description desc;
    desc.add_options()
        ("Adam,a", value<bool>(&adamSelected)->default_value(false)->implicit_value(true), "Choose Adam")
        ("Bertil,B", value<bool>(&bertilSelected)->default_value(false)->implicit_value(true), "Choose Bertil")
        ;

    int ac = 3;
    char appname[] = "test";
    char option1[] = "-a";
    char option2[] = "-B";
    const char* av[] = { appname , option1, option2 };

    variables_map vm;
    auto parsed = command_line_parser(ac, av)
	.options(desc)
	.run();
    store(parsed, vm);
    notify(vm);

    BOOST_CHECK(adamSelected);
    BOOST_CHECK(bertilSelected);
}

void test_short_name_case_default_bad_input()
{
    bool adamSelected = false;

    options_description desc;
    desc.add_options()
        ("Adam,A", value<bool>(&adamSelected)->default_value(false)->implicit_value(true), "Choose Adam")
        ;

    int ac = 2;
    char appname[] = "test";
    char option1[] = "-a";
    const char* av[] = { appname , option1 };

    auto parser = command_line_parser(ac, av).options(desc);
    BOOST_CHECK_THROW(parser.run(), std::exception);
}

void test_only_long_name_case_insensitive()
{
    bool adamSelected = false;
    bool bertilSelected = false;

    options_description desc;
    desc.add_options()
        ("Adam", value<bool>(&adamSelected)->default_value(false)->implicit_value(true), "Choose Adam")
        ("Bertil", value<bool>(&bertilSelected)->default_value(false)->implicit_value(true), "Choose Bertil")
        ;

    int ac = 3;
    char appname[] = "test";
    char option1[] = "--adam";
    char option2[] = "--bErTiL";
    const char* av[] = { appname , option1, option2 };

    variables_map vm;
    auto parsed = command_line_parser(ac, av)
	.options(desc)
	.style(
            command_line_style::unix_style | 
            command_line_style::long_case_insensitive)
	.run();
    store(parsed, vm);
    notify(vm);

    BOOST_CHECK(adamSelected);
    BOOST_CHECK(bertilSelected);
}

void test_short_names_when_only_long_name_case_insensitive_bad_input()
{
    bool bertilSelected = false;

    options_description desc;
    desc.add_options()
        ("Bertil,b", value<bool>(&bertilSelected)->default_value(false)->implicit_value(true), "Choose Bertil")
        ;

    int ac = 2;
    char appname[] = "test";
    char option1[] = "-B";
    const char* av[] = { appname , option1 };

    auto parser = command_line_parser(ac, av)
	.options(desc)
	.style(
            command_line_style::unix_style |
            command_line_style::long_case_insensitive
	);
    BOOST_CHECK_THROW(parser.run(), std::exception);
}


void test_only_short_name_case_insensitive()
{
    bool adamSelected = false;
    bool bertilSelected = false;

    options_description desc;
    desc.add_options()
        ("Adam,a", value<bool>(&adamSelected)->default_value(false)->implicit_value(true), "Choose Adam")
        ("Bertil,B", value<bool>(&bertilSelected)->default_value(false)->implicit_value(true), "Choose Bertil")
        ;

    int ac = 3;
    char appname[] = "test";
    char option1[] = "-a";
    char option2[] = "-B";
    const char* av[] = { appname , option1, option2 };

    variables_map vm;
    auto parsed = command_line_parser(ac, av)
	.options(desc)
	.style(
            command_line_style::unix_style |
            command_line_style::short_case_insensitive)
	.run();
    store(parsed, vm);
    notify(vm);

    BOOST_CHECK(adamSelected);
    BOOST_CHECK(bertilSelected);
}

void test_full_case_insensitive()
{
    bool adamSelected = false;
    bool beritSelected = false;
    bool cesarSelected = false;
    bool dorisSelected = false;

    options_description desc;
    desc.add_options()
        ("Adam,a", value<bool>(&adamSelected)->default_value(false)->implicit_value(true), "Choose Adam")
        ("berit,B", value<bool>(&beritSelected)->default_value(false)->implicit_value(true), "Choose Berit")
        ("Cesar,C", value<bool>(&cesarSelected)->default_value(false)->implicit_value(true), "Choose Cesar")
        ("doris,d", value<bool>(&dorisSelected)->default_value(false)->implicit_value(true), "Choose Doris")
        ;

    int ac = 5;
    char appname[] = "test";
    char option1[] = "--adam";
    char option2[] = "--Berit";
    char option3[] = "-c";
    char option4[] = "-D";
    const char* av[] = { appname , option1, option2, option3, option4 };

    variables_map vm;
    auto parsed = command_line_parser(ac, av)
	.options(desc)
	.style(
            command_line_style::unix_style |
            command_line_style::case_insensitive)
	.run();
    store(parsed, vm);
    notify(vm);

    BOOST_CHECK(adamSelected);
    BOOST_CHECK(beritSelected);
    BOOST_CHECK(cesarSelected);
    BOOST_CHECK(dorisSelected);
}

int main(int, char* [])
{
    test_long_name_case_default();
    test_long_name_case_default_bad_input();
    test_short_name_case_default();
    test_short_name_case_default_bad_input();
    test_only_long_name_case_insensitive();
    test_short_names_when_only_long_name_case_insensitive_bad_input();
    test_only_short_name_case_insensitive();
    test_full_case_insensitive();
    return 0;
}

