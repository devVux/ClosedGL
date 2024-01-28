#pragma once

#include "Layer.h"
#include <vector>

class LayerStack {

	public:

		~LayerStack();

		void updateLayers() const;
		void updateOverlays() const;

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* layer);

		Layer* popLayer();
		Layer* popOverlay();

		auto begin() { return mLayers.begin(); }
		const auto begin() const { return mLayers.begin(); }
		
		auto end() { return mLayers.end(); }
		const auto end() const { return mLayers.end(); }

	private:

		std::vector<Layer*> mLayers;
		unsigned int mOverlayCount { 0 };

};