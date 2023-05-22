#pragma once

#include "stdafx.h"

typedef struct {
	string project_name;
	sDate start;
	vector<string> users;
	ImVec2 scrolling;
	float scale;
	float targetScale;
	float max_scale;
	float min_scale;
	float scaleLerp;
	float newGridSize;
	float curGridSize;
	vector<sNode> task;
	vector<sEdge> edges;
}sProject;

class Project
{
	std::filesystem::file_time_type original_time;
	fs::path original_file_path = "Data\\projects.json";
	vector<sProject> projects;
public:
	bool first_load_project = false;
	int idProjectSelected = -1;

	void tmpProject();
	void LoadProjectFromJson();
	vector<sProject> *GetProjects();
	sProject* GetProjectSelected();
	vector<string>* GetProjectSelectedUser();
	void AddProject(sProject project);
	void SaveProject();
	void LoadProject();
	void LoadProjectRealTime();
};

extern Project gProject;