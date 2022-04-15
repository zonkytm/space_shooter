#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

const 	int x_window = 254, y_window = 508;
RenderWindow window(sf::VideoMode(x_window, y_window), "Space Shooter 2.5.0 release");


class Background {

Texture Background_texture;
Sprite Background_srite;
Image Background_image;
public:

Background(string File) {
	Background_image.loadFromFile("images/"+ File);
	Background_texture.loadFromImage(Background_image);
	Background_srite.setTexture(Background_texture);
	Background_srite.setTextureRect(IntRect(0, 0, 127, 254));
	Background_srite.setScale(2, 2);
	}


void Draw_background() {
	window.draw(Background_srite);
}

};



class Game_texts {
	Font font;
	Text game_text;
public:
	Game_texts(int font_size,string text) {
		font.loadFromFile("fonts/GangSmallYuxian.ttf");
		game_text.setString(text);
		game_text.setCharacterSize(font_size);
		game_text.setStyle(Text::Bold);
		game_text.setFont(font);
		game_text.setOrigin(game_text.getGlobalBounds().width / 2, game_text.getGlobalBounds().height / 2);
		game_text.setPosition(x_window / 2, y_window / 2);

	}

	void setFillColor(int R, int G, int B) {
		game_text.setFillColor(Color(R, G, B));
	}
	void Draw_text() {
		window.draw(game_text);
	}
};



