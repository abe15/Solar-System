#pragma once

#pragma comment(lib, "fmodex_vc.lib" )

#include "fmod.hpp" 


#define NUM_SOUNDS 8

//Sound identifiers
enum {
	SOUND_AMBIENT,
	SOUND_SWISH,
	SOUND_WARP,
	SOUND_UNLOCK,
	SOUND_ENERGYFLOW,
	SOUND_BOUNCE,
	SOUND_PICKUP,
	SOUND_SCREWGRAVITY
};

class Sound
{
public:
	Sound(void);
	virtual ~Sound(void);

	bool Load();
	void Play(int sound_id);
	void PlayBounce(float vol);
	void Stop(int sound_id);
	void SmoothStop(int sound_id);
	void StopAll();
	void Update();

	FMOD::System*     system; //handle to FMOD engine
    FMOD::Sound*      sounds[NUM_SOUNDS]; //sound that will be loaded and played
	FMOD::Channel*    ambient1Channel;
	FMOD::Channel*    bounceChannel;
	FMOD::DSP*        dspSmoothStop;
};