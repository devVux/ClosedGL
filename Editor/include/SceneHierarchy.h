#pragma once

#include "GameObject.h"
#include "Utils.h"
#include "MyObs.h"

using Node = Tree::TreeNode<GameObject>;



class SceneHierarchy: public Subject<SceneHierarchy> {

	public:

		~SceneHierarchy() {

		}

		void update();


		virtual void notifyAll() override {
			for (auto& observer : mObservers)
				observer->notify(*this);
		}

		GameObject* selectedObject() const { return pSelectedObject; }


	private:


		void contextMenu();

		void buildTree();

		void objectContextMenu();

		void buildComponentList();

	private:

		void createEmpty();

		template <class T>
		void addComponent() {
			if (!SceneManager::hasComponent<T>(pSelectedObject->entity)) {
				TRACE("Adding {}Component to '{}'", T::type(), pSelectedObject->label);
				pSelectedObject->addComponent<T>();
			}
		}

		std::vector<GameObject> gameObjects;
		GameObject* pSelectedObject { nullptr };

};

