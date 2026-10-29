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

// The library's own declaration headers are skipped in module builds:
// the imported primary interface provides them.
#ifndef BOOST_PROGRAM_OPTIONS_MODULE_UNIT
#include <boost/program_options/positional_options.hpp>
#endif

#include <boost/limits.hpp>

// Standard library compatibility guard, following the pattern of
// <boost/config/std/...> from boostorg/config PR #535 ("Adds support for
// C++20 modules"). TODO: when that PR is merged, replace the textual
// includes with <boost/config/std/...> (see modules/boost_program_options.cppm).
// 'assert' is a macro, which 'import std;' does not provide; keep the
// macro-only header textual in the global module fragment.
#include <cassert>

#if defined(BOOST_USE_MODULES) || defined(BOOST_PROGRAM_OPTIONS_USE_STD_MODULE)
#ifndef BOOST_IN_MODULE_PURVIEW
import std;
#endif
#else
#include <cassert>
#endif // standard library compatibility guard

#ifdef BOOST_PROGRAM_OPTIONS_MODULE_UNIT
module boost.program_options;

// Purview marker of the boost.program_options module units, per the
// convention used by <boost/config/std/...> (boostorg/config PR #535).
#define BOOST_IN_MODULE_PURVIEW
#endif

namespace boost { namespace program_options {

    positional_options_description::positional_options_description()
    {}

    positional_options_description&
    positional_options_description::add(const char* name, int max_count)
    {
        assert(max_count != -1 || m_trailing.empty());

        if (max_count == -1)
            m_trailing = name;
        else {
            m_names.resize(m_names.size() + max_count, name);
        }
        return *this;
    }

    unsigned
    positional_options_description::max_total_count() const
    {
        return m_trailing.empty() ? 
          static_cast<unsigned>(m_names.size()) : (std::numeric_limits<unsigned>::max)();
    }
    
    const std::string& 
    positional_options_description::name_for_position(unsigned position) const
    {
        assert(position < max_total_count());

        if (position < m_names.size())
            return m_names[position];
        else
            return m_trailing;
    }


}}



