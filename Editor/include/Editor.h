#pragma once

#include "SceneView.h"
#include "Inspector.h"
#include "Toolbar.h"

class Window;

class Editor: public Application, public ToolbarListener {

	public:

		Editor(Window* window);
		~Editor() {
			destroy();
		}
		
		void run() override;
		void setupDock();
		
		void init();
		void destroy();
		void begin();
		void end();

	private:

		Window* pWindow;
		SceneView mSceneView;
		Toolbar mToolbar;
		Inspector mInspector;


		// Inherited via ToolbarListener
		void onPlayPressed() override;

		void onStopPressed() override;

		void onPausePressed() override;

};