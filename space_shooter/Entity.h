#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace std;
using namespace sf;



class Entity {
public:
	string file;
	int x, y, dir,x_sprite,y_sprite;
	float speed, dx, dy,x_position,y_position;
	bool entity_is_alive;
	String name;
	Texture entity_texture;
	Sprite entity_sprite;
	Entity(Image & entity_image,string name, int x, int y, int x_sprite, int y_sprite, float x_position, float y_position) {
		this->x_position = x_position;
		this->y_position = y_position;
		this->name = name;
		entity_image.createMaskFromColor(Color(255, 255, 255));
		entity_texture.loadFromImage(entity_image);
		entity_sprite.setTexture(entity_texture);
		entity_sprite.setTextureRect(IntRect(x,y,x_sprite,y_sprite));
		entity_sprite.setPosition(x_position, y_position);
		this->entity_is_alive = 1;
		entity_sprite.setScale(2, 2);
		entity_sprite.setOrigin((float)x_sprite/2, (float)y_sprite/2);
	}
	FloatRect getRect() {
		return FloatRect(x_position, y_position, x_sprite, y_sprite);
	}
	virtual void update(float time) = 0;
};



class Player: public Entity {
public:
	int HP;
	int coin=0;
	Player(Image &player_image,string name, int x, int y, int x_spite, int y_sprite, float x_position, float y_position, int HP):Entity(player_image,name,x,y, x_spite, y_sprite,x_position,y_position) {

		this->HP = HP;
	}
	void update(float time) override;
	void interaction_with_map(int x_window);

	void movement(float time);

};


class Enemy : public Entity {
public:
	Enemy(Image& player_image,string name, int x, int y, int x_sprite, int y_sprite, float x_position, float y_position) :Entity(player_image,name, x, y, x_sprite, y_sprite, x_position, y_position) {

	}
	void update(float time) override;

};




class Boss :public Entity {
	int x_window;
	int HP;
public:
	Boss(Image& player_image, string name, int x, int y, int x_sprite, int y_sprite, float x_position, float y_position,int x_window,int HP) :Entity(player_image, name, x, y, x_sprite, y_sprite, x_position, y_position) {
		this->x_window = x_window;
		this->HP = HP;
	}
	void update(float time) override;

};



class Bullet : public Entity {
public:
	Bullet(Image& player_image,string name, int x, int y, int x_sprite, int y_sprite, float x_position, float y_position) :Entity(player_image,name, x, y, x_sprite, y_sprite, x_position, y_position) {
		player_image.createMaskFromColor(Color(0, 0, 0));
		entity_sprite.setScale(4, 4);
	}

	void update(float time);

};






