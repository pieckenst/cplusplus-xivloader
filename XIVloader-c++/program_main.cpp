#pragma once
#include "pch.h"
#include <string>
#include <vector>
#include "Program.h"
#include "pch.h"
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

int main(int argc, char **argv)
{
    std::vector<std::wstring> args(argv + 1, argv + argc);
    csharp_cli_launcher_ffxiv::Program::Main(args);
}

