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
#include <boost/limits.hpp>
#include <boost/throw_exception.hpp>
#include <boost/program_options/config.hpp>

// Standard library compatibility guard, following the pattern of
// <boost/config/std/...> from boostorg/config PR #535 ("Adds support for
// C++20 modules"). TODO: when that PR is merged, replace the textual
// includes with <boost/config/std/...> (see src/cppm/boost/program_options.cppm).
#ifdef BOOST_USE_MODULES
#ifndef BOOST_IN_MODULE_PURVIEW
import std;
#endif
#else
#include <cassert>
#include <cstddef>
#endif // standard library compatibility guard

module boost.program_options;

// Purview marker of the boost.program_options module units, per the
// convention used by <boost/config/std/...> (boostorg/config PR #535).
#define BOOST_IN_MODULE_PURVIEW

#define BOOST_PROGRAM_OPTIONS_POSITIONAL_OPTIONS_VP_2004_03_02
#endif

// Copyright Vladimir Prus 2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROGRAM_OPTIONS_SOURCE
# define BOOST_PROGRAM_OPTIONS_SOURCE
#endif
#include <boost/program_options/config.hpp>

#include <boost/program_options/positional_options.hpp>

#include <boost/limits.hpp>

// Standard library compatibility guard, following the pattern of
// <boost/config/std/...> from boostorg/config PR #535 ("Adds support for
// C++20 modules"). TODO: when that PR is merged, replace the textual
// includes with <boost/config/std/...> (see src/cppm/boost/program_options.cppm).
#ifdef BOOST_USE_MODULES
#ifndef BOOST_IN_MODULE_PURVIEW
import std;
#endif
#else
#include <cassert>
#endif // standard library compatibility guard

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


