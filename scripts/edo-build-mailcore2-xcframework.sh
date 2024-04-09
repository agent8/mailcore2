#!/bin/sh

cd "$(dirname "$0")"
cd ../

MAILCORE_DIR="`pwd`"
BUILD_DIR="$MAILCORE_DIR/Externals"
FRAMEWORK_NAME="MailCore.xcframework"

mkdir -p $BUILD_DIR
rm -rf "$BUILD_DIR/$FRAMEWORK_NAME"

cd build-mac
    
# Build iOS Archive
xcodebuild archive -scheme "mailcore ios" \
    -destination "generic/platform=iOS" \
    VALID_ARCHS="arm64" \
    -archivePath "$BUILD_DIR/mailcore2.iOS.xcarchive" \
    -sdk iphoneos \
    SKIP_INSTALL=NO \
    BUILD_LIBRARY_FOR_DISTRIBUTION=YES | xcpretty

# Build iOS Simulator Archive
xcodebuild archive -scheme "mailcore ios" \
    -destination "generic/platform=iOS Simulator" \
    VALID_ARCHS="arm64 x86_64" \
    -archivePath "$BUILD_DIR/mailcore2.iOS-Simulator.xcarchive" \
    -sdk iphonesimulator \
    SKIP_INSTALL=NO \
    BUILD_LIBRARY_FOR_DISTRIBUTION=YES  | xcpretty

cd $BUILD_DIR

# Create Combined XCArchive - REMOVE ONCE MAC CATALYST BUILDING IS FIXED
xcodebuild -create-xcframework \
	-framework "mailcore2.iOS-Simulator.xcarchive/Products/Library/Frameworks/MailCore.framework" \
	-framework "mailcore2.iOS.xcarchive/Products/Library/Frameworks/MailCore.framework" \
	-output "$FRAMEWORK_NAME"

# Clean Up
rm -rf "$BUILD_DIR/mailcore2.iOS-Simulator.xcarchive"
rm -rf "$BUILD_DIR/mailcore2.iOS.xcarchive"
