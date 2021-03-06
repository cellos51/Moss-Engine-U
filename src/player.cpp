#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "entity.hpp"
#include "player.hpp"
#include "event.hpp"

Player::Player(Vector2 p_pos, SDL_Texture* p_tex, Vector2 p_size, int pNum) : Entity(p_pos,p_tex, p_size)
{
	transform = p_pos;
	tex = p_tex;
	size = p_size;
	playerNum = pNum;
	Player::init();
}

void Player::init() // this was the biggest pain in the fucking ass ever
{
	Entity::friction = friction;
	Entity::dragX = dragX;
	Entity::dragY = dragY;
	Entity::gravity = gravity;
	Entity::bounciness = bounciness;

	texturePos.x = 0;
	texturePos.y = 0;
	texturePos.w = size.x;
	texturePos.h = size.y;
	offset.x = 0; //offset is for textures
	offset.y = 0;
	offset.w = size.x;
	offset.h = size.y;
}

void Player::update()
{
	// SDL_GetMouseState(&mouseX, &mouseY);
	if (playerNum == 1)
	{
		if (Event::JoyPressed(SDL_CONTROLLER_BUTTON_DPAD_RIGHT, playerNum) || Event::StickPosition(playerNum).x > 0) // for somereason the controls for the wii u are reversed :P
		{
			velocity.x += 0.0625 * Time::deltaTime();
		}

		else if (Event::JoyPressed(SDL_CONTROLLER_BUTTON_DPAD_DOWN, playerNum) || Event::StickPosition(playerNum).x < 0)
		{
			velocity.x -= 0.0625 * Time::deltaTime();
		}

		if (Event::JoyDown(SDL_CONTROLLER_BUTTON_B, playerNum) && OnGround == true)
		{
			velocity.y = -25;
		}

		if (!Event::JoyPressed(SDL_CONTROLLER_BUTTON_B, playerNum))
		{
			if (velocity.y < 0)
			{
				velocity.y += 0.1875 * Time::deltaTime();
			}
		}
	}
	else if (playerNum == 2)
	{
		if (Event::JoyPressed(SDL_CONTROLLER_BUTTON_MAX, playerNum)) // for somereason the controls for the wii u are reversed :P
		{
			velocity.x += 0.0625 * Time::deltaTime();
		}

		else if (Event::JoyPressed(SDL_CONTROLLER_BUTTON_DPAD_LEFT, playerNum))
		{
			velocity.x -= 0.0625 * Time::deltaTime();
		}

		if (Event::JoyDown(SDL_CONTROLLER_BUTTON_LEFTSTICK, playerNum) && OnGround == true)
		{
			velocity.y = -25;
		}

		if (!Event::JoyPressed(SDL_CONTROLLER_BUTTON_LEFTSTICK, playerNum))
		{
			if (velocity.y < 0)
			{
				velocity.y += 0.1875 * Time::deltaTime();
			}
		}
	}


		OnGround = false;

		Player::physics(phys);
	}