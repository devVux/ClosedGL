#pragma once

#include "MyObs.h"
#include "SceneHierarchy.h"
#include "GameObject.h"

class Inspector: public Observer<SceneHierarchy> {

	public:
		
		void update();

		void notify(const SceneHierarchy& hierarchy) override {
			obj = hierarchy.selectedObject();
		}

		void transformView();
		
		void spriteView();

	private:

		float position[2] { 0 };
		float size[2] { 1 };
		float rotation { 0 };
		float color[3] { 255, 255, 255 };
		
		GameObject* obj { nullptr };
};
