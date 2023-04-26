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

#include <SlyvQCol.hpp>

#include "../Headers/Flow.hpp"
#include "../Headers/FlowClass.hpp"

using namespace Slyvina;
using namespace Units;
using namespace TQSA;

namespace JCR6_Show {

	static void AudioInit() {}
	static void AudioRun() {}

	static Flow AudioFlow{AudioRun,AudioInit};

	void InitFlowAudio() {
		QCol->Doing("Registering", "Audio routines");		
		RegisterFlow("FLAC", &AudioFlow); // Free Lossless Audio Codec
		RegisterFlow("MP3", &AudioFlow);  // Moving Picture Experts Group - Audio Layer III
		RegisterFlow("WAV", &AudioFlow);  // Wave
		RegisterFlow("OGG", &AudioFlow);  // OGG / OGG Vorbis

	}
}