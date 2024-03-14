#pragma once

class Command {

	public:

	virtual ~Command() = default;

	virtual void execute() = 0;

};

class SceneHierarchy;
class DeleteCommand: public Command {

	public:

		DeleteCommand(SceneHierarchy* receiver);

		virtual void execute() override;

	private:

		SceneHierarchy* mReceiver;

};