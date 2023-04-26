// Lic:
// JCR6 Show
// Globals
// 
// 
// 
// (c) Jeroen P. Broks, 2023
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// 
// Please note that some references to data like pictures or audio, do not automatically
// fall under this licenses. Mostly this is noted in the respective files.
// 
// Version: 23.04.26
// EndLic
#include <SlyvMKL.hpp>
#include <SlyvQuickHead.hpp>
#include <SlyvStream.hpp>
#include <SlyvString.hpp>
#include <SlyvGINIE.hpp>
#include <SlyvMD5.hpp>

#include <JCR6_Core.hpp>
#include <JCR6_JQL.hpp>
#include <JCR6_QuakePAK.hpp>
#include <JCR6_WAD.hpp>
#include <JCR6_Westwood.hpp>
#include <JCR6_zlib.hpp>

#include "../Headers/Glob.hpp"
#include "../Headers/Crash.hpp"

using namespace Slyvina;
using namespace Units;
using namespace JCR6;

namespace JCR6_Show {

	const char* IDHash{ "91b397db8f1dc198555ce2d1cffbb5a3" };

	Slyvina::Units::ParsedArg CLI;
	static JT_Dir _IntRes{ nullptr };
	static JT_Dir _Res{ nullptr };

	void JPaniek(std::string e) {
		Crash("JCR6 Error ->" + e);
	}
		
	static void _initJCR() {
		static bool done{ false };
		if (!done) {
			JCR_InitZlib();
			Westwood_Init();
			InitQuake();
			InitWAD();
			InitJQL();
			JCR6PANIC = JPaniek;
		}
		done = true;
	}

	void InitGlob(int c, char** a,FlagConfig &CFG) {
		Slyvina::Units::MKL_VersionP("Glob.cpp", __DATE__);
		CLI = ParseArg(c, a, CFG);
		Title();
	}

	void Title() {
		if (!CLI.bool_flags["NoHead"]) QuickHeader("JCR6 Show", 2023);
	}

	Slyvina::TQSG::TImageFont BigFont() {
		using namespace Slyvina::TQSG;
		static TImageFont Ret{ nullptr };
		if (!Ret) {
			QCol->Doing("Get Font", "Ryanna");
			Ret = LoadImageFont(IntRes(),"Fonts/Ryanna.jfbf");
			Assert((bool)Ret, "Font not loaded properly");
		}
		return Ret;
	}

	Slyvina::TQSG::TImageFont MiniFont() {
		using namespace Slyvina::TQSG;
		static TImageFont Ret{ nullptr };
		if (!Ret) {
			QCol->Doing("Get Font", "Mini");
			Ret = LoadImageFont(IntRes(), "Fonts/Mini.jfbf");
			Assert((bool)Ret, "Font not loaded properly");
		}
		return Ret;
	}

	std::string IntResFile() { return ExtractDir(CLI.myexe) + "/JCR6_Assets.jcr"; }

	JT_Dir IntRes() {
		try {
			_initJCR();
			if (!FileExists(IntResFile())) Crash(TrSPrintF("File not found: %s", IntResFile().c_str()));
			if (!_IntRes) {
				QCol->Doing("Analysing", StripDir(IntResFile()));
				_IntRes = JCR6_Dir(IntResFile());
				Assert((bool)_IntRes, "Failed to load: " + IntResFile());
				auto ID{ ParseUGINIE(_IntRes->GetString("Identify.ini")) };
				//std::cout << md5(ID->Value("check", "show")) << " <==> " << IDHash << "\n"; // debug only
				Assert(md5(ID->Value("check", "show")) == IDHash, "Identification wrong");
			}
		} catch (std::exception e) { Crash(e.what()); }
		return _IntRes;
	}

	Slyvina::JCR6::JT_Dir Res() {
		try {
			_initJCR();
			if (!FileExists(ResFile())) Crash(TrSPrintF("File not found: %s", ResFile().c_str()));
			if (!_Res) {
				QCol->Doing("Analysing", ResFile());
				_Res = JCR6_Dir(ResFile());
				Assert((bool)_Res, "Failed to load: " + ResFile());
				//cout << "DEBUG\n"; for (auto E : _Res->_Entries) cout << ">" << E.second->Name() << endl; cout << "END DEBUG\n";
			}
		} catch (std::exception e) { Crash(e.what()); }
		return _Res;
	}

}