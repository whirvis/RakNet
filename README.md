# RakNet v4.081

A cross platform, open source, C++ networking engine for game programmers. 

The goal of this fork is to make it easy to build and use RakNet in modern
development environments. At the moment, I am focusing solely on Windows. In
the future, intend to do this for Cygwin, Linux, etc.

## Package notes

- The `Help` directory contains [`index.html`](https://github.com/whirvis/RakNet/blob/master/Help/index.html),
  which is full of documentation that can be viewed in the browser.
- The `Source` directory contain all files required for the core of RakNet,
  and is used if you want to use the source in your own program or build it
  from source.
- The `Samples` directory contains code samples and one game using an older
  version of RakNet. Each sample demonstrates one feature of RakNet. The game
  samples cover several features.
- The `Lib` directory contains libraries for debug and release versions of
  RakNet, as well as RakVoice.
- There is a makefile for Linux users in the root directory.  Windows users
  can use projects under `Samples\Project` in Visual Studio.

For C# support, see the [Swig Tool Based Tutorial](https://github.com/whirvis/RakNet/blob/master/Help/swigtutorial.html).

## Windows users

Load `RakNet_VS2017.sln` and perform conversion if necessary.

After the project conversion, if you encounter error `MSB4006` ("There is a
circular dependency in the target dependency graph"), follow the steps below
to fix it:
1. Open project properties
2. Click on "Common Properties"
3. Click on "Framework and References"
4. Look under "Build Properties"
5. Change the "Copy Local" flag from "True" to "False"

For other compiler issues, see [Compiler Setup](https://github.com/whirvis/RakNet/blob/master/Help/compilersetup.html).

## Cygwin users

Copy the `Include` and `Source` directories, and whatever samples you want to
run, to the home directory. Then, run `g++ ../../lib/w32api/libws2_32.a *.cpp`.
To run the generated executables (`a.exe`), you may need to copy the generated
DLLs to `cygwin\bin` first.

## Linux users

Use `cmake` or `g++ -lpthread -g *.cpp` in the `Source` directory.
  - To build for 64-bit, use the `-m64` flag with `g++`. 
  - To enable LibCat support, use `-I./../DependentExtensions` with `g++`.
  - For threads, you may need to use `-pthread` instead of `-lpthread`.
  - Add `-march=i686` if you encounter `/usr/local/lib/libraknet.so:
    undefined reference to __sync_fetch_and_add_4`.

## MacOSX users

Open a terminal window and run the following commands:
```sh
cd ./RakNet/Source
g++ -c -I -DNDEBUG                               \
  -isysroot /Developer/SDKs/MacOSX[version].sdk/ \
  -arch i386 *.cpp
gcc -c -I ../Include                             \
  -isysroot /Developer/SDKs/MacOSX[version].sdk/ \
  -arch i386 *.cpp
```
Use whichever version SDK you have. The above should result in a clean build;
giving you both PowerPC and Intel binaries compiled against version 10.3.9 of
the SDK (which is a good thing).
 - **Note:** Version 10.4 of the SDK is bugged, and will *not* compile unless
   you use GCC 4.0 from inside XCode.

Next, run the following:
```sh
libtool -static -o  raknetppc.a *.o
libtool -static -o rakneti386.a *.o
```    
These commands will each stitch together a static library for both the PowerPC
and Intel architectures. There may be warnings that some `.o` files do not have
any symbols. If you want to be prudent, remove the mentioned `.o` files (not
the `.cpp` files!) and re-run the commands.

Finally, run this command:
```sh
lipo -create *.a -o libraknet.a
```
There should now be a file named `libraknet.a`. This is the RakNet library,
built for MacOSX machines using either the PowerPC or Intel architectures.

## Android

You will need the latest version of Cygwin and the Android SDK to build
native code on Android.

First, create a directory for RakNet (e.g., `cygwin\home\<User>\android-ndk-r4b\samples\RakNet`).
Copy `Android.Manifest.xml` (and other such files) from another sample to
this directory.

Next, create a directory caled `jni` under the `RakNet` directory, and add
the following `Android.mk`:
```make
LOCAL_PATH      := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE    := RakNet
MY_PREFIX       := $(LOCAL_PATH)/RakNetSources/
MY_SOURCES      := $(wildcard $(MY_PREFIX)*.cpp)
LOCAL_SRC_FILES += $(MY_SOURCES:$(MY_PREFIX)%=RakNetSources/%)
include $(BUILD_SHARED_LIBRARY)
```
This makefile assumes the existence of a directory called `RakNetSources`,
that being: `cygwin/home/<User>/android-ndk-r4b/samples/RakNet/jni/RakNetSources`.
Under `RakNetSources`, there should be a `Source` directory (the same one
from RakNet). You can either copy the files (not recommended) or create a
symbolic link.
  - To create a symbolic link on Windows, see [`junction.exe`](http://technet.microsoft.com/en-us/sysinternals/bb896768.aspx).

Finally, within a Cygwin environment, navigate to `home/<User>/android-ndk-r4b/samples/RakNet`
and run `../../ndk-build`. Everything should build, and you should end up
with a `.so` file. You should now be able to create a project in Eclipse and
import `cygwin/home/<User>/android-ndk-r4b/samples/RakNet`.
