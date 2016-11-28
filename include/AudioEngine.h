#pragma once

//fmod includes
#include <fmod/fmod_studio.hpp>
#include <fmod\fmod.hpp>

//standard includes
#include <string>
#include <map>
#include <vector>
#include <math.h>
#include <iostream>
#include <glm\glm.hpp>

/*
Created using a tutorial by Cody Claborn 
http://codyclaborn.me/2016/04/12/making-a-basic-fmod-audio-engine-in-c
*/

/*
Contains calls to the FMOD API. Contains initialization, destruction, as well as instances for FMOD Studio, and low-level FMOD.
Also contains a map of all sounds & events played, as well as the update function.

*/

struct Implementation
{
	Implementation();
	~Implementation();

	void update();

	FMOD::Studio::System* mpStudioSystem;
	FMOD::System* mpSystem;

	int mnNextChannelID;

	typedef std::map<std::string, std::pair<FMOD::Sound*, FMOD::Channel*>> SoundMap;
	typedef std::map<int, FMOD::Channel*> ChannelMap;
	typedef std::map<std::string, FMOD::Studio::EventInstance*> EventMap;
	typedef std::map<std::string, FMOD::Studio::Bank*> BankMap;

	BankMap mBanks;
	EventMap mEvents;
	SoundMap mSounds;
	ChannelMap mChannels;
};
/*
Does calls to the Implementation stuct to start, stop and update FMOD. 
Also handles loading, playing, stopping and updating information on sounds and events.
*/
class CAudioEngine
{
//protected:
	//CAudioEngine();
public:
	static void init();
	static void update();
	static void shutDown();
	static int ErrorCheck(FMOD_RESULT result);
	
	void loadBank(const std::string& strBankName, FMOD_STUDIO_LOAD_BANK_FLAGS flags);
	void loadEvent(const std::string& strEventName);
	void loadSound(const std::string& strSoundName, bool b3d = true, bool bLooping = false, bool bstream = false);
	void unLoadSound(const std::string& strSoundName);
	void set3dListenerAndOrientation(const glm::vec3& vpos = glm::vec3(0.0f), float fVolumedB = 0.0f);
	int playSound(const std::string& strSoundName, const glm::vec3 vpos = glm::vec3(0.0f), float fVolumedB = 0.0f);
	void stopSound(const std::string& strSoundName);
	void playEvent(const std::string& strEventName);
	void stopChannel(int nChannelID);
	void stopEvent(const std::string& strEventName, bool bImmediate = false);
	void getEventParameter(const std::string& strEventName, const std::string& strEventParameter, float* parameter);
	void setEventParameter(const std::string& strEventName, const std::string& strParameterName, float fValue);
	void stopAllChannels();
	void setChannel3dPosition(int nChannelID, const glm::vec3& vPosition);
	void setChannelVolume(int nChannelID, float fVolumedB);
	bool isPlaying(int nChannelID) const;
	bool isEventPlaying(const std::string& strEventName) const;
	float dBtoVolume(float db);
	float volumeTodB(float volume);
	FMOD_VECTOR vectorToFmod(const glm::vec3& vPosition);

	static CAudioEngine* sounds(); //Singleton pattern

private:
	static CAudioEngine* inst; //Singleton pattern

};

typedef CAudioEngine AE; //Typedef in order to make calling the singleton easier