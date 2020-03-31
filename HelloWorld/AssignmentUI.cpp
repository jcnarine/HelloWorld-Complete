#include "AssignmentUI.h"

Selectable AssignmentUI::m_selectable= Selectable("Assignment UI");

void AssignmentUI::CreateTab(entt::registry* reg, Scene* scene)
{
	bool temp = false;

	if (ImGui::BeginTabItem(m_selectable.GetName().c_str(), m_selectable.GetSelected())) {

		temp = true;

		ImGui::EndTabItem();

	}

	if (temp)
		CreateEditor(reg, scene);
}

void AssignmentUI::CreateEditor(entt::registry* reg, Scene* scene)
{
	AssignmentScene* Activescene = (AssignmentScene*)scene;

	if (m_selectable.GetSelected()) {

		if (ImGui::Button("Set Luxray Animation", ImVec2(200.f, 20.f))) {
			
			auto& change = reg->get<AnimationController>(Activescene->GetPokemonCompanion());
			auto& sprite = reg->get<Sprite>(Activescene->GetPokemonCompanion());

			std::string filename = "Luxray.png";

			change.SetFileName(filename);;
			change.UpdateUVs();
			sprite.LoadSprite(filename, 18, 20, true, &change);

		} 

		if (ImGui::Button("Set Roserade Animation", ImVec2(200.f, 20.f))) {
			
			auto& change = reg->get<AnimationController>(Activescene->GetPokemonCompanion());
			auto& sprite = reg->get<Sprite>(Activescene->GetPokemonCompanion());

			std::string filename2 = "Roserade.png";
			change.SetFileName(filename2);
			change.UpdateUVs();
			sprite.LoadSprite(filename2, 16, 18, true, &change);

		}

		auto& Player = reg->get<Transform>(EntityIdentifier::MainPlayer());

		float PlayerPosition[] = {Player.GetPosition().x, Player.GetPosition().y, Player.GetPosition().z };

		ImGui::Text("Player Position");

		if (ImGui::SliderFloat("X", &PlayerPosition[0], -100.f, 100.f)) {
			Player.SetPositionX(PlayerPosition[0]);
		}
		if (ImGui::SliderFloat("Y", &PlayerPosition[1], -100.f, 100.f)) {
			Player.SetPositionY(PlayerPosition[1]);
		}
		if (ImGui::SliderFloat("Z", &PlayerPosition[2], -100.f, 100.f)) {
			Player.SetPositionZ(PlayerPosition[2]);
		}

		auto& tempCam = reg->get<Camera>(EntityIdentifier::MainCamera());
		float Rotation = tempCam.GetRotationAngleZ() * 360.f/ PI;

		ImGui::Text("Camera Rotation");

		if (ImGui::SliderFloat("Rotation", &Rotation, -360.f, 360.f)) {
			tempCam.SetRotationAngleZ(Rotation * PI / 360.f);
		}

		}
}

