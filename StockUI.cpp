#include "StockUI.h"
#include "imgui.h"
#include <iostream>

using namespace std;

void StockUI::RenderUI() {
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
	RenderStockInput();
}

void StockUI::RenderStockInput() {
	ImGui::Begin("Symbol Lookup");
	static char symbolBuf[6];
	if (ImGui::InputText("##", symbolBuf, IM_ARRAYSIZE(symbolBuf), ImGuiInputTextFlags_CharsUppercase | ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll)) {
		cout << symbolBuf << endl;
	}
	ImGui::SameLine();
	if (ImGui::Button("Submit")) {
		cout << symbolBuf << endl;
	}

	// Need to create better method in Stock for handling ticker

	ImGui::End();
}