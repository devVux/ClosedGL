#pragma once

#include "ClosedGL/Utils/Observer.h"

#include <algorithm>

class Application;
class View;

class Controller: public Observer {

	public:

		Controller(Application* model, View* view);

		virtual void update() override;


	private:

		Application* mModel;
		View* mView;

};