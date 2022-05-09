#include "Entity.h"

void Player::interaction_with_map(int x_window)
{
	if (x_position < 13) x_position = 13;
	if (x_position > x_window - 13) x_position = x_window - 13;
}


void Player::movement(float time) {
	speed = 0.2;
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			dir = 0;
			entity_sprite.setTextureRect(IntRect(0, 13, 9, 11));
		}
		else if (Keyboard::isKeyPressed(Keyboard::A)) {

			dir = 1;
			entity_sprite.setTextureRect(IntRect(28, 13, 8, 11));
		}

		else {
			entity_sprite.setTextureRect(IntRect(13, 13, 10, 11));
			speed = 0;
			dir = 3;
		}
}

void Player::update(float time) {

		switch (dir)
		{
		case 0:
			dx = speed;
			break;
		case 1:
			dx = -speed;
			break;
		default:
			dx = speed;
			break;

		}
		x_position += dx * time;
		int x_window = 254;
		interaction_with_map(x_window);
		entity_sprite.setPosition(x_position, 508 - entity_sprite.getGlobalBounds().height/2);

}




void Enemy::update(float time) {
	speed = 0.1;
	if (y_position <= 254 * 2 and entity_is_alive) {

		y_position += speed * time;

	}
	else
	{
		entity_is_alive = 0;
	}
	entity_sprite.setPosition(x_position, y_position);
}



void Boss::update(float time) {
	if (entity_sprite.getPosition().x <= 0 or entity_sprite.getPosition().x >= x_window)
	{
		dir = abs(1 - dir);
	}
	speed = 0.1;
	switch (dir)
	{
	case 0:
		dx = speed;
		break;
	case 1:
		dx = -speed;
		break;

	}
	entity_sprite.move(dx * time, 0);
	
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



void Boss_Bullet::update(float time) {
	speed = 0.2;
	if (y_position <500 and entity_is_alive) {

		y_position += speed * time;

	}
	else
	{
		entity_is_alive = 0;
	}
	entity_sprite.setPosition(x_position, y_position);
}