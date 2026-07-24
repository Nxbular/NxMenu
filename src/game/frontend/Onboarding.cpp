#include "Onboarding.hpp"
#include "GUI.hpp"
#include "core/commands/Commands.hpp"
#include "core/commands/BoolCommand.hpp"
#include "game/backend/AnticheatBypass.hpp"
#include "game/pointers/Pointers.hpp"
#include <shellapi.h>

namespace YimMenu
{
	static BoolCommand _OnboardingComplete{"$onboardingcomplete", "", ""};

	void ProcessOnboarding()
	{
		if (_OnboardingComplete.GetState())
			return;

		static bool ensure_popup_open = [] {
			ImGui::OpenPopup("Welcome to NxMenu");
			GUI::SetOnboarding(true);
			return true;
		}();

		const auto window_size = ImVec2{700, 400};
		const auto window_position = ImVec2{(*Pointers.ScreenResX - window_size.x) / 2, (*Pointers.ScreenResY - window_size.y) / 2};

		ImGui::SetNextWindowSize(window_size, ImGuiCond_Once);
		ImGui::SetNextWindowPos(window_position, ImGuiCond_Once);

		if (ImGui::BeginPopupModal("Welcome to NxMenu", nullptr, ImGuiWindowFlags_NoSavedSettings))
		{
			ImGui::TextWrapped("Welcome to NxMenu, a personal fork of YimMenu by github.com/Nxbular!");
			ImGui::Separator();
			ImGui::TextWrapped("You can press INSERT or Ctrl+\\ to open the menu.");
			ImGui::TextWrapped("NxMenu is intended to be used in Story Mode. For Online play, use the Network tab to join sessions.");
			
			if (ImGui::Button("Open GitHub"))
			{
				ShellExecuteA(NULL, "open", "https://github.com/Nxbular/NxMenu", NULL, NULL, SW_SHOWNORMAL);
			}
			
			ImGui::TextWrapped("Have fun!");
			if (ImGui::Button("Close"))
			{
				_OnboardingComplete.SetState(true);
				GUI::SetOnboarding(false);
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
	}
}