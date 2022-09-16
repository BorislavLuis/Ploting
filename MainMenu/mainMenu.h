#ifndef MAIN_MENU
#define MAIN_MENU

#include <time.h>
#include "../imgui.h"
#include "../implot.h"
#include "../implot_internal.h"
#include "../imguidatechooser.h"
#include <iostream>
#include <ctime>
#include <string>
class mainMenu
{
public:
	static mainMenu* getInstance();
	void beginWindow();
	void dateChoser();
	void instrumentChoice();
	void settings();
	static void releaseSingletonInstance();
private:
	mainMenu();
	static bool lt0201;
	static bool lt0202;
	static bool lt0203;
	static bool lt0204;
	static bool lt0205;
	static bool lt0206;
	static bool lt0207;
	static bool lt0301;
	static bool lt0302;
	static bool show_status;
	static float f;
	static int counter;
	static int day;
	static int mounth;
	static int year;
	static tm myDate;
	static mainMenu* s_Instance;
	

};


#endif // !MAIN_MENU

