#include "pch.h"
#include "Program.h"
#include "japanlaunch.h"
#include "launchmethods.h"
#include "germanlaunch.h"
#include "frenchlaunch.h"
#include "russianlaunch.h"
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

	std::wstring Program::ReadPassword()
	{
		std::wstring password = L"";
		ConsoleKeyInfo info = Console::ReadKey(true);
		while (info.Key != ConsoleKey::Enter)
		{
			if (info.Key != ConsoleKey::Backspace)
			{
				std::wcout << L"";
				password += info.KeyChar;
			}
			else if (info.Key == ConsoleKey::Backspace)
			{
				if (!password.empty())
				{
					// remove one character from the list of password characters
					password = password.substr(0, password.length() - 1);
					// get the location of the cursor
					int pos = Console::CursorLeft;
					// move the cursor to the left by one character
					Console::SetCursorPosition(pos - 1, Console::CursorTop);
					// replace it with space
					std::wcout << L" ";
					// move the cursor to the left by one character again
					Console::SetCursorPosition(pos - 1, Console::CursorTop);
				}
			}
			info = Console::ReadKey(true);
		}
		// add a gcnew line because user pressed enter at the end of their password
		std::wcout << std::endl;
		return password;
	}

	void Program::Main(std::vector<std::wstring> &args)
	{
		Console.Title = L"XIVLOADER";
		Console.OutputEncoding = System::Text::Encoding::Unicode;

		auto arr = std::vector<std::wstring> {LR"(                                             )", LR"( __  _______   ___                 _         )", LR"( \ \/ /_ _\ \ / / |   ___  __ _ __| |___ _ _ )", LR"(  >  < | | \ V /| |__/ _ \/ _` / _` / -_) '_| )", LR"( /_/\_\___| \_/ |____\___/\__,_\__,_\___|_|  )", LR"(                                             )"};
		Console.WindowWidth = 160;
		std::wcout << L"\n\n" << std::endl;
		for (auto line : arr)
		{
			std::wcout << line << std::endl;
		}
		//Console.WriteLine("FFXIV Launcher "); // it has to begin somewhere lol



		std::wcout << L"0 - Japanese , 1 - English , 2 - German , 3 - French , 4 - Russian ( The client will still be in english)" << std::endl;

		std::wcout << L"Enter your language - ";

		int language = std::stoi(Console::ReadLine());

		if (language == 0)
		{
			JapaneseLaunchMethod::JapanLaunch(language);
		}

		if (language == 1)
		{
			LaunchMethods::EnglishLaunch(language);
		}

		if (language == 2)
		{
			GermanLaunchMethod::GermanLaunch(language);
		}

		if (language == 3)
		{
			FrenchLaunchMethod::FrenchLaunch(language);
		}
		if (language == 4)
		{
			RussianLaunchMethod::RussianLaunch(language);
		}



	}
}
