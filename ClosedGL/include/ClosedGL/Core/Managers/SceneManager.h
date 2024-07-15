#pragma once

#include "ClosedGL/Scene/Scene.h"
#include <entt/entt.hpp>


class SceneManager {

	public:

		void addScene(Ref<Scene> scene) {
			mScenes.push_back(scene);
		}

		void updateCurrentScene(Timestep ts) const { mScenes[mCurrentScene]->update(ts); }
		Scene& currentScene() const { return *mScenes[mCurrentScene]; }
		bool isEmpty() const { return mScenes.empty(); }
		size_t sceneCount() const { return mScenes.size(); }

		void nextScene() {
			mCurrentScene = (mCurrentScene + 1) % mScenes.size();
		}
		void prevScene() {
			mCurrentScene = std::min(mCurrentScene - 1, static_cast<uint32_t>(mScenes.size() - 1));
		}

		void goToScene(uint32_t index) {
			if (index < mScenes.size())
				mCurrentScene = index;
		}


	private:

		std::vector<Ref<Scene>> mScenes;
		uint32_t mCurrentScene { 0 };

};