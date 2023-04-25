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
// Version: 23.04.25
// EndLic
#include <SlyvMKL.hpp>
#include <SlyvQuickHead.hpp>
#include <SlyvStream.hpp>
#include <SlyvString.hpp>

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
	Slyvina::Units::ParsedArg CLI;
	static JT_Dir _IntRes{ nullptr };

	void JPaniek(std::string e) {
		Crash("JCR6 Error ->" + e);
	}
		
	static void _initJCR() {
		JCR_InitZlib();
		Westwood_Init();
		InitQuake();
		InitWAD();
		InitJQL();
		JCR6PANIC = JPaniek;
	}

	void InitGlob(int c, char** a,FlagConfig &CFG) {
		Slyvina::Units::MKL_VersionP("Glob.cpp", __DATE__);
		CLI = ParseArg(c, a, CFG);
		Title();
	}

	void Title() {
		if (!CLI.bool_flags["NoHead"]) QuickHeader("JCR6 Show", 2023);
	}

	std::string IntResFile() { return ExtractDir(CLI.myexe) + "/JCR6_Assets.jcr"; }

	JT_Dir IntRes() {
		_initJCR();
		if (!FileExists(IntResFile())) Crash(TrSPrintF("File not found: %s",IntResFile().c_str()));
		if (!_IntRes) {
			QCol->Doing("Analysing", StripDir(IntResFile()));
			_IntRes = JCR6_Dir(IntResFile());			
		}
		return _IntRes;
	}

}