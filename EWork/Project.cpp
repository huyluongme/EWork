#include "stdafx.h"
#include "Project.h"

Project gProject;

void Project::tmpProject() {
	if (this->projects.size() > 0) return;
	sProject project;
	project.project_name = "Create Web";
	project.start = sDate{ 12, 5, 2023 };
	project.users = { "Li Yeng", "Duk Hui", "user3" };
	project.scrolling = ImVec2(0.0f, 0.0f);
	project.scale = 1.0f;
	project.targetScale = 1.0f;
	project.max_scale = 0.1f;
	project.min_scale = 2.0f;
	project.scaleLerp = 0.1f;
	project.newGridSize = 32.0f;
	project.curGridSize = 32.0f;
	this->projects.push_back(project);
	this->idProjectSelected = 0;
}

void LoadProjectFromJson() {

}

vector<sProject>* Project::GetProjects() {
	return &projects;
}

sProject* Project::GetProjectSelected() {
	return &projects.at(idProjectSelected);
}


vector<string>* Project::GetProjectSelectedUser() {
	return &projects.at(idProjectSelected).users;
}


void Project::AddProject(sProject project) {
	projects.push_back(project);
}

void Project::SaveProject() {
	// Create a json array to hold the projects
	json project_array;

	// Add each project to the json array
	for (const auto& project : projects) {
		json project_json = {
			{"project_name", project.project_name},
			{"start", {
				{"day", project.start.day},
				{"month", project.start.month},
				{"year", project.start.year}
			}},
			{"users", project.users},
			{"scrolling", {
				{"x", project.scrolling.x},
				{"y", project.scrolling.y}
			}},
			{"scale", project.scale},
			{"targetScale", project.targetScale},
			{"max_scale", project.max_scale},
			{"min_scale", project.min_scale},
			{"scaleLerp", project.scaleLerp},
			{"newGridSize", project.newGridSize},
			{"curGridSize", project.curGridSize},
			{"task", json::array()},
			{"edges", json::array()}
		};

		// Add each task to the project's json object
		for (const auto& task : project.task) {
			json task_json = {
				{"pos", {
					{"x", task.pos.x},
					{"y", task.pos.y}
				}},
				{"task", task.task},
				{"assignment", task.assignment},
				{"start", {
					{"day", task.start.day},
					{"month", task.start.month},
					{"year", task.start.year}
				}},
				{"end", {
					{"day", task.end.day},
					{"month", task.end.month},
					{"year", task.end.year}
				}},
				{"status", task.status},
				{"duration", task.duration},
				{"frame_p1", {
					{"x", task.frame_p1.x},
					{"y", task.frame_p1.y}
				}},
				{"frame_p2", {
					{"x", task.frame_p2.x},
					{"y", task.frame_p2.y}
				}},
				{"input_p", {
					{"x", task.input_p.x},
					{"y", task.input_p.y}
				}},
				{"output_p", {
					{"x", task.output_p.x},
					{"y", task.output_p.y}
				}},
				{"header_color", {
					{"x", task.header_color.x},
					{"y", task.header_color.y},
					{"z", task.header_color.z},
					{"w", task.header_color.w}
				}},
				{"extend", task.extend},
				{"cmt", task.cmt}
			};

			project_json["task"].push_back(task_json);
		}

		// Add each edge to the project's json object
		for (const auto& edge : project.edges) {
			json edge_json = {
				{"node_a", edge.node_a},
				{"node_b", edge.node_b},
				{"p1", {
					{"x", edge.p1.x},
					{"y", edge.p1.y}
				}},
				{"p2", {
					{"x", edge.p2.x},
					{"y", edge.p2.y}
				}},
				{"p3", {
					{"x", edge.p3.x},
					{"y", edge.p3.y}
					  }},
			{"p4", {
				{"x", edge.p4.x},
				{"y", edge.p4.y}
			}}
			};

			project_json["edges"].push_back(edge_json);
		}

		project_array.push_back(project_json);
	}
	std::ofstream file(original_file_path);
	file << project_array.dump(4) << std::endl;
	file.close();
}

void Project::LoadProject() {
	std::ifstream file(original_file_path);

	json project_array;
	file >> project_array;
	file.close();

	projects.clear();

	for (const auto& project_json : project_array) {
		sProject project;

		if (project_json.contains("project_name"))
			project.project_name = project_json["project_name"];


		if (project_json.contains("start"))
			project.start = {
				project_json["start"]["day"],
				project_json["start"]["month"],
				project_json["start"]["year"]
		};


		if (project_json.contains("users")) {
			for (const auto& user : project_json["users"]) {
				//char* u = user.get<string>().c_str();
				project.users.push_back(user.get<std::string>());
			}

		}

		if (project_json.contains("scrolling"))
			project.scrolling = {
				project_json["scrolling"]["x"],
				project_json["scrolling"]["y"]
		};

		if (project_json.contains("scale"))
			project.scale = project_json["scale"];

		if (project_json.contains("targetScale"))
			project.targetScale = project_json["targetScale"];

		if (project_json.contains("max_scale"))
			project.max_scale = project_json["max_scale"];

		if (project_json.contains("min_scale"))
			project.min_scale = project_json["min_scale"];

		if (project_json.contains("scaleLerp"))
			project.scaleLerp = project_json["scaleLerp"];

		if (project_json.contains("newGridSize"))
			project.newGridSize = project_json["newGridSize"];

		if (project_json.contains("curGridSize"))
			project.curGridSize = project_json["curGridSize"];


		if (project_json.contains("task"))
			// Parse the task array and add each task to the project
			for (const auto& task_json : project_json["task"]) {
				sNode task;

				task.pos = {
					task_json["pos"]["x"],
					task_json["pos"]["y"]
				};
				task.task = task_json["task"];
				task.assignment = task_json["assignment"];
				task.start = {
					task_json["start"]["day"],
					task_json["start"]["month"],
					task_json["start"]["year"]
				};
				task.end = {
					task_json["end"]["day"],
					task_json["end"]["month"],
					task_json["end"]["year"]
				};
				task.status = task_json["status"];
				task.duration = task_json["duration"];
				task.frame_p1 = {
					task_json["frame_p1"]["x"],
					task_json["frame_p1"]["y"]
				};
				task.frame_p2 = {
					task_json["frame_p2"]["x"],
					task_json["frame_p2"]["y"]
				};
				task.input_p = {
					task_json["input_p"]["x"],
					task_json["input_p"]["y"]
				};
				task.output_p = {
					task_json["output_p"]["x"],
					task_json["output_p"]["y"]
				};
				task.header_color = {
					task_json["header_color"]["x"],
					task_json["header_color"]["y"],
					task_json["header_color"]["z"],
					task_json["header_color"]["w"]
				};
				task.extend = task_json["extend"];
				for (const auto& cmt : task_json["cmt"]) {
					task.cmt.push_back(cmt);
				}
				project.task.push_back(task);
			}

		if (project_json.contains("edges"))
			// Parse the edge array and add each edge to the project
			for (const auto& edge_json : project_json["edges"]) {
				sEdge edge;

				edge.node_a = edge_json["node_a"];
				edge.node_b = edge_json["node_b"];
				edge.p1 = {
				edge_json["p1"]["x"],
				edge_json["p1"]["y"]
				};
				edge.p2 = {
					edge_json["p2"]["x"],
					edge_json["p2"]["y"]
				};
				edge.p3 = {
					edge_json["p3"]["x"],
					edge_json["p3"]["y"]
				};
				edge.p4 = {
					edge_json["p4"]["x"],
					edge_json["p4"]["y"]
				};

				project.edges.push_back(edge);
			}

		projects.push_back(project);
		//MessageBoxA(0, to_string(projects.size()).c_str(), 0, 0);
	}

}

void Project::LoadProjectRealTime() {
	if (!first_load_project) {
		std::ifstream file(original_file_path);
		if (!file) return;
		LoadProject();
		original_time = fs::last_write_time(original_file_path);
		first_load_project = true;
	}
	else {
		std::ifstream file(original_file_path);
		if (!file) return;
		if (original_time < fs::last_write_time(original_file_path)) {
			LoadProject();
			original_time = fs::last_write_time(original_file_path);
		}
	}
	/*else {
		if (original_time < fs::last_write_time(original_file_path)) {
			LoadProject();
			original_time = fs::last_write_time(original_file_path);
		}
	}*/
}