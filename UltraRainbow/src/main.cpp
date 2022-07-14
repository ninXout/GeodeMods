#include <Geode.hpp>
#include <chrono>

using namespace std::chrono;

class $modify(MoreOptionsLayer) {
	bool init() {
		if (!MoreOptionsLayer::init()) return false;
		this->addToggle("Show only on death", "2387", "Shows the hitbox visuals only on death");
		this->addToggle("Enable hitbox trail", "2388", "Enables the hitbox trail");
		this->addToggle("Show only hitboxes", "2389", "Hides all objects themselves, leaving only the hitboxes");
		this->addToggle("No limit trail", "2390", "Shows all of the player trails in the editor. May lag, haven't tested.");
		return true;
	}
};

// i found this on the internet
void HSVtoRGB(float& fR, float& fG, float& fB, float& fH, float& fS, float& fV) {
  float fC = fV * fS; // Chroma
  float fHPrime = fmod(fH / 60.0, 6);
  float fX = fC * (1 - fabs(fmod(fHPrime, 2) - 1));
  float fM = fV - fC;
  
  if(0 <= fHPrime && fHPrime < 1) {
    fR = fC;
    fG = fX;
    fB = 0;
  } else if(1 <= fHPrime && fHPrime < 2) {
    fR = fX;
    fG = fC;
    fB = 0;
  } else if(2 <= fHPrime && fHPrime < 3) {
    fR = 0;
    fG = fC;
    fB = fX;
  } else if(3 <= fHPrime && fHPrime < 4) {
    fR = 0;
    fG = fX;
    fB = fC;
  } else if(4 <= fHPrime && fHPrime < 5) {
    fR = fX;
    fG = 0;
    fB = fC;
  } else if(5 <= fHPrime && fHPrime < 6) {
    fR = fC;
    fG = 0;
    fB = fX;
  } else {
    fR = 0;
    fG = 0;
    fB = 0;
  }
  
  fR += fM;
  fG += fM;
  fB += fM;
}

float g = 0;
// wacky way to convert pure hue to rgb
cocos2d::_ccColor3B getRainbow(float offset) {
	float R;
	float G;
	float B;

	float hue = fmod(g + offset, 360);
	//geode::log << hue;
	float sat = 1;
	float vc = 1;
	HSVtoRGB(R, G, B, hue, sat, vc);

	cocos2d::_ccColor3B out;
	out.r = R*255;
	out.g = G*255;
	out.b = B*255;
	return out;
}

class $(PlayLayer) {
	void update(float a) {
		if (g >= 360) // mod 360
			g = 0;
		else
			g += 2.5; // a good rotation
		auto col = getRainbow(0);
		auto colInverse = getRainbow(180);

		if (m_player1) {
			m_player1->setColor(col);
			
			if (m_player1->m_waveTrail)
				m_player1->m_waveTrail->setColor(col);
		}

		if (m_player2) {
			m_player2->setColor(colInverse);
			
			if (m_player2->m_waveTrail)
				m_player2->m_waveTrail->setColor(colInverse);
		}

		PlayLayer::update(a);
	}
};

//m_player2->setSecondColor(col);
//m_player1->setSecondColor(colInverse);