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
// * The dependencies of the library's headers are preloaded textually in
//   the global module fragment below, and the library's own umbrella
//   header is then included in the module purview inside an export block,
//   which exports its declarations without modifying any header.
//
// * Unlike Boost.Any or Boost.PFR, this library is compiled: entities
//   declared in a module purview are attached to the module, and some
//   compilers (e.g. MSVC) mangle their out-of-line definitions with a
//   module qualifier, so they cannot be provided by the classic,
//   non-modular library. The module build therefore compiles the library
//   sources in src/*.cpp as module implementation units (see the
//   BOOST_PROGRAM_OPTIONS_MODULE_UNIT conditionals in those files); the
//   classic build of the same files is unchanged.
//
// * Macros (e.g. BOOST_PROGRAM_OPTIONS_VERSION) are not exported by C++20
//   modules. Code that needs them must keep including the classic headers.
//
// * The module covers everything reachable from <boost/program_options.hpp>.
//   The auxiliary iterator headers <boost/program_options/eof_iterator.hpp>
//   and <boost/program_options/environment_iterator.hpp> are generic
//   utilities outside of that umbrella header and are not exported here.

module;

// Standard headers used by the library's headers, through the local
// compatibility shims in std/ (counterparts of <boost/config/std/*> from
// boostorg/config PR #535 "Adds support for C++20 modules").
// TODO: when that PR is merged, replace the shims with
// <boost/config/std/...> includes.
#include "../std/cassert.hpp"
#include "../std/cwchar.hpp"
#include "../std/iosfwd.hpp"
#include "../std/iterator.hpp"
#include "../std/limits.hpp"
#include "../std/locale.hpp"
#include "../std/map.hpp"
#include "../std/optional.hpp"
#include "../std/set.hpp"
#include "../std/stdexcept.hpp"
#include "../std/string.hpp"
#include "../std/typeinfo.hpp"
#include "../std/utility.hpp"
#include "../std/vector.hpp"

// Boost dependencies used by the library's headers.
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
#include <boost/iterator/iterator_facade.hpp>
#include <boost/noncopyable.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

// Consume the standard library through 'import std;' as well when the
// toolchain provides it (BOOST_PROGRAM_OPTIONS_USE_STD_MODULE, set by CMake
// like in other modularized Boost libraries). The import must come after
// the textual includes above: on MSVC, a textual standard header parsed
// after 'import std;' clashes with the declarations already provided by
// the std module. The textual includes stay in both modes because the
// library's (unconverted) headers include standard headers textually; they
// set the include guards that make those purview includes no-ops, keeping
// the standard library attached to the global module. Libraries whose
// headers are converted to compatibility headers (e.g. Boost.Any) can
// replace them with 'import std;' alone.
#ifdef BOOST_PROGRAM_OPTIONS_USE_STD_MODULE
import std;
#endif

export module boost.program_options;

// Some compilers prune global-module-fragment declarations from the BMI.
// The preloaded boost::any_cast template is instantiated in importing
// translation units (e.g. by variable_value::as<T>()) and looks up
// boost::typeindex::operator== by ADL; such global-module declarations
// must be exported by the module to be usable there (MSVC: error C2679).
export namespace boost { namespace typeindex {
using ::boost::typeindex::operator==;
using ::boost::typeindex::operator!=;
}}

// The library's umbrella header, in the module purview: its declarations
// are attached to this module and exported by the enclosing block. The
// includes of the preloaded dependencies above are no-ops here (include
// guards), so nothing foreign is attached.
export {
#include <boost/program_options.hpp>
}

// Internal headers used by the implementation units: included here once
// (unexported) so that every unit of the module sees the same declarations
// instead of re-including them textually.
#include <boost/program_options/detail/config_file.hpp>
#include <boost/program_options/environment_iterator.hpp>
