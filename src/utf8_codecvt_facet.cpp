#ifdef BOOST_PROGRAM_OPTIONS_MODULE_UNIT
// In the boost.program_options module build, this translation unit is a
// module implementation unit: it provides the module-attached definitions
// matching the interface in src/cppm/boost/program_options.cppm. In the
// classic build (below) this file is compiled unchanged.
module;

// Dependencies included by this file, preloaded in the global module
// fragment so that nothing foreign is attached to the module.
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
#define BOOST_UTF8_BEGIN_NAMESPACE \
     namespace boost { namespace program_options { namespace detail {
#define BOOST_UTF8_END_NAMESPACE }}}
#define BOOST_UTF8_DECL
#include <boost/detail/utf8_codecvt_facet.hpp>
#undef BOOST_UTF8_BEGIN_NAMESPACE
#undef BOOST_UTF8_END_NAMESPACE
#undef BOOST_UTF8_DECL
#include <boost/program_options/config.hpp>

module boost.program_options;

// The library's own headers included below are no-ops: their declarations
// are provided by the imported primary interface.
#define BOOST_ERRORS_VP_2003_01_02
#define BOOST_CMDLINE_HPP_VP_2004_03_13
#define BOOST_OPTION_HPP_VP_2004_02_25
#define BOOST_VALUE_SEMANTIC_HPP_VP_2004_02_24
#define BOOST_OPTION_DESCRIPTION_VP_2003_05_19
#define BOOST_PROGRAM_OPTIONS_POSITIONAL_OPTIONS_VP_2004_03_02
#define BOOST_PARSERS_VP_2003_05_19
#define BOOST_VARIABLES_MAP_VP_2003_05_19
#define BOOST_CMDLINE_VP_2003_05_19
#define BOOST_CONVERT_HPP_VP_2004_04_28
#define BOOST_CONFIG_FILE_VP_2003_01_02
#define BOOST_ENVIRONMENT_ITERATOR_VP_2004_05_14
#define BOOST_EOF_ITERATOR_VP_2004_03_12
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

