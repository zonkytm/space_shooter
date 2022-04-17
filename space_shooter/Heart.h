#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Sounds.h"
using namespace std;
using namespace sf;


View view;


class Heart {
public:
	int x, y, x_sprite, y_sprite;
	string file;
	Image image;
	Texture texture;
	Sprite sprite;

	Heart(string File, int x_sprite, int y_sprite) {
		this->file = File;

		this->x_sprite = x_sprite;
		this->y_sprite = y_sprite;
		image.loadFromFile("images/" + file);
		image.createMaskFromColor(Color(255, 255, 255));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, x_sprite, y_sprite));
	}

	void update(Player* player) {
		sprite.setPosition(0, 0);
		if (player->HP ==3) sprite.setTextureRect(IntRect(0, 0, 96, 32));
		else if (player->HP ==2) sprite.setTextureRect(IntRect(0, 0, 64, 32));
		else if (player->HP ==1) sprite.setTextureRect(IntRect(0, 0, 32, 32));
		else if (player->HP<=0 ) sprite.setTextureRect(IntRect(0, 0, 0, 0));

	}
};

void heart_damage(Player& player, Entity* enemy, int y_window,game_sounds& enemy_sound,bool& game_over) {


	if (enemy->entity_sprite.getPosition().y >= y_window) {
		
		player.HP -= 1;
		enemy_sound.play_sound();
		player.coin -= 1;
		enemy->HP -= 1;
		cout << "Problem\n";

	}
	if (player.entity_sprite.getGlobalBounds().intersects(enemy->entity_sprite.getGlobalBounds())) {
		enemy->HP -= 1;
		
		player.HP -= 1;
		enemy_sound.play_sound();
	}


	if (player.HP <= 0)
	{
		player.entity_is_alive = 0;
		player.entity_sprite.setColor(Color::Red);
		player.entity_sprite.setTextureRect(IntRect(13, 13, 10, 13));
		game_over = 1;
	}

}
