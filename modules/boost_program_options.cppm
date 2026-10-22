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
// * Unlike Boost.Any or Boost.PFR, this library is compiled: entities
//   declared in a module purview are attached to the module, and MSVC (for
//   one) mangles their out-of-line definitions with a module qualifier, so
//   they cannot be provided by the classic, non-modular library. The module
//   target therefore also compiles the library sources as module
//   implementation units (impl/*.cc), which redeclare the exported
//   interface and provide matching, module-attached definitions. The
//   classic library is unchanged and keeps serving header builds.
//
// * The standard library and the non-modularized dependencies are preloaded
//   textually in the global module fragment (see gmf_preload.hpp), and
//   'import std;' is used in addition when the toolchain provides it.
//   The import must come after the textual preloads: on MSVC, a textual
//   standard header parsed after 'import std;' clashes with the
//   declarations already provided by the std module.
//
// * Macros (e.g. BOOST_PROGRAM_OPTIONS_VERSION) are not exported by C++20
//   modules. Code that needs them must keep including the classic headers.
//
// * The module covers everything reachable from <boost/program_options.hpp>.
//   The auxiliary iterator headers <boost/program_options/eof_iterator.hpp>
//   and <boost/program_options/environment_iterator.hpp> are generic
//   utilities outside of that umbrella header and are not exported here.

module;

#include "gmf_preload.hpp"

#ifdef BOOST_PROGRAM_OPTIONS_USE_STD_MODULE
import std;
#endif

export module boost.program_options;

#define BOOST_PROGRAM_OPTIONS_INTERFACE_UNIT

#ifdef __clang__
#   pragma clang diagnostic ignored "-Winclude-angled-in-module-purview"
#endif

// boost::typeindex comparison operators are re-exported on purpose.
// boost::type_index ships a module of its own, but it is not imported (or
// built) here: <boost/type_index.hpp> is preloaded textually in the global
// module fragment via <boost/any.hpp>. Templates from those preloaded
// headers (e.g. boost::any_cast, used by variable_value::as<T>()) look up
// these operators by ADL when instantiated in importing translation units,
// and some compilers do not find global-module declarations there unless
// the module exports them (MSVC: error C2679).
export namespace boost { namespace typeindex {
using ::boost::typeindex::operator==;
using ::boost::typeindex::operator!=;
}}

// The library's headers, in the module purview: the declarations below are
// attached to this module and the public ones are exported through the
// BOOST_PROGRAM_OPTIONS_BEGIN/END_MODULE_EXPORT blocks.
#include <boost/program_options.hpp>

// Additional internal headers used by the implementation units: included
// here once (unexported) so that every unit of the module sees the same
// declarations instead of re-including them textually.
#include <boost/program_options/detail/config_file.hpp>
#include <boost/program_options/environment_iterator.hpp>
