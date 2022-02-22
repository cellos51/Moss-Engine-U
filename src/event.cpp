#include "event.hpp"

#include <SDL2/SDL.h>
#include <map>
#include <string>
#include <iostream>


bool quit = false;

std::map<int, bool> mouseMap;

std::map<int, bool> mouseDownMap;

std::map<int, bool> keyMap;

std::map<int, bool> keyDownMap;

std::map<int, bool> joyMap;

std::map<int, bool> joyDownMap;

Vector2 StickState;

//bool isTextInput = false;

std::string text;

void Event::PollEvent()
{
	for (auto & element : keyDownMap)
	{
		element.second = false;
	}

	for (auto & element : mouseDownMap)
	{
		element.second = false;
	}

	for (auto & element : joyDownMap)
	{
		element.second = false;
	}

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type) 
		{
			case SDL_QUIT: 
			quit = true;
			break;
			case SDL_MOUSEBUTTONDOWN:
			{
				mouseMap[event.button.button] = true;
				mouseDownMap[event.button.button] = true;
			}
			break;
			case SDL_MOUSEBUTTONUP:
			{
				mouseMap[event.button.button] = false;
				mouseDownMap[event.button.button] = false;
			}
			break;
			case SDL_KEYDOWN:
			{
				if (event.key.repeat == 0)
				{
					keyMap[event.key.keysym.sym] = true;
					keyDownMap[event.key.keysym.sym] = true;
				}

				// if( event.key.keysym.sym == SDLK_BACKSPACE && text.length() > 0 && isTextInput == true ) //Handle backspace
				// {               
				// 	text.pop_back(); //lop off character
				// }

				// else if( event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL && isTextInput == true ) //Handle paste
				// {
				// 	text += SDL_GetClipboardText();
				// }
			}
			break;
			case SDL_KEYUP:
			{
				if (event.key.repeat == 0)
				{
					keyMap[event.key.keysym.sym] = false;
					keyDownMap[event.key.keysym.sym] = false;
				}
			}
			break;
			case SDL_JOYBUTTONDOWN:
			{
				joyMap[event.jbutton.button] = true;
				joyDownMap[event.jbutton.button] = true;
			}
			break;
			case SDL_JOYBUTTONUP:
			{
				joyMap[event.jbutton.button] = false;
				joyDownMap[event.jbutton.button] = false;
			}
			case SDL_JOYAXISMOTION:
			{
				if( event.jaxis.axis == 0 )
				{
                                //Left of dead zone
					if( event.jaxis.value < -8000 )
					{
						StickState.x = -1;
					}
                                //Right of dead zone
					else if( event.jaxis.value > 8000 )
					{
						StickState.x =  1;
					}
					else
					{
						StickState.x = 0;
					}
				}
				else if( event.jaxis.axis == 1 )
				{
                                //Below of dead zone
					if( event.jaxis.value < -8000 )
					{
						StickState.y = -1;
					}
                                //Above of dead zone
					else if( event.jaxis.value > 8000 )
					{
						StickState.y =  1;
					}
					else
					{
						StickState.y = 0;
					}
				}
			}
			break;
			// case SDL_TEXTINPUT: 
			// text += event.text.text; /* Add new text onto the end of our text */
			// std::cout << event.text.text;
			// break;
			// case SDL_TEXTEDITING:
			// std::cout << event.edit.text;   
			// text += event.edit.text;
			// break;
		}
	}
}

bool Event::AppQuit()
{
	if (quit)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Event::MousePressed(int i)
{
	return mouseMap.find(i)->second;
}

bool Event::MouseDown(int i)
{
	return mouseDownMap.find(i)->second;
}

bool Event::KeyPressed(int i)
{
	return keyMap.find(i)->second; 
}

bool Event::KeyDown(int i)
{
	return keyDownMap.find(i)->second; 
}

bool Event::JoyPressed(int i)
{
	return joyMap.find(i)->second;
}

bool Event::JoyDown(int i)
{
	return joyDownMap.find(i)->second;
}

Vector2 Event::StickPosition()
{
	return StickState;
}
// bool Event::TextInputEnabled(bool i)
// {
// 	isTextInput = i;
// 	if (i == true)
// 	{
// 		SDL_StartTextInput();
// 	}
// 	else
// 	{
// 		SDL_StopTextInput();
// 	}
// 	return isTextInput;
// }

// bool Event::TextInputEnabled()
// {
// 	return isTextInput;
// }

// std::string Event::GetInputText()
// {
// 	return text;
// }

// void Event::SetInputText(std::string i)
// {
// 	text = i;
// 	return;
// }