#include <Geode.hpp>

USE_GEODE_NAMESPACE();

static float frames, noclipped_frames = 0;
bool completed = false;
static float limitframes = 0;

class $modify(MyPlayLayer, PlayLayer) {
	bool noclip = true;
	bool visible = true;
	CCLabelBMFont* g_startPosText;
	CCLabelBMFont* text;
	float percent;

    void vfDChk() {}
	bool init(GJGameLevel* p0) {
		text = CCLabelBMFont::create("100%", "bigFont.fnt");
        auto corner = CCDirector::sharedDirector()->getScreenTop();
        g_startPosText = CCLabelBMFont::create("Noclip: On", "bigFont.fnt");

        PlayLayer::init(p0);

		g_startPosText->setPosition(510 , corner - 15);
		g_startPosText->setScale(0.4);
		g_startPosText->setAnchorPoint({0.25, 0.5});
		text->setPosition(5 , corner - 25);
		text->setAnchorPoint({0, 0.5});
		text->setTag(31403);
		text->setScale(0.4);
		addChild(text, 10);
		addChild(g_startPosText, 1000);
		frames = noclipped_frames = 0;
		return true;
	}
	void update(float dt, GJGameLevel* ok) {
		bool m_antiCheatPassed = true;
		ok->m_isCompletionLegitimate = true;
		float percent = (m_player1->getPositionX() / m_levelLength) * 100;
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
		if (noclip) {
            PlayLayer::destroyPlayer(p,g);
        }else{
            //noclip
        }
	}
	void checkCollisions(PlayerObject* p, float g) {
			frames++;

			PlayLayer::checkCollisions(p, g);

			char ok[20];
			sprintf(ok, "%.2f%%", 100*(1.0 - (noclipped_frames/frames)));
			reinterpret_cast<CCLabelBMFont*>(getChildByTag(31403))->setString(ok);
	}
	
};

class $(UILayer) {
	void keyDown(cocos2d::enumKeyCodes kc) {
		auto mpl = reinterpret_cast<MyPlayLayer*>(PlayLayer::get());

		if (kc == KEY_N) {
			if (mpl->noclip == false) {
				mpl->g_startPosText->setString("Noclip: Off");
				mpl->noclip = true;
			}else{
				mpl->g_startPosText->setString("Noclip: On");
				mpl->noclip = false;
			}
			
		} else if (kc == KEY_M) {
			if (mpl->visible == false) {
				mpl->text->setVisible(true);
				mpl->visible = true;
			}else{
				mpl->text->setVisible(false);
				mpl->visible = false;
			}
		} else {
			UILayer::keyDown(kc);
		}

	}
};
