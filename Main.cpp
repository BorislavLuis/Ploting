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
static int scrWidth = 1920;
static int scrHeight = 1080;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double dx, double dy);
void processInput(GLFWwindow* window);
static float xs1[1001], ys1[1001];
static double xs2[20], ys2[20];
static bool opn = true;
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
	ImVec4 clear_color = ImVec4(0.2f, 0.7f, 0.4f, 1.0f);
	
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		processInput(window);

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
			ImGui::Begin("Configuration");  
			ImGui::Text(u8"Избор на дата");
			if (ImGui::DateChooser(u8"Дата", myDate, "%d/%m/%Y"))
			{
				ImGui::Begin(u8"ден");
				char* buf;
				//itoa(myDate.tm_mday, buf, 10);
				//ImGui::Text(buf);
				ImGui::End();
			}

			const char* mounthItems[] = { "1","2","3","4","5","6","7","8","9","10","11","12" };
			const char* dayItems[] = { "1","2","3","4","5","6","7","8","9","10","11","12" };
			const char* yearItems[] = { "2022","2023","2024","2025" ,"2026","2027" ,"2028","2029","2030" };
			ImGui::Combo(u8"Ìåñåö", &mounth, mounthItems, IM_ARRAYSIZE(mounthItems));
			ImGui::Combo(u8"Äåí", &day, dayItems, IM_ARRAYSIZE(dayItems));
			ImGui::Combo(u8"Ãîäèíà", &year, yearItems, IM_ARRAYSIZE(yearItems));
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
			ImGui::ShowFontSelector("Font");
			ImGui::ShowStyleSelector("ImGui Style");
			ImGuiStyle stl = ImGui::GetStyle();
			std::cout << stl.Colors->x << std::endl;
			ImPlot::ShowStyleSelector("ImPlot Style");
			ImPlot::ShowColormapSelector("ImPlot Colormap");
			ImPlot::ShowInputMapSelector("Input Map");
			ImGui::Separator();
			ImGui::Checkbox("Use Local Time", &ImPlot::GetStyle().UseLocalTime);
			ImGui::Checkbox("Use ISO 8601", &ImPlot::GetStyle().UseISO8601);
			ImGui::Checkbox("Use 24 Hour Clock", &ImPlot::GetStyle().Use24HourClock);
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
		ImGui::Text("Test window");
			ImGui::Button("Open");
			ImGui::Separator();
		ImGui::End();


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