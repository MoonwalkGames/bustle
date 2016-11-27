#include "AudioEngine.h"

CAudioEngine* CAudioEngine::inst = nullptr;

/*
Initialize FMOD, create Fmod Studio & low-level fmod systems, sets their variables. 
*/
Implementation::Implementation()
{
	mpStudioSystem = NULL;
	/*
	creating the Fmod Studio System that handles all the events and sounds, then we initialize it with the number of channels, 
	and then the flags that can change the way the system runs.
	*/
	CAudioEngine::ErrorCheck(FMOD::Studio::System::create(&mpStudioSystem));
	CAudioEngine::ErrorCheck(mpStudioSystem->initialize(32, FMOD_STUDIO_INIT_LIVEUPDATE, FMOD_INIT_PROFILE_ENABLE, NULL));

	mpSystem = NULL;
	CAudioEngine::ErrorCheck(mpStudioSystem->getLowLevelSystem(&mpSystem));
}

/*
Clean up FMOD, unload all assets.
*/
Implementation::~Implementation()
{
	CAudioEngine::ErrorCheck(mpStudioSystem->unloadAll());
	CAudioEngine::ErrorCheck(mpStudioSystem->release());
}

/*
Check if channel has stopped playing, if it has, destroy it to free up the channel. 
Update FMOD to update sounds.
*/
void Implementation::update()
{
	std::vector<ChannelMap::iterator> pStoppedChannels;
	for (auto it = mChannels.begin(), itEnd = mChannels.end(); it != itEnd; ++it)
	{
		bool bIsPlaying = false;
		it->second->isPlaying(&bIsPlaying);
		if (!bIsPlaying)
		{
			pStoppedChannels.push_back(it);
		}
	}
	for (auto& it : pStoppedChannels)
	{
		mChannels.erase(it);
	}
	CAudioEngine::ErrorCheck(mpStudioSystem->update());
}

//create an instance of the implementation
Implementation * sgpImplementation = nullptr;

//init the implementation
void CAudioEngine::init()
{
	sgpImplementation = new Implementation;
}

//call its update
void CAudioEngine::update()
{
	sgpImplementation->update();
}

/*
loads a given sound, and gives it the provided parameters, whether it's 3d or not, if it's looping, if it's being streamed or sampled.
then stores the sound in our sound map
*/
void CAudioEngine::loadSound(const std::string& strSoundName, bool b3d, bool blooping, bool bstream)
{
	auto tFoundIt = sgpImplementation->mSounds.find(strSoundName);
	if (tFoundIt != sgpImplementation->mSounds.end())
		return;

	FMOD_MODE eMode = FMOD_DEFAULT;
	eMode |= b3d ? FMOD_3D : FMOD_2D;
	eMode |= blooping ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
	eMode | bstream ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE;

	FMOD::Sound* pSound = nullptr;
	CAudioEngine::ErrorCheck(sgpImplementation->mpSystem->createSound(strSoundName.c_str(), eMode, nullptr, &pSound));
	if (pSound)
	{
		sgpImplementation->mSounds[strSoundName] = pSound;
	}
}
/*
looks up the given sound in the sound map, if it finds it then deletes it.
*/
void CAudioEngine::unLoadSound(const std::string& strSoundName)
{
	auto tFoundIt = sgpImplementation->mSounds.find(strSoundName);
	if (tFoundIt == sgpImplementation->mSounds.end())
		return;

	CAudioEngine::ErrorCheck(tFoundIt->second->release());
	sgpImplementation->mSounds.erase(tFoundIt);
}

/*
check if we have the sound in our sound map, if we don't then load it.
Create new channel to house the sound, and set parameters, then set it to play. 
Returns channel id.
*/
int CAudioEngine::playSound(const std::string& strSoundName, const glm::vec3 vpos, float fVolumedB)
{
	int nChannelId = sgpImplementation->mnNextChannelID++;
	auto tFoundIt = sgpImplementation->mSounds.find(strSoundName);
	if (tFoundIt == sgpImplementation->mSounds.end())
	{
		loadSound(strSoundName);
		tFoundIt = sgpImplementation->mSounds.find(strSoundName);
		if (tFoundIt == sgpImplementation->mSounds.end())
		{
			return nChannelId;
		}
	}
	FMOD::Channel* pChannel = nullptr;
	CAudioEngine::ErrorCheck(sgpImplementation->mpSystem->playSound(tFoundIt->second, nullptr, true, &pChannel));
	if (pChannel)
	{
		FMOD_MODE currMode;
		tFoundIt->second->getMode(&currMode);
		if (currMode & FMOD_3D) {
			FMOD_VECTOR position = vectorToFmod(vpos);
			CAudioEngine::ErrorCheck(pChannel->set3DAttributes(&position, nullptr));
		}
		CAudioEngine::ErrorCheck(pChannel->setVolume(dBtoVolume(fVolumedB)));
		CAudioEngine::ErrorCheck(pChannel->setPaused(false));
		sgpImplementation->mChannels[nChannelId] = pChannel;
	}
	return nChannelId;
}

/*
looks up the given id, if it's found then set its position.
*/
void CAudioEngine::setChannel3dPosition(int nChannelId, const glm::vec3& vPosition)
{
	auto tFoundIt = sgpImplementation->mChannels.find(nChannelId);
	if (tFoundIt == sgpImplementation->mChannels.end())
		return;
	

	FMOD_VECTOR position = vectorToFmod(vPosition);
	CAudioEngine::ErrorCheck(tFoundIt->second->set3DAttributes(&position, NULL));
}

/*
looks up the given id, if it's found then set its volume.
*/
void CAudioEngine::setChannelVolume(int nChannelId, float fVolumedB)
{
	auto tFoundIt = sgpImplementation->mChannels.find(nChannelId);
	if (tFoundIt == sgpImplementation->mChannels.end())
		return;

	CAudioEngine::ErrorCheck(tFoundIt->second->setVolume(dBtoVolume(fVolumedB)));
}

//loads the given bank. banks store all the sounds and information for each event.
void CAudioEngine::loadBank(const std::string& strBankName,  FMOD_STUDIO_LOAD_BANK_FLAGS flags) 
{
	auto tFoundIt = sgpImplementation->mBanks.find(strBankName);
	if (tFoundIt != sgpImplementation->mBanks.end())
		return;
	FMOD::Studio::Bank* pBank;
	CAudioEngine::ErrorCheck(sgpImplementation->mpStudioSystem->loadBankFile(strBankName.c_str(), flags, &pBank));
	if (pBank) {
		sgpImplementation->mBanks[strBankName] = pBank;
	}
}

//check if given event has been loaded, if it haasnt then load it
void CAudioEngine::loadEvent(const std::string& strEventName) 
{
	auto tFoundit = sgpImplementation->mEvents.find(strEventName);
	if (tFoundit != sgpImplementation->mEvents.end())
		return;
	FMOD::Studio::EventDescription* pEventDescription = NULL;
	CAudioEngine::ErrorCheck(sgpImplementation->mpStudioSystem->getEvent(strEventName.c_str(), &pEventDescription));
	if (pEventDescription) {
		FMOD::Studio::EventInstance* pEventInstance = NULL;
		CAudioEngine::ErrorCheck(pEventDescription->createInstance(&pEventInstance));
		if (pEventInstance) {
			sgpImplementation->mEvents[strEventName] = pEventInstance;
		}
	}
}

//check if event is loaded, if it isn't then load it, and then play it.
void CAudioEngine::playEvent(const std::string &strEventName) 
{
	auto tFoundit = sgpImplementation->mEvents.find(strEventName);
	if (tFoundit == sgpImplementation->mEvents.end()) {
		loadEvent(strEventName);
		tFoundit = sgpImplementation->mEvents.find(strEventName);
		if (tFoundit == sgpImplementation->mEvents.end())
			return;
	}
	tFoundit->second->start();
}

//stops the given event, whether it should stop immediately or have a fade out.
void CAudioEngine::stopEvent(const std::string &strEventName, bool bImmediate) 
{
	auto tFoundIt = sgpImplementation->mEvents.find(strEventName);
	if (tFoundIt == sgpImplementation->mEvents.end())
		return;

	FMOD_STUDIO_STOP_MODE eMode;
	eMode = bImmediate ? FMOD_STUDIO_STOP_IMMEDIATE : FMOD_STUDIO_STOP_ALLOWFADEOUT;
	CAudioEngine::ErrorCheck(tFoundIt->second->stop(eMode));
}

//if the give event isn't found, then it's not playing. if it's playing then return true, else return false. 
bool CAudioEngine::isEventPlaying(const std::string &strEventName) const 
{
	auto tFoundIt = sgpImplementation->mEvents.find(strEventName);
	if (tFoundIt == sgpImplementation->mEvents.end())
		return false;

	FMOD_STUDIO_PLAYBACK_STATE* state = NULL;
	if (tFoundIt->second->getPlaybackState(state) == FMOD_STUDIO_PLAYBACK_PLAYING) {
		return true;
	}
	return false;
}

//get the given parameter.
void CAudioEngine::getEventParameter(const std::string &strEventName, const std::string &strParameterName, float* parameter) 
{
	auto tFoundIt = sgpImplementation->mEvents.find(strEventName);
	if (tFoundIt == sgpImplementation->mEvents.end())
		return;

	FMOD::Studio::ParameterInstance* pParameter = NULL;
	CAudioEngine::ErrorCheck(tFoundIt->second->getParameter(strParameterName.c_str(), &pParameter));
	CAudioEngine::ErrorCheck(pParameter->getValue(parameter));
}

//pass a string of what event we want to change, and what we want to set it to.
void CAudioEngine::setEventParameter(const std::string &strEventName, const std::string &strParameterName, float fValue) 
{
	auto tFoundIt = sgpImplementation->mEvents.find(strEventName);
	if (tFoundIt == sgpImplementation->mEvents.end())
		return;

	FMOD::Studio::ParameterInstance* pParameter = NULL;
	CAudioEngine::ErrorCheck(tFoundIt->second->getParameter(strParameterName.c_str(), &pParameter));
	CAudioEngine::ErrorCheck(pParameter->setValue(fValue));
}

//converts a glm vec3 to an fmod vector 3
FMOD_VECTOR CAudioEngine::vectorToFmod(const glm::vec3& vPosition) 
{
	FMOD_VECTOR fVec;
	fVec.x = vPosition.x;
	fVec.y = vPosition.y;
	fVec.z = vPosition.z;
	return fVec;
}

//converts decibels to fmod volulme
float  CAudioEngine::dBtoVolume(float dB)
{
	return powf(10.0f, 0.05f * dB);
}

//converts fmod volume to decibels
float  CAudioEngine::volumeTodB(float volume)
{
	return 20.0f * log10f(volume);
}

//checks & prints out errors
int CAudioEngine::ErrorCheck(FMOD_RESULT result) 
{
	if (result != FMOD_OK) {
		std::cout << "FMOD ERROR " << result << std::endl;
		return 1;
	}
	// cout << "fmod's ok"<< endl;
	return 0;
}

void CAudioEngine::shutDown() 
{
	delete sgpImplementation;
}

CAudioEngine* CAudioEngine::sounds()
{
	if (!inst)
		inst = new CAudioEngine();

	return inst;
}

void CAudioEngine::stopChannel(int nChannelID)
{
	
	auto tFoundIt = sgpImplementation->mChannels.find(nChannelID);
	if (tFoundIt == sgpImplementation->mChannels.end())
		return;

	CAudioEngine::ErrorCheck(tFoundIt->second->stop());
}

void CAudioEngine::stopAllChannels()
{
	for (int i = 0; i < 32; i++)
	{
		stopChannel(i);
	}
}