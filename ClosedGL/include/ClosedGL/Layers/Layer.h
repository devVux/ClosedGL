#pragma once

#include <string>

class Layer {

	public:

		virtual ~Layer() = default;
		
		virtual void update() {};

		virtual void attach() {};
		virtual void detach() {};

	protected:

		std::string mName;

};
