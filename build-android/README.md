### Binary ###

Download the latest [build for Android](http://d.etpan.org/mailcore2-deps/mailcore2-android/)

### Build for Android ###

```
$ cp libetpan/build-android/dependencies/cyrus-sasl/cyrus-sasl-android-4.zip mailcore2/build-android/third-party/
$ cp libetpan/build-android/dependencies/openssl/openssl-android-3.zip mailcore2/build-android/third-party/
$ cp libetpan/build-android/libetpan-android-6.zip mailcore2/build-android/third-party/
$ cd mailcore2/build-android/third-party
$ unzip cyrus-sasl-android-4.zip
$ unzip openssl-android-3.zip
$ unzip libetpan-android-6.zip

$ export ANDROID_SDK=/path/to/android-sdk
$ export ANDROID_NDK=/Users/xxx/Library/Android/sdk/ndk/17.2.4988734 #Use ndk 17
$ cd build-android
$ ./build.sh
```

It will produce the following binaries:

- mailcore2-android-*version*.aar

### Running example ###

Copy the binary result of the build (mailcore2-android-*version*.aar) to `mailcore2/example/android/AndroidExample/app/libs`.

- Open the example in Android Studio
- Tweaks the login and password in the class `MessagesSyncManager`
- Then, run it.
