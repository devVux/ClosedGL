#pragma once

#include "Layer.h"

class ImGuiLayer sealed: public Layer {

	public:
		
		void attach() override;
		void detach() override;

		void begin();
		void end();

};