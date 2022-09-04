#include <Geode.hpp>

USE_GEODE_NAMESPACE();

class $(UILayer) {
	void keyDown(cocos2d::enumKeyCodes kc) {
		auto mpl = reinterpret_cast<PlayLayer*>(PlayLayer::get());

		if (kc == KEY_R) {
			mpl->resetLevel();
		} else {
			UILayer::keyDown(kc);
		}
	}
};
