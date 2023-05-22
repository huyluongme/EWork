#include "Gantt.h"

Gantt gGantt;

void Gantt::DrawGanttChart() {
	ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowSize(ImGui::GetMainViewport()->WorkSize - ImVec2(50, 50), ImGuiCond_Appearing);
	ImGui::PushFont(gInterface.smallFont);
	static ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable;

	bool open = true;
	if (ImGui::BeginPopupModal("Gantt Chart", &open, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize))
	{
		ImGui::BeginChild("##ganttleft", ImVec2(250, 0), true);
		ImGui::BeginTable("Task", 2, flags);
		ImGui::TableSetupColumn("ID", ImGuiTableColumnFlags_WidthFixed);
		ImGui::TableSetupColumn("Task");
		ImGui::TableHeadersRow();

		for (int row = 1; row < gGraph.GetRanking().size() - 1; row++) {
			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			ImGui::Text(to_string(row).c_str());
			ImGui::TableSetColumnIndex(1);
			ImGui::Text(gProject.GetProjectSelected()->task[gGraph.GetRanking()[row]].task.c_str());
		}



		/*for (int row = 0; row < 5; row++)
		{
			ImGui::TableNextRow();
			for (int column = 0; column < 3; column++)
			{
				ImGui::TableSetColumnIndex(column);
				char buf[32];
				sprintf(buf, "Hello %d,%d", column, row);
				if (contents_type == CT_Text)
					ImGui::TextUnformatted(buf);
				else if (contents_type == CT_FillButton)
					ImGui::Button(buf, ImVec2(-FLT_MIN, 0.0f));
			}
		}*/
		ImGui::EndTable();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Duration: %d", gGraph.GetTotalDuration());
		ImGui::TextColored(ImVec4(1.000f, 0.000f, 0.000f, 1.000f), "Red: Critical");
		ImGui::TextColored(ImVec4(0.259f, 0.588f, 0.980f, 1.000f), "Blue: Non-critical");
		ImGui::EndChild();

		ImGui::SameLine();
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::BeginChild("##ganttright", ImVec2(0, 0), true, ImGuiWindowFlags_HorizontalScrollbar );


		ImVec2 canvas_p0 = ImGui::GetCursorScreenPos();
		ImVec2 canvas_pz = canvas_p0 + ImVec2(34.0f * gGraph.GetTotalDuration() + 160.0f, (gGraph.GetRanking().size() -2)* 40.0f + 16.0f);
		ImDrawList* draw_list = ImGui::GetWindowDrawList();
		draw_list->AddRectFilled(canvas_p0, canvas_pz, IM_COL32(60, 60, 70, 255));

		ImGui::InvisibleButton("canvas", canvas_pz);

		draw_list->PushClipRect(canvas_p0, canvas_pz, true);

		draw_list->AddText(canvas_p0 + ImVec2(40.0f - ImGui::CalcTextSize(gDate.DateToString(gProject.GetProjectSelected()->start).c_str()).x / 2.0f, 0),
			IM_COL32(255, 255, 255, 255), gDate.DateToString(gProject.GetProjectSelected()->start).c_str());

		draw_list->AddText(canvas_p0 + ImVec2(34.0f * gGraph.GetTotalDuration() + 120.0f - ImGui::CalcTextSize(gDate.DateToString(gProject.GetProjectSelected()->task[gGraph.GetRanking()[gGraph.GetRanking().size() - 2]].end).c_str()).x / 2.0f, 0),
			IM_COL32(255, 255, 255, 255), gDate.DateToString(gProject.GetProjectSelected()->task[gGraph.GetRanking()[gGraph.GetRanking().size() - 2]].end).c_str());

		ImVec2 p1 = canvas_p0 + ImVec2(80.f, 0.0f);
		ImVec2 p2 = p1 + ImVec2(0.0f, 16.0f);
		draw_list->AddLine(p1, p2, IM_COL32(100, 100, 100, 255));

		//draw_list->AddText(canvas_p0 + ImVec2(40.0f) - , IM_COL32(255, 255, 255, 255), to_string(gGraph.GetTotalDuration()).c_str());

		for (int i = 1; i <= gGraph.GetTotalDuration(); i++) {

			ImVec2 p1 = canvas_p0 + ImVec2(34.0f * i + 80.f, 0.0f);
			ImVec2 p2 = p1 + ImVec2(0.0f, 16.0f);
			ImVec2 text_size = ImGui::CalcTextSize(to_string(i).c_str());
			ImVec2 text_pos(p1.x - 17.0f - text_size.x / 2.0f, p1.y);
			draw_list->AddLine(p1, p2, IM_COL32(100, 100, 100, 255));
			draw_list->AddText(text_pos, IM_COL32(255, 255, 255, 255), to_string(i).c_str());

			//draw_list->AddLine()
		}

		draw_list->AddLine(canvas_p0 + ImVec2(0, 16.0f), canvas_p0 + ImVec2(canvas_pz.x, 16.0f), IM_COL32(100, 100, 100, 255));
		/*MessageBoxA(0, to_string(gGraph.GetRanking().size()).c_str(), 0, 0);*/

		map<int, ImVec2> start, end;

		for (int h = 1; h < gGraph.GetRanking().size() - 1; h++) {
			int u = gGraph.GetRanking()[h];

			ImU32 Col = IM_COL32(66, 150, 250, 255);
			if (gGraph.Get_t()[u] == gGraph.Get_T()[u])
				Col = IM_COL32(255, 0, 0, 255);

			ImVec2 p1 = canvas_p0 + ImVec2(0, 16.0f + (h * 40.0f));
			ImVec2 p2 = p1 + ImVec2(canvas_pz.x, 0);
			draw_list->AddLine(p1, p2, IM_COL32(100, 100, 100, 255));


			ImVec2 p3 = p1 + ImVec2(gGraph.Get_t()[gGraph.GetRanking()[h]] * 34.0f + 80.0f, -30.0f);
			ImVec2 p4 = p3 + ImVec2(gProject.GetProjectSelected()->task[gGraph.GetRanking()[h]].duration * 34.0f, 20.0f);
			draw_list->AddRectFilled(p3, p4, Col);
			if (gProject.GetProjectSelected()->task[u].status) {
				draw_list->AddRectFilled(p4 - ImVec2(10.0f, 20.0f), p4, IM_COL32(113, 255, 0, 255));
			}
			start[u] = p3 + ImVec2(0, 10.0f);
			end[u] = p4 - ImVec2(16.0f, 0);

			//start[u] = p3 + ImVec2(0, 10.0f);
			//end[u] = p4 - ImVec2(16.0f, 0);

			ImVec2 task_size = ImGui::CalcTextSize(to_string(u).c_str());
			ImVec2 p_task = p3 + ImVec2((p4 - p3).x / 2.0f, (p4 - p3).y / 2.0f) - (task_size / 2.0f);
			draw_list->AddText(p_task, IM_COL32(255, 255, 255, 255), to_string(u).c_str());

			/*ImVec2 start_size = ImGui::CalcTextSize(gDate.DateToString(gProject.GetProjectSelected()->task[u].start).c_str());
			ImVec2 p_start = p3 + ImVec2(-40 - (start_size.x / 2.0f), 10.0f - (start_size.y / 2.0f));
			draw_list->AddText(p_start, IM_COL32(255, 255, 255, 255), gDate.DateToString(gProject.GetProjectSelected()->task[u].start).c_str());*/

			ImVec2 end_size = ImGui::CalcTextSize(gDate.DateToString(gProject.GetProjectSelected()->task[u].end).c_str());
			ImVec2 p_end = p4 + ImVec2(40.0f - (end_size.x / 2.0f), -10.0f - (end_size.y / 2.0f));


			draw_list->AddText(p_end, IM_COL32(255, 255, 255, 255), gDate.DateToString(gProject.GetProjectSelected()->task[u].end).c_str());

			//draw_list->AddCircle(p1, 4, IM_COL32(255, 255, 255, 255));
		}

		for (int i = 0; i < gGraph.GetGraph()->n - 2; i++) {
			for (int j = 0; j < gGraph.GetGraph()->n - 2; j++) {
				if (gGraph.GetGraph()->A[i][j] > 0) {
					ImU32 Col = IM_COL32(66, 150, 250, 255);
					if (gGraph.Get_t()[i] == gGraph.Get_T()[i] && gGraph.Get_t()[j] == gGraph.Get_T()[j])
						Col = IM_COL32(255, 0, 0, 255);
					ImVec2 p3 = end[i] + ImVec2(0, (start[j].y - end[i].y) / 4.0f);
					ImVec2 p4 = start[j] - ImVec2(10.0f, (start[j].y - end[i].y) / 4.0f);
					ImVec2 mid = ImVec2(end[i].x, start[j].y);
					/*draw_list->AddLine(end[i], p3, IM_COL32(255, 0, 0, 255));
					draw_list->AddLine(p3, p4, IM_COL32(255, 0, 0, 255));
					draw_list->AddLine(p4, start[j], IM_COL32(255, 0, 0, 255));*/
					draw_list->AddBezierQuadratic(end[i], mid, start[j], Col, 1.0f, 100);
					/*draw_list->AddCircleFilled(end[i], 5, IM_COL32(255, 255, 255, 255));
					draw_list->AddCircleFilled(start[j], 5, IM_COL32(255, 255, 255, 255));
					draw_list->AddCircleFilled(p3, 5, IM_COL32(255, 255, 255, 255));
					draw_list->AddCircleFilled(p4, 5, IM_COL32(255, 255, 255, 255));*/
					/*draw_list->AddBezierCubic(end[i], p3, p4, mid[j], IM_COL32(255, 255, 255, 255),1.0f, 2);
					draw_list->AddCircleFilled(p4, 5, IM_COL32(255, 255, 255, 255));*/
				}
			}
		}

		draw_list->PopClipRect();
		//draw_list->AddRectFilled(canvas_p0, canvas_pz, IM_COL32(50, 50, 50, 255));
		//ImGui::InvisibleButton("canvas", canvas_pz);
		//for (int i = 1; i < gGraph.GetTotalDuration(); i++) {
		//	//draw_list->AddText(canvas_p0 + ImVec2( 71.0f * (i - 1), 0), IM_COL32(255, 255, 255, 255), gDate.DateToString(gProject.GetProjectSelected()->start).c_str());
		//	if (i < gGraph.GetTotalDuration() - 1) {
		//		ImVec2 p1(canvas_p0.x + 70.0f * i, canvas_p0.y);
		//		ImVec2 p2(canvas_p0.x + 70.0f * i, canvas_p0.y + 10.0f);

		//		draw_list->AddLine(p1, p2, IM_COL32(255, 255, 255, 255));
		//	}
		//}
		//ImGui::InvisibleButton("canvas", canvas_p0 + ImVec2(10000, 100), ImGuiButtonFlags_MouseButtonLeft | ImGuiButtonFlags_MouseButtonRight);
		ImGui::EndChild();
		ImGui::PopStyleVar();
		ImGui::EndPopup();
	}

	ImGui::PopFont();
}