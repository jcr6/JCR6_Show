// Lic:
// JCR6 Show
// Flow Class
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
#pragma once
#include <TQSG.hpp>

namespace JCR6_Show {
	typedef void (*FShow)();
	typedef void(*FInit)(std::string);
	typedef bool (*Fertig)();	

	class Flow {
	private:
		std::string _Name{ "" };
	public:
		FShow Show{ nullptr };
		FInit Init{ nullptr };
		Fertig Done{ nullptr };

		Slyvina::uint32 Width{ Slyvina::TQSG::DesktopWidth() - 25u };
		Slyvina::uint32 Height{ 250 };

		inline std::string Name() { return _Name; }

		inline Flow(std::string _Nm,FShow _Sh = nullptr, FInit _In = nullptr,Fertig _Done=nullptr) {
			Show = _Sh;
			Init = _In;
			Done = _Done;
			_Name = _Nm;
		}
	};
}