#ifndef MAIN_MENU
#define MAIN_MENU

#include <time.h>
#include "../imgui.h"
#include "../implot.h"
#include "../implot_internal.h"
class mainMenu
{
public:
	static mainMenu* getInstance();
	void beginWindow();
	void dateChoser();
	void instrumentChoice();
	void settings();

private:
	mainMenu();
	static float f;
	static int counter;
	static int day;
	static int mounth;
	static int year;
	static tm myDate;
	static mainMenu* s_Instance;
};



#endif // !MAIN_MENU

