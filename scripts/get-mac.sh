#!/bin/sh

pushd "`dirname "$0"`" > /dev/null
scriptpath="`pwd`"
popd > /dev/null

echo "In get-mac.sh  scriptpath: $scriptpath"

. "$scriptpath/include.sh/build-dep.sh"

deps="ctemplate-osx libetpan-osx"
for dep in $deps ; do
  name="$dep"
  get_prebuilt_dep
done

if test "x$CONFIGURATION_BUILD_DIR" != x ; then
	echo "In get-mac.sh  CONFIGURATION_BUILD_DIR: $CONFIGURATION_BUILD_DIR"
  	mkdir -p "$CONFIGURATION_BUILD_DIR"
  	cd "$scriptpath/../Externals"
  	for dep in $deps ; do
    	if test -d "$dep" ; then
      		if test -d "$dep"/lib ; then
      			#if test dep = "libetpan-osx" ; then
      			if [ "$dep"x = "libetpan-osx"x ]; then
        			echo "rsync -a $dep/lib/ $CONFIGURATION_BUILD_DIR skipped"
        		else
        			echo "rsync -a $dep/lib/ $CONFIGURATION_BUILD_DIR"
        			rsync -a "$dep"/lib/ "$CONFIGURATION_BUILD_DIR"
        		fi
      		fi
      		if test -d "$dep"/include ; then
        		echo "rsync -a $dep/include/ $CONFIGURATION_BUILD_DIR/include/"
        		rsync -a "$dep"/include/ "$CONFIGURATION_BUILD_DIR/include/"
      		fi
    	fi
  	done
fi
