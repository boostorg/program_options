// Copyright Sorush Sabzpour 2026.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Local counterpart of <boost/config/std/utility.hpp> from boostorg/config
// PR #535 "Adds support for C++20 modules" (not merged yet). It follows
// that PR's compatibility-header pattern so that, in the future modules
// mode (BOOST_USE_MODULES), the standard library is consumed through
// 'import std;' instead of textual includes inside module units.
//
// TODO: when boostorg/config PR #535 is merged, replace the callers of
// this shim with <boost/config/std/utility.hpp> and delete this file.

#ifdef BOOST_USE_MODULES
#ifndef BOOST_IN_MODULE_PURVIEW
import std;
#endif
#else
#include <utility>
#endif
