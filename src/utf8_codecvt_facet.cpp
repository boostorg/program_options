#ifdef BOOST_PROGRAM_OPTIONS_MODULE_UNIT
// In the boost.program_options module build, this translation unit is a module
// implementation unit. The global module fragment starts here: the textual
// includes below attach their declarations to the global module, the library's
// own declaration headers are skipped (their declarations come from the
// imported primary interface), and the module declaration closes the fragment.
module;
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

#ifdef BOOST_PROGRAM_OPTIONS_MODULE_UNIT
module boost.program_options;

// Purview marker of the boost.program_options module units, per the
// convention used by <boost/config/std/...> (boostorg/config PR #535).
#define BOOST_IN_MODULE_PURVIEW
#endif



