// Lic:
// JCR6 Show
// Flow
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

#include <Slyvina.hpp>
#include <algorithm>

#include <SlyvString.hpp>
#include <SlyvQCol.hpp>

#include <TQSG.hpp>
#include <TQSE.hpp>

#include "../Headers/Crash.hpp"
#include "../Headers/Glob.hpp"
#include "../Headers/Flow.hpp"
#include "../Headers/FlowClass.hpp"


#include "../Headers/FlowAudio.hpp"

using namespace std;
using namespace Slyvina;
using namespace Units;
using namespace TQSG;
using namespace TQSE;


namespace JCR6_Show {
	static map<string, Flow*> _FlowReg{};
	static bool __never() { return false; }

	void GoGraphics() {
		uint32 x{ 0 }, y{ 0 };
		for (uint32 i = 1; i < CLI.arguments.size(); i++) {
			auto FR{ RecEnt(CLI.arguments[i]) };
			if (FR) {
				x = max(x, FR->Width);
				y = max(y, FR->Height);
			}
		}
		QCol->Doing("Graphics", TrSPrintF("%04dx%04d", x, y));
		Graphics(x, y, "JCR6 Show - Coded and copyrighted by: Jeroen P. Broks");
	}

	Flow* RecEnt(std::string f, Bank B) {
		auto e{ Upper(ExtractExt(f)) };
		if (e.size() && _FlowReg.count(e)) return FlowReg(e);
		return nullptr;
	}

	Flow* FlowReg(string n) {
		Trans2Upper(n);
		Assert(_FlowReg.count(n), "There is no flow for: " + n);
		if (!_FlowReg[n]->Done) _FlowReg[n]->Done = __never;
		return _FlowReg[n];
	}

	void RegisterFlow(std::string n, Flow* f) { _FlowReg[n] = f; }

	void InitFlow() {
		InitFlowAudio();
	}

	bool RunFlow(Flow* F,string n) {
		try {
			static uint32 Hue;
			Poll(); Cls();
			Hue = (Hue + 1) % 360;
			for (uint32 y = 0; y < ScreenHeight(); y++) {
				SetColorHSV((Hue + (y / 5)) % 360, 1, .5);
				Line(0, y, ScreenWidth(), y);
			}
			SetColor(255, 255, 255);
			BigFont()->Text(n, 2, 2);
			if (F->Show) F->Show();
			Flip();
			return !(F->Done() || AppTerminate());
		} catch (std::exception e) {
			Crash(e.what());
			return true;
		}
	}

}