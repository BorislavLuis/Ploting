#include "mainMenu.h"
mainMenu* mainMenu::s_Instance = nullptr;
bool mainMenu::lt0201 = false;
bool mainMenu::lt0202 = false;
bool mainMenu::lt0203 = false;
bool mainMenu::lt0204 = false;
bool mainMenu::lt0205 = false;
bool mainMenu::lt0206 = false;
bool mainMenu::lt0207 = false;
bool mainMenu::lt0301 = false;
bool mainMenu::lt0302 = false;
bool mainMenu::show_status = false;
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
	ImGui::Begin(u8"������ ����");
		dateChoser();
		instrumentChoice();
		settings();
	ImGui::End();
}

void mainMenu::dateChoser()
{
	//����� �� ��������
	if (ImGui::CollapsingHeader(u8"����� �� ����"))
	{
		if (ImGui::DateChooser(u8"����", myDate, "%d/%m/%Y"))
		{
			show_status = true;
		}
		if (show_status)
		{
			std::cout << "Here" << std::endl;
			ImGui::Begin(u8"���");
			std::string str = std::to_string(myDate.tm_mday);
			ImGui::Text(str.c_str());
			ImGui::End();
		}
	}
}

void mainMenu::instrumentChoice()
{
	if (ImGui::CollapsingHeader(u8"����� �� ������������ ����"))
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
}

void mainMenu::settings()
{
	if (ImGui::CollapsingHeader(u8"���������"))
	{
		ImGui::ShowFontSelector(u8"����");
		ImGui::ShowStyleSelector(u8"���� �� ����������");
		ImGuiStyle stl = ImGui::GetStyle();
		ImPlot::ShowStyleSelector(u8"���� �� �������");
		ImPlot::ShowColormapSelector(u8"���� �� �������");
		ImGui::Separator();
		ImGui::Checkbox(u8"�������� ������ �����", &ImPlot::GetStyle().UseLocalTime);
		ImGui::Checkbox(u8"��������� ISO 8601", &ImPlot::GetStyle().UseISO8601);
		ImGui::Checkbox(u8"�������� 24 ����� ��������", &ImPlot::GetStyle().Use24HourClock);
		ImGui::Separator();
	}
}

void mainMenu::releaseSingletonInstance()
{
	if (s_Instance != nullptr)
	{
		delete s_Instance;
		s_Instance = nullptr;
	}
}

mainMenu::~mainMenu()
{
	if (s_Instance != nullptr)
	{
		// ������ 
		delete s_Instance;
		s_Instance = nullptr;
	}
}

