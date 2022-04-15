#include "Entity.h"

void Player::interaction_with_map(int x_window)
{
	if (x_position < 13) x_position = 13;
	if (x_position > x_window - 13) x_position = x_window - 13;
}


void Player::movement(float time) {
	if (entity_is_alive) {
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			dir = 0;
			speed = 0.2;
			entity_sprite.setTextureRect(IntRect(0, 13, 9, 11));
		}
		else if (Keyboard::isKeyPressed(Keyboard::A)) {

			dir = 1;
			speed = 0.2;
			entity_sprite.setTextureRect(IntRect(28, 13, 8, 11));
		}
		else if (Keyboard::isKeyPressed(Keyboard::G)) {
			entity_sprite.setPosition(0, 0);
		}
		else {
			entity_sprite.setTextureRect(IntRect(13, 13, 10, 11));
		}

	}
}

void Player::update(float time) {
	if (entity_is_alive) {
		switch (dir)
		{
		case 0:
			dx = speed;
			break;
		case 1:
			dx = -speed;
			break;
		default:
			dx = 0;
			break;

		}
		x_position += dx * time;
		speed = 0;
		int x_window = 127 * 2;
		interaction_with_map(x_window);
		entity_sprite.setPosition(x_position, 254 * 2 - 26);
	}
}




void Enemy::update(float time) {
	speed = 0.1;
	if (y_position <= 254 * 2 and entity_is_alive) {

		y_position += speed * time;

	}

	entity_sprite.setPosition(x_position, y_position);
}



void Boss::update(float time) {
	speed = 0.1;
	if (x_position > x_window or x_position < 0) {
		speed = -speed;
	}

	x_position += speed * time;
	entity_sprite.setPosition(x_position, y_position);
}


void Bullet::update(float time) {
	speed = -0.2;
	if (y_position > 0 and entity_is_alive) {

		y_position += speed * time;

	}
	else
	{
		entity_is_alive = 0;
	}
	entity_sprite.setPosition(x_position, y_position);
}