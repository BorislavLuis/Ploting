#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H
#include "../imgui.h"
#include "../implot.h"
#include "../implot_internal.h"
#include "../imguidatechooser.h"
#include <string>

template <typename T>
inline T RandomRange(T min, T max) {
	T scale = rand() / (T)RAND_MAX;
	return min + scale * (max - min);
}

ImVec4 RandomColor();
struct MyDndItem {
	int              Idx;
	int              Plt;
	ImAxis           Yax;
	char             Label[16];
	ImVector<ImVec2> Data;
	ImVec4           Color;
	MyDndItem();
	ImVec2 LoadData(std::string filename);
	void Reset();
};

class PlotWindow
{
public:
	PlotWindow();
	void BeginWindow();
	void Show();

private:
	const int k_dnd = 20;
	MyDndItem  dnd[20];
	MyDndItem* dndx = NULL; // for plot 2
	MyDndItem* dndy = NULL;
};

#endif

