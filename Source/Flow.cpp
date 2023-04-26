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

#include "../Headers/Crash.hpp"
#include "../Headers/Glob.hpp"
#include "../Headers/Flow.hpp"
#include "../Headers/FlowClass.hpp"


#include "../Headers/FlowAudio.hpp"

using namespace std;
using namespace Slyvina;
using namespace Units;
using namespace TQSG;


namespace JCR6_Show {
	static map<string, Flow*> _FlowReg{};

	void GoGraphics() {
		uint32 x{ 0 }, y{ 0 };
		for (uint32 i = 1; i < CLI.arguments.size();i++) {
			auto FR{ RecEnt(CLI[i]) };
			if (FR) {
				x = max(x, FR->Width);
				y = max(y, FR->Height);
			}
		}
		QCol->Doing("Graphics", TrSPrintF("%04dx%04d", x, y));
		Graphics(x, y, "JCR6 Show - Coded and copyrighted by: Jeroen P. Broks");
	}

	Flow* RecEnt(std::string f, Bank B) {
		Trans2Upper(f);
		if (f.size() && _FlowReg.count(f)) return _FlowReg[f];
		return nullptr;
	}

	Flow* FlowReg(string n) {
		Trans2Upper(n);
		Assert(_FlowReg.count(n), "There is no flow for: " + n);
		return _FlowReg[n];
	}

	void RegisterFlow(std::string n, Flow* f) { _FlowReg[n] = f; }

	void InitFlow() {
		InitFlowAudio();
	}

}