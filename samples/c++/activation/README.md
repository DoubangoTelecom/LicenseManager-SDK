

- [Building](#building)
  - [Windows](#building-windows)
  - [Generic GCC](#building-generic-gcc)
  - [Raspberry Pi (Raspbian OS)](#building-rpi)
- [Testing](#testing)
  - [Usage](#testing-usage)
  - [Example](#testing-example)


This sample application is used to show how to automatically activate a runtime license. More information about the automatic activation could be found at [https://www.doubango.org/SDKs/LicenseManager/docs/Activation_use_cases.html#automatic-activation](https://www.doubango.org/SDKs/LicenseManager/docs/Activation_use_cases.html#automatic-activation).

This library depends on [libcurl](https://curl.haxx.se/libcurl/). On Windows, [libcurl](https://curl.haxx.se/libcurl/) [binaries and headers](../../../libcurl-7.61.1) are provided but for other systems you have to install **libcurl-dev**. For example, on Ubuntu you may use one of these commands:

 - `sudo  apt-get install libcurl4-openssl-dev` or
 - `sudo apt-get install libcurl4-gnutls-dev` or
 - `sudo  apt-get install libcurl4-nss-dev`


<a name="building"></a>
# Building #

This sample contains [a single C++ source file](main.cxx) and is easy to build. The documentation about the C++ API is at [https://www.doubango.org/SDKs/LicenseManager/docs/cpp-api.html](https://www.doubango.org/SDKs/LicenseManager/docs/cpp-api.html).

<a name="building-windows"></a>
## Windows ##
You'll need Visual Studio and the project is at [activation.vcxproj](activation.vcxproj).

<a name="building-generic-gcc"></a>
## Generic GCC ##

Next command is a generic GCC command:
```
cd LicenseManager-SDK/samples/c++/activation

g++ main.cxx -O3 -I../../../c++ -lcurl -o activation
```
In the above GCC command we assume that libcurl is install in a standard directory. If this isn't the case then, you have to run the next command to check where it's installed and which **GCC LDFLAGS** to use.
```
curl-config --libs
```

<a name="building-rpi"></a>
## Raspberry Pi (Raspbian OS) ##

To build the sample for Raspberry Pi you can either do it on the device itself or cross compile it on [Windows](#cross-compilation-rpi-install-windows), [Linux](#cross-compilation-rpi-install-ubunt) or OSX machines. 
For more information on how to install the toolchain for cross compilation please check [here](../README.md#cross-compilation-rpi).

```
cd LicenseManager-SDK/samples/c++/recognizer

arm-linux-gnueabihf-g++ main.cxx -O3 -I../../../c++ -lcurl -o activation
```
- On Windows: replace `arm-linux-gnueabihf-g++` with `arm-linux-gnueabihf-g++.exe`
- If you're building on the device itself: replace `arm-linux-gnueabihf-g++` with `g++` to use the default GCC

<a name="testing"></a>
# Testing #
After [building](#building) the application you can test it on your local machine.

<a name="testing-usage"></a>
## Usage ##

**activation** is a command line application with the following usage:
```
activation \
      --url <url:string> \
      --masterOrSlaveKey <base64:string> \
      --runtimeKey <base64:string>
```
Options surrounded with **[]** are optional.
- `--url` The server URL to connect to. Should be something like https://localhost:3600. Please contact us to get the right URL to use.
- `--masterOrSlaveKey` Your secret [master key](https://www.doubango.org/SDKs/LicenseManager/docs/Jargon.html#master-key) or [slave key](https://www.doubango.org/SDKs/LicenseManager/docs/Jargon.html#slave-key). Base64 string.
- `--runtimeKey` The [runtime key](https://www.doubango.org/SDKs/LicenseManager/docs/Jargon.html#runtime-key) to activate. Base64 string.

<a name="testing-example"></a>
## Example ##

```
activation \
    --url http://localhost:3600 \
    --masterOrSlaveKey APL+PjwAHQQ0YGcwOW40ZDc2PDcMcXtkZTA8Oj= \
    --runtimeKey HQ/QBQS8bEw4NTggBOSRvYU1gfG1sFkFSQUJlb3oADT81OSg2MDg0NCkEKgc3JgQGaWM=
```



