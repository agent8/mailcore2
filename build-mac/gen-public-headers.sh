#!/bin/sh

files=""

# create folder
if test ! -d ./include/MailCore/
then
    mkdir -p ./include/MailCore/
fi

list_headers()
{
  local filename="$1"
  
  if echo $files | grep "\[$filename\]" >/dev/null ; then
    return
  fi
  
  local path="`find ../src -name $filename`"
  echo $path
  cp -f $path ./include/MailCore/
  #echo $path | sed 's/^.\//src\//' | sed 's/\//\\/g'
  files="$files[$filename]"
  subfilenames="`grep '#include <MailCore/' "$path" | sed 's/^#include <MailCore\/\(.*\)>$/\1/'`"
  subfilenames+=" "
  subfilenames+="`grep '#import <MailCore/' "$path" | sed 's/^#import <MailCore\/\(.*\)>$/\1/'`"
  for include_dir in $subfilenames ; do
    list_headers $include_dir
  done
}

#cd ../src
list_headers MailCore.h
