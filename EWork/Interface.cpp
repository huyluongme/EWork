#include "stdafx.h"
#include "Interface.h"

Interface gInterface;

void Interface::DrawInterface() {

	//gProject.tmpProject();
	//gProject.LoadProjectRealTime();
	//MessageBoxA(0, gProject.GetProjectSelected()->project_name.c_str(), 0, 0);
	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);
	ImGui::Begin("EWork", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoResize);
	if (!gUser.login)
		Login();
	else {
		ImGui::BeginChild("##left", ImVec2(ImGui::GetWindowSize().x / 5.0f, 0), true);
		DrawInterfaceLeft();
		ImGui::EndChild();

		ImGui::SameLine();

		ImGui::BeginChild("##right", ImVec2(0, 0), true);
		DrawInterfaceRight();
		ImGui::EndChild();
	}
	ImGui::End();
}

void Interface::Login() {
	ImGui::PushItemWidth(200);
	static char str0[128] = "";
	ImGui::SetCursorPos(ImGui::GetMainViewport()->GetCenter() - ImVec2(100, 0));
	ImGui::InputTextWithHint("##Username", "Username", str0, IM_ARRAYSIZE(str0));
	static char str2[128] = "";
	ImGui::SetCursorPosX(ImGui::GetMainViewport()->GetCenter().x - 100.0f);
	ImGui::InputTextWithHint("##Password", "Password", str2, IM_ARRAYSIZE(str2), ImGuiInputTextFlags_Password);
	ImGui::SetCursorPosX(ImGui::GetMainViewport()->GetCenter().x - 75.0f);
	if (ImGui::Button("Login", ImVec2(150, 0))) {
		for (int i = 0; i < gUser.GetUsers()->size(); i++) {
			if (string(str0) == gUser.GetUsers()->at(i).username && string(str2) == gUser.GetUsers()->at(i).password) {
				gUser.GetMyAcc()->name = gUser.GetUsers()->at(i).name;
				gUser.GetMyAcc()->username = gUser.GetUsers()->at(i).username;
				gUser.GetMyAcc()->password = gUser.GetUsers()->at(i).password;
				gUser.GetMyAcc()->type = gUser.GetUsers()->at(i).type;

				gUser.login = true;
				str0[0] = '\0';
				str2[0] = '\0';
				gProject.idProjectSelected = -1;
				gFlowGraph.idNodeSelected = -1;
				gFlowGraph.idEdgeSelected = -1;
				bDrawFlowGraph = false;
			}
		}
	}
}

void Interface::DrawInterfaceLeft() {
	ImGui::Text(ICON_FA_DIAMOND " EWork");
	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();
	ImGui::PushFont(mediumFont);
	ImGui::Text((ICON_FA_USER " " + gUser.GetMyAcc()->name).c_str());
	if (gUser.GetMyAcc()->type == LEADER)
		ImGui::Text("Position: Leader");
	else
		ImGui::Text("Position: Employee");

	ImGui::Spacing();
	//ImGui::Button("Setting", ImVec2(ImGui::GetWindowSize().x - 16.0f, 0));
	if (ImGui::Button("Log out", ImVec2(ImGui::GetWindowSize().x - 16.0f, 0))) {
		gUser.login = false;
		

	}
	ImGui::PopFont();

	ImGui::SetCursorPosY(ImGui::GetWindowSize().y - 28.0f);
	ImGui::Separator();
	ImGui::PushFont(smallFont);
	ImGui::SetCursorPosX(ImGui::GetWindowSize().x/2.0f - (ImGui::CalcTextSize("Version: 1.0.0").x / 2.0f));
	ImGui::Text("Version: 1.0.0");
	ImGui::PopFont();
}

void Interface::DrawInterfaceRight() {
	//DrawFlowGraph();
	if (!bDrawFlowGraph)
		DrawProjects();
	else
		DrawFlowGraph();
	/*if (bDrawFlowGraph && gProject.idProjectSelected != -1)
		DrawFlowGraph();
	else
		DrawProjects();*/
}

void Interface::DrawProjects() {


	if (gUser.GetMyAcc()->type == LEADER) {
		ImGui::PushFont(mediumFont);
		if (ImGui::Button("New Project", ImVec2(150,0))) {
			ImGui::OpenPopup("New Project");
		}
		ImGui::PopFont();
		/*for (int i = 0; i < gProject.GetProjects()->at(0).users.size(); i++) {
			MessageBoxA(0, gProject.GetProjects()->at(0).users[i].c_str(), 0, 0);
		}*/

		NewProject();
	}

	ImGui::BeginChild("Projects", ImVec2(0, 0), true);
	int max = (int)(ImGui::GetWindowSize().x - 16.0f) / 300;

	for (int i = 0; i < gProject.GetProjects()->size(); ++i) {
		for (auto it : gProject.GetProjects()->at(i).users) {
			if (it == gUser.GetMyAcc()->name) {
				string label = gProject.GetProjects()->at(i).project_name + "\nStart day: " + gDate.DateToString(gProject.GetProjects()->at(i).start);
				ImGui::Button(label.c_str(), ImVec2(300, 200));
				if (ImGui::IsItemClicked(0)) {
					gProject.idProjectSelected = i;
					this->bDrawFlowGraph = true;
				}
				else if (ImGui::IsItemClicked(1)) {
					if (gUser.GetMyAcc()->type == LEADER) {
						gProject.idProjectSelected = i;
						ImGui::OpenPopup("Project Option");
					}
				}
				if (i + 1 < max)
					ImGui::SameLine();
				if ((i + 1) % max != 0)
					ImGui::SameLine();
				break;
			}
		}


		/*for (auto it:  gProject.GetProjects()->at(i).users) {
			MessageBoxA(0, it, 0, 0);
		}*/
	}
	if (ImGui::BeginPopup("Project Option"))
	{
		ImGui::MenuItem("Edit Project");
		if (ImGui::IsItemClicked()) {
			//ImGui::CloseCurrentPopup();
			ImGui::OpenPopup("Edit Project");
		}

		ImGui::MenuItem("Remove Project");
		if (ImGui::IsItemClicked()) {
			gProject.GetProjects()->erase(gProject.GetProjects()->begin() + gProject.idProjectSelected, gProject.GetProjects()->begin() + gProject.idProjectSelected + 1);
			gProject.idProjectSelected = -1;
			ImGui::CloseCurrentPopup();
			gProject.SaveProject();
		}
	}

	EditProject();

	ImGui::EndChild();
}

void Interface::NewProject() {
	ImGui::PushFont(mediumFont);
	ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiCond_Appearing);
	ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.0f);
	if (ImGui::BeginPopupModal("New Project", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize))
	{
		static char projectname[1024] = "";
		static vector<const char*> cur_user({ gUser.GetMyAcc()->name.c_str() });
		static int item_cur_user = 0, item_user = 0;

		ImGui::Text("Project Name:");
		ImGui::PushItemWidth(300);
		ImGui::InputText("##projectname", projectname, IM_ARRAYSIZE(projectname));

		static int s_day;
		static int s_month;
		static int s_year;

		if (!gDate.bGetCurDate) {
			s_day = gDate.GetCurrentDate().day - 1;
			s_month = gDate.GetCurrentDate().month - 1;
			s_year = gDate.GetCurrentDate().year - 2023;
			gDate.bGetCurDate = true;
		}




		ImGui::Text("Start day:");
		ImGui::PushItemWidth(90);
		if (s_month + 1 == 2) {
			if (gDate.isLeapYear(s_year + 2023)) {
				if (s_day > 28) s_day = 0;

				ImGui::Combo("##StartDay", &s_day, gDate.day_29, IM_ARRAYSIZE(gDate.day_29));
			}
			else {
				if (s_day > 27) s_day = 0;
				ImGui::Combo("##StartDay", &s_day, gDate.day_28, IM_ARRAYSIZE(gDate.day_28));
			}
		}
		else if (s_month + 1 == 4 || s_month + 1 == 6 || s_month + 1 == 9 || s_month + 1 == 11) {
			ImGui::Combo("##StartDay", &s_day, gDate.day_30, IM_ARRAYSIZE(gDate.day_30));
		}
		else {
			ImGui::Combo("##StartDay", &s_day, gDate.day_31, IM_ARRAYSIZE(gDate.day_31));
		}

		ImGui::SameLine();
		ImGui::Combo("##StartMonth", &s_month, gDate.month, IM_ARRAYSIZE(gDate.month));
		ImGui::SameLine();
		ImGui::Combo("##StartYear", &s_year, gDate.year, IM_ARRAYSIZE(gDate.year));

		ImGui::Spacing();


		ImGui::BeginChild("##currentuser", ImVec2(ImGui::GetWindowSize().x / 2 - 6.0f, 214), true);
		ImGui::Text("Current Users:");
		ImGui::PushItemWidth(ImGui::GetWindowSize().x - 16.0f);
		ImGui::ListBox("##cur_users", &item_cur_user, cur_user.data(), cur_user.size(), 7);
		if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
			if (item_cur_user != 0)
				cur_user.erase(cur_user.begin() + item_cur_user, cur_user.begin() + item_cur_user + 1);
		ImGui::EndChild();

		ImGui::SameLine();
		ImGui::BeginChild("##Users:", ImVec2(0, 214), true);
		ImGui::Text("Users");
		vector<const char*> vec;

		for (int i = 0; i < gUser.GetUsers()->size(); i++) {
			bool find = false;
			for (int j = 0; j < cur_user.size(); j++) {
				if (gUser.GetUsers()->at(i).name == string(cur_user[j])) {
					find = true;
					break;
				}
			}
			if (!find) {
				vec.push_back(gUser.GetUsers()->at(i).name.c_str());
			}
		}

		ImGui::PushItemWidth(ImGui::GetWindowSize().x - 16.0f);
		ImGui::ListBox("##users", &item_user, vec.data(), vec.size(), 7);
		if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
			cur_user.push_back(vec[item_user]);

		ImGui::EndChild();
		ImGui::Spacing();
		ImGui::SetCursorPosX(ImGui::GetWindowSize().x / 2 - 150.0f - 6.0f);
		if (ImGui::Button("Add", ImVec2(150, 0))) {
			if (strlen(projectname) > 0) {
				sProject project{ projectname, sDate{ s_day + 1, s_month + 1, s_year + 2023 } };

				for (int i = 0; i < cur_user.size(); i++) {
					project.users.push_back(cur_user.at(i));
				}
				project.scrolling = ImVec2(0.0f, 0.0f);
				project.scale = 1.0f;
				project.targetScale = 1.0f;
				project.max_scale = 0.1f;
				project.min_scale = 2.0f;
				project.scaleLerp = 0.1f;
				project.newGridSize = 32.0f;
				project.curGridSize = 32.0f;
				gProject.AddProject(project);
				projectname[0] = '\0';
				item_cur_user = 0;
				item_user = 0;
				cur_user.clear();
				gProject.SaveProject();
				ImGui::CloseCurrentPopup();
			}
		}

		ImGui::SameLine();

		if (ImGui::Button("Cancel", ImVec2(150, 0))) {
			projectname[0] = '\0';
			item_cur_user = 0;
			item_user = 0;
			cur_user.clear();
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();

	ImGui::PopFont();
}

void Interface::EditProject() {
	ImGui::PushFont(mediumFont);
	ImGui::SetNextWindowSize(ImVec2(600, 330), ImGuiCond_Appearing);
	ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.0f);
	if (ImGui::BeginPopupModal("Edit Project", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize))
	{
		static char projectname[1024] = "";
		static bool get = false;
		static vector<const char*> cur_user;
		if (!get) {
			for (int i = 0; i < gProject.GetProjectSelectedUser()->size(); i++) {
				//MessageBoxA(0, gProject.GetProjectSelectedUser()[i].c_str(), 0, 0);
				cur_user.push_back(gProject.GetProjectSelectedUser()->at(i).data());
			}
			get = true;
		}
		static int item_cur_user = 0, item_user = 0;
		strncpy(projectname, gProject.GetProjects()->at(gProject.idProjectSelected).project_name.c_str(), sizeof(projectname));

		ImGui::Text("Project Name");
		ImGui::SameLine();
		ImGui::PushItemWidth(300);
		if (ImGui::InputText("##projectname", projectname, IM_ARRAYSIZE(projectname)))
			gProject.GetProjects()->at(gProject.idProjectSelected).project_name = string(projectname);

		ImGui::Spacing();


		ImGui::BeginChild("##currentuser", ImVec2(ImGui::GetWindowSize().x / 2 - 6.0f, 214), true);

		ImGui::Text("Current Users:");
		ImGui::PushItemWidth(ImGui::GetWindowSize().x - 16.0f);
		ImGui::ListBox("##cur_users", &item_cur_user, cur_user.data()
			, cur_user.size(), 7);
		if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
			if (item_cur_user != 0)
				cur_user.erase(cur_user.begin() + item_cur_user, cur_user.begin() + item_cur_user + 1);

		ImGui::EndChild();

		ImGui::SameLine();
		ImGui::BeginChild("##Users:", ImVec2(0, 214), true);

		ImGui::Text("Users");
		vector<const char*> vec;
		for (int i = 0; i < gUser.GetUsers()->size(); i++) {
			bool find = false;
			for (int j = 0; j < cur_user.size(); j++) {
				if (gUser.GetUsers()->at(i).name == string(cur_user[j])) {
					find = true;
					break;
				}
			}
			if (!find) {
				vec.push_back(gUser.GetUsers()->at(i).name.c_str());
			}
		}
		ImGui::PushItemWidth(ImGui::GetWindowSize().x - 16.0f);
		ImGui::ListBox("##users", &item_user, vec.data(), vec.size(), 7);
		if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
			cur_user.push_back(vec[item_user]);

		ImGui::EndChild();

		ImGui::Spacing();

		ImGui::SetCursorPosX(ImGui::GetWindowSize().x / 2 - 75.0f);

		if (ImGui::Button("Close", ImVec2(150, 0))) {
			vector<string> tmp;
			for (int i = 0; i < cur_user.size(); i++) {
				//MessageBoxA(0, cur_user.at(i), 0, 0);
				tmp.push_back(cur_user[i]);
			}
			*gProject.GetProjectSelectedUser() = tmp;
			cur_user.clear();
			get = false;
			projectname[0] = '\0';
			item_cur_user = 0;
			item_user = 0;
			//cur_user.clear();
			gProject.idProjectSelected = -1;
			gProject.SaveProject();
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
	ImGui::PopFont();
}

void Interface::DrawFlowGraph() {
	ImGui::PushFont(mediumFont);
	if (ImGui::Button("Back", ImVec2(150,0))) {
		gProject.idProjectSelected = -1;
		bDrawFlowGraph = false;
	}
	if (!bDrawFlowGraph) return;
	if (gUser.GetMyAcc()->type == LEADER) {
		ImGui::SameLine();
		if (ImGui::Button("Save Project", ImVec2(150, 0))) {
			gProject.SaveProject();
		}
	}
	ImGui::SameLine();
	if (ImGui::Button("Gantt Chart", ImVec2(150, 0))) {
		gGraph.GraphProcess();
		ImGui::OpenPopup("Gantt Chart");
	}
	ImGui::PopFont();

	gGantt.DrawGanttChart();

	ImGui::BeginChild("##flowgraph", ImVec2(0, 0), true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
	// Using InvisibleButton() as a convenience 1) it will advance the layout cursor and 2) allows us to use IsItemHovered()/IsItemActive()
	canvas_p0 = ImGui::GetCursorScreenPos();      // ImDrawList API uses screen coordinates!
	canvas_sz = ImGui::GetContentRegionAvail();   // Resize canvas to what's available
	if (canvas_sz.x < 50.0f) canvas_sz.x = 50.0f;
	if (canvas_sz.y < 50.0f) canvas_sz.y = 50.0f;
	canvas_p1 = canvas_p0 + canvas_sz;

	// Draw border and background color
	ImGuiIO& io = ImGui::GetIO();
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	draw_list->AddRectFilled(canvas_p0, canvas_p1, IM_COL32(60, 60, 70, 200));
	//draw_list->AddRect(canvas_p0, canvas_p1, IM_COL32(255, 255, 255, 255));
	origin = ImVec2(canvas_p0.x + gProject.GetProjectSelected()->scrolling.x, canvas_p0.y + gProject.GetProjectSelected()->scrolling.y); // Lock scrolled origin
	mouse_pos_in_canvas = ImVec2(io.MousePos.x - origin.x, io.MousePos.y - origin.y);

	// This will catch our interactions
	ImGui::InvisibleButton("canvas", canvas_sz, ImGuiButtonFlags_MouseButtonLeft | ImGuiButtonFlags_MouseButtonRight);
	const bool is_hovered = ImGui::IsItemHovered(); // Hovered
	const bool is_active = ImGui::IsItemActive();   // Held

	// Drag canvas
	if (is_active && ImGui::IsMouseDragging(ImGuiMouseButton_Right, -1.0f))
	{
		gProject.GetProjectSelected()->scrolling.x += io.MouseDelta.x;
		gProject.GetProjectSelected()->scrolling.y += io.MouseDelta.y;
		//gProject.SaveProject();
	}

	// Zoomwheel
	if (is_hovered) {
		// Update the target zoom level based on the scroll delta
		gProject.GetProjectSelected()->targetScale -= ImGui::GetIO().MouseWheel * 0.1f;

		// Clamp the target zoom level to a reasonable range
		gProject.GetProjectSelected()->targetScale = ImClamp(gProject.GetProjectSelected()->targetScale, gProject.GetProjectSelected()->max_scale, gProject.GetProjectSelected()->min_scale);

		// Interpolate the current zoom level towards the target level
		gProject.GetProjectSelected()->scale = ImLerp(gProject.GetProjectSelected()->scale, gProject.GetProjectSelected()->targetScale, gProject.GetProjectSelected()->scaleLerp);

		// Calculate the size of the grid cells based on the current zoom level
		gProject.GetProjectSelected()->newGridSize = 32.0f / gProject.GetProjectSelected()->scale;

		gProject.GetProjectSelected()->scrolling.x -= mouse_pos_in_canvas.x * ((gProject.GetProjectSelected()->newGridSize / gProject.GetProjectSelected()->curGridSize) - 1.f);
		gProject.GetProjectSelected()->scrolling.y -= mouse_pos_in_canvas.y * ((gProject.GetProjectSelected()->newGridSize / gProject.GetProjectSelected()->curGridSize) - 1.f);
		gFlowGraph.ScaleNodePos(((gProject.GetProjectSelected()->newGridSize / gProject.GetProjectSelected()->curGridSize) - 1.f));

		gProject.GetProjectSelected()->curGridSize = gProject.GetProjectSelected()->newGridSize;
		//gProject.SaveProject();
		/*gFlowGraph.GetIDNodeSelecting(mouse_pos_in_canvas, scale);
		gFlowGraph.GetIDEdgeSelecting();*/

		if (gUser.GetMyAcc()->type == LEADER)
			if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
				if (!gFlowGraph.bAddTask && !gFlowGraph.IsMousePosInTaskPos()) {
					gFlowGraph.mouse_pos_in_canvas_bakup = mouse_pos_in_canvas;
					ImGui::OpenPopup("Add Task");
					gFlowGraph.bAddTask = true;
				}
			}

		gFlowGraph.GetIDNodeSelecting(gProject.GetProjectSelected()->scale);
		if (gUser.GetMyAcc()->type == LEADER)
			gFlowGraph.GetIDEdgeSelecting();
		/*else if (ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
		gFlowGraph.GetIDNodeSelecting();
		if (!gFlowGraph.bMoveNode) {
		gFlowGraph.GetIDNodeSelecting();
		if (gFlowGraph.idNodeSelected != -1) {
		gFlowGraph.pos_bakup = ImGui::GetMousePos() - gFlowGraph.node[gFlowGraph.idNodeSelected].frame_p1;
		gFlowGraph.bMoveNode = true;
		}
		}
		}*/
		//gFlowGraph.GetIDNodeSelecting(scale);
		/*else if (ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
		if (!gFlowGraph.bMoveNode) {
		gFlowGraph.GetIDNodeSelecting(scale);
		}
		}
		else if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
		if (!gFlowGraph.bTaskOption) {
		gFlowGraph.bTaskOption = true;
		gFlowGraph.GetIDNodeSelecting(scale);
		}
		}*/
	}
	if (gUser.GetMyAcc()->type == LEADER) {
		gFlowGraph.AddTask();
		gFlowGraph.MoveNode(mouse_pos_in_canvas);
		gFlowGraph.AddLine(draw_list, gProject.GetProjectSelected()->scale);
		gFlowGraph.DeleteEdge();
	}

	gFlowGraph.TaskOptions();
	/*gFlowGraph.TaskOptions();*/

	//if (gFlowGraph.idNodeSelected == -1 && !gFlowGraph.bNodeOptions && !gFlowGraph.bDeleleEdge) {
	//	ImVec2 drag_delta = ImGui::GetMouseDragDelta(ImGuiMouseButton_Right);
	//	if (drag_delta.x == 0.0f && drag_delta.y == 0.0f)
	//		ImGui::OpenPopupOnItemClick("Add Task", ImGuiPopupFlags_MouseButtonRight);
	//	if (ImGui::BeginPopup("Add Task"))
	//	{
	//		ImVec2 tmp = mouse_pos_in_canvas;
	//		if (ImGui::MenuItem("Add Task", NULL, false)) {
	//			gFlowGraph.AddNode(mouse_pos_in_canvas);
	//		}
	//		ImGui::EndPopup();
	//	}
	//}

	/*gFlowGraph.DeleteNode();
	gFlowGraph.DeleteEdge();*/

	ImGui::SetWindowFontScale(1.0f / gProject.GetProjectSelected()->scale);
	// Draw grid and content in Canvas
	draw_list->PushClipRect(canvas_p0, canvas_p1, true);

	draw_list->AddLine(origin + ImVec2(0, gProject.GetProjectSelected()->newGridSize), origin + ImVec2(0, -gProject.GetProjectSelected()->newGridSize), IM_COL32(255, 255, 255, 255), 1.0f);
	draw_list->AddLine(origin + ImVec2(-gProject.GetProjectSelected()->newGridSize, 0), origin + ImVec2(gProject.GetProjectSelected()->newGridSize, 0), IM_COL32(255, 255, 255, 255), 1.0f);

	for (float x = fmodf(gProject.GetProjectSelected()->scrolling.x, gProject.GetProjectSelected()->newGridSize); x < canvas_sz.x; x += gProject.GetProjectSelected()->newGridSize)
		draw_list->AddLine(ImVec2(canvas_p0.x + x, canvas_p0.y), ImVec2(canvas_p0.x + x, canvas_p1.y), IM_COL32(120, 120, 120, 40));
	for (float y = fmodf(gProject.GetProjectSelected()->scrolling.y, gProject.GetProjectSelected()->newGridSize); y < canvas_sz.y; y += gProject.GetProjectSelected()->newGridSize)
		draw_list->AddLine(ImVec2(canvas_p0.x, canvas_p0.y + y), ImVec2(canvas_p1.x, canvas_p0.y + y), IM_COL32(120, 120, 120, 40));
	gFlowGraph.DrawNode(draw_list, origin, mouse_pos_in_canvas, gProject.GetProjectSelected()->scale);
	gFlowGraph.DrawEdge(draw_list, gProject.GetProjectSelected()->scale);


	draw_list->PopClipRect();

	ImGui::SetWindowFontScale(1.0f);

	ImGui::EndChild();
	//gGraph.GraphProcess();
}

bool Interface::CheckMouseHover(ImVec2 mousePos, ImVec2 pos1, ImVec2 pos2) {
	return mousePos.x >= pos1.x && mousePos.x <= pos2.x && mousePos.y >= pos1.y && mousePos.y <= pos2.y;
}

void Interface::HelpMarker(const char* desc)
{
	//ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort) && ImGui::BeginTooltip())
	{
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}