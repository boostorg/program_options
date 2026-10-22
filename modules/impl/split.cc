// Copyright Sorush Sabzpour 2026.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Module implementation unit for src/split.cpp. Together with the module
// interface in modules/boost_program_options.cppm, this attaches the
// library's definitions to the boost.program_options module, matching the
// attachment of the exported declarations. See the notes in that file.

module;

#include "../gmf_preload.hpp"

// Macros used by the sources (the library's headers are no-ops below).
#include <boost/program_options/config.hpp>

module boost.program_options;

// The library's headers are no-ops in this unit: their declarations are
// provided by the imported primary interface.
#define BOOST_PROGRAM_OPTIONS_MODULE_IMPL_UNIT

#include "../../src/split.cpp"