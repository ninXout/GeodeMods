#include <Geode.hpp>
#include <sstream>

USE_GEODE_NAMESPACE();

void fps_shower_init();

GEODE_API bool GEODE_CALL geode_load(Mod* mod) {
	geode::Interface::get()->init(mod);
	fps_shower_init();
    return true;
}

class FPSOverlay : public cocos2d::CCNode {
 protected:
    static inline FPSOverlay* s_sharedState = 0;

    cocos2d::CCLabelBMFont* m_label;
    cocos2d::extension::CCScale9Sprite* m_backdrop;
    int m_frames;
    double m_accumulate;
    double m_resetInterval;

 public:
    static FPSOverlay* sharedState() {
        if (!FPSOverlay::s_sharedState) {
            auto ret = FPSOverlay::s_sharedState = new FPSOverlay();
            ret->init();
        }
        return FPSOverlay::s_sharedState;
    }

 private:
    cocos2d::CCSize getBackdropSize() {
        auto textSize = m_label->getContentSize();
        return cocos2d::CCSizeMake(2 * 6 + textSize.width * 2, 2 * 6 + textSize.height * 2);
    }

 public:
    bool init() {
        m_frames = 0;
        m_resetInterval = 1.0;

        auto winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
        
        m_label = cocos2d::CCLabelBMFont::create("No FPS", "bigFont.fnt");
        m_label->setPosition({3, winSize.height - 290});
        m_label->setAnchorPoint(cocos2d::CCPoint(0, 1));
        m_label->setScale(0.5);
        m_label->setOpacity(127);
        addChild(m_label, 2);        

        m_backdrop = cocos2d::extension::CCScale9Sprite::create("square02_small.png");
        m_backdrop->setContentSize(getBackdropSize());
        m_backdrop->setPosition({2, winSize.height - 2});
        m_backdrop->setAnchorPoint(cocos2d::CCPoint(0, 1));
        m_backdrop->setOpacity(0);
        m_backdrop->setScale(0.166666);
        addChild(m_backdrop, 1);

        return true;
    }

    void update(float dt) {
    	updateLabel(dt);
    }

    void updateLabel(float dt) {
    	++m_frames;
        m_accumulate += dt;

        if (m_accumulate > m_resetInterval) {
            float framerate = m_frames / m_accumulate;
            framerate = round(framerate * 10) / 10;
            m_frames = 0;
            m_accumulate = 0;
            
            std::stringstream stream;
        	stream << framerate << " FPS";
            m_label->setString(stream.str().c_str());
            m_backdrop->setContentSize(getBackdropSize());
        }
    }
};

class $modify(AchievementNotifier) {
    void willSwitchToScene(cocos2d::CCScene* newScene) {
        AchievementNotifier::willSwitchToScene(newScene);
        
        if (FPSOverlay::sharedState()->getParent() != newScene) {
            FPSOverlay::sharedState()->removeFromParentAndCleanup(false);
            reinterpret_cast<cocos2d::CCNode*>(newScene->getChildren()->objectAtIndex(0))
                ->addChild(FPSOverlay::sharedState(), 100001);
        }
    }
};

void fps_shower_init() {
	geode::Loader::get()->queueInGDThread([](){
		cocos2d::CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(FPSOverlay::sharedState(), 0, true);
		auto scene = cocos2d::CCDirector::sharedDirector()->getRunningScene();
		if (scene) {
			auto layer = reinterpret_cast<cocos2d::CCNode*>(scene->getChildren()->objectAtIndex(0));
			if (layer) layer->addChild(FPSOverlay::sharedState(), 100001);
		}
	});
}