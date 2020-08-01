#pragma once

#include <SFML/Audio.hpp>
#include <string>
#include <map>

class AudioManager{
public:
	// Load sound buffer data and store it by given name
	// and prepare sf::Sound with same name
	bool loadSoundBuffer(const std::string &name, const std::string &path);
	// Add new path to music file and store it by given name.
	void addMusicPath(const std::string &name, const std::string &path);

	bool soundBufferExists(const std::string &name);
	bool musicPathExists(const std::string &name);

	void unloadSoundBuffer(const std::string &name);
	void removeMusicPath(const std::string &name);

	void playSound(const std::string &name);
	// Open stream from music file and play it.
	void playMusic(const std::string &name);
	
	void stopMusic();
	bool isMusicPaused();
	// Toggle music pause. If music is paused then play it and vice versa.
	void toggleMusicPause();
	void setMusicLoop(bool loop);

	sf::SoundBuffer &getSoundBuffer(const std::string &name);
	std::string getMusicPath(const std::string &name);

	// Set sound effects volume and clamp it between 0 and 100.
	void setSfxVolume(float n);
	float getSfxVolume();

	// Set music volume and clamp it between 0 and 100.
	void setMusicVolume(float n);
	float getMusicVolume();

private:
	std::map<std::string, sf::SoundBuffer> soundBuffers;
	std::map<std::string, sf::Sound> sounds;
	std::map<std::string, std::string> musicPaths;
	
	sf::Music currentMusic;

	float sfxVolume = 100.f;
	float musicVolume = 100.f;
};
