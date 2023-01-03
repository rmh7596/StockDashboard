#include "StockUI.h"
#include "imgui.h"
#include <iostream>
#include <string.h>

using namespace std;

Stock s;

void StockUI::RenderUI() {
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
	RenderStockInput();
}

void StockUI::RenderStockInput() {
	ImGui::Begin("Symbol Lookup");
	static char symbolBuf[6]; // 5 chars with null
	if (ImGui::InputText("##", symbolBuf, IM_ARRAYSIZE(symbolBuf), ImGuiInputTextFlags_CharsUppercase | ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll)) {
		s.getStockData(symbolBuf);
	}
	ImGui::SameLine();
	if (ImGui::Button("Submit")) {
		s.getStockData(symbolBuf);
	}

	ImGui::LabelText(to_string(s.getRegularMarketPrice()).c_str(), "Regular Market Price: ");
	ImGui::LabelText(to_string(s.getPreMarket()).c_str(), "Pre-Market: ");
	ImGui::LabelText(to_string(s.getPostMarket()).c_str(), "Post-Market: ");
	ImGui::LabelText(s.getMarketCap().c_str(), "Market Cap: ");
	ImGui::LabelText(s.getQuoteType().c_str(), "Quote Type: ");

	ImGui::End();
}