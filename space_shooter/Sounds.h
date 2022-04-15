#pragma once



class game_sounds {

	SoundBuffer game_buffer;
	Sound game_sound;
public:
	game_sounds(string file, float volume) {
		game_buffer.loadFromFile("sounds/"+ file);
		game_sound.setBuffer(game_buffer);
		game_sound.setVolume(volume);

		
	}
	void play_sound() {
		game_sound.play();
	}
	void set_volume(int volume) {
		game_sound.setVolume(volume);
	}
};
