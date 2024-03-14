#include "Inspector.h"

#include "imgui.h"
#include "imgui_stdlib.h"
#include "ImGuiFileDialog.h"

void Inspector::update() {

	ImGui::Begin("Inspector"); {

		if (obj == nullptr) {
			ImGui::End();
			return;
		}

		ImGui::InputText("Name", obj->label.data(), ImGuiInputTextFlags_EnterReturnsTrue);

		if (obj->hasComponent<TransformComponent>())
			transformView();

		if (obj->hasComponent<SpriteComponent>())
			spriteView();


	} ImGui::End();
}

void Inspector::transformView() {

	TransformComponent* component = SceneManager::get<TransformComponent>(obj->entity);

	position[0] = component->transform[3][0];
	position[1] = component->transform[3][1];
	

	bool open = true;
	if (ImGui::CollapsingHeader("Transform", &open, ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap)) {

		if (ImGui::DragFloat2("Position", position, 0.01f))
			component->translate({ position[0], position[1] });

		if (ImGui::DragFloat("Rotation", &rotation, 0.01f, 0.1f, 360.0f)) {
			component->rotate(rotation, { 0, 1 });
		}

		if (ImGui::DragFloat2("Size", size, 0.01f, 0.0f, 100.0f)) {
			component->scale({ size[0], size[1] });

		}

	}

	if (!open)
		obj->removeComponent<TransformComponent>();

}

void Inspector::spriteView() {

	SpriteComponent* component = SceneManager::get<SpriteComponent>(obj->entity);

	bool open = true;
	if (ImGui::CollapsingHeader("Sprite", &open, ImGuiTreeNodeFlags_DefaultOpen)) {

		if (ImGui::ColorPicker3("Color filer", color)) {
			
			component->color.x = color[0];
			component->color.y = color[1];
			component->color.z = color[2];
		}

		ImGui::Spacing();

		if (ImGui::Button("Load texture")) {
			IGFD::FileDialogConfig config;
			config.path = "F:\\dev\\ClosedGL\\ClosedGL\\assets\\sprites\\Minecraft";
			ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".png", config);
		}

		if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) {
			if (ImGuiFileDialog::Instance()->IsOk()) {
				std::string file = ImGuiFileDialog::Instance()->GetFilePathName();

				Texture& texture = TextureManager::create(file);
				component->addTexture(&texture);

			}

			ImGuiFileDialog::Instance()->Close();
		}




	}



	if (!open) {
		obj->removeComponent<SpriteComponent>();
		TextureManager::remove(*component->texture);
	}

}
