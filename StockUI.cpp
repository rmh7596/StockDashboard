#include "StockUI.h"
#include "imgui.h"
#include "implot.h"
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
	if (ImGui::InputText("##", symbolBuf, IM_ARRAYSIZE(symbolBuf), ImGuiInputTextFlags_CharsUppercase | ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll) | ImGui::Button("Submit")) {
		s.getStockData(symbolBuf);
		if (s.getQuoteType() != "") { // Gather chart data only once
			string interval = "5m";
			string range = "1d";
			s.getStockChart(interval, range);
			s.computeChartBounds();
		}
	}
	ImGui::LabelText(to_string(s.getRegularMarketPrice()).c_str(), "Regular Market Price: ");
	ImGui::LabelText(to_string(s.getPreMarket()).c_str(), "Pre-Market: ");
	ImGui::LabelText(to_string(s.getPostMarket()).c_str(), "Post-Market: ");
	ImGui::LabelText(s.getMarketCap().c_str(), "Market Cap: ");
	ImGui::LabelText(s.getQuoteType().c_str(), "Quote Type: ");

	ImGui::End();
	RenderChart();
}

void StockUI::RenderChart() {
	ImGui::Begin("Graph");
	//if (s.getQuoteType() != "") {
	//	std::vector<float> prices = s.getPrices();
	//	float* a = &prices[0];
	//	// Render histogram
	//	//ImGui::PlotHistogram("Histogram", a, prices.size(), 0, NULL, s.getMinPrice(), s.getMaxPrice(), ImVec2(0, 80.0f));
	//	ImGui::PlotLines("Lines", a, prices.size());
	//}
	//ImGui::End();
	static float fill_ref = 0;
	static int shade_mode = 0;

	if (ImPlot::BeginPlot("Stock Prices")) {
		if (s.getQuoteType() != "") {
			std::vector<float> prices = s.getPrices();
			float* a = &prices[0];
			ImPlot::SetupAxes("Time", "Price");
			ImPlot::SetupAxesLimits(0, prices.size(), s.getMinPrice(), s.getMaxPrice(), ImPlotCond_Always);
			ImPlot::PlotLine(s.getTicker().c_str(), a, prices.size());
		}

		ImPlot::EndPlot();
	}

	ImGui::End();
}