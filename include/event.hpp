#pragma once

#include <SDL2/SDL.h>
#include <string>

#include "math.hpp"

namespace Event
{
	void PollEvent();
	bool AppQuit();
	bool MousePressed(int i);
	bool MouseDown(int i);
	bool KeyPressed(int i);
	bool KeyDown(int i);
	bool JoyPressed(int i);
	bool JoyDown(int i);
	Vector2 StickPosition();
	//bool TextInputEnabled(bool i);
	//bool TextInputEnabled();
	//std::string GetInputText();
	//void SetInputText(std::string i);
}