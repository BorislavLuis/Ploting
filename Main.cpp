
#define _CRT_SECURE_NO_WARNINGS


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "implot.h"
#include "implot_internal.h"
#include "imguidatechooser.h"
#include <iostream>
#include <ctime>
#include <string>

static int scrWidth = 1920;
static int scrHeight = 1080;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double dx, double dy);
void processInput(GLFWwindow* window);
static float xs1[1001], ys1[1001];
static double xs2[20], ys2[20];
static bool opn = true;
template <typename T>
inline T RandomRange(T min, T max) {
	T scale = rand() / (T)RAND_MAX;
	return min + scale * (max - min);
}
ImVec4 RandomColor() {
	ImVec4 col;
	col.x = RandomRange(0.0f, 1.0f);
	col.y = RandomRange(0.0f, 1.0f);
	col.z = RandomRange(0.0f, 1.0f);
	col.w = 1.0f;
	return col;
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(scrWidth, scrHeight, "ImGuiPlot", NULL, NULL);
	if (!window)
	{
		std::cout << "Window problem" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "GLAD problem" << std::endl;
		return -1;
	}

	glViewport(0, 0, 1024, 768);
	const char* glsl_version = "#version 130";

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImPlot::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
	//io.ConfigViewportsNoAutoMerge = true;
	//io.ConfigViewportsNoTaskBarIcon = true;
	io.Fonts->AddFontFromFileTTF("Furore.otf", 18, NULL, io.Fonts->GetGlyphRangesCyrillic());
	io.Fonts->AddFontFromFileTTF("Wizland.ttf", 18, NULL, io.Fonts->GetGlyphRangesCyrillic());
	io.Fonts->AddFontFromFileTTF("Jazz_Ball_Bold.ttf", 18, NULL, io.Fonts->GetGlyphRangesCyrillic());
	io.Fonts->AddFontFromFileTTF("Jazz_Ball_Regular.ttf", 18, NULL, io.Fonts->GetGlyphRangesCyrillic());
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);


	bool show_demo_window = true;
	bool show_another_window = false;
	bool show_status = false;
	ImVec4 clear_color = ImVec4(0.2f, 0.7f, 0.4f, 1.0f);
	
	bool lt0201 = false;
	bool lt0202 = false;
	bool lt0203 = false;
	bool lt0204 = false;
	bool lt0205 = false;
	bool lt0206 = false;
	bool lt0207 = false;
	bool lt0301 = false;
	bool lt0302 = false;
	bool open = true;
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		processInput(window);
		static ImS8  data[10] = { 1,2,3,4,5,6,7,8,9,10 };
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::DockSpaceOverViewport(NULL, 0);
		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		//if (show_demo_window)
			//ImGui::ShowDemoWindow(&show_demo_window);

		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
		{
			static float f = 0.0f;
			static int counter = 0;
			static int day = 0;
			static int mounth = 0;
			static int year = 0;
			static tm myDate = {};
			//io.Fonts->GetGlyphRangesCyrillic();
			ImGui::Begin(u8"Главно меню");  
			if (ImGui::CollapsingHeader(u8"Избор на дата"))
			{
				if (ImGui::DateChooser(u8"Дата", myDate, "%d/%m/%Y"))
				{
					show_status = true;
				}
				if (show_status)
				{
					std::cout << "Here" << std::endl;
					ImGui::Begin(u8"ден");
					std::string str = std::to_string(myDate.tm_mday);
					ImGui::Text(str.c_str());
					ImGui::End();
				}
			}
			
			if (ImGui::CollapsingHeader(u8"Избор на измервателен уред"))
			{
				ImGui::Separator();
				ImGui::Checkbox("LT0201", &lt0201);
				ImGui::SameLine(120);
				ImGui::Checkbox("LT0202", &lt0202);
				ImGui::SameLine(240);
				ImGui::Checkbox("LT0203", &lt0203);
				ImGui::SameLine(360);
				ImGui::Checkbox("LT0204", &lt0204);
				ImGui::Separator();
				ImGui::Checkbox("LT0205", &lt0205);
				ImGui::SameLine(120);
				ImGui::Checkbox("LT0206", &lt0206);
				ImGui::SameLine(240);
				ImGui::Checkbox("LT0207", &lt0207);
				ImGui::SameLine(360);
				ImGui::Checkbox("LT0301", &lt0301);
			}


			if (ImGui::CollapsingHeader(u8"Настройки"))
			{
				ImGui::ShowFontSelector(u8"Фонт");
				ImGui::ShowStyleSelector(u8"Стил на интерфейса");
				ImGuiStyle stl = ImGui::GetStyle();
				//std::cout << stl.Colors->x << std::endl;
				ImPlot::ShowStyleSelector(u8"Стил на плотера");
				ImPlot::ShowColormapSelector(u8"Цвят на плотера");
				ImGui::Separator();
				ImGui::Checkbox(u8"Изполвай местно време", &ImPlot::GetStyle().UseLocalTime);
				ImGui::Checkbox(u8"Използвай ISO 8601", &ImPlot::GetStyle().UseISO8601);
				ImGui::Checkbox(u8"Изполвай 24 часов часовник", &ImPlot::GetStyle().Use24HourClock);
				ImGui::Separator();
			}
			ImGui::End();
		}


		// 3. Show another simple window.
		if (show_another_window)
		{
			ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
			ImGui::Text("Hello from another window!");
			if (ImGui::Button("Close Me"))
				show_another_window = false;
			ImGui::End();
		}

		ImGui::Begin("Second window");
		if (lt0201)
		{

			static double xs1[101], ys1[101], ys2[101], ys3[101];
			srand(0);
			for (int i = 0; i < 101; ++i) {
				xs1[i] = (float)i;
				ys1[i] = RandomRange(400.0, 450.0);
				ys2[i] = RandomRange(275.0, 350.0);
				ys3[i] = RandomRange(150.0, 225.0);
			}
			static bool show_lines = true;
			static bool show_fills = true;
			static float fill_ref = 0;
			static int shade_mode = 0;
			ImGui::Checkbox("Lines", &show_lines); ImGui::SameLine();
			ImGui::Checkbox("Fills", &show_fills);
			if (show_fills) {
				ImGui::SameLine();
				if (ImGui::RadioButton("To -INF", shade_mode == 0))
					shade_mode = 0;
				ImGui::SameLine();
				if (ImGui::RadioButton("To +INF", shade_mode == 1))
					shade_mode = 1;
				ImGui::SameLine();
				if (ImGui::RadioButton("To Ref", shade_mode == 2))
					shade_mode = 2;
				if (shade_mode == 2) {
					ImGui::SameLine();
					ImGui::SetNextItemWidth(100);
					ImGui::DragFloat("##Ref", &fill_ref, 1, -100, 500);
				}
			}

			if (ImPlot::BeginPlot("Stock Prices")) {
				ImPlot::SetupAxes("Days", "Price");
				ImPlot::SetupAxesLimits(0, 100, 0, 500);
				if (show_fills) {
					ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 0.25f);
					ImPlot::PlotShaded("Stock 1", xs1, ys1, 101, shade_mode == 0 ? -INFINITY : shade_mode == 1 ? INFINITY : fill_ref);
					ImPlot::PlotShaded("Stock 2", xs1, ys2, 101, shade_mode == 0 ? -INFINITY : shade_mode == 1 ? INFINITY : fill_ref);
					ImPlot::PlotShaded("Stock 3", xs1, ys3, 101, shade_mode == 0 ? -INFINITY : shade_mode == 1 ? INFINITY : fill_ref);
					ImPlot::PopStyleVar();
				}
				if (show_lines) {
					ImPlot::PlotLine("Stock 1", xs1, ys1, 101);
					ImPlot::PlotLine("Stock 2", xs1, ys2, 101);
					ImPlot::PlotLine("Stock 3", xs1, ys3, 101);
				}
				ImPlot::EndPlot();
			}
		}



		ImGui::Text("Test window");
			ImGui::Button("Open");
			ImGui::Separator();
			if (lt0202)
			{
				static double xs1[101], ys1[101], ys2[101], ys3[101];
				srand(0);
				for (int i = 0; i < 101; ++i) {
					xs1[i] = (float)i;
					ys1[i] = RandomRange(400.0, 450.0);
					ys2[i] = RandomRange(275.0, 350.0);
					ys3[i] = RandomRange(150.0, 225.0);
				}
				static bool show_lines = true;
				static bool show_fills = true;
				static float fill_ref = 0;
				static int shade_mode = 0;
				ImGui::Checkbox("Lines", &show_lines); ImGui::SameLine();
				ImGui::Checkbox("Fills", &show_fills);
				if (show_fills) {
					ImGui::SameLine();
					if (ImGui::RadioButton("To -INF", shade_mode == 0))
						shade_mode = 0;
					ImGui::SameLine();
					if (ImGui::RadioButton("To +INF", shade_mode == 1))
						shade_mode = 1;
					ImGui::SameLine();
					if (ImGui::RadioButton("To Ref", shade_mode == 2))
						shade_mode = 2;
					if (shade_mode == 2) {
						ImGui::SameLine();
						ImGui::SetNextItemWidth(100);
						ImGui::DragFloat("##Ref", &fill_ref, 1, -100, 500);
					}
				}

				if (ImPlot::BeginPlot("Stock Prices")) {
					ImPlot::SetupAxes("Days", "Price");
					ImPlot::SetupAxesLimits(0, 100, 0, 500);
					if (show_fills) {
						ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 0.25f);
						ImPlot::PlotShaded("Stock 1", xs1, ys1, 101, shade_mode == 0 ? -INFINITY : shade_mode == 1 ? INFINITY : fill_ref);
						ImPlot::PlotShaded("Stock 2", xs1, ys2, 101, shade_mode == 0 ? -INFINITY : shade_mode == 1 ? INFINITY : fill_ref);
						ImPlot::PlotShaded("Stock 3", xs1, ys3, 101, shade_mode == 0 ? -INFINITY : shade_mode == 1 ? INFINITY : fill_ref);
						ImPlot::PopStyleVar();
					}
					if (show_lines) {
						ImPlot::PlotLine("Stock 1", xs1, ys1, 101);
						ImPlot::PlotLine("Stock 2", xs1, ys2, 101);
						ImPlot::PlotLine("Stock 3", xs1, ys3, 101);
					}
					ImPlot::EndPlot();
				}
			}


			ImGui::BulletText("Drag/drop items from the left column.");
			ImGui::BulletText("Drag/drop items between plots.");
			ImGui::Indent();
			ImGui::BulletText("Plot 1 Targets: Plot, Y-Axes, Legend");
			ImGui::BulletText("Plot 1 Sources: Legend Item Labels");
			ImGui::BulletText("Plot 2 Targets: Plot, X-Axis, Y-Axis");
			ImGui::BulletText("Plot 2 Sources: Plot, X-Axis, Y-Axis (hold Ctrl)");
			ImGui::Unindent();

			// convenience struct to manage DND items; do this however you like
			struct MyDndItem {
				int              Idx;
				int              Plt;
				ImAxis           Yax;
				char             Label[16];
				ImVector<ImVec2> Data;
				ImVec4           Color;
				MyDndItem() {
					static int i = 0;
					Idx = i++;
					Plt = 0;
					Yax = ImAxis_Y1;
					sprintf(Label, "%02d Hz", Idx + 1);
					Color = RandomColor();
					Data.reserve(1001);
					for (int k = 0; k < 1001; ++k) {
						float t = k * 1.0f / 999;
						Data.push_back(ImVec2(t, 0.5f + 0.5f * sinf(2 * 3.14f * t * (Idx + 1))));
					}
				}
				void Reset() { Plt = 0; Yax = ImAxis_Y1; }
			};

			const int         k_dnd = 20;
			static MyDndItem  dnd[k_dnd];
			static MyDndItem* dndx = NULL; // for plot 2
			static MyDndItem* dndy = NULL; // for plot 2

			// child window to serve as initial source for our DND items
			ImGui::BeginChild("DND_LEFT", ImVec2(100, 600));
			if (ImGui::Button("Reset Data")) {
				for (int k = 0; k < k_dnd; ++k)
					dnd[k].Reset();
				dndx = dndy = NULL;
			}
			for (int k = 0; k < k_dnd; ++k) {
				if (dnd[k].Plt > 0)
					continue;
				ImPlot::ItemIcon(dnd[k].Color); ImGui::SameLine();
				ImGui::Selectable(dnd[k].Label, false, 0, ImVec2(100, 0));
				if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
					ImGui::SetDragDropPayload("MY_DND", &k, sizeof(int));
					ImPlot::ItemIcon(dnd[k].Color); ImGui::SameLine();
					ImGui::TextUnformatted(dnd[k].Label);
					ImGui::EndDragDropSource();
				}
			}
			ImGui::EndChild();
			if (ImGui::BeginDragDropTarget()) {
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("MY_DND")) {
					int i = *(int*)payload->Data; dnd[i].Reset();
				}
				ImGui::EndDragDropTarget();
			}

			ImGui::SameLine();
			ImGui::BeginChild("DND_RIGHT", ImVec2(-1, 400));
			// plot 1 (time series)
			ImPlotAxisFlags flags = ImPlotAxisFlags_NoTickLabels | ImPlotAxisFlags_NoGridLines | ImPlotAxisFlags_NoHighlight;
			if (ImPlot::BeginPlot("##DND1", ImVec2(-1, 395))) {
				ImPlot::SetupAxis(ImAxis_X1, NULL, flags | ImPlotAxisFlags_Lock);
				ImPlot::SetupAxis(ImAxis_Y1, "[drop here]", flags);
				ImPlot::SetupAxis(ImAxis_Y2, "[drop here]", flags | ImPlotAxisFlags_Opposite);
				ImPlot::SetupAxis(ImAxis_Y3, "[drop here]", flags | ImPlotAxisFlags_Opposite);

				for (int k = 0; k < k_dnd; ++k) {
					if (dnd[k].Plt == 1 && dnd[k].Data.size() > 0) {
						ImPlot::SetAxis(dnd[k].Yax);
						ImPlot::SetNextLineStyle(dnd[k].Color);
						ImPlot::PlotLine(dnd[k].Label, &dnd[k].Data[0].x, &dnd[k].Data[0].y, dnd[k].Data.size(), 0, 0, 2 * sizeof(float));
						// allow legend item labels to be DND sources
						if (ImPlot::BeginDragDropSourceItem(dnd[k].Label)) {
							ImGui::SetDragDropPayload("MY_DND", &k, sizeof(int));
							ImPlot::ItemIcon(dnd[k].Color); ImGui::SameLine();
							ImGui::TextUnformatted(dnd[k].Label);
							ImPlot::EndDragDropSource();
						}
					}
				}
				// allow the main plot area to be a DND target
				if (ImPlot::BeginDragDropTargetPlot()) {
					if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("MY_DND")) {
						int i = *(int*)payload->Data; dnd[i].Plt = 1; dnd[i].Yax = ImAxis_Y1;
					}
					ImPlot::EndDragDropTarget();
				}
				// allow each y-axis to be a DND target
				for (int y = ImAxis_Y1; y <= ImAxis_Y3; ++y) {
					if (ImPlot::BeginDragDropTargetAxis(y)) {
						if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("MY_DND")) {
							int i = *(int*)payload->Data; dnd[i].Plt = 1; dnd[i].Yax = y;
						}
						ImPlot::EndDragDropTarget();
					}
				}
				// allow the legend to be a DND target
				if (ImPlot::BeginDragDropTargetLegend()) {
					if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("MY_DND")) {
						int i = *(int*)payload->Data; dnd[i].Plt = 1; dnd[i].Yax = ImAxis_Y1;
					}
					ImPlot::EndDragDropTarget();
				}
				ImPlot::EndPlot();
			}
		
			
			ImGui::EndChild();
		ImGui::End();
		ImGui::ShowDemoWindow(&open);
		ImPlot::ShowDemoWindow(&open);
		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Update and Render additional Platform Windows
		// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
		//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
		
		//ImPlot::ShowDemoWindow(&opn);

	

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	ImPlot::DestroyContext();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();

	return 1;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	scrWidth = width;
	scrHeight = height;
}
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	//cameraPos.y = 0.0f;
}
void mouse_callback(GLFWwindow* window, double dx, double dy)
{

}