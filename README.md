Program Options, part of the collection of [Boost C++ Libraries](http://github.com/boostorg), allows for definition and acquisition of (name, value) pairs from the user via conventional methods such as command line and config file.  It is roughly analogous to getopt_long, but for use with C++.

### License

Distributed under the [Boost Software License, Version 1.0](http://www.boost.org/LICENSE_1_0.txt).

### Properties

* C++11
* Requires Linking
* Optional C++20 module interface (`import boost.program_options;`)

### C++20 module support

The library ships an optional C++20 module interface, so that instead of

```cpp
#include <boost/program_options.hpp>
```

you can write

```cpp
import boost.program_options;
```

and keep using the `boost::program_options` namespace unchanged.

The interface (`src/cppm/boost/program_options.cppm`) is a thin wrapper: it
includes the classic umbrella header in the global module fragment and
re-exports the public declarations with exported using-declarations. No
library header is modified, every declaration stays attached to the global
module, and the definitions in the classic compiled library are reused
directly. (The export-block style used by header-only libraries such as
Boost.Any and Boost.PFR is not applicable here yet: for a compiled library
it requires module implementation units and modularized dependencies; the
migration can be revisited once the Boost dependencies are modularized.)

The module is not built by default. Enable it by configuring CMake with
`-DBOOST_PROGRAM_OPTIONS_BUILD_MODULES=ON`, which creates the additional
`Boost::program_options_modules` target (it links the classic compiled
library automatically). Building the module requires CMake 3.28+ with the
Ninja generator (CMake 3.30+ with the Visual Studio generator) and a compiler
with C++20 modules support. The `test/module_test.cpp` test verifies that the
exported interface is complete and functional, without including any Boost
header.

Macros (e.g. `BOOST_PROGRAM_OPTIONS_VERSION`) are not exported by C++20
modules; include the classic headers where macros are needed. See
`doc/modules.xml` for details.

### Development

The library is essentially done. No major new features are expected, the primary goal is stability, as well as small
changes to re-align with the evolution of Boost C++ Libraries and C++.

* Good PRs within the scope are welcome. It may take some time, and maybe a ping or two, to get merged.
* Good issues are appreciated, but realistically, might remain open indefinitely, unless you also prepare a PR.
* Drive-by PRs and issues are not welcome.
* AI-assisted PRs are OK, but you should self-review every changed line.

### Build Status
(in progress...)

|Branch          | Travis | Appveyor | codecov.io | Deps | Docs | Tests |
|:-------------: | ------ | -------- | ---------- | ---- | ---- | ----- |
|[`master`](https://github.com/boostorg/program_options/tree/master) | [![Build Status](https://travis-ci.org/boostorg/program_options.svg?branch=master)](https://travis-ci.org/boostorg/program_options) | [![Build status](https://ci.appveyor.com/api/projects/status/e0quisadwh1v7ok5/branch/master?svg=true)](https://ci.appveyor.com/project/vprus/program-options/branch/master) | [![codecov](https://codecov.io/gh/boostorg/program_options/branch/master/graph/badge.svg)](https://codecov.io/gh/boostorg/program_options/branch/master) | [![Deps](https://img.shields.io/badge/deps-master-brightgreen.svg)](https://pdimov.github.io/boostdep-report/master/program_options.html) | [![Documentation](https://img.shields.io/badge/docs-master-brightgreen.svg)](http://www.boost.org/doc/libs/master/doc/html/program_options.html) | [![Enter the Matrix](https://img.shields.io/badge/matrix-master-brightgreen.svg)](https://regression.boost.io/master/developer/program_options.html) 
|[`develop`](https://github.com/boostorg/program_options/tree/develop) | [![Build Status](https://travis-ci.org/boostorg/program_options.svg?branch=develop)](https://travis-ci.org/boostorg/program_options) | [![Build status](https://ci.appveyor.com/api/projects/status/e0quisadwh1v7ok5/branch/develop?svg=true)](https://ci.appveyor.com/project/vprus/program-options/branch/develop) | [![codecov](https://codecov.io/gh/boostorg/program_options/branch/develop/graph/badge.svg)](https://codecov.io/gh/boostorg/program_options/branch/develop) | [![Deps](https://img.shields.io/badge/deps-develop-brightgreen.svg)](https://pdimov.github.io/boostdep-report/develop/program_options.html) | [![Documentation](https://img.shields.io/badge/docs-develop-brightgreen.svg)](http://www.boost.org/doc/libs/develop/doc/html/program_options.html) | [![Enter the Matrix](https://img.shields.io/badge/matrix-develop-brightgreen.svg)](https://regression.boost.io/develop/developer/program_options.html)
 
### Directories

| Name      | Purpose                          |
| --------- | -------------------------------- |
| `build`   | build script for link library    |
| `ci`      | continuous integration scripts   |
| `doc`     | documentation                    |
| `example` | use case examples                |
| `include` | headers                          |
| `src`     | source code for link library and  |
|           | C++20 module interface           |
| `test`    | unit tests                       |

### More information

* [Ask questions](http://stackoverflow.com/questions/ask?tags=c%2B%2B,boost,boost-program_options): Be sure to read the documentation first to see if it answers your question.
* [Report bugs](https://github.com/boostorg/program_options/issues): Be sure to mention Boost version, platform and compiler you're using. A small compilable code sample to reproduce the problem is always good as well.
* [Submit Pull Requests](https://github.com/boostorg/program_options/pulls) against the **develop** branch. Note that by submitting patches you agree to license your modifications under the [Boost Software License, Version 1.0](http://www.boost.org/LICENSE_1_0.txt).  Be sure to include tests proving your changes work properly.
* Discussions about the library are held on the [Boost developers mailing list](http://www.boost.org/community/groups.html#main). Be sure to read the [discussion policy](http://www.boost.org/community/policy.html) before posting and add the `[program_options]` tag at the beginning of the subject line.
