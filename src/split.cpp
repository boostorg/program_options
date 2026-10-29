#ifdef BOOST_PROGRAM_OPTIONS_MODULE_UNIT
// In the boost.program_options module build, this translation unit is a module
// implementation unit. The global module fragment starts here: the textual
// includes below attach their declarations to the global module, the library's
// own declaration headers are skipped (their declarations come from the
// imported primary interface), and the module declaration closes the fragment.
module;
#endif

// Copyright Sascha Ochsenknecht 2009.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROGRAM_OPTIONS_SOURCE
# define BOOST_PROGRAM_OPTIONS_SOURCE
#endif

// The library's own declaration headers are skipped in module builds:
// the imported primary interface provides them.
#ifndef BOOST_PROGRAM_OPTIONS_MODULE_UNIT
#include <boost/program_options/parsers.hpp>
#endif
#include <boost/tokenizer.hpp>

#ifdef BOOST_PROGRAM_OPTIONS_MODULE_UNIT
// Declarations the classic build gets transitively through the
// library's own headers (skipped above in this mode).
#include <boost/program_options/config.hpp>
#endif

// Standard library compatibility guard, following the pattern of
// <boost/config/std/...> from boostorg/config PR #535 ("Adds support for
// C++20 modules"). TODO: when that PR is merged, replace the textual
// includes with <boost/config/std/...> (see modules/boost_program_options.cppm).
#if defined(BOOST_USE_MODULES) || defined(BOOST_PROGRAM_OPTIONS_USE_STD_MODULE)
#ifndef BOOST_IN_MODULE_PURVIEW
import std;
#endif
#else
#include <string>
#include <vector>
#endif // standard library compatibility guard

#ifdef BOOST_PROGRAM_OPTIONS_MODULE_UNIT
module boost.program_options;

// Purview marker of the boost.program_options module units, per the
// convention used by <boost/config/std/...> (boostorg/config PR #535).
#define BOOST_IN_MODULE_PURVIEW
#endif

namespace boost { namespace program_options { namespace detail {

   template< class charT >
   std::vector<std::basic_string<charT> > 
   split_unix(
         const std::basic_string<charT>& cmdline, 
         const std::basic_string<charT>& seperator, 
         const std::basic_string<charT>& quote, 
         const std::basic_string<charT>& escape)
   {   
      typedef boost::tokenizer< boost::escaped_list_separator<charT>, 
            typename std::basic_string<charT>::const_iterator, 
            std::basic_string<charT> >  tokenizerT;
         
      tokenizerT tok(cmdline.begin(), cmdline.end(), 
                boost::escaped_list_separator< charT >(escape, seperator, quote));
         
      std::vector< std::basic_string<charT> > result;
      for (typename tokenizerT::iterator cur_token(tok.begin()), end_token(tok.end()); cur_token != end_token; ++cur_token) {
         if (!cur_token->empty())
            result.push_back(*cur_token);
      }
      return result;
   }
   
}}}   // namespace

namespace boost { namespace program_options {

   // Take a command line string and splits in into tokens, according
   // to the given collection of seperators chars.
   BOOST_PROGRAM_OPTIONS_DECL std::vector<std::string> 
   split_unix(const std::string& cmdline, const std::string& seperator, 
         const std::string& quote, const std::string& escape)
   {
      return detail::split_unix< char >(cmdline, seperator, quote, escape);
   }

#ifndef BOOST_NO_STD_WSTRING
   BOOST_PROGRAM_OPTIONS_DECL std::vector<std::wstring>
   split_unix(const std::wstring& cmdline, const std::wstring& seperator, 
         const std::wstring& quote, const std::wstring& escape)
   {
      return detail::split_unix< wchar_t >(cmdline, seperator, quote, escape);
   }
#endif

}}  // namespace



