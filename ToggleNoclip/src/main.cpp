#include <Geode.hpp>

using namespace cocos2d;

class $(MyPlayLayer, PlayLayer) {
    CCLabelBMFont* g_startPosText;

    bool init(GJGameLevel* gl) {
		g_startPosText = CCLabelBMFont::create("Noclip: Off", "bigFont.fnt");

		PlayLayer::init(gl);

		auto corner = CCDirector::sharedDirector()->getScreenTop();
		g_startPosText->setPosition(510 , corner - 15);
		g_startPosText->setScale(0.4);
		g_startPosText->setAnchorPoint({0.25, 0.5});
		g_startPosText->setOpacity(127);

		addChild(g_startPosText, 1000);

		return true;
	}

    bool noclip = true;

    void update(float dt) {
		bool m_antiCheatPassed = true;
        if (!noclip) {
            this->g_startPosText->setString("Noclip: On");
        }else{
            this->g_startPosText->setString("Noclip: Off");
        }
		PlayLayer::update(dt);
		m_antiCheatPassed = true;
	}

	void vfDChk() {}

    void destroyPlayer(PlayerObject* p, GameObject* g) {
        if (noclip) {
            PlayLayer::destroyPlayer(p,g);
        }else{
            //noclip
        }
    }
};

class $(UILayer) {
	void keyDown(cocos2d::enumKeyCodes kc) {
		auto mpl = reinterpret_cast<MyPlayLayer*>(PlayLayer::get());

		if (kc == KEY_N) {
			mpl->noclip = !mpl->noclip;
		} else {
			UILayer::keyDown(kc);
		}
	}
};
