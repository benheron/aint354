#include "MainMenuState.h"
#include "../Utility.h"

MainMenuState::MainMenuState(StateManager* manager, Platform *platform)
	: State(manager, platform)
{
	stateName = "MainMenuState";
}

MainMenuState::~MainMenuState()
{

}

bool MainMenuState::eventHandler()
{
	return false;
}

void MainMenuState::update(float dt)
{
	
}

void MainMenuState::render()
{
	
}

void MainMenuState::load()
{

}

void MainMenuState::unload()
{
	
}