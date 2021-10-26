#include "pch.h"
#include "network.h"
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
const std::wstring networklogic::UserAgentTemplate = L"SQEXAuthor/2.0.0(Windows 6.2; ja-jp; {0})";
const std::wstring networklogic::UserAgent = GenerateUserAgent();

Process networklogic::LaunchGame(const std::wstring &gamePath, const std::wstring &realsid, int language, bool dx11, int expansionlevel, bool isSteam, int region)
{
	try
	{
		Process ffxivgame = gcnew Process();
		if (dx11 == true)
		{
			ffxivgame.StartInfo.FileName = gamePath + L"/game/ffxiv_dx11.exe";
		}
		else
		{
			ffxivgame.StartInfo.FileName = gamePath + L"/game/ffxiv.exe";
		}
//C# TO C++ CONVERTER TODO TASK: String.Format is not converted to C++ if more than 3 data arguments of different types are specified:
		ffxivgame.StartInfo.Arguments = std::wstring::Format(L"DEV.TestSID={0} DEV.MaxEntitledExpansionID={1} language={2} region={3}", realsid, expansionlevel, language, region);
		if (isSteam)
		{
			ffxivgame.StartInfo.Environment.Add(L"IS_FFXIV_LAUNCH_FROM_STEAM", L"1");
			ffxivgame.StartInfo.Arguments += L" IsSteam=1";
			ffxivgame.StartInfo.UseShellExecute = false;
		}
		ffxivgame.Start();

//C# TO C++ CONVERTER TODO TASK: A 'delete ffxivgame' statement was not added since ffxivgame was used in a 'return' or 'throw' statement.
		return ffxivgame;
	}
	catch (const std::runtime_error &exc)
	{
		if (language == 0)
		{
			std::wcout << L"実行可能ファイルを起動できませんでした。 ゲームパスは正しいですか? " << exc << std::endl;
		}
		if (language == 1)
		{
			std::wcout << L"Could not launch executable. Is your game path correct? " << exc << std::endl;
		}
		if (language == 2)
		{
			std::wcout << L"Die ausführbare Datei konnte nicht gestartet werden. Ist dein Spielpfad korrekt? " << exc << std::endl;
		}
		if (language == 3)
		{
			std::wcout << L"Impossible de lancer l'exécutable. Votre chemin de jeu est-il correct? " << exc << std::endl;
		}
		if (language == 4)
		{
			std::wcout << L"Не удалось запустить файл. Ввели ли вы корректный путь к игре? " << exc << std::endl;
		}

	}

	return nullptr;
}

std::wstring networklogic::GetRealSid(const std::wstring &gamePath, const std::wstring &username, const std::wstring &password, const std::wstring &otp, bool isSteam)
{
	std::wstring hashstr = L"";
	try
	{
		// make the string of hashed files to prove game version//make the string of hashed files to prove game version
		hashstr = L"ffxivboot.exe/" + GenerateHash(gamePath + L"/boot/ffxivboot.exe") + L",ffxivboot64.exe/" + GenerateHash(gamePath + L"/boot/ffxivboot64.exe") + L",ffxivlauncher.exe/" + GenerateHash(gamePath + L"/boot/ffxivlauncher.exe") + L",ffxivlauncher64.exe/" + GenerateHash(gamePath + L"/boot/ffxivlauncher64.exe") + L",ffxivupdater.exe/" + GenerateHash(gamePath + L"/boot/ffxivupdater.exe") + L",ffxivupdater64.exe/" + GenerateHash(gamePath + L"/boot/ffxivupdater64.exe");
	}
	catch (const std::runtime_error &exc)
	{
		std::wcout << L"Could not generate hashes. Is your game path correct? " << exc << std::endl;
	}

	WebClient sidClient = gcnew WebClient();
	sidClient.Headers.Add(L"X-Hash-Check", L"enabled");
	sidClient.Headers.Add(L"user-agent", UserAgent);
	sidClient.Headers.Add(L"Referer", L"https://ffxiv-login.square-enix.com/oauth/ffxivarr/login/top?lng=en&rgn=3");
	sidClient.Headers.Add(L"Content-Type", L"application/x-www-form-urlencoded");

	InitiateSslTrust();

	try
	{
		auto localGameVer = GetLocalGamever(gamePath);
		auto localSid = GetSid(username, password, otp, isSteam);

		if (localGameVer == L"BAD" || localSid == L"BAD")
		{
			delete sidClient;
			return L"BAD";
		}

		auto url = L"https://patch-gamever.ffxiv.com/http/win32/ffxivneo_release_game/" + localGameVer + L"/" + localSid;
		sidClient.UploadString(url, hashstr); //request real session id
	}
	catch (const std::runtime_error &exc)
	{
		std::wcout << std::wstring::Format(L"Unable to retrieve a session ID from the server.\n") << exc << std::endl;
	}

	delete sidClient;
	return sidClient.ResponseHeaders[L"X-Patch-Unique-Id"];
}

std::wstring networklogic::GetStored(bool isSteam)
{
	WebClient loginInfo = gcnew WebClient();
	loginInfo.Headers.Add(L"user-agent", UserAgent);
	std::wstring reply = loginInfo.DownloadString(StringHelper::formatSimple(L"https://ffxiv-login.square-enix.com/oauth/ffxivarr/login/top?lng=en&rgn=3&isft=0&issteam={0}", isSteam ? 1 : 0));

	Regex storedre = gcnew Regex(LR"(\t<\sinput . name="_STORED_" value="(?<stored>.)">)");

	auto stored = storedre.Matches(reply)[0].Groups[L"stored"].Value;

	delete storedre;
	delete loginInfo;
	return stored;
}

std::wstring networklogic::GetSid(const std::wstring &username, const std::wstring &password, const std::wstring &otp, bool isSteam)
{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (WebClient loginData = gcnew WebClient())
	{
		WebClient loginData = WebClient();
		loginData.Headers.Add(L"user-agent", UserAgent);
		loginData.Headers.Add(L"Referer", StringHelper::formatSimple(L"https://ffxiv-login.square-enix.com/oauth/ffxivarr/login/top?lng=en&rgn=3&isft=0&issteam={0}", isSteam ? 1 : 0));
		loginData.Headers.Add(L"Content-Type", L"application/x-www-form-urlencoded");

		try
		{
			std::vector<unsigned char> response = loginData.UploadValues(L"https://ffxiv-login.square-enix.com/oauth/ffxivarr/login/login.send", gcnew NameValueCollection()
			{
				{L"_STORED_", GetStored(isSteam)},
				{L"sqexid", username},
				{L"password", password},
				{L"otppw", otp}
			});

			std::wstring reply = System::Text::Encoding::UTF8.GetString(response);
			//Console.WriteLine(reply);
			Regex sidre = gcnew Regex(LR"(sid,(?<sid>.),terms)");
			auto matches = sidre.Matches(reply);
			if (matches.Count == 0)
			{
				if (reply.find(L"ID or password is incorrect") != std::wstring::npos)
				{
					std::wcout << L"Incorrect username or password." << std::endl;

					delete sidre;
					return L"BAD";
				}
			}

			auto sid = sidre.Matches(reply)[0].Groups[L"sid"].Value;

			delete sidre;
			return sid;
		}
		catch (const std::runtime_error &exc)
		{
			std::wcout << std::wstring::Format(L"Something failed when attempting to request a session ID.\n") << exc << std::endl;
			return L"BAD";
		}
	}
}

std::wstring networklogic::GetLocalGamever(const std::wstring &gamePath)
{
	try
	{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (StreamReader sr = gcnew StreamReader(gamePath + R"(/game/ffxivgame.ver)"))
		{
			StreamReader sr = StreamReader(gamePath + LR"(/game/ffxivgame.ver)");
			std::wstring line = sr.ReadToEnd();
			return line;
		}
	}
	catch (const std::runtime_error &exc)
	{
		std::wcout << L"Unable to get local game version.\n" << exc << std::endl;
		return L"BAD";
	}
}

std::wstring networklogic::GenerateHash(const std::wstring &file)
{
	std::vector<unsigned char> filebytes = File::ReadAllBytes(file);

	SHA1Managed tempVar();
	auto hash = (&tempVar).ComputeHash(filebytes);
	std::wstring hashstring = std::wstring::Join(L"", hash.Select([&] (std::any b)
	{
		return b.ToString(L"x2");
	}).ToArray());

	FileInfo tempVar2(file);
	long long length = (&tempVar2).Length;

	return std::to_wstring(length) + L"/" + hashstring;
}

bool networklogic::GetGateStatus()
{
	try
	{
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (WebClient client = gcnew WebClient())
		{
			WebClient client = WebClient();
			std::wstring reply = client.DownloadString(L"http://frontier.ffxiv.com/worldStatus/gate_status.json");

			return static_cast<bool>(std::stoi(StringHelper::toString(reply[10])));
		}
	}
	catch (const std::runtime_error &exc)
	{
		std::wcout << L"Failed getting gate status. " << exc << std::endl;
		return false;
	}

}

void networklogic::InitiateSslTrust()
{
	//Change SSL checks so that all checks pass, squares gamever server does strange things
	ServicePointManager.ServerCertificateValidationCallback = gcnew RemoteCertificateValidationCallback([&] ()
	{
				return true;
	});
}

std::wstring networklogic::GenerateUserAgent()
{
	return std::wstring::Format(UserAgentTemplate, MakeComputerId());
}

std::wstring networklogic::MakeComputerId()
{
	auto hashString = Environment::MachineName + Environment::UserName + Environment::OSVersion + Environment::ProcessorCount;

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (var sha1 = HashAlgorithm.Create("SHA1"))
	{
		auto sha1 = HashAlgorithm::Create(L"SHA1");
		auto bytes = std::vector<unsigned char>(5);

		Array::Copy(sha1.ComputeHash(Encoding::Unicode.GetBytes(hashString)), 0, bytes, 1, 4);

		auto checkSum = static_cast<unsigned char>(-(bytes[1] + bytes[2] + bytes[3] + bytes[4]));
		bytes[0] = checkSum;

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
		return StringHelper::toLower(BitConverter::ToString(bytes).Replace(L"-", L""));
	}
}
