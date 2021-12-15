## MailCore 2: Introduction ##

MailCore 2 provides a simple and asynchronous Objective-C API to work with the e-mail protocols **IMAP**, **POP** and **SMTP**. The API has been redesigned from the ground up.  It features:

- **POP**, **IMAP** and **SMTP** support
- **[RFC822](http://www.ietf.org/rfc/rfc0822.txt)** parser and generator
- **Asynchronous** APIs
- **HTML** rendering of messages
- **iOS** and **Mac** support

[![Build Status](https://travis-ci.org/MailCore/mailcore2.png?branch=master)](https://travis-ci.org/MailCore/mailcore2)


## Installation ##

### Build for iOS/OSX ###

Read [instructions for iOS/OSX](https://github.com/MailCore/mailcore2/blob/master/build-mac/README.md).

### Build for Android ###

Read [instructions for Android](https://github.com/MailCore/mailcore2/blob/master/build-android/README.md).

### Build for Windows ###

Read [instructions for Windows](https://github.com/MailCore/mailcore2/blob/master/build-windows/README.md).

### Build for Linux ###

Read [instructions for Linux](https://github.com/MailCore/mailcore2/blob/master/build-linux/README.md).

## Basic IMAP Usage ##

Using MailCore 2 is just a little more complex conceptually than the original MailCore.  All fetch requests in MailCore 2 are made asynchronously through a queue.  What does this mean?  Well, let's take a look at a simple example:

```swift
  let session = MCOIMAPSession()
  
  session.hostname       = "imap.gmail.com"
  session.port           = 993
  session.username       = "ADDRESS@gmail.com"
  session.password       = "123456"
  session.connectionType = .TLS
  
  let folder = "INBOX"
  let uids   = MCOIndexSet(range: MCORange(location: 1, length: UInt64.max))
  
  if let fetchOperation = session.fetchMessagesOperation(withFolder: folder, requestKind: .headers, uids: uids) {
    fetchOperation.start { error, fetchedMessages, vanishedMessages in
      // We've finished downloading the messages!
      
      // Let's check if there was an error
      if let error = error {
        print("Error downloading message headers: \(error.localizedDescription)")
      }
      
      // And, let's print out the messages:
      print("The post man delivereth: \(fetchedMessages.debugDescription)")
    }
  }
```
(You can also read an [Objective-C Version](https://github.com/MailCore/mailcore2/wiki/IMAP-Examples))

In this sample, we retrieved and printed a list of email headers from an IMAP server.  In order to execute the fetch, we request an asynchronous operation object from the `MCOIMAPSession` instance with our parameters (more on this later).  This operation object is able to initiate a connection to Gmail when we call the `start` method.  Now here's where things get a little tricky.  We call the `start` function with a block, which is executed on the main thread when the fetch operation completes.  The actual fetching from IMAP is done on a **background thread**, leaving your UI and other processing **free to use the main thread**.

## Documentation ##

* Class documentation [Obj-C](http://libmailcore.com/api/objc/index.html) / [Java](http://libmailcore.com/api/java/index.html)
* [Wiki](https://github.com/MailCore/mailcore2/wiki)

## License ##

MailCore 2 is BSD-Licensed.

## MailCore Supporters ##

[<img src="https://triage.cc/triage-badge.png" width="180">](https://triage.cc?ref=mailcore)

## Add by farmer

compile libetpan and mailcore2

1. install homebrew.
2. brew install automake
3. brew install ibtool*
4. enter libetpan folder, cd build-android,./build.sh
5. copy libetpan-android-6.zip and dependencies/cyrus-sasl/cyrus-sasl-android-4.zip to mailcore2/build-android/third-party. unzip these files.
6. enter mailcore2 folder, cd build-android, ./build.sh
7. finished.

debug mailcore and libetpan
1. enter troin source folder.
2. modify build.gradle and mailcore2's android_All_libetpan.mk. Add your NDK PATH and your Target CPU.
3. debug android programe by android studio.

