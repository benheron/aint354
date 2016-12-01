#include "EditorState.h"
#include "../Utility.h"

EditorState::EditorState(StateManager* manager, Platform *platform)
	: State(manager, platform)
{
	stateName = "EditorState";
}

EditorState::~EditorState()
{

}

bool EditorState::eventHandler()
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	SDL_Event events;
	while (SDL_PollEvent(&events))
	{
		switch (events.type)
		{

		case SDL_MOUSEMOTION:
			//while mouse is moving
			break;

		case SDL_QUIT:
			return true;
			break;

		case SDL_MOUSEBUTTONDOWN:
			switch (events.button.button)
			{
				//while mouse is down


			}
			break;
		case SDL_KEYDOWN:
			switch (events.key.keysym.sym)
			{
				//pressing a key
			case SDLK_ESCAPE:
				//do same as quit
				return true;
				break;
			}
			break;
		case SDL_KEYUP:
			switch (events.key.keysym.sym)
			{
				//letting go of a key
			default:
				Utility::log(Utility::I, Utility::intToString(events.key.keysym.sym));
				break;
			}
			break;
		}
	}
	return false;
}

void EditorState::update(float dt)
{

}

void EditorState::render()
{

}

void EditorState::load()
{

	
}

void EditorState::unload()
{

}