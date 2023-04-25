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
// Version: 23.04.25
// EndLic
#include <SlyvMKL.hpp>
#include <SlyvQuickHead.hpp>
#include <SlyvArgParse.hpp>
#include <SlyvQCol.hpp>

#include <SDL.h>

#include "../Headers/FlowClass.hpp"
#include "../Headers/Glob.hpp"

using namespace Slyvina;
using namespace Units;

MKL_Init;

namespace JCR6_Show {
	void VersionList() {
		MKL_VersionP("JCR6_Show.cpp", __DATE__);
		MKL_Lic("JCR6_Show.cpp", "General Public License 3");
	}
}

int main(int c, char** a) {
	using namespace JCR6_Show;
	MKL_VersionP("JCR6_Show.cpp", __DATE__);
	MKL_Lic("JCR6_Show.cpp", "General Public License 3");
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
}