// Lic:
// JCR6 Show
// Flow Audio
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

#include <TQSA.hpp>

#include <SlyvMKL.hpp>
#include <SlyvQCol.hpp>
#include <SlyvTime.hpp>

#include "../Headers/Crash.hpp"
#include "../Headers/Glob.hpp"
#include "../Headers/Flow.hpp"
#include "../Headers/FlowClass.hpp"
#include "../Headers/FlowAudio.hpp"

using namespace std;
using namespace Slyvina;
using namespace Units;
using namespace TQSA;

namespace JCR6_Show {

	static TAudio LoadedAudio;
	static string Artist{ "" }, Notes{ "" };
	static uint64 PlayTime{ 0 };
	static string _PT{ "" };
	static int PChannel{ 0 };

	static void AudioInit(string AudEntry) {
		cout << "Loading: " << AudEntry << "\n"; // debug
		LoadedAudio = LoadAudio(Res(), AudEntry);
		if (!LoadedAudio) {
			QCol->Red("FATAL "); QCol->Error("Couldn't load audio: " + AudEntry);
			QCol->Red("FATAL "); QCol->Error("SDL2 Reported: " + string(SDL_GetError()));
			QCol->Red("FATAL "); QCol->Error("JCR6 Reported: " + JCR6::Last()->ErrorMessage);
			exit(2);
		}
		auto E{ Res()->Entry(AudEntry) };
		Artist = E->Author();
		Notes = E->Notes();
		PlayTime = 0;
		PChannel = LoadedAudio->Play();
		_PT = CurrentTime();
	}

	static void AudioRun() {
		if (Artist.size()) MiniFont()->Text("Artist: " + Artist, 2, 80);
		MiniFont()->Text(Notes, 2, 100);
		if (_PT != CurrentTime()) {
			PlayTime++;
			_PT = CurrentTime();
		}
		int64 RMin = PlayTime / 60;
		int64 RHor = RMin / 60;
		MiniFont()->Text(TrSPrintF("Time: %d:%02d:%02d", RHor, RMin % 60, PlayTime % 60), 2, 120);
	}

	static bool Playing() {
		// cout << Mix_Playing(PChannel) << endl; // debug
		return !Mix_Playing(PChannel);
	}

	static Flow AudioFlow{"Audio",AudioRun,AudioInit,Playing};

	void FA_Version() {
		MKL_VersionP("FlowAudio.cpp", __DATE__);
		MKL_Lic("FlowAudio.cpp", "General Public License 3");
	}

	void InitFlowAudio() {
		QCol->Doing("Registering", "Audio routines");		
		RegisterFlow("FLAC", &AudioFlow); // Free Lossless Audio Codec
		RegisterFlow("MP3", &AudioFlow);  // Moving Picture Experts Group - Audio Layer III
		RegisterFlow("WAV", &AudioFlow);  // Wave
		RegisterFlow("OGG", &AudioFlow);  // OGG / OGG Vorbis
	}
}