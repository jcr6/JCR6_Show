// Lic:
// JCR6 Show
// Show images and audio inside JCR6 file
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
#include <SlyvArgParse.hpp>
#include <SlyvQCol.hpp>

#include <SDL.h>
#include <TQSG.hpp>
#include <TQSA.hpp>

#include "../Headers/Flow.hpp"
#include "../Headers/FlowClass.hpp"
#include "../Headers/FlowAudio.hpp"
#include "../Headers/Glob.hpp"

using namespace Slyvina;
using namespace Units;
using namespace TQSG;
using namespace TQSA;

MKL_Init;

namespace JCR6_Show {
	void VersionList() {
		MKL_VersionP("JCR6_Show.cpp", __DATE__);
		MKL_Lic("JCR6_Show.cpp", "General Public License 3");
		FA_Version();
	}
	
}

int main(int c, char** a) {
	using namespace JCR6_Show;
	VersionList();
	FlagConfig C{};
	AddFlag_Bool(C, "NoHead", false);
	InitGlob(c,a,C);
	//IntRes(); // debug only
	if (CLI.arguments.size() < 2) {
		QCol->White("Usage: ");
		QCol->Magenta(StripAll(a[0]));
		QCol->Yellow(" <JCR6 Resource> ");
		QCol->Cyan("<Entry/Entries>\n");
		QCol->Reset();
		return 0;
	}
	InitFlowAudio();
	GoGraphics();
	Init_TQSA();
	for (uint32 i = 1; i < CLI.arguments.size(); i++) {
		auto F{ RecEnt(CLI.arguments[i]) };
		if (F) {
			QCol->Doing("Entry", CLI.arguments[i], "\t");
			QCol->Magenta("(" + F->Name() + ")\n");
			if (F->Init) F->Init(CLI.arguments[i]);
			do {} while (RunFlow(F, CLI.arguments[i]));
		} else {
			QCol->Error("I didn't find the right way to work with entry " + CLI.arguments[i]);
		}
	}
}