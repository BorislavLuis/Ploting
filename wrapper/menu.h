#ifndef MENU_H
#define MENU_H
#include "../imgui.h"

class MainScreen
{
public:
	MainScreen()
	{
		if (ImGui::CollapsingHeader("Open file"))
		{
			ImGui::Text("Proba");
		}
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		static ImS8  data[10] = { 1,2,3,4,5,6,7,8,9,10 };
		if (ImPlot::BeginPlot("Bar Plot")) {
			ImPlot::PlotBars("Vertical", data, 10, 0.7, 1);
			ImPlot::PlotBars("Horizontal", data, 10, 0.4, 1, ImPlotBarsFlags_Horizontal);
			ImPlot::EndPlot();
		}
		ImGui::Separator();
		ImGui::Separator();
		ImGui::Separator();
		ImGui::Separator();
		ImGui::Separator();
		ImGui::Separator();

		if (ImPlot::BeginPlot("Preview")) {
			static double now = (double)time(0);
			ImPlot::SetupAxisScale(ImAxis_X1, ImPlotScale_Time);
			ImPlot::SetupAxisLimits(ImAxis_X1, now, now + 24 * 3600);
			for (int i = 0; i < 10; ++i) {
				double x[2] = { now, now + 24 * 3600 };
				double y[2] = { 0,i / 9.0 };
				ImGui::PushID(i);
				ImPlot::PlotLine("##Line", x, y, 2);
				ImGui::PopID();
			}
			ImPlot::EndPlot();
		}
	};


private:
};


#endif // !MENU_H
