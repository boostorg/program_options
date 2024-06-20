# Use, modification, and distribution are
# subject to the Boost Software License, Version 1.0. (See accompanying
# file LICENSE.txt)
#
# Copyright Rene Rivera 2020.

# For Drone CI we use the Starlark scripting language to reduce duplication.
# As the yaml syntax for Drone CI is rather limited.
#
#
globalenv={'B2_VARIANT': 'variant=release,debug'}
linuxglobalimage="cppalliance/droneubuntu1404:1"
windowsglobalimage="cppalliance/dronevs2019"

def main(ctx):
  return [
  linux_cxx("COMMENT=C++03 TOOLSET=gcc,gcc-7 Job 0", "g++", packages="g++-7", buildtype="boost", buildscript="drone", image=linuxglobalimage, environment={'COMMENT': 'C++03', 'TOOLSET': 'gcc,gcc-7', 'DRONE_JOB_UUID': 'b6589fc6ab'}, globalenv=globalenv),
  linux_cxx("COMMENT=C++11 TOOLSET=clang CXXSTD=11 Job 1", "clang++", packages="g++-7", buildtype="boost", buildscript="drone", image=linuxglobalimage, environment={'COMMENT': 'C++11', 'TOOLSET': 'clang', 'CXXSTD': '11', 'DRONE_JOB_UUID': '356a192b79'}, globalenv=globalenv),
  linux_cxx("COMMENT=valgrind TOOLSET=clang B2_VARIANT=var Job 2", "clang++", packages="clang-5.0 libstdc++-7-dev valgrind", llvm_os="trusty", llvm_ver="5.0", buildtype="boost", buildscript="drone", image=linuxglobalimage, environment={'COMMENT': 'valgrind', 'TOOLSET': 'clang', 'B2_VARIANT': 'variant=debug', 'TESTFLAGS': 'testing.launcher=valgrind', 'DRONE_JOB_UUID': 'da4b9237ba'}, globalenv=globalenv),
  linux_cxx("COMMENT=cppcheck Job 3", "g++", packages="binutils-gold gdb libc6-dbg", buildtype="15edef0d20-06e41ec903", buildscript="drone", image=linuxglobalimage, environment={'COMMENT': 'cppcheck', 'DRONE_JOB_UUID': '77de68daec'}, globalenv=globalenv),
  linux_cxx("COMMENT=CodeCov TOOLSET=gcc-7 Job 4", "g++", packages="gcc-7 g++-7", buildtype="15edef0d20-35de83136e", buildscript="drone", image=linuxglobalimage, environment={'COMMENT': 'CodeCov', 'TOOLSET': 'gcc-7', 'DRONE_JOB_UUID': '1b64538924'}, globalenv=globalenv),
    ]

# from https://github.com/boostorg/boost-ci
load("@boost_ci//ci/drone/:functions.star", "linux_cxx","windows_cxx","osx_cxx","freebsd_cxx")
