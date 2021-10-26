#pragma once
#include "pch.h"
#include "network.h"
#include "launchmethods.h"
#include <string>
#include <iostream>
#include <FileSystem>
#include "stringhelper.h"



//C# TO C++ CONVERTER TODO TASK: The C# 'using static' statement  cannot be converted to C++:
//using static networklogic;
//C# TO C++ CONVERTER TODO TASK: The C# 'using static' statement  cannot be converted to C++:
//using static LaunchMethods;
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
using namespace csharp_cli_launcher_ffxiv;
/// <summary>
/// Russian Launch Logic
/// </summary>
class RussianLaunchMethod
{
public:
	static void RussianLaunch(int language);
};
