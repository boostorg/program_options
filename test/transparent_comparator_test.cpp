#include <boost/config.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/utility/string_view.hpp>

#ifndef BOOST_NO_CXX17_HDR_STRING_VIEW
#include <string_view>
#endif

namespace {
// Contrived class that proves no extra copies are being made and only operator< is being used
struct Dummy : private boost::noncopyable
{};

bool operator<(const Dummy&, const std::string& rhs) { return "test" < rhs; }
bool operator<(const std::string& lhs, const Dummy&) { return lhs < "test"; }
}

void test_transparent_comparator()
{
    boost::program_options::variables_map vm;
    vm.insert({"test", boost::program_options::variable_value(42, false)});

    boost::program_options::variables_map::iterator iter;

    // c-string literal.
    // If pre c++14, a std::string object will be implicitly created on the call to find()
    // after c++14 no extra object will be created
    iter = vm.find("test");
    BOOST_REQUIRE(iter != vm.end());
    BOOST_CHECK(boost::any_cast<int>(iter->second.value()) == 42);

    // Rest of the checks require c++14 for a transparent comparator
#ifdef BOOST_CXX_VERSION > 201402L
    // boost::string_view
    const boost::string_view bsv("test");
    iter = vm.find(bsv);
    BOOST_REQUIRE(iter != vm.end());
    BOOST_CHECK(boost::any_cast<int>(iter->second.value()) == 42);

    #ifndef BOOST_NO_CXX17_HDR_STRING_VIEW
    // std::string_view
    const std::string_view sv("test");
    iter = vm.find(sv);
    BOOST_REQUIRE(iter != vm.end());
    BOOST_CHECK(boost::any_cast<int>(iter->second.value()) == 42);
    #endif

    // custom class
    Dummy d;
    iter = vm.find(d);
    BOOST_REQUIRE(iter != vm.end());
    BOOST_CHECK(boost::any_cast<int>(iter->second.value()) == 42);
#endif
}
