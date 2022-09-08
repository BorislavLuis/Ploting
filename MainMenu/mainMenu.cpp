#include "mainMenu.h"
mainMenu* mainMenu::s_Instance = nullptr;
float mainMenu::f = 0.0f;
int mainMenu::counter = 0;
int mainMenu::day = 0;
int mainMenu::mounth = 0;
int mainMenu::year = 0;
tm mainMenu::myDate = {};

mainMenu::mainMenu()
{
}

mainMenu* mainMenu::getInstance()
{
	return s_Instance = (s_Instance != nullptr) ? s_Instance : new mainMenu();
}

void mainMenu::beginWindow()
{
	ImGui::Begin(u8"Главно меню");
		dateChoser();
		instrumentChoice();
		settings();
	ImGui::End();
}

void mainMenu::dateChoser()
{
}

void mainMenu::instrumentChoice()
{
}

void mainMenu::settings()
{
}
