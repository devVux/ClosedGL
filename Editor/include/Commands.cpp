#include "Commands.h"

#include "SceneView.h"

DeleteCommand::DeleteCommand(SceneHierarchy* receiver): mReceiver(receiver) {

}

void DeleteCommand::execute() {

	//mReceiver->remove(mReceiver->selectedComponent());

}
