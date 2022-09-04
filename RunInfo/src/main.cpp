#include <Geode.hpp>

using namespace cocos2d;

CCLabelBMFont* g_run;

class $modify(PlayLayer) {
	bool init(GJGameLevel* gj) {
		g_run = CCLabelBMFont::create("Run from: ???", "bigFont.fnt");

		PlayLayer::init(gj);

		auto corner = CCDirector::sharedDirector()->getScreenTop();
		g_run->setPosition(5 , corner - 45);
		g_run->setScale(0.4);
		g_run->setAnchorPoint({0, 0.5});
		g_run->setOpacity(100);
		double start = (m_player1->getPositionX() / m_levelLength) * 100;
		char str[64];
		sprintf(str, "Run from: %.0lf%%", start);
		g_run->setString(str);

		addChild(g_run, 1000);

		return true;
	}

	void delayedResetLevel() {
		PlayLayer::delayedResetLevel();
		double start = (m_player1->getPositionX() / m_levelLength) * 100;
		char str[64];
		sprintf(str, "Run from %.0lf%%", start);
		g_run->setString(str);
	}
};