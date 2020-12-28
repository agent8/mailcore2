#!/bin/sh

pushd "`dirname "$0"`" > /dev/null
scriptpath="`pwd`"
popd > /dev/null

. "$scriptpath/include.sh/edo-build-dep.sh"

name="mailcore2-ios"
xcode_target="EdoMailcore2"
xcode_project="mailcore2.xcodeproj"
library="libEdoMailcore2.a"
embedded_deps="ctemplate-ios libsasl-ios tidy-html5-ios"
build_mailcore=1
build_for_external=1

build_git_ios
