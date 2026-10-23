#ifdef BOOST_PROGRAM_OPTIONS_MODULE_UNIT
// In the boost.program_options module build, this translation unit is a
// module implementation unit providing the module-attached definitions
// matching the interface in modules/boost_program_options.cppm. The
// classic code below is compiled unchanged except that its includes are
// skipped: their declarations come from the imported interface, and the
// non-program_options headers are preloaded here instead.
module;

// Dependencies of the classic code below, preloaded in the global module
// fragment so that nothing foreign is attached to the module.
#include <boost/throw_exception.hpp>
#include <boost/bind/bind.hpp>
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
#include <fstream>
#include <locale.h>
#include <locale>
#include <iostream>
#include <string>
#include <stdexcept>
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


#ifndef BOOST_PROGRAM_OPTIONS_MODULE_UNIT
#include <boost/config.hpp>

#ifndef BOOST_PROGRAM_OPTIONS_SOURCE
# define BOOST_PROGRAM_OPTIONS_SOURCE
#endif
#include <boost/program_options/config.hpp>
#include <boost/program_options/detail/convert.hpp>
#include <boost/program_options/detail/utf8_codecvt_facet.hpp>
#include <boost/throw_exception.hpp>

#include <boost/bind/bind.hpp>

// Standard library compatibility guard, following the pattern of
// <boost/config/std/...> from boostorg/config PR #535 ("Adds support for
// C++20 modules"). TODO: when that PR is merged, replace the textual
// includes with <boost/config/std/...> (see modules/boost_program_options.cppm).
#ifdef BOOST_USE_MODULES
#ifndef BOOST_IN_MODULE_PURVIEW
import std;
#endif
#else
#include <fstream>
#include <locale.h>
#include <locale>
#include <iostream>
#include <string>
#include <locale>
#include <stdexcept>
#endif // standard library compatibility guard
#endif // !BOOST_PROGRAM_OPTIONS_MODULE_UNIT

using namespace std;
using namespace boost::placeholders;

namespace boost { namespace detail {

    /* Internal function to actually perform conversion.
       The logic in from_8_bit and to_8_bit function is exactly
       the same, except that one calls 'in' method of codecvt and another
       calls the 'out' method, and that syntax difference makes straightforward
       template implementation impossible.

       This functions takes a 'fun' argument, which should have the same 
       parameters and return type and the in/out methods. The actual converting
       function will pass functional objects created with boost::bind.
       Experiments show that the performance loss is less than 10%.
    */
    template<class ToChar, class FromChar, class Fun>
    std::basic_string<ToChar>
    convert(const std::basic_string<FromChar>& s, Fun fun)
        
    {
        std::basic_string<ToChar> result;
        
        std::mbstate_t state = std::mbstate_t();

        const FromChar* from = s.data();
        const FromChar* from_end = s.data() + s.size();
        // The interface of cvt is not really iterator-like, and it's
        // not possible the tell the required output size without the conversion.
        // All we can is convert data by pieces.
        while(from != from_end) {
            
            // std::basic_string does not provide non-const pointers to the data,
            // so converting directly into string is not possible.
            ToChar buffer[32];
            
            ToChar* to_next = buffer;
            // Need variable because boost::bind doesn't work with rvalues.
            ToChar* to_end = buffer + 32;
            std::codecvt_base::result r = 
                fun(state, from, from_end, from, buffer, to_end, to_next);
            
            if (r == std::codecvt_base::error)
                boost::throw_exception(
                    std::logic_error("character conversion failed"));
            // 'partial' is not an error, it just means not all source
            // characters were converted. However, we need to check that at
            // least one new target character was produced. If not, it means
            // the source data is incomplete, and since we don't have extra
            // data to add to source, it's error.
            if (to_next == buffer)
                boost::throw_exception(
                    std::logic_error("character conversion failed"));
            
            // Add converted characters
            result.append(buffer, to_next);
        }
        
        return result;        
    }           
}}

namespace boost {

#ifndef BOOST_NO_STD_WSTRING
    BOOST_PROGRAM_OPTIONS_DECL std::wstring 
    from_8_bit(const std::string& s, 
               const std::codecvt<wchar_t, char, std::mbstate_t>& cvt)
    {
        return detail::convert<wchar_t>(
            s,                 
            boost::bind(&std::codecvt<wchar_t, char, mbstate_t>::in,
                        &cvt,
                        _1, _2, _3, _4, _5, _6, _7));
    }

    BOOST_PROGRAM_OPTIONS_DECL std::string 
    to_8_bit(const std::wstring& s, 
             const std::codecvt<wchar_t, char, std::mbstate_t>& cvt)
    {
        return detail::convert<char>(
            s,                 
            boost::bind(&codecvt<wchar_t, char, mbstate_t>::out,
                        &cvt,
                        _1, _2, _3, _4, _5, _6, _7));
    }


    namespace {
        boost::program_options::detail::utf8_codecvt_facet
            utf8_facet;
    }
    
    BOOST_PROGRAM_OPTIONS_DECL std::wstring
    from_utf8(const std::string& s)
    {
        return from_8_bit(s, utf8_facet);
    }
    
    BOOST_PROGRAM_OPTIONS_DECL std::string
    to_utf8(const std::wstring& s)
    {
        return to_8_bit(s, utf8_facet);
    }

    BOOST_PROGRAM_OPTIONS_DECL std::wstring
    from_local_8_bit(const std::string& s)
    {
        typedef codecvt<wchar_t, char, mbstate_t> facet_type;
        return from_8_bit(s, 
                          BOOST_USE_FACET(facet_type, locale()));
    }

    BOOST_PROGRAM_OPTIONS_DECL std::string
    to_local_8_bit(const std::wstring& s)
    {
        typedef codecvt<wchar_t, char, mbstate_t> facet_type;
        return to_8_bit(s, 
                        BOOST_USE_FACET(facet_type, locale()));                        
    }
#endif

    namespace program_options
    {
        BOOST_PROGRAM_OPTIONS_DECL std::string to_internal(const std::string& s)
        {
            return s;
        }

#ifndef BOOST_NO_STD_WSTRING
        BOOST_PROGRAM_OPTIONS_DECL std::string to_internal(const std::wstring& s)
        {
            return to_utf8(s);
        }
#endif
    }


}

