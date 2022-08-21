#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "implot.h"
#include "implot_internal.h"
#include <iostream>

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


	GLFWwindow* window = glfwCreateWindow(1024, 768, "ImGuiPlot", NULL, NULL);
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

		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);

		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

			ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
			ImGui::Checkbox("Another Window", &show_another_window);

			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
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
		static float xs[1001], xs2[1001], ys1[1001], ys2[1001], ys3[1001];
		for (int i = 0; i < 1001; ++i) {
			xs[i] = (i * 0.1f);
			xs2[i] = xs[i] + 10.0f;
			ys1[i] = sinf(xs[i]) * 3 + 1;
			ys2[i] = cosf(xs[i]) * 0.2f + 0.5f;
			ys3[i] = sinf(xs[i] + 0.5f) * 100 + 200;
		}

		static bool x2_axis = true;
		static bool y2_axis = true;
		static bool y3_axis = true;

		ImGui::Checkbox("X-Axis 2", &x2_axis);
		ImGui::SameLine();
		ImGui::Checkbox("Y-Axis 2", &y2_axis);
		ImGui::SameLine();
		ImGui::Checkbox("Y-Axis 3", &y3_axis);

		ImGui::BulletText("You can drag axes to the opposite side of the plot.");
		ImGui::BulletText("Hover over legend items to see which axis they are plotted on.");

		if (ImPlot::BeginPlot("Multi-Axis Plot", ImVec2(-1, 0))) {
			ImPlot::SetupAxes("X-Axis 1", "Y-Axis 1");
			ImPlot::SetupAxesLimits(0, 100, 0, 10);
			if (x2_axis) {
				ImPlot::SetupAxis(ImAxis_X2, "X-Axis 2", ImPlotAxisFlags_AuxDefault);
				ImPlot::SetupAxisLimits(ImAxis_X2, 0, 100);
			}
			if (y2_axis) {
				ImPlot::SetupAxis(ImAxis_Y2, "Y-Axis 2", ImPlotAxisFlags_AuxDefault);
				ImPlot::SetupAxisLimits(ImAxis_Y2, 0, 1);
			}
			if (y3_axis) {
				ImPlot::SetupAxis(ImAxis_Y3, "Y-Axis 3", ImPlotAxisFlags_AuxDefault);
				ImPlot::SetupAxisLimits(ImAxis_Y3, 0, 300);
			}

			ImPlot::PlotLine("f(x) = x", xs, xs, 1001);
			if (x2_axis) {
				ImPlot::SetAxes(ImAxis_X2, ImAxis_Y1);
				ImPlot::PlotLine("f(x) = sin(x)*3+1", xs2, ys1, 1001);
			}
			if (y2_axis) {
				ImPlot::SetAxes(ImAxis_X1, ImAxis_Y2);
				ImPlot::PlotLine("f(x) = cos(x)*.2+.5", xs, ys2, 1001);
			}
			if (y3_axis) {
				ImPlot::SetAxes(ImAxis_X2, ImAxis_Y3);
				ImPlot::PlotLine("f(x) = sin(x+.5)*100+200 ", xs2, ys3, 1001);
			}
			ImPlot::EndPlot();
		}

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
	glViewport(0, 0, 1024, 768);
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