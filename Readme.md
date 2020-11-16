# CefSimpleApp

this is just a test app to test [Chromium Embed Framework](https://bitbucket.org/chromiumembedded/cef)

## Building

### create a temp dir
```Console
mkdir build
cd build
```

### build the project
you have to download libcef.so from the cef project and put it inside Libs/Release or use the libcef.so on the [releases](https://github.com/litch0/CefSimpleClient/releases/tag/1.0.0)

```Console
cmake ..
make
```

## Runing the Project

```Console
LD_LIBRARY_PATH=../Libs/Release PATH=$PATH:../Libs/Release ./cefClientTest
```

if you receive error with locales just copy the contents of the Libs/Resource to the curent dir
if you receive error about icudtl.dat you need to copy it from the Libs/Release to the current dir

