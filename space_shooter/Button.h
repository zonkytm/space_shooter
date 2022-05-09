#pragma once
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Button {
	Texture texture;
	Sprite sprite;
public:

	Button(Image& image, Vector2f bPosition, IntRect bSprite) {
		image.createMaskFromColor(Color(255, 255, 255));
		this->texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(bSprite);

		sprite.setPosition(bPosition);
		sprite.setScale(2, 2);

	}
	void set_scale(float x,float y){
		sprite.setScale(x, y);
	}
	void set_origin(int x, int y) {
		sprite.setOrigin(x, y);
	}

	void Set_TextureRect(IntRect rect) {

		sprite.setTextureRect(rect);
	}
	void Set_position(Vector2f position) {
		sprite.setPosition(position);
	}

	Sprite Get_sprite() {
		return sprite;
	}
	void Set_color(Color color) {
		sprite.setColor(color);
	}
};