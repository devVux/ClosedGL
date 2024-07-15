#include <gtest/gtest.h>
#include "ClosedGL/Core/Managers/SceneManager.h"


class SceneManagerTest: 
public ::testing::Test {
	protected:
	SceneManager manager;
};

// Test case to verify adding scenes
TEST_F(SceneManagerTest, AddScene) {
	auto scene1 = std::make_shared<Scene>();
	auto scene2 = std::make_shared<Scene>();

	manager.addScene(scene1);
	manager.addScene(scene2);

	EXPECT_EQ(manager.sceneCount(), 2);  // Check if scenes were added correctly
}

// Test case to verify nextScene and prevScene functions
TEST_F(SceneManagerTest, NextPrevScene) {
	auto scene1 = std::make_shared<Scene>();
	auto scene2 = std::make_shared<Scene>();

	manager.addScene(scene1);
	manager.addScene(scene2);

	EXPECT_EQ(manager.currentScene(), *scene1);  // Initial current scene should be scene1

	manager.nextScene();
	EXPECT_EQ(manager.currentScene(), *scene2);  // After nextScene, current scene should be scene2

	manager.prevScene();
	EXPECT_EQ(manager.currentScene(), *scene1);  // After prevScene, current scene should be scene1 again
}

// Test case to verify goToScene function
TEST_F(SceneManagerTest, GoToScene) {
	auto scene1 = std::make_shared<Scene>();
	auto scene2 = std::make_shared<Scene>();

	manager.addScene(scene1);
	manager.addScene(scene2);

	manager.goToScene(1);  // Go to scene at index 1 (scene2)

	EXPECT_EQ(manager.currentScene(), *scene2);  // Verify current scene is scene2

	manager.goToScene(0);  // Go back to scene at index 0 (scene1)

	EXPECT_EQ(manager.currentScene(), *scene1);  // Verify current scene is scene1
}

// Test case to verify goToScene function
TEST_F(SceneManagerTest, GoToNonExistentScene) {
	auto scene1 = std::make_shared<Scene>();
	auto scene2 = std::make_shared<Scene>();

	manager.addScene(scene1);
	manager.addScene(scene2);

	manager.goToScene(1);  // Go to scene at index 1 (scene2)

	EXPECT_EQ(manager.currentScene(), *scene2);  // Verify current scene is scene2

	manager.goToScene(123);  // Go back to scene at index 0 (scene1)

	EXPECT_EQ(manager.currentScene(), *scene2);  // Verify current scene is scene1
}

// Test case to verify isEmpty function
TEST_F(SceneManagerTest, IsEmpty) {
	EXPECT_TRUE(manager.isEmpty());  // Initially, SceneManager should be empty

	auto scene = std::make_shared<Scene>();
	manager.addScene(scene);

	EXPECT_FALSE(manager.isEmpty());  // After adding a scene, SceneManager should not be empty
}