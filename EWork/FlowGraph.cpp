#include "stdafx.h"
#include "FlowGraph.h"

FlowGraph gFlowGraph;


void FlowGraph::ScaleNodePos(float scale) {
	for (int i = 0; i < gProject.GetProjectSelected()->task.size(); ++i) {
		gProject.GetProjectSelected()->task[i].pos.x += gProject.GetProjectSelected()->task[i].pos.x * scale;
		gProject.GetProjectSelected()->task[i].pos.y += gProject.GetProjectSelected()->task[i].pos.y * scale;
	}
}

template<typename... Args>
float find_max_float(Args... args) {
	float nums[] = { args... };
	size_t num_count = sizeof...(args);
	if (num_count == 0) {
		return 0.0f; // or return some other value to indicate an error
	}
	auto max_element = std::max_element(nums, nums + num_count);
	return *max_element;
}


void FlowGraph::DrawNode(ImDrawList* draw_list, ImVec2 origin, ImVec2 mousePos, float scale) {
	for (int i = 0; i < gProject.GetProjectSelected()->task.size(); ++i) {
		ImVec2 task_text_size(ImGui::CalcTextSize(gProject.GetProjectSelected()->task[i].task.c_str()));

		std::string ct1, ct2, ct3, ct4, ct5, ct6;

		ct1 = ICON_FA_USER " " + gProject.GetProjectSelected()->task[i].assignment;
		ct2 = ICON_FA_HOURGLASS_START " " + gDate.DateToString(gProject.GetProjectSelected()->task[i].start);
		ct3 = ICON_FA_HOURGLASS_END " " + gDate.DateToString(gProject.GetProjectSelected()->task[i].end);
		ct4 = ((gProject.GetProjectSelected()->task[i].extend) ? "New Duration: " : "Duration: ") + std::to_string(gProject.GetProjectSelected()->task[i].duration);


		ct5 = "Status: ";
		gProject.GetProjectSelected()->task[i].status ? ct5 += "Finished" : ct5 += "Unfinished";


		ImGui::PushFont(gInterface.mediumFont);

		float max_size = find_max_float(task_text_size.x, ImGui::CalcTextSize(ct1.c_str()).x, ImGui::CalcTextSize(ct2.c_str()).x
			, ImGui::CalcTextSize(ct3.c_str()).x, ImGui::CalcTextSize(ct4.c_str()).x, ImGui::CalcTextSize(ct5.c_str()).x
			, ImGui::CalcTextSize(ct6.c_str()).x);

		ImVec2 content_text_size(max_size + (20.0f / scale), ImGui::CalcTextSize(ct1.c_str()).y);

		ImGui::PopFont();

		ImVec2 header_start(origin + gProject.GetProjectSelected()->task[i].pos);
		ImVec2 header_end(header_start.x + content_text_size.x, header_start.y + task_text_size.y);

		draw_list->AddRectFilled(header_start, header_end, ImGui::GetColorU32(gProject.GetProjectSelected()->task[i].header_color), 10.0f / scale, ImDrawFlags_RoundCornersTop);

		draw_list->AddText(header_start + (header_end - header_start) / 2.0f - task_text_size / 2.0f, IM_COL32(255, 255, 255, 255), gProject.GetProjectSelected()->task[i].task.c_str());

		ImVec2 main_start(header_start.x, header_end.y);
		ImVec2 main_end(header_end.x, main_start.y + content_text_size.y);

		draw_list->AddRectFilled(main_start, main_end + ImVec2(0.0f, content_text_size.y * (ct6.empty() ? 4.0f : 5.0f)), IM_COL32(32, 32, 32, 200), 10.0f / scale, ImDrawFlags_RoundCornersBottom);

		ImGui::PushFont(gInterface.smallFont);

		ImVec2 p1_start(header_start.x, header_end.y);
		ImVec2 p1_end(header_end.x, p1_start.y + content_text_size.y);


		draw_list->AddText(ImVec2(main_start.x + 10.0f / scale, main_start.y + (main_end.y - main_start.y) / 2.0f - ImGui::CalcTextSize(ct1.c_str()).y / 2.0f), IM_COL32(255, 255, 255, 255), ct1.c_str());
		draw_list->AddText(ImVec2(main_start.x + 10.0f / scale, main_start.y + content_text_size.y + (main_end.y - main_start.y) / 2.0f - ImGui::CalcTextSize(ct2.c_str()).y / 2.0f), IM_COL32(255, 255, 255, 255), ct2.c_str());
		if (ct6.empty()) {
			draw_list->AddText(ImVec2(main_start.x + 10.0f / scale, main_start.y + 2.0f * content_text_size.y + (main_end.y - main_start.y) / 2.0f - ImGui::CalcTextSize(ct3.c_str()).y / 2.0f), IM_COL32(255, 255, 255, 255), ct3.c_str());

			draw_list->AddText(ImVec2(main_start.x + 10.0f / scale, main_start.y + 3.0f * content_text_size.y + (main_end.y - main_start.y) / 2.0f - ImGui::CalcTextSize(ct4.c_str()).y / 2.0f), IM_COL32(255, 255, 255, 255), ct4.c_str());

			draw_list->AddText(ImVec2(main_start.x + 10.0f / scale, main_start.y + 4.0f * content_text_size.y + (main_end.y - main_start.y) / 2.0f - ImGui::CalcTextSize(ct5.c_str()).y / 2.0f), IM_COL32(255, 255, 255, 255), ct5.c_str());
		}
		else {
			draw_list->AddText(ImVec2(main_start.x + 10.0f / scale, main_start.y + 2.0f * content_text_size.y + (main_end.y - main_start.y) / 2.0f - ImGui::CalcTextSize(ct3.c_str()).y / 2.0f), IM_COL32(255, 255, 255, 255), ct3.c_str());
			draw_list->AddText(ImVec2(main_start.x + 10.0f / scale, main_start.y + 3.0f * content_text_size.y + (main_end.y - main_start.y) / 2.0f - ImGui::CalcTextSize(ct6.c_str()).y / 2.0f), IM_COL32(255, 255, 255, 255), ct6.c_str());

			draw_list->AddText(ImVec2(main_start.x + 10.0f / scale, main_start.y + 4.0f * content_text_size.y + (main_end.y - main_start.y) / 2.0f - ImGui::CalcTextSize(ct4.c_str()).y / 2.0f), IM_COL32(255, 255, 255, 255), ct4.c_str());

			draw_list->AddText(ImVec2(main_start.x + 10.0f / scale, main_start.y + 5.0f * content_text_size.y + (main_end.y - main_start.y) / 2.0f - ImGui::CalcTextSize(ct5.c_str()).y / 2.0f), IM_COL32(255, 255, 255, 255), ct5.c_str());
		}
		ImGui::PopFont();

		gProject.GetProjectSelected()->task[i].frame_p1 = header_start;
		gProject.GetProjectSelected()->task[i].frame_p2 = main_end + ImVec2(0.0f, content_text_size.y * (ct6.empty() ? 4.0f : 5.0f));

		ImVec2 p1(gProject.GetProjectSelected()->task[i].frame_p1.x, gProject.GetProjectSelected()->task[i].frame_p1.y + (gProject.GetProjectSelected()->task[i].frame_p2.y - gProject.GetProjectSelected()->task[i].frame_p1.y) / 2.0f);
		ImVec2 p2(gProject.GetProjectSelected()->task[i].frame_p2.x, gProject.GetProjectSelected()->task[i].frame_p1.y + (gProject.GetProjectSelected()->task[i].frame_p2.y - gProject.GetProjectSelected()->task[i].frame_p1.y) / 2.0f);
		gProject.GetProjectSelected()->task[i].input_p = p1;
		gProject.GetProjectSelected()->task[i].output_p = p2;
		draw_list->AddRect(gProject.GetProjectSelected()->task[i].frame_p1, gProject.GetProjectSelected()->task[i].frame_p2, IM_COL32_WHITE, 10.0f / scale, ImDrawFlags_RoundCornersAll, 1.0f / scale);
		draw_list->AddCircleFilled(p1, 5.0f / scale, IM_COL32_WHITE);
		draw_list->AddCircleFilled(p2, 5.0f / scale, IM_COL32_WHITE);

	}
}

void FlowGraph::GetIDNodeSelecting(float scale) {
	if (this->bMoveNode || this->bTaskOption || this->bAddLine) return;
	for (int n = 0; n < gProject.GetProjectSelected()->task.size(); n++) {
		float distance = sqrt(pow(ImGui::GetMousePos().x - gProject.GetProjectSelected()->task[n].output_p.x, 2) + pow(ImGui::GetMousePos().y - gProject.GetProjectSelected()->task[n].output_p.y, 2));
		if (gUser.GetMyAcc()->type == LEADER) {
			if (!bAddLine && distance <= (10.0f / scale) && ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
				idNodeSelected = n;
				bAddLine = true;
				return;
			}
		}
		if (gInterface.CheckMouseHover(ImGui::GetMousePos(), gProject.GetProjectSelected()->task[n].frame_p1, gProject.GetProjectSelected()->task[n].frame_p2)) {
			if (!bMoveNode && ImGui::IsMouseDown(ImGuiMouseButton_Left) && gUser.GetMyAcc()->type == LEADER) {
				idNodeSelected = n;
				bMoveNode = true;
				pos_bakup = ImGui::GetMousePos() - gProject.GetProjectSelected()->task[n].frame_p1;
				return;
			}
			else if (!this->bTaskOption && ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
				if (gUser.GetMyAcc()->type == LEADER) {
					idNodeSelected = n;
					this->bTaskOption = true;

					ImGui::OpenPopup("Task Options");
				}
				else {
					if (gProject.GetProjectSelected()->task[n].assignment == gUser.GetMyAcc()->name) {
						idNodeSelected = n;
						this->bTaskOption = true;

						ImGui::OpenPopup("Task Options");
					}
				}
				return;
			}
		}
	}
	idNodeSelected = -1;
}

void FlowGraph::GetIDEdgeSelecting() {
	if (bDeleleEdge) return;
	for (int i = 0; i < gProject.GetProjectSelected()->edges.size(); ++i) {
		ImVec2 mouse_pos_projected_on_segment = ImBezierCubicClosestPoint(gProject.GetProjectSelected()->edges[i].p1, gProject.GetProjectSelected()->edges[i].p2
			, gProject.GetProjectSelected()->edges[i].p3, gProject.GetProjectSelected()->edges[i].p4, ImGui::GetMousePos(), 100);
		ImVec2 mouse_pos_delta_to_segment = ImVec2(mouse_pos_projected_on_segment.x - ImGui::GetMousePos().x, mouse_pos_projected_on_segment.y - ImGui::GetMousePos().y);
		bool is_segment_hovered = (ImLengthSqr(mouse_pos_delta_to_segment) <= 10.0f);

		if (is_segment_hovered) {
			if (!bDeleleEdge && ImGui::IsMouseClicked(1)) {
				idEdgeSelected = i;
				bDeleleEdge = true;
				ImGui::OpenPopup("Edge Option");
				return;
			}
		}
	}
	idEdgeSelected = -1;
}

void FlowGraph::MoveNode(ImVec2 new_pos) {
	if (!bMoveNode || idNodeSelected == -1) return;

	if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
		gProject.GetProjectSelected()->task[idNodeSelected].pos = new_pos - pos_bakup;
		//gProject.SaveProject();
	}
	else {

		idNodeSelected = -1;
		bMoveNode = false;
	}
}

void FlowGraph::DrawEdge(ImDrawList* draw_list, float scale) {
	for (int i = 0; i < gProject.GetProjectSelected()->edges.size(); ++i) {
		int id_node_from = gProject.GetProjectSelected()->edges[i].node_a, id_node_to = gProject.GetProjectSelected()->edges[i].node_b;
		ImVec2 pos_from = gProject.GetProjectSelected()->task[gProject.GetProjectSelected()->edges[i].node_a].output_p, pos_to = gProject.GetProjectSelected()->task[gProject.GetProjectSelected()->edges[i].node_b].input_p;
		float distance = sqrt(pow(pos_from.x - pos_to.x, 2) + pow(pos_from.y - pos_to.y, 2));
		gProject.GetProjectSelected()->edges[i].p1 = pos_from;
		gProject.GetProjectSelected()->edges[i].p2 = pos_from + ImVec2(distance / 4.0f, 0.0f);
		gProject.GetProjectSelected()->edges[i].p3 = pos_to - ImVec2(distance / 4.0f, 0.0f);
		gProject.GetProjectSelected()->edges[i].p4 = pos_to;
		draw_list->AddBezierCubic(pos_from, pos_from + ImVec2(distance / 4.0f, 0.0f), pos_to - ImVec2(distance / 4.0f, 0.0f), pos_to, IM_COL32_WHITE, 1.0f / scale, 100);

	}
	//float distance = sqrt(pow(node[0].output_p.x - node[1].input_p.x, 2) + pow(node[0].output_p.y - node[1].input_p.y, 2));
	//float distance2 = sqrt(pow(node[0].output_p.x - node[2].input_p.x, 2) + pow(node[0].output_p.y - node[2].input_p.y, 2));

	////draw_list->AddCircleFilled(node[0].output_p + ImVec2(distance / 2.0f,0.0f), 10.0f, IM_COL32_WHITE);
	////draw_list->AddCircleFilled(p1, 10.0f, IM_COL32_WHITE);
	//draw_list->AddBezierCubic(node[0].output_p, node[0].output_p + ImVec2(distance/4.0f,0.0f), node[1].input_p - ImVec2(distance / 4.0f, 0.0f), node[1].input_p, IM_COL32_WHITE, 1.0f/scale, 0);
	//draw_list->AddBezierCubic(node[0].output_p, node[0].output_p + ImVec2(distance2/4.0f,0.0f), node[2].input_p - ImVec2(distance2 / 4.0f, 0.0f), node[2].input_p, IM_COL32_WHITE, 1.0f/scale, 0);
}

bool FlowGraph::IsConnectExist(int in, int out) {
	for (auto e : gProject.GetProjectSelected()->edges) {
		if (e.node_a == in && e.node_b == out)
			return true;
	}
	return false;
}

void FlowGraph::AddLine(ImDrawList* draw_list, float scale) {
	if (!bAddLine || idNodeSelected == -1) return;
	static int idNodeConnect = -1;
	if (ImGui::IsMouseDown(0) && ImGui::IsMouseDragging(0)) {
		ImVec2 pos_from = gProject.GetProjectSelected()->task[idNodeSelected].output_p, pos_to;
		float distance;
		for (int i = 0; i < gProject.GetProjectSelected()->task.size(); ++i) {
			if (i != idNodeSelected) {
				if (sqrt(pow(ImGui::GetMousePos().x - gProject.GetProjectSelected()->task[i].input_p.x, 2) + pow(ImGui::GetMousePos().y - gProject.GetProjectSelected()->task[i].input_p.y, 2)) <= (10.0f / scale)) {
					idNodeConnect = i;
					break;
				}
				else idNodeConnect = -1;
			}
		}

		if (idNodeConnect != -1) {
			pos_to = gProject.GetProjectSelected()->task[idNodeConnect].input_p;
			distance = sqrt(pow(pos_from.x - pos_to.x, 2) + pow(pos_from.y - pos_to.y, 2));
		}
		else {
			pos_to = ImGui::GetMousePos();
			distance = sqrt(pow(ImGui::GetMousePos().x - pos_from.x, 2) + pow(ImGui::GetMousePos().y - pos_from.y, 2));
		}
		draw_list->AddBezierCubic(pos_from, pos_from + ImVec2(distance / 4.0f, 0.0f), pos_to - ImVec2(distance / 4.0f, 0.0f), pos_to, IM_COL32_WHITE, 1.0f / scale, 0);
		//float distance;
		//int id_node_connect = -1;
		//ImVec2 pos_start = node[idNodeSelected].output_p;
		//ImVec2 pos_end = ImGui::GetMousePos();
		//for (int i = 0; i < node.size(); ++i) {
		//	if (i != idNodeSelected) {
		//		distance = sqrt(pow(node[i].input_p.x - node[idNodeSelected].output_p.x, 2) + pow(node[i].input_p.y - node[idNodeSelected].output_p.y, 2));
		//		if (distance <= (10.0f / scale)) {
		//			MessageBoxA(0, std::to_string(i).c_str(), 0, 0);
		//			/*id_node_connect = i;
		//			break;*/
		//		}
		//	}
		//}
		//if (id_node_connect == -1)
		//	distance = sqrt(pow(ImGui::GetMousePos().x - node[idNodeSelected].output_p.x, 2) + pow(ImGui::GetMousePos().y - node[idNodeSelected].output_p.y, 2));
		//else pos_end = node[id_node_connect].input_p;
		//draw_list->AddBezierCubic(pos_start, pos_start + ImVec2(distance / 4.0f, 0.0f), pos_end - ImVec2(distance / 4.0f, 0.0f), pos_end, IM_COL32_WHITE, 1.0f / scale, 0);
	}
	else {
		if (idNodeConnect != -1 && !this->IsConnectExist(idNodeSelected, idNodeConnect)) {
			gProject.GetProjectSelected()->edges.push_back({ idNodeSelected, idNodeConnect });
			gGraph.GraphProcess();
			//gProject.SaveProject();
		}
		idNodeSelected = -1;
		idNodeConnect = -1;
		bAddLine = false;
	}
}

void FlowGraph::TaskOptions() {
	if (!bTaskOption || idNodeSelected == -1) return;

	/*if (!bTaskOptionPopup) {
		ImGui::OpenPopup("Task Options");
		bTaskOptionPopup = true;
	}*/

	ImGui::PushFont(gInterface.smallFont);
	if (ImGui::BeginPopup("Task Options"))
	{
		if (gUser.GetMyAcc()->type == LEADER) {
			ImGui::Text("Header Color");
			ImGui::SameLine();
			static bool alpha_preview = true;
			static bool alpha_half_preview = false;
			static bool drag_and_drop = true;
			static bool options_menu = true;
			static bool hdr = false;
			ImGuiColorEditFlags misc_flags = (hdr ? ImGuiColorEditFlags_HDR : 0) | (drag_and_drop ? 0 : ImGuiColorEditFlags_NoDragDrop) | (alpha_half_preview ? ImGuiColorEditFlags_AlphaPreviewHalf : (alpha_preview ? ImGuiColorEditFlags_AlphaPreview : 0)) | (options_menu ? 0 : ImGuiColorEditFlags_NoOptions);

			static ImVec4 color = ImVec4(114.0f / 255.0f, 144.0f / 255.0f, 154.0f / 255.0f, 200.0f / 255.0f);
			bool open_popup = ImGui::ColorButton("HeaderColor", gProject.GetProjectSelected()->task[idNodeSelected].header_color, ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_AlphaPreview);
			static ImVec4 backup_color;
			if (open_popup)
			{
				ImGui::OpenPopup("HeaderColor");
				backup_color = color;
			}
			if (ImGui::BeginPopup("HeaderColor"))
			{
				ImGui::ColorPicker4("##HeaderColor", (float*)&gProject.GetProjectSelected()->task[idNodeSelected].header_color, misc_flags | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview);
				ImGui::SameLine();

				ImGui::BeginGroup(); // Lock X position

				ImGui::Text("Palette");
				for (int n = 0; n < IM_ARRAYSIZE(saved_palette); n++)
				{
					ImGui::PushID(n);
					if ((n % 8) != 0)
						ImGui::SameLine(0.0f, ImGui::GetStyle().ItemSpacing.y);

					ImGuiColorEditFlags palette_button_flags = ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoDragDrop;
					if (ImGui::ColorButton("##palette", saved_palette[n], palette_button_flags, ImVec2(20, 20))) {
						gProject.GetProjectSelected()->task[idNodeSelected].header_color = saved_palette[n]; // Preserve alpha!
						//gProject.SaveProject();
					}
					ImGui::PopID();
				}
				ImGui::EndGroup();

				ImGui::EndPopup();
			}
		}

		ImGui::MenuItem("Show more");
		if (ImGui::IsItemClicked()) {
			ImGui::OpenPopup(gProject.GetProjectSelected()->task[idNodeSelected].task.c_str());
		}

		ShowMore();

		if (gUser.GetMyAcc()->type == LEADER()) {
			if (!gProject.GetProjectSelected()->task[idNodeSelected].extend) {
				ImGui::MenuItem("Extend");
				if (ImGui::IsItemClicked())
					ImGui::OpenPopup("Extend");
			}
		}

		if (!gProject.GetProjectSelected()->task[idNodeSelected].status) {
			ImGui::MenuItem("Finished");
			if (ImGui::IsItemClicked()) {
				gProject.GetProjectSelected()->task[idNodeSelected].status = true;
				int new_duration = gDate.diffDays(gProject.GetProjectSelected()->task[idNodeSelected].start, gDate.GetCurrentDate());
				gProject.GetProjectSelected()->task[idNodeSelected].duration = new_duration + 1;
				gGraph.GraphProcess();
				gProject.SaveProject();
				ImGui::CloseCurrentPopup();
				idNodeSelected = -1;
				bTaskOption = false;
			}
		}
		

		ImVec2 center = ImGui::GetMainViewport()->GetCenter();
		ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
		if (ImGui::BeginPopupModal("Extend", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize))
		{
			static int add_duration = 1;
			ImGui::Text("Add Duration (day):");
			ImGui::InputInt("##addduration", &add_duration);
			if (add_duration < 1) add_duration = 1;
			if (ImGui::Button("Add", ImVec2(120, 0))) {
				gProject.GetProjectSelected()->task[idNodeSelected].duration += add_duration;
				gProject.GetProjectSelected()->task[idNodeSelected].extend = true;
				gGraph.GraphProcess();
				bGetCurDateID = false;
				gProject.SaveProject();
				ImGui::CloseCurrentPopup();
			}
			ImGui::SetItemDefaultFocus();
			ImGui::SameLine();
			if (ImGui::Button("Cancel", ImVec2(120, 0))) {
				bGetCurDateID = false;
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
		if (gUser.GetMyAcc()->type == LEADER) {
			if (ImGui::MenuItem("Remove Task", NULL, false)) {
				for (int e = 0; e < gProject.GetProjectSelected()->edges.size(); ++e) {
					if (gProject.GetProjectSelected()->edges[e].node_a == idNodeSelected || gProject.GetProjectSelected()->edges[e].node_b == idNodeSelected) {
						gProject.GetProjectSelected()->edges.erase(gProject.GetProjectSelected()->edges.begin() + e, gProject.GetProjectSelected()->edges.begin() + e + 1);
						e--;
					}
					else {
						if (gProject.GetProjectSelected()->edges[e].node_a > idNodeSelected)
							gProject.GetProjectSelected()->edges[e].node_a -= 1;
						if (gProject.GetProjectSelected()->edges[e].node_b > idNodeSelected)
							gProject.GetProjectSelected()->edges[e].node_b -= 1;
					}

				}
				gProject.GetProjectSelected()->task.erase(gProject.GetProjectSelected()->task.begin() + idNodeSelected, gProject.GetProjectSelected()->task.begin() + idNodeSelected + 1);
				idNodeSelected = -1;
				bTaskOption = false;
				//gProject.SaveProject();
			}
		}
		ImGui::EndPopup();
	}
	else {
		idNodeSelected = -1;
		bTaskOption = false;
	}
	/*if (!ImGui::IsPopupOpen("Task Options"))
	MessageBox(0, 0, 0, 0);*/
	//if (ImGui::IsItemHovered()) { MessageBox(0,0,0,0); }
	/*else {
	idNodeSelected = -1;
	bTaskOptionPopup = false;
	bTaskOption = false;
	}*/

	//if()
	ImGui::PopFont();
}

void FlowGraph::ShowMore() {
	ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowSize(ImGui::GetMainViewport()->WorkSize - ImVec2(200.0f, 200.0f), ImGuiCond_Appearing);
	if (ImGui::BeginPopupModal(gProject.GetProjectSelected()->task[idNodeSelected].task.c_str(), NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize))
	{
		ImGui::Text((ICON_FA_USER " " + gProject.GetProjectSelected()->task[idNodeSelected].assignment).c_str());
		ImGui::Text((ICON_FA_HOURGLASS_START " " + gDate.DateToString(gProject.GetProjectSelected()->task[idNodeSelected].start)).c_str());
		ImGui::Text((ICON_FA_HOURGLASS_END " " + gDate.DateToString(gProject.GetProjectSelected()->task[idNodeSelected].end)).c_str());

		ImGui::Text(("Duration: " + to_string(gProject.GetProjectSelected()->task[idNodeSelected].duration)).c_str());

		ImGui::Spacing();
		ImGui::Text("Discuss");
		ImGui::BeginChild("##dis", ImVec2(0, ImGui::GetTextLineHeight() * 7 + 2.0f), false, ImGuiWindowFlags_AlwaysAutoResize);
		static char text[1024 * 16];

		ImGui::InputTextMultiline("##cmt", text, IM_ARRAYSIZE(text), ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 5), ImGuiInputTextFlags_AllowTabInput);

		if (ImGui::Button("Send")) {
			gProject.GetProjectSelected()->task[idNodeSelected].cmt.push_back(gUser.GetMyAcc()->name + ": " + text);
			gProject.SaveProject();
			text[0] = '\0';
		}
		ImGui::EndChild();
		
		ImGui::BeginChild("##cmt", ImVec2(0, ImGui::GetWindowSize().y - 290.0f), true);
		for (int i = gProject.GetProjectSelected()->task[idNodeSelected].cmt.size() - 1; i >= 0; i--) {
			ImGui::Text(gProject.GetProjectSelected()->task[idNodeSelected].cmt[i].c_str());
			ImGui::Separator();
		}
		
		ImGui::EndChild();

		ImGui::SetCursorPosX(ImGui::GetWindowSize().x / 2.0f - 60.0f);
		if (ImGui::Button("Cancel", ImVec2(120, 0))) {
			bGetCurDateID = false;
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}

}

void FlowGraph::DeleteEdge() {
	if (!bDeleleEdge || idEdgeSelected == -1) return;

	if (ImGui::BeginPopup("Edge Option"))
	{
		if (ImGui::MenuItem("Remove Connect", NULL, false)) {
			gProject.GetProjectSelected()->edges.erase(gProject.GetProjectSelected()->edges.begin() + idEdgeSelected, gProject.GetProjectSelected()->edges.begin() + idEdgeSelected + 1);
			//gProject.SaveProject();
			//node.erase(node.begin() + idNodeSelected, node.begin() + idNodeSelected + 1);
		}
		////ImVec2 tmp = mouse_pos_in_canvas;
		//if (ImGui::MenuItem("Delete Task")) MessageBox(0, 0, 0, 0);
		///*if (ImGui::MenuItem("Add Task", NULL, false)) {
		//	gGraph.AddNode(mouse_pos_in_canvas);
		//}*/
		////else
		////bNodeOptions = false;
		ImGui::EndPopup();
	}
	else {
		idEdgeSelected = -1;
		//bOpenDeleteEdgeOption = false;
		bDeleleEdge = false;
	}
}

void FlowGraph::AddTask() {
	if (!this->bAddTask) return;

	ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
	ImGui::PushFont(gInterface.smallFont);

	if (ImGui::BeginPopupModal("Add Task", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize))
	{
		static char task_name[1024] = "";
		static int user = 0;
		static int duration = 1;

		ImGui::Text("Task:");
		ImGui::PushItemWidth(300);
		ImGui::InputText("##task", task_name, IM_ARRAYSIZE(task_name));
		ImGui::Text("User:");

		static bool get = false;
		static vector<const char*> cur_user;
		if (!get) {
			for (int i = 0; i < gProject.GetProjectSelectedUser()->size(); i++) {
				//MessageBoxA(0, gProject.GetProjectSelectedUser()[i].c_str(), 0, 0);
				cur_user.push_back(gProject.GetProjectSelectedUser()->at(i).data());
			}
			get = true;
		}

		ImGui::Combo("##User", &user, cur_user.data(),
			cur_user.size());

		ImGui::Text("Duration (day):");
		ImGui::InputInt("##duration", &duration);
		if (duration < 1) duration = 1;

		if (ImGui::Button("Add", ImVec2(120, 0))) {
			if (strlen(task_name) > 0) {
				sNode tmp;
				tmp.task = std::string(task_name);
				tmp.assignment = std::string(cur_user[user]);
				tmp.pos = mouse_pos_in_canvas_bakup;
				tmp.duration = duration;
				tmp.start = sDate{ -1,-1,-1 };
				tmp.end = sDate{ -1,-1,-1 };
				tmp.header_color = ImVec4(0.259f, 0.588f, 0.980f, 0.784f);
				tmp.extend = false;
				tmp.status = false;
				gProject.GetProjects()->at(gProject.idProjectSelected).task.push_back(tmp);
				task_name[0] = '\0';
				user = 0;
				duration = 1;
				gFlowGraph.bAddTask = false;
				bGetCurDateID = false;
				//gProject.SaveProject();
				gGraph.GraphProcess();
				ImGui::CloseCurrentPopup();
			}
		}
		ImGui::SetItemDefaultFocus();
		ImGui::SameLine();
		if (ImGui::Button("Cancel", ImVec2(120, 0))) {
			task_name[0] = '\0';
			user = 0;
			duration = 1;
			get = false;
			cur_user.clear();
			gFlowGraph.bAddTask = false;
			bGetCurDateID = false;
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	ImGui::PopFont();
}

bool FlowGraph::IsMousePosInTaskPos() {
	for (auto n : gProject.GetProjectSelected()->task) {
		if (gInterface.CheckMouseHover(ImGui::GetMousePos(), n.frame_p1, n.frame_p2))
			return true;
	}
	return false;
}