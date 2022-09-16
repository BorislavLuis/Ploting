#include "plotWindow.h"


ImVec4 RandomColor() {
	ImVec4 col;
	col.x = RandomRange(0.0f, 1.0f);
	col.y = RandomRange(0.0f, 1.0f);
	col.z = RandomRange(0.0f, 1.0f);
	col.w = 1.0f;
	return col;
}


MyDndItem::MyDndItem() {
	static int i = 0;
	Idx = i++;
	Plt = 0;
	Yax = ImAxis_Y1;
	sprintf_s(Label, "%02d Hz", Idx + 1);
	Color = RandomColor();
	Data.reserve(2880);
	for (int k = 0; k < 2880; ++k) {
		float t = k * 1.0f / 999;
		Data.push_back(ImVec2(t, 0.5f + 0.5f * sinf(2 * 3.14f * t * (Idx + 1))));
	}
}

ImVec2 MyDndItem::LoadData(std::string filename)
{

	return ImVec2();
}

void MyDndItem::Reset() 
{ 
	Plt = 0; Yax = ImAxis_Y1; 
}

PlotWindow::PlotWindow()
{
}

void PlotWindow::BeginWindow()
{

	ImGui::Begin(u8"Графики");
	ImGui::Separator();
	if (false)
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


	 // for plot 2

	// child window to serve as initial source for our DND items
	ImGui::BeginChild(u8"Лява част", ImVec2(100, 600));
		if (ImGui::Button(u8"Ресет")) {
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
	ImGui::BeginChild(u8"Дясна част", ImVec2(-1, 400));
	// plot 1 (time series)
	ImPlotAxisFlags flags = ImPlotAxisFlags_NoHighlight;
	if (ImPlot::BeginPlot("##DND1", ImVec2(-1, 395))) {
		ImPlot::SetupAxis(ImAxis_X1, NULL, flags);
		ImPlot::SetupAxis(ImAxis_Y1, u8"[пусни тук]", flags | ImPlotAxisFlags_Lock);
		ImPlot::SetupAxis(ImAxis_Y2, u8"[пусни тук]", flags | ImPlotAxisFlags_Lock | ImPlotAxisFlags_Opposite);
		//ImPlot::SetupAxis(ImAxis_Y3, "[drop here]", flags | ImPlotAxisFlags_Opposite);

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
}

void PlotWindow::Show()
{
}


