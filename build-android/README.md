### Binary ###

Download the latest [build for Android](http://d.etpan.org/mailcore2-deps/mailcore2-android/)

### Build for Android ###
Mailcore library depends on the libetpan library.
$ cp libetpan/build-android/dependencies/cyrus-sasl/cyrus-sasl-android-4.zip mailcore2/build-android/third-party/
$ cp libetpan/build-android/dependencies/openssl/openssl-android-3.zip mailcore2/build-android/third-party/
$ cp libetpan/build-android/libetpan-android-6.zip mailcore2/build-android/third-party/
-$ cd mailcore2/build-android/third-party
-$ unzip cyrus-sasl-android-4.zip
-$ unzip openssl-android-3.zip
-$ unzip libetpan-android-6.zip

```
$ cd mailcore2/build-android/
Unzip the third-party-all-abi.zip file to the third-party directory;

Unzip all the .zip files(ctemplate-android-3.zip, iconv-android-1.zip, libxml2-android-3.zip, tidy-html5-android-3.zip, icu4c-android-3.zip);
Don't need to recompile these libraries, we just use these libraries directly.

$ export ANDROID_SDK=/path/to/android-sdk
$ export ANDROID_NDK=/Users/xxx/Library/Android/sdk/ndk/28.2.13676358 #Use ndk 28
$ cd mailcore2/build-android/
$ ./build.sh
```

It will produce the following binaries:

- mailcore2-android-*version*.aar


### Source codes of some libraries 
ctemplate:
https://github.com/agent8/ctemplate

Libiconv:
https://github.com/dinhvh/libetpan/tree/master/build-android/dependencies/iconv

Libxml2:
https://github.com/dinhvh/libxml2

Icu4c(version 54.2):
https://github.com/unicode-org/icu/releases/download/release-54-2/icu4c-54_2-src.tgz
Or
https://github.com/unicode-org/icu/releases/tag/release-54-2/icu4c-54_2-src.tgz

Tidy-html:
https://github.com/dinhvh/tidy-html5/tree/10c3674befa76f0f8c56e2944959a0ba9e1ef638


### Running example ###

Copy the binary result of the build (mailcore2-android-*version*.aar) to `mailcore2/example/android/AndroidExample/app/libs`.

- Open the example in Android Studio
- Tweaks the login and password in the class `MessagesSyncManager`
- Then, run it.
