#include <Geode.hpp>

class $(PlayLayer) {
	void updateProgressbar() {
		PlayLayer::updateProgressbar();

		double percent = (m_player1->getPositionX() / m_levelLength) * 100;
		char str[64];
		sprintf(str, "%.5lf%%", percent);
		this->m_percentLabel->setString(str);
	}
};