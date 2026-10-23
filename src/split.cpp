#ifdef BOOST_PROGRAM_OPTIONS_MODULE_UNIT
// In the boost.program_options module build, this translation unit is a
// module implementation unit providing the module-attached definitions
// matching the interface in src/cppm/boost/program_options.cppm. In the
// classic build (below) this file is compiled unchanged.
module;

// The headers this file includes, preloaded in the global module fragment
// so that nothing foreign is attached to the module. The library's own
// headers included below are no-ops (guards predefined after the module
// declaration): their declarations come from the imported interface.
#include "cppm/std/string.hpp"
#include "cppm/std/vector.hpp"
#include <boost/tokenizer.hpp>
#include "cppm/std/cstddef.hpp"
#include <boost/throw_exception.hpp>
#include <boost/program_options/config.hpp>

module boost.program_options;

#define BOOST_PARSERS_VP_2003_05_19
#endif

// Copyright Sascha Ochsenknecht 2009.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROGRAM_OPTIONS_SOURCE
# define BOOST_PROGRAM_OPTIONS_SOURCE
#endif

#include <boost/program_options/parsers.hpp>
#include <boost/tokenizer.hpp>

#include <string>
#include <vector>

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

