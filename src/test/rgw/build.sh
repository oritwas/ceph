#!/bin/sh

branch=$1

function get_processors() {
    if test -n "$NPROC" ; then
        echo $NPROC
    else
        if test $(nproc) -ge 2 ; then
            expr $(nproc) / 2
        else
            echo 1
        fi
    fi
}

DEFAULT_MAKEOPTS=${DEFAULT_MAKEOPTS:--j$(get_processors)}
BUILD_MAKEOPTS=${BUILD_MAKEOPTS:-$DEFAULT_MAKEOPTS}

function clone() {
    git clone $1 $2
    cd $2
}

function main() {
    git checkout $branch
    git submodule update
    ./autogen.sh || return 1
    ./configure "$@" --disable-static --with-radosgw --with-debug --without-lttng \
             CC="ccache gcc" CXX="ccache g++" CFLAGS="-Wall -g" CXXFLAGS="-Wall -g" || return 1
    cd src
    make $BUILD_MAKEOPTS || return 1
}

main "$@"
