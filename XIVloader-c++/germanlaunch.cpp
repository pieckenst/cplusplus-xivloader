#include "pch.h"
#include "germanlaunch.h"
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
using namespace csharp_cli_launcher_ffxiv;

void GermanLaunchMethod::GermanLaunch(int language)
{
		std::wcout << L"-------------------------------------" << std::endl;
		std::wcout << L"Was würdest du gern tun?" << std::endl;
		std::wcout << L"  1) Anmeldung" << std::endl;
		std::wcout << L"  2) Ausgang" << std::endl;

		std::wcout << L"Eingang - ";
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
			  std::wcout << L"Bitte geben Sie Ihren Spielpfad ein - ";
			  gamePath = LaunchMethods::GamePathWrite();
			}
			std::wcout << L"-------------------------------------" << std::endl;
			bool isSteam = false;
			std::wcout << L"Ist Ihr Spiel eine Steam-Version des Clients? - ";
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
			  std::wcout << L"Möchten Sie das vorhandene gespeicherte Login und Passwort verwenden? - ";
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
				std::wcout << L"Nutzername - ";
				std::getline(std::wcin, username);
				std::wcout << L"Passwort - ";
				password = Program::ReadPassword();
			  }
		}
			else
			{
			  std::wcout << L"Nutzername - ";
			  username = LaunchMethods::UserNameWrite();
			  std::wcout << L"Passwort - ";
			  password = LaunchMethods::PasswordWrite();

			}
			//string maskpassword = "";
			//for (int i = 0; i < password.Length; i++) { 
			//maskpassword += ""; 
			//}


			//Console.Write("Your Password is:" + maskpassword);
			std::wcout << std::endl;

			std::wcout << L"Zwei-Faktor-Authentifizierungsschlüssel - ";
			std::wstring otp;
			std::getline(std::wcin, otp);
			std::wstring dx1prompt;
			bool dx11 = false;
			int expansionLevel;
			int region;
			if (File::Exists(Directory::GetCurrentDirectory() + LR"(\booleansandvars.txt)"))
			{
			   bool promterx = false;
			   std::wcout << L"Möchten Sie vorhandene Parameter laden? - ";
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
				 std::wcout << L"Möchten Sie das Spiel mit aktiviertem DirectX 11 starten? - ";
				 std::getline(std::wcin, dx1prompt);
				 if (StringHelper::toLower(dx1prompt) == L"yes")
				 {
				 dx11 = true;
				 }
				 else
				 {
				 dx11 = false;
				 }
				 std::wcout << L"Bitte geben Sie Ihr Erweiterungspaket-Level ein - Derzeit gültig sind \n 0- ARR - 1 - Heavensward - 2 - Stormblood - 3 - Shadowbringers" << std::endl;
				 expansionLevel = std::stoi(Console::ReadLine());
				 std::wcout << L"Bitte geben Sie eine Region für Ihre Client-Installation an - Derzeit gültige sind \n 1- Japan , 2 - America , 3 - International: - ";
				 region = std::stoi(Console::ReadLine());
			   }
			}
			else
			{
			  std::wcout << L"Möchten Sie das Spiel mit aktiviertem DirectX 11 starten? - ";
			  std::getline(std::wcin, dx1prompt);
			  if (StringHelper::toLower(dx1prompt) == L"yes")
			  {
				dx11 = true;
			  }
			  else
			  {
				dx11 = false;
			  }
			  std::wcout << L"Bitte geben Sie Ihr Erweiterungspaket-Level ein - Derzeit gültig sind \n 0- ARR - 1 - Heavensward - 2 - Stormblood - 3 - Shadowbringers" << std::endl;
			  expansionLevel = std::stoi(Console::ReadLine());
			  TextWriter twxx = gcnew StreamWriter(L"booleansandvars.txt");
			  std::wcout << L"Bitte geben Sie eine Region für Ihre Client-Installation an - Derzeit gültige sind \n 1- Japan , 2 - America , 3 - International: - ";
			  region = std::stoi(Console::ReadLine());
			  twxx.WriteLine(dx1prompt);
			  twxx.WriteLine(expansionLevel);
			  twxx.WriteLine(region);
			  twxx.Close();

				delete twxx;
			}
			File::Delete(L"password.txt");
			LaunchMethods::LogicLaunchNorm(gamePath,username,password,otp,language, expansionLevel,region,isSteam,dx11);

			std::wstring tempVar;
			std::getline(std::wcin, tempVar);

		}
		else
		{
			std::wcout << L"-------------------------------------" << std::endl;
			std::wcout << L"Beenden des Launchers" << std::endl;
			std::wcout << L"-------------------------------------" << std::endl;
			std::wstring tempVar2;
			std::getline(std::wcin, tempVar2);
		}
}
