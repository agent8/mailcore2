#!/bin/sh

pushd "`dirname "$0"`" > /dev/null
scriptpath="`pwd`"
popd > /dev/null

. "$scriptpath/include.sh/edo-build-dep-cocoapod.sh"

name="mailcore2-ios"
xcode_target="edo Mailcore2"
xcode_project="mailcore2.xcodeproj"
library="libEdoMailcore2.a"
embedded_deps="ctemplate-ios libsasl-ios tidy-html5-ios"
build_mailcore=1
TOPDIR="$scriptpath/.."

build_git_ios
