#pragma once
#include "pch.h"
#include <string>
#include <vector>
#include <iostream>
#include <FileSystem>


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

namespace csharp_cli_launcher_ffxiv
{
	class Program
	{


	public:
		static std::wstring ReadPassword();

		static void Main(std::vector<std::wstring> &args);





	};
}
