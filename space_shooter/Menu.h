#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include"Button.h"
#include "IU.h"
#include <SFML/Audio.hpp>
using namespace sf;



bool is_music_on = 1, mode = 0;


void menu(RenderWindow& window, int x_window, int y_window) {
	Image logo_image, buttons_image;
	logo_image.loadFromFile("images/logo1.png");
	buttons_image.loadFromFile("images/assets.png");

	Texture logo_texture;
	logo_texture.loadFromImage(logo_image);

	Button play_button(buttons_image, Vector2f(x_window/2, y_window/2), IntRect(125, 0, 12, 13)),
		music_button(buttons_image,Vector2f(0,0),IntRect(88,14,12,13)),
		mode_button(buttons_image,Vector2f(0,0),IntRect(0,64,16,16));
	
	play_button.set_origin(play_button.Get_sprite().getLocalBounds().width / 2, play_button.Get_sprite().getLocalBounds().height / 2);
	play_button.set_scale(10, 10);
	play_button.Set_position(Vector2f(x_window/2, y_window/2));
	music_button.set_origin(music_button.Get_sprite().getLocalBounds().width / 2, music_button.Get_sprite().getLocalBounds().height / 2);
	music_button.set_scale(5, 5);
	music_button.Set_position(Vector2f((x_window / 2 - play_button.Get_sprite().getGlobalBounds().width / 2) + music_button.Get_sprite().getGlobalBounds().width / 2, y_window / 2 + play_button.Get_sprite().getGlobalBounds().height / 2 + 50));
	mode_button.set_origin(mode_button.Get_sprite().getLocalBounds().width / 2, mode_button.Get_sprite().getLocalBounds().height / 2);
	mode_button.set_scale(3.75, 3.75);
	mode_button.Set_position(Vector2f(music_button.Get_sprite().getPosition().x + music_button.Get_sprite().getGlobalBounds().width, music_button.Get_sprite().getPosition().y ));
	mode_button.Set_color(Color::Green);


	Background backGrount("SpaceShooterAssetPack_BackGrounds.png");
	Sprite logo_sprite(logo_texture);
	

	logo_sprite.setOrigin(900 / 2, 389 / 2);
	logo_sprite.setScale(0.25, 0.25);
	logo_sprite.setPosition(x_window / 2, 60);
	

	

	bool isMenu = 1;

	while (isMenu)
	{
		Event menu_event;
		Vector2i mouse_position = Mouse::getPosition(window);
		while (window.pollEvent(menu_event))
		{
			if (menu_event.type == Event::Closed)
			{
				window.close();
				isMenu = false;
			}

			if (menu_event.type == Event::MouseButtonPressed)
			{

				if (menu_event.key.code == Mouse::Left)
				{
					if (play_button.Get_sprite().getGlobalBounds().contains(mouse_position.x, mouse_position.y)) {
						cout << "clicked\n";
						isMenu = false;
					}
					else if (music_button.Get_sprite().getGlobalBounds().contains(mouse_position.x, mouse_position.y)) {
						cout << "clicked\n";
						is_music_on = !is_music_on;

					}

					else if (mode_button.Get_sprite().getGlobalBounds().contains(mouse_position.x, mouse_position.y)) {
						cout << "clicked\n";
						mode = !mode;

					}
				}
			}

		}

		if (play_button.Get_sprite().getGlobalBounds().contains(mouse_position.x, mouse_position.y))
		{
			play_button.Set_TextureRect(IntRect(137, 0, 12, 13));
		}
		else {
			play_button.Set_TextureRect(IntRect(125, 0, 12, 13));
		}

		if (!is_music_on)
		{
			music_button.Set_TextureRect(IntRect(100, 14, 12, 13));
		}
		else {
			music_button.Set_TextureRect(IntRect(88, 14, 12, 13));
		}

		if (!mode)
		{
			mode_button.Set_color(Color::Green);
		}
		else {
			mode_button.Set_color(Color::Red);
		}



		backGrount.Draw_background();
		window.draw(logo_sprite);
		window.draw(play_button.Get_sprite());
		window.draw(music_button.Get_sprite());
		window.draw(mode_button.Get_sprite());
		window.display();
	}

}



bool startGame() {
	menu(window, x_window, y_window);

	//задний фон
	Background BackGround("SpaceShooterAssetPack_BackGrounds.png");
	//игрок
	Image player1_image;
	player1_image.loadFromFile("images/SpaceShooterAssetPack_Ships.png");
	Player player1(player1_image, "player", 13, 13, 10, 13, x_window / 2, y_window - 26, 3);
	Clock player_clock;
	//enemy
	Image enemy_image;
	enemy_image.loadFromFile("images/SpaceShooterAssetPack_Ships.png");
	vector <Entity*> entities;
	//hearts
	Heart heart("heart.gif", 96, 32);
	//монетки за убийство врагов
	Font font;
	font.loadFromFile("fonts/GangSmallYuxian.ttf");
	Text coins("", font, 20);
	coins.setPosition(10, 30);
	coins.setFillColor(Color::Yellow);

	int coin_to_boss;


	//win and kill texts
	Game_texts kill_screen(40, "Game over!");
	kill_screen.setFillColor(255, 0, 0);
	Game_texts win_screen(40, "You win!");
	win_screen.setFillColor(255, 255, 0);
	//pause button
	Image image_button;
	image_button.loadFromFile("images/first.png");
	Button button(image_button, Vector2f(254 - 25, 5), IntRect(162, 0, 12, 13));
	bool pause = 0;
	//restart button
	Image restart_button_image;
	restart_button_image.loadFromFile("images/buttons.png");
	Button restart_button(restart_button_image, Vector2f(x_window / 2, y_window / 2 + 90), IntRect(0, 48, 16, 16));
	restart_button.set_origin(8, 8);
	restart_button.set_scale(5, 5);
	
	//sounds



		game_sounds  shoot("gun_shot.ogg", 25), enemy_sound("Hit_damage.wav", 75);

		Music win_game_music;
		win_game_music.openFromFile("sounds/win_game.wav");
		win_game_music.setVolume(15);

		Music loose_game_music;
		loose_game_music.openFromFile("sounds/game_over_sound.wav");
		loose_game_music.setVolume(15);
		bool music_play = 1;



	//time
	float enemy_time = 0, time_to_spawn_enemy;
	float bullet_time = 0;
	//game over
	bool game_over = 0,boss_spawned=0;

	if (!mode)
	{

		coin_to_boss = 5;
		time_to_spawn_enemy = 1;
		player1.HP = 3;

	}
	else
	{
		coin_to_boss = 50;
		time_to_spawn_enemy = 0.65;
		player1.HP = 1;
	}

	if (!is_music_on)
	{
		win_game_music.setVolume(0);
		loose_game_music.setVolume(0);
		shoot.set_volume(0);
		enemy_sound.set_volume(0);
	}
	while (window.isOpen()) {
		float time = player_clock.getElapsedTime().asMicroseconds();
		enemy_time += player_clock.getElapsedTime().asSeconds();
		bullet_time += player_clock.getElapsedTime().asSeconds();
		player_clock.restart();
		time = time / 800;
		Event event;
		Vector2i mouse_position = Mouse::getPosition(window);




		while (window.pollEvent(event))
		{

			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::W and !game_over and !pause and player1.entity_is_alive)
				{

					entities.push_back(new Bullet(player1_image, "bullet", 101, 2, 4, 4, (float)player1.x_position, player1.entity_sprite.getGlobalBounds().top - 20,1));

					shoot.play_sound();

				}

			}
			if (event.type == Event::MouseButtonPressed)
			{
				if (event.key.code == Mouse::Left)
				{
					if (button.Get_sprite().getGlobalBounds().contains(mouse_position.x, mouse_position.y))
					{
						if (pause == 0) {
							button.Set_TextureRect(IntRect(125, 0, 12, 13));
							pause = !pause;
						}
						else {
							button.Set_TextureRect(IntRect(162, 0, 12, 13));
							pause = !pause;
						}
					}
					if (restart_button.Get_sprite().getGlobalBounds().contains(mouse_position.x, mouse_position.y))
					{
						return true;
					}

				}
			}


		}

		//работает до тех пор пока игрок жив или не набрал ужное количество очков
		if (!game_over and !pause) {
			if (enemy_time > time_to_spawn_enemy and player1.coin<coin_to_boss) {
				entities.push_back(new Enemy(player1_image, "enemy", 82, 2, 6, 5, rand() % (x_window - 20) + 1, -20,1));
				enemy_time = 0;

			}

			if (player1.coin>=coin_to_boss and !boss_spawned)
			{
				entities.clear();
				
				entities.push_back(new Boss(player1_image, "boss", 39, 61, 21, 20, rand() % (x_window - 20) + 1, 60, x_window, 20));
				boss_spawned = 1;
			}
			for (Entity* i : entities)
			{


				for (Entity* j : entities)
				{
					if ((i)->entity_sprite.getGlobalBounds().intersects((j)->entity_sprite.getGlobalBounds()) and i->name!=j->name) {
						


						i->HP -= 1;
						j->HP -= 1;


					}
					
				}
				heart_damage(player1, i, y_window, enemy_sound,game_over);
				i->update(time);
			}
			for (Entity* k : entities)
			{
				if (k->HP<=0)
				{
					k->entity_is_alive = 0;
				}

				if (k->name == "enemy" and !k->entity_is_alive)
				{
					enemy_sound.play_sound();
					player1.coin += 1;
				}
				if (k->name == "boss" and !k->entity_is_alive)
				{
					enemy_sound.play_sound();

					player1.coin += 1000;
					game_over = 1;
				}
			}
			//лампда
			auto newEnd = remove_if(entities.begin(), entities.end(), [](Entity* entity_live) {
				return entity_live->entity_is_alive == 0;
				});



			// Удаляем все элементы, следующие после
			entities.erase(newEnd, entities.end());
			player1.movement(time);
			player1.update(time);


		}
		heart.update(&player1);
		window.clear();
		BackGround.Draw_background();
		for (Entity* i : entities) {
			window.draw((i)->entity_sprite); //рисуем entities объекты (сейчас это только враги)
		}

		window.draw(player1.entity_sprite);
		window.draw(heart.sprite);
		coins.setString("Coins: " + to_string(player1.coin));
		window.draw(coins);
		if (game_over==true) {
			

				if (player1.coin < coin_to_boss)
				{
					if (music_play) {
						loose_game_music.play();
						music_play = !music_play;
					}
			
					kill_screen.Draw_text();
					
				}



				else if (player1.coin >= coin_to_boss) {
					win_screen.Draw_text();
					if (music_play)
					{
						win_game_music.play();
						music_play = !music_play;

					}
				}
			
			window.draw(restart_button.Get_sprite());
		}

		
		window.draw(button.Get_sprite());
		window.display();
	}
}


void gameRunning() {
	if (startGame()) {
		return gameRunning();
	}
}