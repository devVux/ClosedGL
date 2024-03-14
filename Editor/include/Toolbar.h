#pragma once


class ToolbarListener {

	public:

	virtual ~ToolbarListener() = default;

	virtual void onPlayPressed() = 0;
	virtual void onStopPressed() = 0;
	virtual void onPausePressed() = 0;

};


class Toolbar {

	public:

		void update();

		void setListener(ToolbarListener* l) {
			listener = l;
		}

	private:

		bool mPlaying { false };
		ToolbarListener* listener;

};



