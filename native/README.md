# Native Development

## Prerequisite

Install the NDK required to build and develop Magisk with `./build.py ndk`. The NDK will be installed to `$ANDROID_SDK_ROOT/ndk/magisk`.

## Code Paths

- `jni`: Magisk's code in C++
- `jni/external`: external dependencies, mostly submodules
- `src`: irrelevant, only exists to setup a native Android Studio project

## Build Configs

All C/C++ code and its dependencies are built with [`ndk-build`](https://developer.android.com/ndk/guides/ndk-build) and configured with several `*.mk` files scatterred in many places.

## Development / IDE

All C++ code should be recognized and properly indexed by Android Studio out of the box.

Note: run `./build.py binary` before developing to make sure generated code is created.
