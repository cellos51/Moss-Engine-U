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

std::map<int, bool> joyMap1;

std::map<int, bool> joyDownMap1;

std::map<int, bool> joyMap2;

std::map<int, bool> joyDownMap2;

Vector2 StickState1;

Vector2 StickState2;

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

	for (auto & element : joyDownMap1)
	{
		element.second = false;
	}

	for (auto & element : joyDownMap2)
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
				if (event.jbutton.which == 0)
				{
					joyMap1[event.jbutton.button] = true;
					joyDownMap1[event.jbutton.button] = true;
				}
				else if (event.jbutton.which == 1)
				{
					joyMap2[event.jbutton.button] = true;
					joyDownMap2[event.jbutton.button] = true;
				}
				
			}
			break;
			case SDL_JOYBUTTONUP:
			{
				if (event.jbutton.which == 0)
				{
					joyMap1[event.jbutton.button] = false;
					joyDownMap1[event.jbutton.button] = false;
				}
				else if (event.jbutton.which == 1)
				{
					joyMap2[event.jbutton.button] = false;
					joyDownMap2[event.jbutton.button] = false;
				}
			}
			case SDL_JOYAXISMOTION:
			{
				if (event.jbutton.which == 0)
				{
					if( event.jaxis.axis == 0 )
					{
                                //Left of dead zone
						if( event.jaxis.value < -8000 )
						{
							StickState1.x = -1;
						}
                                //Right of dead zone
						else if( event.jaxis.value > 8000 )
						{
							StickState1.x =  1;
						}
						else
						{
							StickState1.x = 0;
						}
					}
					else if( event.jaxis.axis == 1 )
					{
                                //Below of dead zone
						if( event.jaxis.value < -8000 )
						{
							StickState1.y = -1;
						}
                                //Above of dead zone
						else if( event.jaxis.value > 8000 )
						{
							StickState1.y =  1;
						}
						else
						{
							StickState1.y = 0;
						}
					}
				}
				else if (event.jbutton.which == 1)
				{
					if( event.jaxis.axis == 0 )
					{
                                //Left of dead zone
						if( event.jaxis.value < -8000 )
						{
							StickState2.x = -1;
						}
                                //Right of dead zone
						else if( event.jaxis.value > 8000 )
						{
							StickState2.x =  1;
						}
						else
						{
							StickState2.x = 0;
						}
					}
					else if( event.jaxis.axis == 1 )
					{
                                //Below of dead zone
						if( event.jaxis.value < -8000 )
						{
							StickState2.y = -1;
						}
                                //Above of dead zone
						else if( event.jaxis.value > 8000 )
						{
							StickState2.y =  1;
						}
						else
						{
							StickState2.y = 0;
						}
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

bool Event::JoyPressed(int i, int player)
{
	if (player == 1)
	{
		return joyMap1.find(i)->second;
	}
	else if (player == 2)
	{
		return joyMap2.find(i)->second;
	}

	return false;
}

bool Event::JoyDown(int i, int player)
{
	if (player == 1)
	{
		return joyDownMap1.find(i)->second;
	}
	else if (player == 2)
	{
		return joyDownMap2.find(i)->second;
	}

	return false;
}

Vector2 Event::StickPosition(int player)
{
	if (player == 1)
	{
		return StickState1;
	}
	else if (player == 2)
	{
		return StickState2;
	}

	return Vector2(0,0);
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