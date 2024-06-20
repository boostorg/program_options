#!/bin/bash

# Copyright 2020 Rene Rivera, Sam Darwin
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.txt or copy at http://boost.org/LICENSE_1_0.txt)

set -e
export TRAVIS_BUILD_DIR=$(pwd)
export DRONE_BUILD_DIR=$(pwd)
export TRAVIS_BRANCH=$DRONE_BRANCH
export VCS_COMMIT_ID=$DRONE_COMMIT
export GIT_COMMIT=$DRONE_COMMIT
export REPO_NAME=$DRONE_REPO
export PATH=~/.local/bin:/usr/local/bin:$PATH

if [ "$DRONE_JOB_BUILDTYPE" == "boost" ]; then

echo '==================================> INSTALL'

export SELF=`basename $REPO_NAME`
cd ..
git clone -b $TRAVIS_BRANCH --depth 1 https://github.com/boostorg/boost.git boost-root
cd boost-root
git submodule update -q --init tools/boostdep
git submodule update -q --init tools/build
git submodule update -q --init tools/inspect
cp -r $TRAVIS_BUILD_DIR/* libs/$SELF
export BOOST_ROOT="`pwd`"
export PATH="`pwd`":$PATH
python tools/boostdep/depinst/depinst.py $SELF --include example
./bootstrap.sh
./b2 headers

echo '==================================> SCRIPT'

cd libs/$SELF
ci/build.sh

elif [ "$DRONE_JOB_BUILDTYPE" == "15edef0d20-06e41ec903" ]; then

echo '==================================> INSTALL'

export SELF=`basename $REPO_NAME`
cd ..
git clone -b $TRAVIS_BRANCH --depth 1 https://github.com/boostorg/boost.git boost-root
cd boost-root
git submodule update -q --init tools/boostdep
git submodule update -q --init tools/build
git submodule update -q --init tools/inspect
cp -r $TRAVIS_BUILD_DIR/* libs/$SELF
export BOOST_ROOT="`pwd`"
export PATH="`pwd`":$PATH
python tools/boostdep/depinst/depinst.py $SELF --include example
./bootstrap.sh
./b2 headers

echo '==================================> SCRIPT'

libs/$SELF/ci/cppcheck.sh

elif [ "$DRONE_JOB_BUILDTYPE" == "15edef0d20-35de83136e" ]; then

echo '==================================> INSTALL'

export SELF=`basename $REPO_NAME`
cd ..
git clone -b $TRAVIS_BRANCH --depth 1 https://github.com/boostorg/boost.git boost-root
cd boost-root
git submodule update -q --init tools/boostdep
git submodule update -q --init tools/build
git submodule update -q --init tools/inspect
cp -r $TRAVIS_BUILD_DIR/* libs/$SELF
export BOOST_ROOT="`pwd`"
export PATH="`pwd`":$PATH
python tools/boostdep/depinst/depinst.py $SELF --include example
./bootstrap.sh
./b2 headers

echo '==================================> SCRIPT'

pushd /tmp && git clone https://github.com/linux-test-project/lcov.git && cd lcov && sudo make install && which lcov && lcov --version && popd
cd libs/$SELF
ci/codecov.sh

fi
