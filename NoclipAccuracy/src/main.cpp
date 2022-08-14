#include <Geode.hpp>

USE_GEODE_NAMESPACE();

field<std::string> myString;

static float frames, noclipped_frames = 0;
bool completed = false;
static float limitframes = 0;

class $modify(PlayLayer) {
    void vfDChk() {}
	void update(float dt, GJGameLevel* ok) {
		bool m_antiCheatPassed = true;
		ok->m_isCompletionLegitimate = true;
		PlayLayer::update(dt);
		ok->m_isCompletionLegitimate = true;
		m_antiCheatPassed = true;
	}
    void resetLevel() {
		PlayLayer::resetLevel();
		frames = noclipped_frames = 0;
	}
	void destroyPlayer(PlayerObject* p, GameObject* g) {
		if (frames>20) {
			noclipped_frames++;
		}
	}
	void checkCollisions(PlayerObject* p, float g) {
		if (completed == true) {
			PlayLayer::checkCollisions(p, g);
			return;
		}
		frames++;

		PlayLayer::checkCollisions(p, g);

		char ok[20];
		sprintf(ok, "%.2f%%", 100*(1.0 - (noclipped_frames/frames)));
		reinterpret_cast<CCLabelBMFont*>(getChildByTag(31403))->setString(ok);
	}
	bool init(GJGameLevel* p0) {
		auto text = CCLabelBMFont::create("100%", "bigFont.fnt");
        auto corner = CCDirector::sharedDirector()->getScreenTop();
        
        PlayLayer::init(p0);

		text->setPosition(5 , corner - 25);
		text->setAnchorPoint({0, 0.5});
		text->setTag(31403);
		text->setScale(0.5);
		addChild(text, 10);
		frames = noclipped_frames = 0;
		return true;
	}
    void levelComplete() {
        PlayLayer::levelComplete();
        bool completed = true;
    }
	
};
