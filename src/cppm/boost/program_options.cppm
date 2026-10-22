// Copyright Sorush Sabzpour 2026.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// C++20 module interface for Boost.ProgramOptions.
//
// Consumers can replace
//     #include <boost/program_options.hpp>
// with
//     import boost.program_options;
// and keep using the boost::program_options namespace as before.
//
// Implementation notes:
//
// * The classic headers are included in the global module fragment and the
//   public declarations are re-exported with exported using-declarations.
//   This is a thin wrapper: no header is modified, no declaration is moved,
//   renamed or otherwise changed, and every declaration stays attached to
//   the global module, so the definitions in the classic compiled library
//   link directly.
//
// * The alternative design used by Boost.Any and Boost.PFR (export blocks
//   in the library's own headers) is not applicable here yet: it attaches
//   the declarations to the module, and a compiled library must then also
//   provide its definitions as module implementation units, because some
//   compilers (e.g. MSVC) mangle module-attached functions differently
//   than the classic library's. It also requires modularized dependencies.
//   The thin wrapper needs neither; the migration can be revisited once
//   the Boost dependencies are modularized.
//
// * Macros (e.g. BOOST_PROGRAM_OPTIONS_VERSION) are not exported by C++20
//   modules. Code that needs them must keep including the classic headers.
//
// * The module covers everything reachable from <boost/program_options.hpp>.
//   The auxiliary iterator headers <boost/program_options/eof_iterator.hpp>
//   and <boost/program_options/environment_iterator.hpp> are generic
//   utilities outside of that umbrella header and are not exported here.

module;

#include <boost/program_options.hpp>

// Consume the standard library through 'import std;' as well when the
// toolchain provides it (BOOST_PROGRAM_OPTIONS_USE_STD_MODULE, set by CMake
// like in other modularized Boost libraries). The import must come after
// the textual includes above: on MSVC, a textual standard header parsed
// after 'import std;' clashes with the declarations already provided by
// the std module.
#ifdef BOOST_PROGRAM_OPTIONS_USE_STD_MODULE
import std;
#endif

export module boost.program_options;

// Some compilers prune global-module-fragment declarations from the BMI.
// Templates defined by the headers (e.g. boost::any_cast, used by
// variable_value::as<T>()) look up operators such as
// boost::typeindex::operator== by ADL when instantiated in importing
// translation units. Those operators must therefore be exported by the
// module, like the library's own declarations.
export namespace boost { namespace typeindex {
using ::boost::typeindex::operator==;
using ::boost::typeindex::operator!=;
}}

export namespace boost {

// Character conversion helpers declared in namespace boost by
// <boost/program_options/detail/convert.hpp>.
#if !defined(BOOST_NO_STD_WSTRING)
using ::boost::from_8_bit;
using ::boost::to_8_bit;
using ::boost::from_utf8;
using ::boost::to_utf8;
using ::boost::from_local_8_bit;
using ::boost::to_local_8_bit;
#endif

namespace program_options {

// errors.hpp
using ::boost::program_options::strip_prefixes;
using ::boost::program_options::error;
using ::boost::program_options::too_many_positional_options_error;
using ::boost::program_options::invalid_command_line_style;
using ::boost::program_options::reading_file;
using ::boost::program_options::error_with_option_name;
using ::boost::program_options::multiple_values;
using ::boost::program_options::multiple_occurrences;
using ::boost::program_options::required_option;
using ::boost::program_options::error_with_no_option_name;
using ::boost::program_options::unknown_option;
using ::boost::program_options::ambiguous_option;
using ::boost::program_options::invalid_syntax;
using ::boost::program_options::invalid_config_file_syntax;
using ::boost::program_options::invalid_command_line_syntax;
using ::boost::program_options::validation_error;
using ::boost::program_options::invalid_option_value;
using ::boost::program_options::invalid_bool_value;

// option.hpp
using ::boost::program_options::basic_option;
using ::boost::program_options::option;
using ::boost::program_options::woption;

// value_semantic.hpp and detail/value_semantic.hpp
// Note: the explicit specializations (e.g. value_semantic_codecvt_helper<char>)
// are declared by the headers in the global module fragment and are therefore
// reachable by importers of this module; only the primary templates are
// named below, as some compilers reject using-declarations that name
// template specializations.
using ::boost::program_options::value_semantic;
using ::boost::program_options::value_semantic_codecvt_helper;
using ::boost::program_options::untyped_value;
#ifndef BOOST_NO_RTTI
using ::boost::program_options::typed_value_base;
#endif
using ::boost::program_options::typed_value;
using ::boost::program_options::value;
using ::boost::program_options::wvalue;
using ::boost::program_options::bool_switch;
using ::boost::program_options::validate;

namespace validators {
using ::boost::program_options::validators::get_single_string;
using ::boost::program_options::validators::check_first_occurrence;
}

// options_description.hpp
using ::boost::program_options::option_description;
using ::boost::program_options::options_description_easy_init;
using ::boost::program_options::options_description;
using ::boost::program_options::duplicate_option_error;

// positional_options.hpp
using ::boost::program_options::positional_options_description;

// cmdline.hpp
namespace command_line_style {
using ::boost::program_options::command_line_style::style_t;
using ::boost::program_options::command_line_style::allow_long;
using ::boost::program_options::command_line_style::allow_short;
using ::boost::program_options::command_line_style::allow_dash_for_short;
using ::boost::program_options::command_line_style::allow_slash_for_short;
using ::boost::program_options::command_line_style::long_allow_adjacent;
using ::boost::program_options::command_line_style::long_allow_next;
using ::boost::program_options::command_line_style::short_allow_adjacent;
using ::boost::program_options::command_line_style::short_allow_next;
using ::boost::program_options::command_line_style::allow_sticky;
using ::boost::program_options::command_line_style::allow_guessing;
using ::boost::program_options::command_line_style::long_case_insensitive;
using ::boost::program_options::command_line_style::short_case_insensitive;
using ::boost::program_options::command_line_style::case_insensitive;
using ::boost::program_options::command_line_style::allow_long_disguise;
using ::boost::program_options::command_line_style::unix_style;
using ::boost::program_options::command_line_style::default_style;
}

// parsers.hpp and detail/parsers.hpp
using ::boost::program_options::basic_parsed_options;
using ::boost::program_options::parsed_options;
using ::boost::program_options::wparsed_options;
using ::boost::program_options::ext_parser;
using ::boost::program_options::basic_command_line_parser;
using ::boost::program_options::command_line_parser;
using ::boost::program_options::wcommand_line_parser;
using ::boost::program_options::parse_command_line;
using ::boost::program_options::parse_config_file;
using ::boost::program_options::collect_unrecognized_mode;
using ::boost::program_options::include_positional;
using ::boost::program_options::exclude_positional;
using ::boost::program_options::collect_unrecognized;
using ::boost::program_options::parse_environment;
using ::boost::program_options::split_unix;
#ifdef _WIN32
using ::boost::program_options::split_winmain;
#endif

// detail/convert.hpp
using ::boost::program_options::to_internal;

// detail/cmdline.hpp, detail/config_file.hpp
namespace detail {
using ::boost::program_options::detail::cmdline;
using ::boost::program_options::detail::arg;
}

// variables_map.hpp
using ::boost::program_options::store;
using ::boost::program_options::notify;
using ::boost::program_options::variable_value;
using ::boost::program_options::abstract_variables_map;
using ::boost::program_options::variables_map;

} // namespace program_options
} // namespace boost
