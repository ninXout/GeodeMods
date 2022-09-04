#include <Geode.hpp>

USE_GEODE_NAMESPACE();

class $modify(PlayLayer) {
	void update(float dt) {
		bool m_antiCheatPassed = true;
		PlayLayer::update(dt);
		m_antiCheatPassed = true;
	}

	void vfDChk() {}

	void switchToFlyMode(PlayerObject* p, GameObject* o, bool b, int i) {
		if (m_isPracticeMode) {
			PlayLayer::markCheckpoint();
			PlayLayer::switchToFlyMode(p,o,b,i);
		}
		else {
			PlayLayer::switchToFlyMode(p,o,b,i);
		}
	}
	
	void switchToRobotMode(PlayerObject* p0, GameObject* g0, bool b1) {
		if (m_isPracticeMode) {
			PlayLayer::markCheckpoint();
			PlayLayer::switchToRobotMode(p0,g0,b1);
		}
		else {
			PlayLayer::switchToRobotMode(p0,g0,b1);
		}
	}

	void switchToRollMode(PlayerObject* p0, GameObject* g0, bool b1) {
		if (m_isPracticeMode) {
			PlayLayer::markCheckpoint();
			PlayLayer::switchToRollMode(p0,g0,b1);
		}
		else {
			PlayLayer::switchToRollMode(p0,g0,b1);
		}
	}

	void switchToSpiderMode(PlayerObject* p0, GameObject* g0, bool b1) {
		if (m_isPracticeMode) {
			PlayLayer::markCheckpoint();
			PlayLayer::switchToSpiderMode(p0,g0,b1);
		}
		else {
			PlayLayer::switchToSpiderMode(p0,g0,b1);
		}
	}

	void toggleFlipped(bool p1, bool g1) {
		if (m_isPracticeMode) {
			PlayLayer::markCheckpoint();
			PlayLayer::toggleFlipped(p1, g1);
		}
		else {
			PlayLayer::toggleFlipped(p1, g1);
		}
	}

	void playGravityEffect(bool p2) {
		if (m_isPracticeMode) {
			PlayLayer::markCheckpoint();
			PlayLayer::playGravityEffect(p2);
		}
		else {
			PlayLayer::playGravityEffect(p2);
		}
	}
};
