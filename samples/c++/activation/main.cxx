/* Copyright (C) 2011-2019 Doubango Telecom <https://www.doubango.org>
* File author: Mamadou DIOP (Doubango Telecom, France).
* License: For non commercial use only.
* Source code: https://github.com/DoubangoTelecom/LicenseManager-SDK
* WebSite: https://www.doubango.org/SDKs/LicenseManager
*/

#include <LicenseManager-SDK-API-PUBLIC.h>
#include <algorithm>
#include <map>
#include <assert.h>

using namespace LicenseManagerSdk;

static void printUsage(const std::string& message = "");
static bool parseArgs(int argc, char *argv[], std::map<std::string, std::string >& values);

/*
* Entry point
*/
int main(int argc, char *argv[])
{
	// Parsing args
	std::map<std::string, std::string > args;
	if (!parseArgs(argc, argv, args)) {
		printUsage();
		return -1;
	}

	// Check args
	if (args.find("--url") == args.end()) {
		printUsage("--url required");
		return -1;
	}
	if (args.find("--masterOrSlaveKey") == args.end()) {
		printUsage("--masterOrSlaveKey required");
		return -1;
	}
	if (args.find("--runtimeKey") == args.end()) {
		printUsage("--runtimeKey required");
		return -1;
	}

	// Perform activation
	std::string response;
	const int ret = LicenseManager::activate(
		args["--url"],
		args["--masterOrSlaveKey"],
		args["--runtimeKey"],
		response
	);

	if (ret == 0) {
		LICMGR_SDK_PRINT_INFO("Response: %s", response.c_str());
		// Extract "token" string from JSON response.
		// Use the next code only if you don't have a JSON parser.
		static const char tokenprop[] = "\"token\":";
		size_t start = response.find(tokenprop);
		if (start != std::string::npos) {
			start += sizeof(tokenprop);
			size_t end = response.find(",", start);
			if (end == std::string::npos) {
				end = response.find("}", start);
			}
			if (end != std::string::npos) {
				std::string token = response.substr(start, (end - start - 1));
				token.erase(std::remove(token.begin(), token.end(), ' '), token.end()); // trim SPACEs
				LICMGR_SDK_PRINT_INFO("Token: [%s]", token.c_str());
			}
		}
	}

	LICMGR_SDK_PRINT_INFO("Press any key to terminate !!");
	getchar();

	return ret;
}

static void printUsage(const std::string& message)
{
	if (!message.empty()) {
		LICMGR_SDK_PRINT_ERROR("%s", message.c_str());
	}

	LICMGR_SDK_PRINT_INFO(
		"\n********************************************************************************\n"
		"activation\n"
		"\t--url <url:string> \n"
		"\t--masterOrSlaveKey <base64:string> \n"
		"\t--runtimeKey <base64:string> \n"
		"\n"
		"Options surrounded with [] are optional.\n"
		"\n"
		"--url: The server URL to connect to. Should be something like https://localhost:3600. Please contact us to get the right URL to use.\n"
		"--masterOrSlaveKey: Your secret master key or slave key. Base64 string.\n"
		"--runtimeKey: The runtime key to activate. Base64 string.\n\n"
		"********************************************************************************\n"
	);
}

static bool parseArgs(int argc, char *argv[], std::map<std::string, std::string >& values)
{
	LICMGR_SDK_ASSERT(argc > 0 && argv != nullptr);

	values.clear();

	// Make sure the number of arguments is even
	if ((argc - 1) & 1) {
		LICMGR_SDK_PRINT_ERROR("Number of args must be even");
		return false;
	}

	// Parsing
	for (int index = 1; index < argc; index += 2) {
		std::string key = argv[index];
		if (key.size() < 2 || key[0] != '-' || key[1] != '-') {
			LICMGR_SDK_PRINT_ERROR("Invalid key: %s", key.c_str());
			return false;
		}
		values[key] = argv[index + 1];
	}

	return true;
}
