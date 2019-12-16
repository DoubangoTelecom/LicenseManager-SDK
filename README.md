The license manager service is a secure cloud-based system to help our customers manage their licenses with minimal effort. 
The system was designed with simplicity in mind to allow easy integration in your products.

The service has two parts:
 - A web application: https://www.doubango.org/LicenseManager/
 - A C++ SDK: https://github.com/DoubangoTelecom/LicenseManager-SDK
 
Full documentation is hosted at https://www.doubango.org/SDKs/LicenseManager/docs/

The [web application](https://www.doubango.org/LicenseManager/) is the easiest way to manage your licenses but sometimes you’ll need to automate the process and this is when the SDK is needed. The automation allows managing hundreds of licenses with little effort.

If you're using C++ then, this SDK is for you. For other languages (Java, C#, Python...) it's easy to directly target the [REST-API](https://www.doubango.org/SDKs/LicenseManager/docs/REST_API.html). A sample C++ code for automatic activation could be found at [samples/c++/activation](samples/c++/activation/README.md).

This SDK is a single file header-only C++ code using [libcurl](https://curl.haxx.se/libcurl/). You need to include [LicenseManager-SDK-API-PUBLIC.h](c++/LicenseManager-SDK-API-PUBLIC.h) and link to [libcurl](https://curl.haxx.se/libcurl/) to use the SDK.

The first step is to obtain your login and password from us.
