// Copyright Sorush Sabzpour 2026.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Shared global module fragment preloads for the boost.program_options
// module units (the interface in boost_program_options.cppm and the
// implementation units in impl/).
//
// Everything that the library's headers and sources include, except the
// library's own headers, is preloaded here so that the includes triggered
// inside the module purviews are no-ops (include guards) and no foreign
// declarations get attached to the module. Boost.ProgramOptions headers
// must NOT be preloaded here: they are included in the purviews, where
// their declarations are attached to (or, in implementation units,
// redeclare those of) the boost.program_options module.

#ifndef BOOST_PROGRAM_OPTIONS_MODULE_GMF_PRELOAD_HPP
#define BOOST_PROGRAM_OPTIONS_MODULE_GMF_PRELOAD_HPP

// Macro-only header; macros are not exported by 'import std'.
#include <version>

// Standard headers used by the library's headers and sources.
#include <cassert>
#include <cctype>
#include <climits>
#include <clocale>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cwchar>
#include <fstream>
#include <iosfwd>
#include <istream>
#include <iterator>
#include <iostream>
#include <limits>
#include <locale>
#include <map>
#include <optional>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <utility>
#include <vector>

// Boost dependencies used by the library's headers and sources.
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
#include <boost/bind/bind.hpp>
#include <boost/tokenizer.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/noncopyable.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

// The shared utf8_codecvt_facet detail header is macro-parameterized; wrap
// it exactly like <boost/program_options/detail/utf8_codecvt_facet.hpp>
// and src/utf8_codecvt_facet.cpp do, so that the class stays attached to
// the global module, as in classic builds.
#define BOOST_UTF8_BEGIN_NAMESPACE \
     namespace boost { namespace program_options { namespace detail {
#define BOOST_UTF8_END_NAMESPACE }}}
#define BOOST_UTF8_DECL
#include <boost/detail/utf8_codecvt_facet.hpp>
#undef BOOST_UTF8_BEGIN_NAMESPACE
#undef BOOST_UTF8_END_NAMESPACE
#undef BOOST_UTF8_DECL

#endif
