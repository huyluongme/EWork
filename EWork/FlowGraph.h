#pragma once

#include "stdafx.h"

typedef struct {
	ImVec2 pos;
	std::string task;
	std::string assignment;
	sDate start, end;
	bool status;
	int duration;
	ImVec2 frame_p1, frame_p2;
	ImVec2 input_p, output_p;
	ImVec4 header_color;
	bool extend;
	vector<string> cmt;
}sNode;

typedef struct {
	int node_a, node_b;
	ImVec2 p1, p2, p3, p4;
}sEdge;

class FlowGraph
{
public:
	ImVec4 saved_palette[32] = { ImVec4(0.800f, 0.160f, 0.160, 1.000f),
		ImVec4(0.800f, 0.284f, 0.160, 1.000f),
		ImVec4(0.800f, 0.408f, 0.160, 1.000f),
		ImVec4(0.800f, 0.532f, 0.160, 1.000f),
		ImVec4(0.800f, 0.655f, 0.160, 1.000f),
		ImVec4(0.800f, 0.779f, 0.160, 1.000f),
		ImVec4(0.697f, 0.800f, 0.160, 1.000f),
		ImVec4(0.573f, 0.800f, 0.160, 1.000f),
		ImVec4(0.449f, 0.800f, 0.160, 1.000f),
		ImVec4(0.325f, 0.800f, 0.160, 1.000f),
		ImVec4(0.201f, 0.800f, 0.160, 1.000f),
		ImVec4(0.160f, 0.800f, 0.243, 1.000f),
		ImVec4(0.160f, 0.800f, 0.366, 1.000f),
		ImVec4(0.160f, 0.800f, 0.490, 1.000f),
		ImVec4(0.160f, 0.800f, 0.614, 1.000f),
		ImVec4(0.160f, 0.800f, 0.738, 1.000f),
		ImVec4(0.160f, 0.738f, 0.800, 1.000f),
		ImVec4(0.160f, 0.614f, 0.800, 1.000f),
		ImVec4(0.160f, 0.490f, 0.800, 1.000f),
		ImVec4(0.160f, 0.366f, 0.800, 1.000f),
		ImVec4(0.160f, 0.243f, 0.800, 1.000f),
		ImVec4(0.201f, 0.160f, 0.800, 1.000f),
		ImVec4(0.325f, 0.160f, 0.800, 1.000f),
		ImVec4(0.449f, 0.160f, 0.800, 1.000f),
		ImVec4(0.573f, 0.160f, 0.800, 1.000f),
		ImVec4(0.697f, 0.160f, 0.800, 1.000f),
		ImVec4(0.800f, 0.160f, 0.779, 1.000f),
		ImVec4(0.800f, 0.160f, 0.655, 1.000f),
		ImVec4(0.800f, 0.160f, 0.532, 1.000f),
		ImVec4(0.800f, 0.160f, 0.408, 1.000f),
		ImVec4(0.800f, 0.160f, 0.284, 1.000f),
		ImVec4(0.800f, 0.160f, 0.160, 1.000f) };

	int idNodeSelected = -1;
	int idEdgeSelected = -1;
	ImVec2 pos_bakup;
	bool bMoveNode = false;
	bool bAddLine = false;

	bool bDeleleEdge = false;
	bool bGetCurDateID = false;
	bool bAddTask = false;
	ImVec2 mouse_pos_in_canvas_bakup;

	bool bTaskOption = false;

	void DrawNode(ImDrawList* draw_list, ImVec2 origin, ImVec2 mousePos, float scale);
	void ScaleNodePos(float scale);

	void GetIDNodeSelecting(float scale);
	void GetIDEdgeSelecting();
	void AddNode(ImVec2 mouse_pos);
	void MoveNode(ImVec2 new_pos);

	void DrawEdge(ImDrawList* draw_list, float scale);
	void AddLine(ImDrawList* draw_list, float scale);
	void DeleteNode();
	void DeleteEdge();

	void AddTask();

	bool IsMousePosInTaskPos();
	bool IsConnectExist(int in, int out);
	void TaskOptions();
	void ShowMore();
};

extern FlowGraph gFlowGraph;