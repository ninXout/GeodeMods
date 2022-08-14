#include <Geode.hpp>

USE_GEODE_NAMESPACE();

bool m_isPracticeMode = false;

class $modify(PlayLayer) {
	void update(float dt) {
		bool m_antiCheatPassed = true;
		PlayLayer::update(dt);
		m_antiCheatPassed = true;
	}

	void vfDChk() {}

	void togglePracticeMode(bool b) {
		bool m_isPracticeMode = true;
		PlayLayer::togglePracticeMode(b);
	}

	void playerWillSwitchMode(PlayerObject* po, GameObject* go) {
		if (bool m_isPracticeMode = true) {
			PlayLayer::markCheckpoint();
			PlayLayer::playerWillSwitchMode(po, go);
		}
		if (bool m_isPracticeMode = false) {
			PlayLayer::playerWillSwitchMode(po, go);
		}
	}
	
	void toggleFlipped(bool p1, bool g1) {
		if (bool m_isPracticeMode = true) {
			PlayLayer::markCheckpoint();
			PlayLayer::toggleFlipped(p1, g1);
		}
		if (bool m_isPracticeMode = false) {
			PlayLayer::toggleFlipped(p1, g1);
		}
	}

	void playGravityEffect(bool p2) {
		if (bool m_isPracticeMode = true) {
			PlayLayer::markCheckpoint();
			PlayLayer::playGravityEffect(p2);
		}
		if (bool m_isPracticeMode = false) {
			PlayLayer::playGravityEffect(p2);
		}
	}
};
