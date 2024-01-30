#include "Controller.h"

#include "ClosedGL/Core/Application.h"
#include "ClosedGL/Layers/View.h"

Controller::Controller(Application* model, View* view): mModel(model), mView(view) {
	model->registerObserver(this);
	view->registerObserver(this);
}

// on view update
void Controller::update() {


}
