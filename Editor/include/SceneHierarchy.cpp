#include "SceneHierarchy.h"


#include "imgui.h"

void SceneHierarchy::update() {

	ImGui::Begin("Hierarchy");
	{

		contextMenu();

		buildTree();


	} ImGui::End();

}

void SceneHierarchy::contextMenu() {

	if (ImGui::BeginPopupContextWindow("Create")) {

		if (ImGui::Selectable("Empty Object"))
			createEmpty();

		ImGui::EndPopup();
	}

}

void SceneHierarchy::buildTree() {

	int id = 0;
	for (auto& obj : gameObjects) {

		ImGui::PushID(id);
		if (ImGui::Selectable(obj.label.c_str())) {
			
			pSelectedObject = &obj;
			notifyAll();

		}
		objectContextMenu();

		ImGui::PopID();
		id++;


	}

}

void SceneHierarchy::objectContextMenu() {

	if (ImGui::BeginPopupContextItem("ObjectMenu")) {
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(5, 5));

		ImGui::Selectable("Copy");
		ImGui::Selectable("Paste");
		if (ImGui::Selectable("Delete")) {
			if (pSelectedObject != nullptr)	{
				auto pos = std::find(gameObjects.begin(), gameObjects.end(), *pSelectedObject);
				gameObjects.erase(pos);
				pSelectedObject = &(*(pos - 1));
				notifyAll();
			}
		}

		ImGui::Separator();

		ImGui::Selectable("Rename");
		ImGui::Selectable("Duplicate");


		ImGui::Separator();

		buildComponentList();


		ImGui::PopStyleVar();
		ImGui::EndPopup();
	}

}

void SceneHierarchy::buildComponentList() {

	if (ImGui::BeginMenu("Add component")) {

		if (ImGui::MenuItem("Transform"))
			addComponent<TransformComponent>();

		if (ImGui::MenuItem("Sprite"))
			addComponent<SpriteComponent>();

		if (ImGui::MenuItem("Motion"))
			addComponent<MotionComponent>();


		ImGui::EndMenu();
	}

}


void SceneHierarchy::createEmpty() {
	gameObjects.emplace_back(SceneManager::createEntity(), "Empty Object");
	pSelectedObject = &gameObjects.back();

	addComponent<TransformComponent>();
	addComponent<SpriteComponent>();

	notifyAll();
}
