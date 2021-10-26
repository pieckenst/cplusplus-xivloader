#include "pch.h"
#include "launchmethods.h"
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

void LaunchMethods::EnglishLaunch(int language)
{
	std::wcout << L"-------------------------------------" << std::endl;
	std::wcout << L"What would you like to do?" << std::endl;
	std::wcout << L"  1) Login" << std::endl;
	std::wcout << L"  2) Exit" << std::endl;

	std::wcout << L"Input - ";
	auto ansys = Console::ReadKey();
	std::wcout << std::endl;
	std::wcout << L"-------------------------------------" << std::endl;

	if (ansys->KeyChar == L'1')
	{
		//Console.WriteLine("-------------------------------------");
		std::wcout << std::endl;
		std::wstring gamePath;
		if (FileSystem::fileExists(FileSystem::getCurrentDirectory() + LR"(\gamepath.txt)"))
		{
		  gamePath = GamePathLoad();
		}
		else
		{
		  std::wcout << L"Please enter your gamepath - ";
		  gamePath = GamePathWrite();
		}
		std::wcout << L"-------------------------------------" << std::endl;
		bool isSteam = false;
		std::wcout << L"Is your game a steam version of the client? - ";
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
		if (FileSystem::fileExists(FileSystem::getCurrentDirectory() + LR"(\password.txt)") || FileSystem::fileExists(FileSystem::getCurrentDirectory() + LR"(\password.XIVloadEnc)") && FileSystem::fileExists(FileSystem::getCurrentDirectory() + LR"(\username.txt)"))
		{
		  bool promter = false;
		  std::wcout << L"Do you wish to use existing saved login and password? - ";
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
			username = ReturnUsername();
			TextReader *tr = gcnew StreamReader(L"privatekey.txt");
			std::wstring keyread = tr->ReadLine();
			DecryptFile(L"password.XIVloadEnc",L"password.txt", keyread);
			TextReader *prr = gcnew StreamReader(L"password.txt");
			password = prr->ReadLine();
			prr->Close();

			delete prr;
			delete tr;
		  }
		  else
		  {
			std::wcout << L"Username - ";
			std::getline(std::wcin, username);
			std::wcout << L"Password - ";
			password = Program::ReadPassword();
			//string key = GenerateKey();

			//EncryptFile("password.txt", "password.XIVloadEnc", key);
		  }
		}
		else
		{
		  std::wcout << L"Username - ";
		  username = UserNameWrite();
		  std::wcout << L"Password - ";
		  password = PasswordWrite();
		  std::wstring key = GenerateKey();


		  EncryptFile(L"password.txt", L"password.XIVloadEnc", key);

		}
		//string maskpassword = "";
		//for (int i = 0; i < password.Length; i++) { 
		//maskpassword += "*"; 
		//}


		//Console.Write("Your Password is:" + maskpassword);
		std::wcout << std::endl;

		std::wcout << L"Two-Factor Authefication Key - ";
		std::wstring otp;
		std::getline(std::wcin, otp);
		std::wstring dx1prompt;
		bool dx11 = false;
		int expansionLevel;
		int region;
		if (FileSystem::fileExists(FileSystem::getCurrentDirectory() + LR"(\booleansandvars.txt)"))
		{
		   bool promterx = false;
		   std::wcout << L"Do you wish to load existing params? - ";
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
			 dx1prompt = dx1readd();
			 if (StringHelper::toLower(dx1prompt) == L"yes")
			 {
			   dx11 = true;
			 }
			 else
			 {
			   dx11 = false;
			 }
			 expansionLevel = exlevelread();
			 region = regionread();
		   }
		   else
		   {
			 std::wcout << L"Do you want to launch the game with enabled DirectX 11? - ";
			 std::getline(std::wcin, dx1prompt);
			 if (StringHelper::toLower(dx1prompt) == L"yes")
			 {
			 dx11 = true;
			 }
			 else
			 {
			 dx11 = false;
			 }
			 std::wcout << L"Please enter your expansion pack level - Currently valid ones are \n 0- ARR - 1 - Heavensward - 2 - Stormblood - 3 - Shadowbringers" << std::endl;
			 expansionLevel = std::stoi(Console::ReadLine());
			 std::wcout << L"Please provide a region for your client install - Currently valid ones are \n 1- Japan , 2 - America , 3 - International: - ";
			 region = std::stoi(Console::ReadLine());
		   }
		}
		else
		{
		  std::wcout << L"Do you want to launch the game with enabled DirectX 11? - ";
		  std::getline(std::wcin, dx1prompt);
		  if (StringHelper::toLower(dx1prompt) == L"yes")
		  {
			dx11 = true;
		  }
		  else
		  {
			dx11 = false;
		  }
		  std::wcout << L"Please enter your expansion pack level - Currently valid ones are \n 0- ARR - 1 - Heavensward - 2 - Stormblood - 3 - Shadowbringers" << std::endl;
		  expansionLevel = std::stoi(Console::ReadLine());
		  TextWriter *twxx = gcnew StreamWriter(L"booleansandvars.txt");
		  std::wcout << L"Please provide a region for your client install - Currently valid ones are \n 1- Japan , 2 - America , 3 - International: - ";
		  region = std::stoi(Console::ReadLine());
		  twxx->WriteLine(dx1prompt);
		  twxx->WriteLine(expansionLevel);
		  twxx->WriteLine(region);
		  twxx->Close();

			delete twxx;
		}
		File::Delete(L"password.txt");
		LogicLaunchNorm(gamePath,username,password,otp,language, expansionLevel,region,isSteam,dx11);

		std::wstring tempVar;
		std::getline(std::wcin, tempVar);

	}
	else
	{
		std::wcout << L"-------------------------------------" << std::endl;
		std::wcout << L"Exiting the launcher" << std::endl;
		std::wcout << L"-------------------------------------" << std::endl;
		std::wstring tempVar2;
		std::getline(std::wcin, tempVar2);
	}
}

std::wstring LaunchMethods::ReturnUsername()
{
   TextReader *trx = gcnew StreamReader(L"username.txt");
   std::wstring usernameread = trx->ReadLine();
   std::wstring username = usernameread;
   trx->Close();

   delete trx;
   return username;
}

void LaunchMethods::LogicLaunchNorm(const std::wstring &gamePath, const std::wstring &username, const std::wstring &password, const std::wstring &otp, int language, int expansionLevel, int region, bool isSteam, bool dx11)
{
		try
		{
			auto sid = networklogic::GetRealSid(gamePath, username, password, otp, isSteam);
			if (sid == L"BAD")
			{
				return;
			}

			auto ffxivGame = networklogic::LaunchGame(gamePath, sid, language, dx11, expansionLevel, isSteam, region);



		}
		catch (const std::runtime_error &exc)
		{
			if (language == 0)
			{
			  std::wcout << L"ログインに失敗しました。ログイン情報を確認するか、再試行してください.\n" << exc.what() << std::endl;
			}
			if (language == 1)
			{
			  std::wcout << L"Logging in failed, check your login information or try again.\n" << exc.what() << std::endl;
			}
			if (language == 2)
			{
			  std::wcout << L"Anmeldung fehlgeschlagen, überprüfe deine Anmeldedaten oder versuche es noch einmal.\n" << exc.what() << std::endl;
			}
			if (language == 3)
			{
			  std::wcout << L"Échec de la connexion, vérifiez vos informations de connexion ou réessayez.\n" << exc.what() << std::endl;
			}
			if (language == 4)
			{
			  std::wcout << L"Не удалось войти в систему, проверьте данные для входа или попробуйте еще раз.\n" << exc.what() << std::endl;
			}

		}
}

void LaunchMethods::LogicLaunchRnorm(const std::wstring &gamePath, const std::wstring &username, const std::wstring &password, const std::wstring &otp, int language, int expansionLevel, int region, bool isSteam, bool dx11)
{
		try
		{
			auto sid = networklogic::GetRealSid(gamePath, username, password, otp, isSteam);
			if (sid == L"BAD")
			{
				return;
			}

			auto ffxivGame = networklogic::LaunchGame(gamePath, sid, 1, dx11, expansionLevel, isSteam, region);



		}
		catch (const std::runtime_error &exc)
		{
			if (language == 0)
			{
			  std::wcout << L"ログインに失敗しました。ログイン情報を確認するか、再試行してください.\n" << exc.what() << std::endl;
			}
			if (language == 1)
			{
			  std::wcout << L"Logging in failed, check your login information or try again.\n" << exc.what() << std::endl;
			}
			if (language == 2)
			{
			  std::wcout << L"Anmeldung fehlgeschlagen, überprüfe deine Anmeldedaten oder versuche es noch einmal.\n" << exc.what() << std::endl;
			}
			if (language == 3)
			{
			  std::wcout << L"Échec de la connexion, vérifiez vos informations de connexion ou réessayez.\n" << exc.what() << std::endl;
			}
			if (language == 4)
			{
			  std::wcout << L"Не удалось войти в систему, проверьте данные для входа или попробуйте еще раз.\n" << exc.what() << std::endl;
			}

		}
}

std::wstring LaunchMethods::GamePathWrite()
{
   std::wstring gamePath;
   std::getline(std::wcin, gamePath);
   TextWriter *tw = gcnew StreamWriter(L"gamepath.txt");
   tw->WriteLine(gamePath);
   tw->Close();

   delete tw;
   return gamePath;
}

std::wstring LaunchMethods::GamePathLoad()
{
   TextReader *tr = gcnew StreamReader(L"gamepath.txt");
   std::wstring gamePathread = tr->ReadLine();
   std::wstring gamePath = gamePathread;
   tr->Close();
   std::wcout << gamePath << std::endl;

   delete tr;
   return gamePath;
}

std::wstring LaunchMethods::dx1readd()
{
   TextReader *tr = gcnew StreamReader(L"booleansandvars.txt");
   std::wstring dx1reader = tr->ReadLine();
   std::wstring dx1prompt = dx1reader;
   tr->Close();

   delete tr;
   return dx1prompt;
}

int LaunchMethods::exlevelread()
{
  TextReader *tr = gcnew StreamReader(L"booleansandvars.txt");
  std::wstring blankreader = tr->ReadLine();
  std::wstring exlevelreader = tr->ReadLine();
  int expansionLevel = std::stoi(exlevelreader);
  tr->Close();

  delete tr;
  return expansionLevel;
}

int LaunchMethods::regionread()
{
  TextReader *tr = gcnew StreamReader(L"booleansandvars.txt");
  std::wstring blankreaderone = tr->ReadLine();
  std::wstring blankreadertwo = tr->ReadLine();
  std::wstring regionreader = tr->ReadLine();
  int region = std::stoi(regionreader);
  tr->Close();

  delete tr;
  return region;
}

std::wstring LaunchMethods::UserNameWrite()
{
  std::wstring username;
  std::getline(std::wcin, username);
  TextWriter *twx = gcnew StreamWriter(L"username.txt");
  twx->WriteLine(username);
  twx->Close();

  delete twx;
  return username;
}

std::wstring LaunchMethods::PasswordWrite()
{
  std::wstring password = Program::ReadPassword();
  std::wstring filnamex = L"password.txt";
  TextWriter *tw = gcnew StreamWriter(filnamex);
  tw->WriteLine(password);
  tw->Close();


  delete tw;
  return password;
}

std::wstring LaunchMethods::GenerateKey()
{
  // Create an instance of Symetric Algorithm. Key and IV is generated automatically.
  DES *desCrypto = DESCryptoServiceProvider::Create();

// Use the Automatically generated key for Encryption.
  std::vector<unsigned char> proxy = desCrypto->Key;
  std::wcout << ASCIIEncoding::ASCII->GetString(desCrypto->Key) << std::endl;
  //string SaverKey = System.Text.ASCIIEncoding.Default.GetString(proxy);

  File::WriteAllBytes(L"privatekey.txt", proxy);
  return ASCIIEncoding::ASCII->GetString(desCrypto->Key);
}

void LaunchMethods::EncryptFile(const std::wstring &sInputFilename, const std::wstring &sOutputFilename, const std::wstring &sKey)
{
  FileStream *fsInput = gcnew FileStream(sInputFilename, FileMode::Open, FileAccess::ReadWrite);

  FileStream *fsEncrypted = gcnew FileStream(sOutputFilename, FileMode::Create, FileAccess::ReadWrite);
  DESCryptoServiceProvider *DES = gcnew DESCryptoServiceProvider();
  DES->Key = ASCIIEncoding::ASCII->GetBytes(sKey);
  DES->IV = ASCIIEncoding::ASCII->GetBytes(sKey);
  ICryptoTransform *desencrypt = DES->CreateEncryptor();
  CryptoStream *cryptostream = gcnew CryptoStream(fsEncrypted, desencrypt, CryptoStreamMode::Write);

  std::vector<unsigned char> bytearrayinput(fsInput->Length);
  fsInput->Read(bytearrayinput, 0, bytearrayinput.size());
  cryptostream->Write(bytearrayinput, 0, bytearrayinput.size());
  cryptostream->Close();

  fsInput->Close();

  fsEncrypted->Close();
  File::Delete(sInputFilename);

	delete cryptostream;
	delete DES;
//C# TO C++ CONVERTER TODO TASK: A 'delete fsEncrypted' statement was not added since fsEncrypted was passed to a method or constructor. Handle memory management manually.
	delete fsInput;
}

void LaunchMethods::DecryptFile(const std::wstring &sInputFilename, const std::wstring &sOutputFilename, const std::wstring &sKey)
{
  DESCryptoServiceProvider *DES = gcnew DESCryptoServiceProvider();
  //A 64 bit key and IV is required for this provider.
  //Set secret key For DES algorithm.
  DES->Key = ASCIIEncoding::ASCII->GetBytes(sKey);
  //Set initialization vector.
  DES->IV = ASCIIEncoding::ASCII->GetBytes(sKey);

  //Create a file stream to read the encrypted file back.
  FileStream *fsread = gcnew FileStream(sInputFilename, FileMode::Open, FileAccess::Read);
  //Create a DES decryptor from the DES instance.
  ICryptoTransform *desdecrypt = DES->CreateDecryptor();
  //Create crypto stream set to read and do a 
  //DES decryption transform on incoming bytes.
  CryptoStream *cryptostreamDecr = gcnew CryptoStream(fsread, desdecrypt, CryptoStreamMode::Read);
  //Print the contents of the decrypted file.
  StreamWriter *fsDecrypted = gcnew StreamWriter(sOutputFilename);
  StreamReader tempVar(cryptostreamDecr);
  fsDecrypted->Write((&tempVar)->ReadToEnd());
  //fsDecrypted.Flush();
  fsDecrypted->Close();

	delete fsDecrypted;
//C# TO C++ CONVERTER TODO TASK: A 'delete cryptostreamDecr' statement was not added since cryptostreamDecr was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete fsread' statement was not added since fsread was passed to a method or constructor. Handle memory management manually.
	delete DES;
}
