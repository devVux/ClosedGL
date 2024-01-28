#include "pch.h"
#include "LayerStack.h"

LayerStack::~LayerStack() {
	
	while (!mLayers.empty()) {
		mLayers.back()->detach();
		delete mLayers.back();
		mLayers.pop_back();
	}

}

void LayerStack::updateLayers() const {
	for (size_t i = mOverlayCount; i < mLayers.size(); i++)
		mLayers[i]->update();
}

void LayerStack::updateOverlays() const {
	for (size_t i = 0; i < mOverlayCount; i++)
		mLayers[i]->update();
}

void LayerStack::pushLayer(Layer* layer) {
	const auto& it = std::find(mLayers.begin(), mLayers.end(), layer);
	if (it == mLayers.end()) {
		mLayers.push_back(layer);
		layer->attach();
	}
}

void LayerStack::pushOverlay(Layer* overlay) {
	const auto& it = std::find(mLayers.begin(), mLayers.end(), overlay);
	if (it == mLayers.end()) {
		mLayers.insert(mLayers.begin(), overlay);
		mOverlayCount++;
		overlay->attach();
	}
}

Layer* LayerStack::popLayer() {
	if (mLayers.size() == mOverlayCount)
		return nullptr;
	const auto& layer = mLayers.back();
	mLayers.pop_back();
	return layer;
}

Layer* LayerStack::popOverlay() {
	if (mLayers.empty() || mOverlayCount == 0)
		return nullptr;
	const auto& overlay = mLayers[mOverlayCount - 1];
	mLayers.erase(mLayers.begin() + mOverlayCount - 1);
	return overlay;
}
