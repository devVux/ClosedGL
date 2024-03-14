#pragma once

#include <ClosedGL.h>

class SceneView {

	public:

		void switchFullscreen() { f = !f; }

		void update();

	private:
		OrthographicCamera camera;
		Scene scene;
		FrameBuffer mFrameBuffer;
		bool f { false };
};



