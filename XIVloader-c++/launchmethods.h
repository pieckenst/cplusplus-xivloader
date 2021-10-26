#pragma once
#include "pch.h"
#include "network.h"
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <FileSystem>
#include "stringhelper.h"
#include "Program.h"

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
//C# TO C++ CONVERTER TODO TASK: The C# 'using static' statement  cannot be converted to C++:
//using static networklogic;
using namespace csharp_cli_launcher_ffxiv;

/// <summary>
/// Basically a class for launch sequence of the launcher
/// </summary>
class LaunchMethods
{



	public:
		static void EnglishLaunch(int language);

		static std::wstring ReturnUsername();
		static void LogicLaunchNorm(const std::wstring &gamePath, const std::wstring &username, const std::wstring &password, const std::wstring &otp, int language, int expansionLevel, int region, bool isSteam, bool dx11);
		static void LogicLaunchRnorm(const std::wstring &gamePath, const std::wstring &username, const std::wstring &password, const std::wstring &otp, int language, int expansionLevel, int region, bool isSteam, bool dx11);
		static std::wstring GamePathWrite();
		static std::wstring GamePathLoad();
		static std::wstring dx1readd();
		static int exlevelread();
		static int regionread();
		static std::wstring UserNameWrite();
		static std::wstring PasswordWrite();
	private:
		static std::wstring GenerateKey();

	public:
		static void EncryptFile(const std::wstring &sInputFilename, const std::wstring &sOutputFilename, const std::wstring &sKey);

		static void DecryptFile(const std::wstring &sInputFilename, const std::wstring &sOutputFilename, const std::wstring &sKey);

};
