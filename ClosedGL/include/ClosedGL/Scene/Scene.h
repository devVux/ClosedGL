#pragma once

#include "ClosedGL/Core/Clock.h"
#include "ClosedGL/Scene/Entity.h"

#include <entt/entt.hpp>
#include "ClosedGL./Utils/Utils.h"


class Scene {

	public:

		void update(Timestep ts) const;
		
		Ref<Entity> createEntity() {
			Ref<Entity> e = makeRef<Entity>(mRegistry, mRegistry.create());
			mEntities.push_back(e);
			return e;
		}

		template <class T>
		T get(const Entity& entity) {
			return mRegistry.try_get<T>((entt::entity) entity.entityID());
		}


		bool operator==(const Scene& other) const {
			if (other.mEntities.size() != mEntities.size())
				return false;

			for (size_t i = 0; i < mEntities.size(); i++)
				if (*mEntities[i] != *other.mEntities[i])
					return false;

			return true;
		}
		bool operator!=(const Scene& other) const {
			return !(*this == other);
		}

	private:

		std::vector<Ref<Entity>> mEntities;
		entt::registry mRegistry;

};