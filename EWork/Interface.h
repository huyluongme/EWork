#pragma once

#include "stdafx.h"

static inline ImVec2  operator*(const ImVec2& lhs, const float rhs) { return ImVec2(lhs.x * rhs, lhs.y * rhs); }
static inline ImVec2  operator/(const ImVec2& lhs, const float rhs) { return ImVec2(lhs.x / rhs, lhs.y / rhs); }
static inline ImVec2  operator+(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y); }
static inline ImVec2  operator-(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y); }
static inline ImVec2  operator*(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x * rhs.x, lhs.y * rhs.y); }
static inline ImVec2  operator/(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x / rhs.x, lhs.y / rhs.y); }
static inline ImVec2& operator*=(ImVec2& lhs, const float rhs) { lhs.x *= rhs; lhs.y *= rhs; return lhs; }
static inline ImVec2& operator/=(ImVec2& lhs, const float rhs) { lhs.x /= rhs; lhs.y /= rhs; return lhs; }
static inline ImVec2& operator+=(ImVec2& lhs, const ImVec2& rhs) { lhs.x += rhs.x; lhs.y += rhs.y; return lhs; }
static inline ImVec2& operator-=(ImVec2& lhs, const ImVec2& rhs) { lhs.x -= rhs.x; lhs.y -= rhs.y; return lhs; }
static inline ImVec2& operator*=(ImVec2& lhs, const ImVec2& rhs) { lhs.x *= rhs.x; lhs.y *= rhs.y; return lhs; }
static inline ImVec2& operator/=(ImVec2& lhs, const ImVec2& rhs) { lhs.x /= rhs.x; lhs.y /= rhs.y; return lhs; }


class Interface
{
	bool bDrawFlowGraph = false;
public:

	ImVec2 canvas_p0, canvas_sz, canvas_p1;
	ImVec2 origin, mouse_pos_in_canvas;
	//ImVec2 scrolling = ImVec2(0.0f, 0.0f);
	//float GRID_STEP = 16.0f;
	//float canvas_scale = 50.0f;

	//float scale = 1.0f;
	//float targetScale = 1.0f;
	//float max_scale = 0.1f, min_scale = 2.0f;
	/*float scaleLerp = 0.1f;
	float newGridSize = 32.0f;
	float curGridSize = 32.0f;*/

	ImFont* bigFont, *mediumFont, *smallFont;

	void DrawInterface();
	void Login();
	void DrawInterfaceLeft();
	void DrawInterfaceRight();
	void DrawProjects();
	void NewProject();
	void EditProject();
	void DrawFlowGraph();
	bool CheckMouseHover(ImVec2 mousePos, ImVec2 pos1, ImVec2 pos2);
	void HelpMarker(const char* desc);
};

extern Interface gInterface;

