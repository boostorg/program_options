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
// * This follows the same design as other Boost libraries that ship a
//   module (e.g. Boost.Any and Boost.PFR): the library's public headers are
//   included in the module purview below, and their public declarations are
//   wrapped in BOOST_PROGRAM_OPTIONS_BEGIN/END_MODULE_EXPORT blocks, which
//   expand to 'export { ... }' while this interface unit is being compiled
//   and to nothing in ordinary header builds (see
//   <boost/program_options/config.hpp>).
//
// * Unlike Boost.Any or Boost.PFR, this library's public headers include
//   non-modularized Boost libraries (Boost.Any, Boost.Function,
//   Boost.SmartPtr, Boost.LexicalCast) and the standard library directly.
//   All of those headers are preloaded in the global module fragment below,
//   so that the includes triggered inside the purview are no-ops (include
//   guards) and no foreign declarations get attached to this module. They
//   remain attached to the global module, exactly as in header builds.
//
// * Macros (e.g. BOOST_PROGRAM_OPTIONS_VERSION) are not exported by C++20
//   modules. Code that needs them must keep including the classic headers.
//
// * The module covers everything reachable from <boost/program_options.hpp>.
//   The auxiliary iterator headers <boost/program_options/eof_iterator.hpp>
//   and <boost/program_options/environment_iterator.hpp> are generic
//   utilities outside of that umbrella header and are not exported here.

module;

// Dependencies directly included by the library's public headers.
#include <boost/config.hpp>
#include <boost/version.hpp>
#include <boost/any.hpp>
#include <boost/function.hpp>
#include <boost/function/function1.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include <boost/type_index.hpp>
#include <boost/detail/workaround.hpp>

// Standard headers directly included by the library's public headers.
#include <cassert>
#include <cwchar>
#include <iosfwd>
#include <iterator>
#include <limits>
#include <locale>
#include <map>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <utility>
#include <vector>

export module boost.program_options;

#define BOOST_PROGRAM_OPTIONS_INTERFACE_UNIT

#ifdef __clang__
#   pragma clang diagnostic ignored "-Winclude-angled-in-module-purview"
#endif

// Some compilers prune global-module-fragment declarations from the BMI.
// Templates defined by the preloaded headers (e.g. boost::any_cast, used by
// variable_value::as<T>()) look up operators such as
// boost::typeindex::operator== by ADL when instantiated in importing
// translation units. Those operators must therefore be exported by the
// module, like the library's own declarations.
export namespace boost { namespace typeindex {
using ::boost::typeindex::operator==;
using ::boost::typeindex::operator!=;
}}

// The library's headers, in the module purview: declarations below are
// attached to this module and the public ones are exported through the
// BOOST_PROGRAM_OPTIONS_BEGIN/END_MODULE_EXPORT blocks.
#include <boost/program_options.hpp>
