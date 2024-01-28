#pragma once

#include "entt/entt.hpp"

class Entity {

	public:

		Entity() = default;
		Entity(entt::registry& registry, entt::entity entityID): mHandle(registry, entityID) {  }

		template <class T, class... Args>
		inline void addComponent(Args&&... args) {
			mHandle.emplace<T>(std::forward<Args>(args)...);
		}

		template <class T>
		inline bool hasComponent() {
			return mHandle.try_get<T>();
		}

		int entityID() const { return (int) mHandle.entity(); }

	private:

		entt::handle mHandle;

};
