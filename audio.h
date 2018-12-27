#ifndef _AUDIO_H               // Prevent multiple definitions if this 
#define _AUDIO_H               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <xact3.h>
#include "constants.h"

class Audio
{
private:
	IXACT3Engine* xactEngine;		//pointer to XACT sound engine
	IXACT3WaveBank* waveBank;		//pointer to XACT wave bank
	XACTINDEX cueI;					//XACT sound index
	void* mapWaveBank;				//call UnmapViewOfFile() to release file
	void* soundBankData;
	bool* coInitialized;			//set true if coInitialize is successful

public:
	Audio();

	virtual ~Audio();

	HRESULT initialize();

	void run();

	void playCue(const char cue[]);

	void stopCue(const char cue[]);

};

#endif
