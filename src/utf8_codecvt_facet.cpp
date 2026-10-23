#ifdef BOOST_PROGRAM_OPTIONS_MODULE_UNIT
// In the boost.program_options module build, this translation unit is a
// module implementation unit providing the module-attached definitions
// matching the interface in modules/boost_program_options.cppm. In the
// classic build (below) this file is compiled unchanged.
module;

// The headers this file includes, preloaded in the global module fragment
// so that nothing foreign is attached to the module. The library's own
// headers included below are no-ops (guards predefined after the module
// declaration): their declarations come from the imported interface.
#include <boost/limits.hpp>
#include <boost/throw_exception.hpp>
#include <boost/program_options/config.hpp>

#define BOOST_UTF8_BEGIN_NAMESPACE \
     namespace boost { namespace program_options { namespace detail {
#define BOOST_UTF8_END_NAMESPACE }}}
#define BOOST_UTF8_DECL
#include <boost/detail/utf8_codecvt_facet.hpp>
#undef BOOST_UTF8_BEGIN_NAMESPACE
#undef BOOST_UTF8_END_NAMESPACE
#undef BOOST_UTF8_DECL

// Standard library compatibility guard, following the pattern of
// <boost/config/std/...> from boostorg/config PR #535 ("Adds support for
// C++20 modules"). TODO: when that PR is merged, replace the textual
// includes with <boost/config/std/...> (see modules/boost_program_options.cppm).
#ifdef BOOST_USE_MODULES
#ifndef BOOST_IN_MODULE_PURVIEW
import std;
#endif
#else
#include <cassert>
#include <cstdlib>
#include <cstddef>
#endif // standard library compatibility guard

module boost.program_options;

// Purview marker of the boost.program_options module units, per the
// convention used by <boost/config/std/...> (boostorg/config PR #535).
#define BOOST_IN_MODULE_PURVIEW

#endif

// Copyright Vladimir Prus 2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROGRAM_OPTIONS_SOURCE
# define BOOST_PROGRAM_OPTIONS_SOURCE
#endif
#include <boost/program_options/config.hpp>

#define BOOST_UTF8_BEGIN_NAMESPACE \
     namespace boost { namespace program_options { namespace detail {

#define BOOST_UTF8_END_NAMESPACE }}}
#define BOOST_UTF8_DECL BOOST_PROGRAM_OPTIONS_DECL

#include <boost/detail/utf8_codecvt_facet.ipp>


#undef BOOST_UTF8_BEGIN_NAMESPACE
#undef BOOST_UTF8_END_NAMESPACE
#undef BOOST_UTF8_DECL


