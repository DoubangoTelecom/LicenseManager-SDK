/* Copyright (C) 2011-2019 Doubango Telecom <https://www.doubango.org>
* File author: Mamadou DIOP (Doubango Telecom, France).
* License: BSD-3.
* Source code: https://github.com/DoubangoTelecom/LicenseManager-SDK
* WebSite: https://www.doubango.org/SDKs/LicenseManager
*/
/**
\file LicenseManager-SDK-API-PUBLIC.h
License Manager SDK public header.
*/
#ifndef _LICENSE_MANAGER_SDK_API_PUBLIC_H_
#define _LICENSE_MANAGER_SDK_API_PUBLIC_H_

#include <iostream>
#include <curl/curl.h>
#include <string>

#define LICMGR_SDK_VERSION_MAJOR		1
#define LICMGR_SDK_VERSION_MINOR		0
#define LICMGR_SDK_VERSION_MICRO		0

// Android OS detection
#if (defined(__ANDROID__) || defined(ANDROID)) && !defined(SWIG)
#	define LICMGR_SDK_OS_ANDROID	1
#endif /* LICMGR_SDK_OS_ANDROID */

// Macros to print logs to the console
#if LICMGR_SDK_OS_ANDROID
#	define LICMGR_SDK_PRINT_VERBOSE(FMT, ...) __android_log_print(ANDROID_LOG_VERBOSE, "org.doubango.ultimateAlpr.Sdk", "*[LICMGR_SDK VERBOSE]: " FMT "\n", ##__VA_ARGS__)
#	define LICMGR_SDK_PRINT_INFO(FMT, ...) __android_log_print(ANDROID_LOG_INFO, "org.doubango.ultimateAlpr.Sdk", "*[LICMGR_SDK INFO]: " FMT "\n", ##__VA_ARGS__)
#	define LICMGR_SDK_PRINT_WARN(FMT, ...) __android_log_print(ANDROID_LOG_WARN, "org.doubango.ultimateAlpr.Sdk", "**[LICMGR_SDK WARN]: function: \"%s()\" \nfile: \"%s\" \nline: \"%u\" \nmessage: " FMT "\n", __FUNCTION__,  __FILE__, __LINE__, ##__VA_ARGS__)
#	define LICMGR_SDK_PRINT_ERROR(FMT, ...) __android_log_print(ANDROID_LOG_ERROR, "org.doubango.ultimateAlpr.Sdk", "***[LICMGR_SDK ERROR]: function: \"%s()\" \nfile: \"%s\" \nline: \"%u\" \nmessage: " FMT "\n", __FUNCTION__,  __FILE__, __LINE__, ##__VA_ARGS__)
#	define LICMGR_SDK_PRINT_FATAL(FMT, ...) __android_log_print(ANDROID_LOG_FATAL, "org.doubango.ultimateAlpr.Sdk", "****[LICMGR_SDK FATAL]: function: \"%s()\" \nfile: \"%s\" \nline: \"%u\" \nmessage: " FMT "\n", __FUNCTION__,  __FILE__, __LINE__, ##__VA_ARGS__)
#else
#	define LICMGR_SDK_PRINT_VERBOSE(FMT, ...) fprintf(stderr, "*[LICMGR_SDK VERBOSE]: " FMT "\n", ##__VA_ARGS__)
#	define LICMGR_SDK_PRINT_INFO(FMT, ...) fprintf(stderr, "*[LICMGR_SDK INFO]: " FMT "\n", ##__VA_ARGS__)
#	define LICMGR_SDK_PRINT_WARN(FMT, ...) fprintf(stderr, "**[LICMGR_SDK WARN]: function: \"%s()\" \nfile: \"%s\" \nline: \"%u\" \nmessage: " FMT "\n", __FUNCTION__,  __FILE__, __LINE__, ##__VA_ARGS__)
#	define LICMGR_SDK_PRINT_ERROR(FMT, ...) fprintf(stderr, "***[LICMGR_SDK ERROR]: function: \"%s()\" \nfile: \"%s\" \nline: \"%u\" \nmessage: " FMT "\n", __FUNCTION__,  __FILE__, __LINE__, ##__VA_ARGS__)
#	define LICMGR_SDK_PRINT_FATAL(FMT, ...) fprintf(stderr, "****[LICMGR_SDK FATAL]: function: \"%s()\" \nfile: \"%s\" \nline: \"%u\" \nmessage: " FMT "\n", __FUNCTION__,  __FILE__, __LINE__, ##__VA_ARGS__)
#endif /* !LICMGR_SDK_OS_ANDROID */

// Assertion function
#if defined(NDEBUG)
#	define LICMGR_SDK_ASSERT(x) do { bool __LICMGR_SDK_b_ret = (x); if (!__LICMGR_SDK_b_ret) { LICMGR_SDK_PRINT_FATAL("Assertion failed!"); abort(); } } while(0)
#else
#	define LICMGR_SDK_ASSERT(x) do { bool __LICMGR_SDK_b_ret = (x); assert(__LICMGR_SDK_b_ret); } while(0)
#endif /* !NDEBUG */

namespace LicenseManagerSdk
{
	/*! 
	* This is a header-only library to allow automatic activation using C++ code.
	* More information about automatic activation could be found at https://www.doubango.org/SDKs/LicenseManager/docs/Activation_use_cases.html#automatic-activation.
	*/
	class LicenseManager
	{
	public:
		
		/**
		* Creates a <a href="https://www.doubango.org/SDKs/LicenseManager/docs/Jargon.html#slave-key">slave</a>.
		* The <a href="https://www.doubango.org/SDKs/LicenseManager/docs/REST_API.html#generate-slave-key">REST API</a> is defined <a href="https://www.doubango.org/SDKs/LicenseManager/docs/REST_API.html#generate-slave-key">here</a>.
		* \param url The server URL to connect to. Should be something like 'https://localhost:3600'.
		* \param masterKey Your secret <a href="https://www.doubango.org/SDKs/LicenseManager/docs/Jargon.html#master-key">master key</a>. 
		* \param response The JSON response from the server.
		* \param comment Optional field to add comment to the slave. This could be helpful if you want to track the slaves. We recommend adding the end user contact information in this field.
		* \param timeoutInMillis Connection timeout in milliseconds.
		* \returns 0 if success, non-zero error code otherwise.
		*/
		static int createSlave(const std::string& url, const std::string& masterKey, std::string& response, const std::string& comment = "", const long timeoutInMillis = 10 * 1000)
		{
			LICMGR_SDK_PRINT_INFO("Call: %s", __FUNCTION__);

			if (url.empty() || masterKey.empty()) {
				LICMGR_SDK_PRINT_ERROR("Invalid parameter");
				return -1;
			}

			std::string url_ = url;
			if (url_.back() != '/') {
				url_ += "/";
			}
			url_ += "slaves";

			const std::string json_ = std::string("{") +
				std::string("\"masterKey\": \"") + masterKey + std::string("\",") +
				std::string("\"comment\": \"") + comment + std::string("\"") +
				std::string("}");

			return LicenseManager::post(url_, json_, response);
		}
		
		/**
		* Activates a <a href="https://www.doubango.org/SDKs/LicenseManager/docs/Jargon.html#runtime-key">Runtime Key</a>.
		* The <a href="https://www.doubango.org/SDKs/LicenseManager/docs/REST_API.html#activate-runtime-key">REST API</a> is defined <a href="https://www.doubango.org/SDKs/LicenseManager/docs/REST_API.html#activate-runtime-key">here</a>.
		* \param url The server URL to connect to. Should be something like 'https://localhost:3600'.
		* \param masterOrSlaveKey Your secret <a href="https://www.doubango.org/SDKs/LicenseManager/docs/Jargon.html#master-key">master key</a> or <a href="https://www.doubango.org/SDKs/LicenseManager/docs/Jargon.html#slave-key">slave key</a>.
		* \param runtimeKey The <a href="https://www.doubango.org/SDKs/LicenseManager/docs/Jargon.html#runtime-key">runtime key</a> to activate.
		* \param response The JSON response from the server.
		* \param timeoutInMillis Connection timeout in milliseconds.
		* \returns 0 if success, non-zero error code otherwise.
		*/
		static int activate(const std::string& url, const std::string& masterOrSlaveKey, const std::string& runtimeKey, std::string& response, const long timeoutInMillis = 10 * 1000)
		{
			LICMGR_SDK_PRINT_INFO("Call: %s", __FUNCTION__);

			if (url.empty() || masterOrSlaveKey.empty() || runtimeKey.empty()) {
				LICMGR_SDK_PRINT_ERROR("Invalid parameter");
				return -1;
			}

			std::string url_ = url;
			if (url_.back() != '/') {
				url_ += "/";
			}
			url_ += "activate";

			const std::string json_ = std::string("{") +
				std::string("\"masterOrSlaveKey\": \"") + masterOrSlaveKey + std::string("\",") +
				std::string("\"runtimeKey\": \"") + runtimeKey + std::string("\"") +
				std::string("}");

			return LicenseManager::post(url_, json_, response);
		}

	private:
		static int init()
		{
			LICMGR_SDK_PRINT_INFO("Call: %s", __FUNCTION__);

			if (s_bInitialized) {
				return 0;
			}

			LICMGR_SDK_PRINT_INFO("License Manager version %d.%d.%d initialization...", 
				LICMGR_SDK_VERSION_MAJOR, 
				LICMGR_SDK_VERSION_MINOR, 
				LICMGR_SDK_VERSION_MICRO
			);

			CURLcode err = curl_global_init(CURL_GLOBAL_ALL);
			if (err != CURLE_OK) {
				LICMGR_SDK_PRINT_ERROR("curl_global_init failed: %s", curl_easy_strerror(err));
				return static_cast<int>(err);
			}
			return 0;
		}

		static size_t writeFunction(void *contents, size_t size, size_t nmemb, void *userp)
		{
			LICMGR_SDK_PRINT_INFO("Call: %s", __FUNCTION__);

			reinterpret_cast<std::string*>(userp)->append(reinterpret_cast<char*>(contents), size * nmemb);
			return (size * nmemb);
		}

		static int post(const std::string& url, const std::string& content, std::string& response, const long timeoutInMillis = 10 * 1000)
		{
			LICMGR_SDK_PRINT_INFO("Call: %s", __FUNCTION__);

			const int ret = LicenseManager::init();
			if (ret != 0) {
				LICMGR_SDK_PRINT_ERROR("Initialization failed with error code: %d", ret);
				return ret;
			}

			CURL* curl = curl_easy_init();
			if (!curl) {
				LICMGR_SDK_PRINT_ERROR("curl_easy_init failed");
				return -1;
			}
			
			struct curl_slist* headers = nullptr;
			CURLcode err = CURLE_OK;

			if ((err = curl_easy_setopt(curl, CURLOPT_URL, url.c_str())) != CURLE_OK) {
				LICMGR_SDK_PRINT_ERROR("curl_easy_setopt(CURLOPT_URL, %s) failed: %s", url.c_str(), curl_easy_strerror(err));
				goto bail;
			}
			if ((err = curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeoutInMillis / 1000)) != CURLE_OK) { // "CURLOPT_TIMEOUT_MS" not avail on old curl versions
				LICMGR_SDK_PRINT_ERROR("curl_easy_setopt(CURLOPT_TIMEOUT, %ld) failed: %s", timeoutInMillis, curl_easy_strerror(err));
				goto bail;
			}
			if (url.substr(0, 5) == "https") {
				if ((err = curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L)) != CURLE_OK) {
					LICMGR_SDK_PRINT_ERROR("curl_easy_setopt(CURLOPT_SSL_VERIFYHOST, %s, 1) failed: %s", url.c_str(), curl_easy_strerror(err));
					goto bail;
				}
			}
			if ((err = curl_easy_setopt(curl, CURLOPT_POSTFIELDS, content.c_str())) != CURLE_OK) {
				LICMGR_SDK_PRINT_ERROR("curl_easy_setopt(CURLOPT_POSTFIELDS, %s) failed: %s", content.c_str(), curl_easy_strerror(err));
				goto bail;
			}
			if ((err = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction)) != CURLE_OK) {
				LICMGR_SDK_PRINT_ERROR("curl_easy_setopt(CURLOPT_WRITEFUNCTION, %s) failed: %s", url.c_str(), curl_easy_strerror(err));
				goto bail;
			}
			if ((err = curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response)) != CURLE_OK) {
				LICMGR_SDK_PRINT_ERROR("curl_easy_setopt(CURLOPT_WRITEDATA, %s) failed: %s", url.c_str(), curl_easy_strerror(err));
				goto bail;
			}
						
			headers = curl_slist_append(headers, "Content-Type: application/json; charset=utf-8");
			if ((err = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers)) != CURLE_OK) {
				LICMGR_SDK_PRINT_ERROR("curl_easy_setopt(CURLOPT_HTTPHEADER, %s) failed: %s", url.c_str(), curl_easy_strerror(err));
				goto bail;
			}
				
			if ((err = curl_easy_perform(curl)) != CURLE_OK) {
				LICMGR_SDK_PRINT_ERROR("curl_easy_perform(%s) failed: %s", url.c_str(), curl_easy_strerror(err));
				goto bail;
			}

		bail:
			if (headers) {
				curl_slist_free_all(headers);
			}
			curl_easy_cleanup(curl);		

			return static_cast<int>(err);
		}

	private:
		static bool s_bInitialized;
	};

	bool LicenseManager::s_bInitialized = false;

} // namespace LicenseManagerSdk 

#endif /* _LICENSE_MANAGER_SDK_API_PUBLIC_H_ */
