#pragma once
#include "pch.h"
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <FileSystem>
#include "stringhelper.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Collections::Specialized;
using namespace System::Diagnostics;
using namespace System::IO;

using namespace System::Net;
using namespace System::Net::Security;
using namespace System::Security::Cryptography;
using namespace System::Text;
using namespace System::Text::RegularExpressions;
using namespace Microsoft::Win32;

/// <summary>
/// Network and launch logic for XIVLoader
/// </summary>
class networklogic
{
private:
	static const std::wstring UserAgentTemplate;

	static const std::wstring UserAgent;

public:
	static Process LaunchGame(const std::wstring& gamePath, const std::wstring& realsid, int language, bool dx11, int expansionlevel, bool isSteam, int region);

	static std::wstring GetRealSid(const std::wstring &gamePath, const std::wstring &username, const std::wstring &password, const std::wstring &otp, bool isSteam);

private:
	static std::wstring GetStored(bool isSteam); //this is needed to be able to access the login site correctly

public:
	static std::wstring GetSid(const std::wstring &username, const std::wstring &password, const std::wstring &otp, bool isSteam);

private:
	static std::wstring GetLocalGamever(const std::wstring &gamePath);

	static std::wstring GenerateHash(const std::wstring &file);

public:
	static bool GetGateStatus();

private:
	static void InitiateSslTrust();


	static std::wstring GenerateUserAgent();

	static std::wstring MakeComputerId();
};

