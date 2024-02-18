#include "pch.h"
#include "SceneManager.h"
#include "TextureManager.h"

// Scene manager
std::vector<Entity*> SceneManager::mEntities;
entt::registry SceneManager::mRegistry;

// Texture manager
std::vector<const Texture*> TextureManager::mTextures;