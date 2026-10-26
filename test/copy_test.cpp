// Copyright 2026 Treston Cuzzort
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or https://www.boost.org/LICENSE_1_0.txt)

#if defined(__clang__)
# if __has_warning("-Wdeprecated-copy-with-dtor")
#  pragma clang diagnostic error "-Wdeprecated-copy-with-dtor"
# endif
#endif

#include <boost/program_options.hpp>
#include <boost/core/lightweight_test.hpp>
#include <string>
#include <utility>
#include <vector>

namespace po = boost::program_options;

template<class Error>
void check_error(Error error)
{
    error.add_context("value", "--value", po::command_line_style::allow_long);
    const std::string message = error.what();
    const std::string name = error.get_option_name();
    Error copy(error);
    error.m_error_template = "changed";
    BOOST_TEST_EQ(std::string(copy.what()), message);
    BOOST_TEST_EQ(copy.get_option_name(), name);

    Error assigned(error);
    assigned = copy;
    BOOST_TEST_EQ(std::string(assigned.what()), message);
    BOOST_TEST_EQ(assigned.get_option_name(), name);

    Error rvalue_copy(std::move(copy));
    BOOST_TEST_EQ(std::string(rvalue_copy.what()), message);
    BOOST_TEST_EQ(rvalue_copy.get_option_name(), name);
    // Retaining the destructors and copy declarations retains copy fallback.
    BOOST_TEST_EQ(std::string(copy.what()), message);
    assigned = std::move(rvalue_copy);
    BOOST_TEST_EQ(std::string(assigned.what()), message);
    BOOST_TEST_EQ(std::string(rvalue_copy.what()), message);
}

void test_errors()
{
    po::error_with_option_name error("%canonical_option%: %tag%, %fallback%");
    error.set_substitute("tag", "custom value");
    error.set_substitute_default("fallback", "%fallback%", "default value");
    check_error(error);
    check_error(po::multiple_values());
    check_error(po::multiple_occurrences());
    check_error(po::required_option("required"));
    check_error(po::error_with_no_option_name("%original_token%"));
    check_error(po::unknown_option("unknown"));
    const std::vector<std::string> alternatives = { "first", "second" };
    const po::ambiguous_option ambiguous(alternatives);
    check_error(ambiguous);
    po::ambiguous_option ambiguous_copy(ambiguous);
    BOOST_TEST(ambiguous_copy.alternatives() == alternatives);
    ambiguous_copy = po::ambiguous_option(std::vector<std::string>(1, "third"));
    BOOST_TEST_EQ(ambiguous_copy.alternatives().size(), 1u);
    BOOST_TEST_EQ(ambiguous_copy.alternatives()[0], "third");

    const po::invalid_syntax syntax(po::invalid_syntax::missing_parameter);
    check_error(syntax);
    po::invalid_syntax syntax_copy(syntax);
    BOOST_TEST_EQ(syntax_copy.kind(), syntax.kind());
    syntax_copy = po::invalid_syntax(po::invalid_syntax::extra_parameter);
    BOOST_TEST_EQ(syntax_copy.kind(), po::invalid_syntax::extra_parameter);
    const po::invalid_config_file_syntax config("bad line", po::invalid_syntax::unrecognized_line);
    check_error(config);
    BOOST_TEST_EQ(po::invalid_config_file_syntax(config).tokens(), "bad line");
    check_error(po::invalid_command_line_syntax(po::invalid_syntax::missing_parameter));
    const po::validation_error validation(po::validation_error::invalid_bool_value);
    check_error(validation);
    po::validation_error validation_copy(validation);
    BOOST_TEST_EQ(validation_copy.kind(), validation.kind());
    validation_copy = po::validation_error(po::validation_error::invalid_option);
    BOOST_TEST_EQ(validation_copy.kind(), po::validation_error::invalid_option);
    check_error(po::invalid_option_value("bad value"));
    check_error(po::invalid_bool_value("bad bool"));
}

po::variables_map make_map(const po::abstract_variables_map* next, int& notified)
{
    po::options_description description;
    description.add_options()
        ("single", po::value<int>()->default_value(7))
        ("many", po::value<std::vector<int> >()->composing())
        ("notified", po::value<int>()->notifier([&notified](int v) { notified += v; }))
        ("required", po::value<std::string>()->required());
    const std::vector<std::string> arguments = {
        "--single=11", "--many=1", "--notified=5", "--required=yes"
    };
    po::variables_map map(next);
    po::store(po::command_line_parser(arguments).options(description).run(), map);
    return map;
}

void test_maps()
{
    po::variables_map fallback, other_fallback;
    fallback.insert(std::make_pair("fallback", po::variable_value(boost::any(42), false)));
    other_fallback.insert(std::make_pair("fallback", po::variable_value(boost::any(99), false)));
    int notified = 0;
    const po::variables_map original = make_map(&fallback, notified);
    po::variables_map copy(original), assigned(&other_fallback);
    assigned = original;
    po::variables_map move_source(original), moved(std::move(move_source));
    move_source = original;
    po::variables_map move_assigned(&other_fallback);
    move_assigned = std::move(move_source);
    po::variables_map* maps[] = { &copy, &assigned, &moved, &move_assigned };
    // Copies share the non-owning next-map link rather than a snapshot.
    fallback.find("fallback")->second = po::variable_value(boost::any(43), false);
    po::options_description later;
    later.add_options()
        ("single", po::value<int>())
        ("many", po::value<std::vector<int> >()->composing());
    const std::vector<std::string> arguments = { "--single=22", "--many=2" };
    for (unsigned i = 0; i < 4; ++i)
    {
        po::variables_map& map = *maps[i];
        BOOST_TEST_EQ(map["fallback"].as<int>(), 43);
        BOOST_TEST(map["absent"].empty());
        po::store(po::command_line_parser(arguments).options(later).run(), map);
        BOOST_TEST_EQ(map["single"].as<int>(), 11);
        BOOST_TEST(map["many"].as<std::vector<int> >() == std::vector<int>({1, 2}));
        BOOST_TEST_EQ(original["many"].as<std::vector<int> >().size(), 1u);
        map.notify();
        BOOST_TEST_EQ(notified, static_cast<int>(5 * (i + 1)));
    }

    po::options_description required;
    required.add_options()("missing", po::value<int>()->required());
    po::variables_map missing;
    po::store(po::command_line_parser(std::vector<std::string>()).options(required).run(), missing);
    po::variables_map required_copy(missing), required_assigned;
    required_assigned = missing;
    po::variables_map required_moved(std::move(required_copy));
    required_copy = missing;
    po::variables_map required_move_assigned;
    required_move_assigned = std::move(required_copy);
    po::variables_map* missing_maps[] = {
        &missing, &required_assigned, &required_moved, &required_move_assigned
    };
    for (unsigned i = 0; i < 4; ++i)
    {
        bool caught = false;
        try { missing_maps[i]->notify(); }
        catch (const po::required_option& error)
        {
            caught = true;
            BOOST_TEST_EQ(error.get_option_name(), "--missing");
        }
        BOOST_TEST(caught);
    }
}

void test_lookup_priority()
{
    // Rows/columns: absent, explicit, defaulted. Owners: missing, local, next.
    const int owners[3][3] = { {0, 2, 2}, {1, 1, 1}, {1, 2, 1} };
    for (unsigned local = 0; local < 3; ++local)
    {
        for (unsigned next = 0; next < 3; ++next)
        {
            po::variables_map fallback;
            if (next != 0)
                fallback.insert(std::make_pair("value", po::variable_value(boost::any(22), next == 2)));
            po::variables_map original(&fallback);
            if (local != 0)
                original.insert(std::make_pair("value", po::variable_value(boost::any(11), local == 2)));
            po::variables_map copy(original), assigned;
            assigned = original;
            po::variables_map moving(original), moved(std::move(moving));
            moving = original;
            po::variables_map move_assigned;
            move_assigned = std::move(moving);
            const po::variables_map* maps[] = { &copy, &assigned, &moved, &move_assigned };
            for (unsigned i = 0; i < 4; ++i)
            {
                const po::variable_value& value = (*maps[i])["value"];
                if (owners[local][next] == 0)
                    BOOST_TEST(value.empty());
                else
                    BOOST_TEST_EQ(value.as<int>(), owners[local][next] == 1 ? 11 : 22);
            }
        }
    }
}

int main()
{
    test_errors();
    test_maps();
    test_lookup_priority();
    return boost::report_errors();
}
