#include "audioManager.hpp"

bool AudioManager::loadSoundBuffer(const std::string &name, const std::string &path){
	bool success = false;
	sf::SoundBuffer buffer;

	if(buffer.loadFromFile(path)){
		soundBuffers[name] = buffer;

		sf::Sound sound;
		sound.setBuffer(soundBuffers[name]);
		sounds[name] = sound;

		success = true;
	}

	return success;
}

void AudioManager::addMusicPath(const std::string &name, const std::string &path){
	musicPaths[name] = path;
}

bool AudioManager::soundBufferExists(const std::string &name){
	return (soundBuffers.find(name) != soundBuffers.end());
}

bool AudioManager::musicPathExists(const std::string &name){
	return (musicPaths.find(name) != musicPaths.end());
}

void AudioManager::unloadSoundBuffer(const std::string &name){
	soundBuffers.erase(name);
}

void AudioManager::removeMusicPath(const std::string &name){
	musicPaths.erase(name);
}

void AudioManager::playSound(const std::string &name){
	sounds[name].play();
}

void AudioManager::playMusic(const std::string &name){
	currentMusic.openFromFile(musicPaths[name]);
	currentMusic.play();
}

void AudioManager::stopMusic(){
	currentMusic.stop();
}

bool AudioManager::isMusicPaused(){
	return (currentMusic.getStatus() == sf::Music::Paused);
}

void AudioManager::toggleMusicPause(){
	isMusicPaused() ? currentMusic.play() : currentMusic.pause();
}

void AudioManager::setMusicLoop(bool loop){
	currentMusic.setLoop(loop);
}

sf::SoundBuffer &AudioManager::getSoundBuffer(const std::string &name){
	return soundBuffers[name];
}

std::string AudioManager::getMusicPath(const std::string &name){
	return musicPaths[name];
}

void AudioManager::setSfxVolume(float n){
	sfxVolume = n;

	if(sfxVolume > 100.f) sfxVolume = 100.f;
	else if(sfxVolume < 0.f) sfxVolume = 0.f;

	for(auto &s : sounds)
		s.second.setVolume(sfxVolume);
}

float AudioManager::getSfxVolume(){
	return sfxVolume;
}

void AudioManager::setMusicVolume(float n){
	musicVolume = n;

	if(musicVolume > 100.f) musicVolume = 100.f;
	else if(musicVolume < 0.f) musicVolume = 0.f;
	
	currentMusic.setVolume(musicVolume);
}

float AudioManager::getMusicVolume(){
	return musicVolume;
}
