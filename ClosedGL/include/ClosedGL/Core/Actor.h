#pragma once

#include "Timestep.h"

#include "ClosedGL/Renderer/Shader.h"
#include "ClosedGL/Renderer/Buffer.h"

#include "ClosedGL/Scene/Components.h"

class Actor {

	public:

		Actor(const char* name): mName(name) { }
		virtual ~Actor() {
			//while (!mComponents.empty()) {
			//	delete mComponents.back();
			//	mComponents.pop_back();
			//}
			delete pShader;
			delete pVertexArray;
		}

		virtual void update(Timestep ts) = 0;


		const Shader& shader() const { return *pShader; }
		const VertexArray& vertexArray() const { return *pVertexArray; }

		glm::mat4 model() const { return mModel; }
		void setModel(glm::mat4 model) { mModel = model; }

		//void addComponent(Component* component) { mComponents.push_back(component); }

		const char* name() const { return mName; }

	protected:

		Shader* pShader;
		VertexArray* pVertexArray;

		glm::mat4 mModel { glm::mat4(1.0f) };

		//std::vector<Component*> mComponents;

		const char* mName;

};