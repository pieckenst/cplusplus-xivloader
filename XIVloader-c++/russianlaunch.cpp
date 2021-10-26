#include "pch.h"
#include "russianlaunch.h"
#include "Program.h"
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
using namespace csharp_cli_launcher_ffxiv;


void RussianLaunchMethod::RussianLaunch(int language)
{
		std::wcout << L"-------------------------------------" << std::endl;
		std::wcout << L"Что бы вы хотели сделать?" << std::endl;
		std::wcout << L"  1) Вход в игру" << std::endl;
		std::wcout << L"  2) Выйти из лаунчера" << std::endl;

		std::wcout << L"Ввод - ";
		auto ansys = Console::ReadKey();
		std::wcout << std::endl;
		std::wcout << L"-------------------------------------" << std::endl;

		if (ansys.KeyChar == L'1')
		{
			//Console.WriteLine("-------------------------------------");
			std::wcout << std::endl;
			std::wstring gamePath;
			if (File::Exists(Directory::GetCurrentDirectory() + LR"(\gamepath.txt)"))
			{
			  gamePath = LaunchMethods::GamePathLoad();
			}
			else
			{
			  std::wcout << L"Введите путь до клиента игры - ";
			  gamePath = LaunchMethods::GamePathWrite();
			}
			std::wcout << L"-------------------------------------" << std::endl;
			bool isSteam = false;
			std::wcout << L"Является ли ваш клиент версией клиента для Steam? - ";
			std::wstring promtw;
			std::getline(std::wcin, promtw);
			if (StringHelper::toLower(promtw) == L"yes")
			{
				isSteam = true;
			}
			else
			{
				isSteam = false;
			}
			std::wcout << L"-------------------------------------" << std::endl;
			std::wstring username;

			//Console.WriteLine("Provided username {0}", username);

			std::wstring password;
		if (File::Exists(Directory::GetCurrentDirectory() + LR"(\password.txt)") || File::Exists(Directory::GetCurrentDirectory() + LR"(\password.XIVloadEnc)") && File::Exists(Directory::GetCurrentDirectory() + LR"(\username.txt)"))
		{
			  bool promter = false;
			  std::wcout << L"Хотите ли вы использовать сохраненные имя пользователя и пароль? - ";
			  std::wstring askaway;
			  std::getline(std::wcin, askaway);
			  if (StringHelper::toLower(askaway) == L"yes")
			  {
				promter = true;
			  }
			  else
			  {
				promter = false;
			  }
			  if (promter == true)
			  {
				username = LaunchMethods::ReturnUsername();
				TextReader tr = gcnew StreamReader(L"privatekey.txt");
				std::wstring keyread = tr.ReadLine();
				LaunchMethods::DecryptFile(L"password.XIVloadEnc", L"password.txt", keyread);
				TextReader prr = gcnew StreamReader(L"password.txt");
				password = prr.ReadLine();
				prr.Close();

				delete prr;
				delete tr;
			  }
			  else
			  {
				std::wcout << L"Имя Пользователя - ";
				std::getline(std::wcin, username);
				std::wcout << L"Пароль - ";
				password = Program::ReadPassword();
			  }
		}
			else
			{
			  std::wcout << L"Имя Пользователя - ";
			  username = LaunchMethods::UserNameWrite();
			  std::wcout << L"Пароль - ";
			  password = LaunchMethods::PasswordWrite();

			}
			//string maskpassword = "";
			//for (int i = 0; i < password.Length; i++) { 
			//maskpassword += ""; 
			//}


			//Console.Write("Your Password is:" + maskpassword);
			std::wcout << std::endl;

			std::wcout << L"Код Двух-Факторной аутентификации - ";
			std::wstring otp;
			std::getline(std::wcin, otp);
			std::wstring dx1prompt;
			bool dx11 = false;
			int expansionLevel;
			int region;
			if (File::Exists(Directory::GetCurrentDirectory() + LR"(\booleansandvars.txt)"))
			{
			   bool promterx = false;
			   std::wcout << L"Хотитите ли вы запустить игру с сохраненными параметрами? - ";
			   std::wstring askawayx;
			   std::getline(std::wcin, askawayx);
			   if (StringHelper::toLower(askawayx) == L"yes")
			   {
				 promterx = true;
			   }
			   else
			   {
				 promterx = false;
			   }
			   if (promterx == true)
			   {
				 dx1prompt = LaunchMethods::dx1readd();
				 if (StringHelper::toLower(dx1prompt) == L"yes")
				 {
				   dx11 = true;
				 }
				 else
				 {
				   dx11 = false;
				 }
				 expansionLevel = LaunchMethods::exlevelread();
				 region = LaunchMethods::regionread();
			   }
			   else
			   {
				 std::wcout << L"Вы хотите запустить игру с использованием DirectX 11? - ";
				 std::getline(std::wcin, dx1prompt);
				 if (StringHelper::toLower(dx1prompt) == L"yes")
				 {
				 dx11 = true;
				 }
				 else
				 {
				 dx11 = false;
				 }
				 std::wcout << L"Пожалуйста, введите уровень доступного вам дополнения - на текущий момент валидными являются следущие \n 0- ARR - 1 - Heavensward - 2 - Stormblood - 3 - Shadowbringers" << std::endl;
				 expansionLevel = std::stoi(Console::ReadLine());
				 std::wcout << L"Укажите регион установленного клиента. Действующие в настоящее время \n 1- Japan , 2 - America , 3 - International: - ";
				 region = std::stoi(Console::ReadLine());
			   }
			}
			else
			{
			  std::wcout << L"Вы хотите запустить игру с использованием DirectX 11? - ";
			  std::getline(std::wcin, dx1prompt);
			  if (StringHelper::toLower(dx1prompt) == L"yes")
			  {
				dx11 = true;
			  }
			  else
			  {
				dx11 = false;
			  }
			  std::wcout << L"Пожалуйста, введите уровень доступного вам дополнения - на текущий момент валидными являются следущие \n 0- ARR - 1 - Heavensward - 2 - Stormblood - 3 - Shadowbringers" << std::endl;
			  expansionLevel = std::stoi(Console::ReadLine());
			  TextWriter twxx = gcnew StreamWriter(L"booleansandvars.txt");
			  std::wcout << L"Укажите регион установленного клиента. Действующие в настоящее время \n 1- Japan , 2 - America , 3 - International: - ";
			  region = std::stoi(Console::ReadLine());
			  twxx.WriteLine(dx1prompt);
			  twxx.WriteLine(expansionLevel);
			  twxx.WriteLine(region);
			  twxx.Close();

				delete twxx;
			}
			File::Delete(L"password.txt");
			LaunchMethods::LogicLaunchRnorm(gamePath,username,password,otp,language, expansionLevel,region,isSteam,dx11);

			std::wstring tempVar;
			std::getline(std::wcin, tempVar);
		}
		else
		{
			std::wcout << L"-------------------------------------" << std::endl;
			std::wcout << L"Выходим из лаунчера" << std::endl;
			std::wcout << L"-------------------------------------" << std::endl;
			std::wstring tempVar2;
			std::getline(std::wcin, tempVar2);
		}
}
