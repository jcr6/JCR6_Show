// Lic:
// JCR6 Show
// Image Flow
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
#include <SlyvQCol.hpp>
#include <SlyvString.hpp>

#include <TQSG.hpp>
#include <TQSE.hpp>

#include <JCR6_Core.hpp>

#include "../Headers/Crash.hpp"
#include "../Headers/Glob.hpp"
#include "../Headers/Flow.hpp"
#include "../Headers/FlowClass.hpp"
#include "../Headers/FlowImage.hpp"


using namespace Slyvina;
using namespace Units;
using namespace JCR6;
using namespace TQSG;
using namespace TQSE;

namespace JCR6_Show {
	TImage _Img{ nullptr };

	struct cImg {
		TImage Image{ nullptr };
		uint32 Width{ 0 }, Height{ 0 };
		uint32 X{ 0 }, Y{ 0 };
		int Frame{ 0 };
		JT_Entry Ent;
	};

	cImg Img{};

	static void _ImageLoad(std::string entry) {
		cImg _I{ LoadImage(Res(), entry) };
		// cout << "Loaded!\n"; // debug
		if (!_I.Image) Crash("Image could not be loaded");
		Img = _I;
		Img.Height = Img.Image->Height();
		Img.Width = Img.Image->Width();
		if (Img.Width > ScreenWidth()) {
			double Ratio{ (double)ScreenWidth() / (double)Img.Width};
			Img.Width = ScreenWidth();
			Img.Height = floor((double)Img.Height * Ratio);
		}
		if (Img.Width > ScreenHeight()-80) {
			double SH = ScreenHeight() - 80;
			double Ratio{ SH / (double)Img.Height };
			Img.Height = (uint32)SH;
			Img.Width = floor((double)Img.Width * Ratio);
		}
		Img.X = (ScreenWidth() / 2) - (Img.Width / 2);
		Img.Y = (((ScreenHeight() - 80) / 2) - (Img.Height)) + 80;
		if (Res()->DirectoryExists(entry)) {
			auto F{ Res()->Directory(entry) };
			if (!F->size()) Crash("Frameless image bundle");
			Img.Ent = Res()->Entry((*F)[0]);
		} else if (Res()->EntryExists(entry))
			Img.Ent = Res()->Entry(entry);
		else Crash("Image data error!");
	}

	static void _ImageShow() {
		SetColor(255, 255, 255);
		Img.Image->StretchDraw(Img.X, Img.Y, Img.Width, Img.Height, Img.Frame);
		MiniFont()->Text(TrSPrintF("Frame:  %d/%d", Img.Frame + 1, Img.Image->Frames()), 2, 60);
		MiniFont()->Text(TrSPrintF("Format: %dx%d", Img.Image->Width(), Img.Image->Height()), 2, 80);
		MiniFont()->Text(TrSPrintF("Artist: %s", Img.Ent->Author().c_str(), Img.Image->Height()), 2, 100);
		MiniFont()->Text(Img.Ent->Notes(), 2, 120);
		if (KeyHit(SDLK_LEFT)) { Img.Frame--; if (Img.Frame<0) Img.Frame=Img.Image->Frames()-1; }
		if (KeyHit(SDLK_RIGHT)) Img.Frame = (Img.Frame + 1) % Img.Image->Frames();
	}

	Flow _ImageFlow{"Image", _ImageShow,_ImageLoad};
	Flow _ImageFlowBundle{"Image Bundle",_ImageShow,_ImageLoad };

	void InitImage() {
		MKL_VersionP("Flow_Image.cpp", __DATE__);
		MKL_Lic("Flow_Image.cpp", "General Public License 3");
		QCol->Doing("Init", "Image");
		_ImageFlow.Height = DesktopHeight() - 200;
		_ImageFlowBundle.Height = DesktopHeight() - 200;
		RegisterFlow("PNG", &_ImageFlow);        // Portable Network Graphic
		RegisterFlow("BMP", &_ImageFlow);        // BitMap
		RegisterFlow("JPG", &_ImageFlow);        // Joint-Point Expert Group
		RegisterFlow("JPEG", &_ImageFlow);       // Joint-Point Expert Group
		RegisterFlow("GIF", &_ImageFlow);        // Graphics interchange format
		RegisterFlow("TIFF", &_ImageFlow);       // Tagged Image File Format
		RegisterFlow("JPBF", &_ImageFlowBundle); // JCR6 Picture Bundle File
	}

}