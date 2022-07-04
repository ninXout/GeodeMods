#include <Geode.hpp>
#include <vector>

/**
 * Brings cocos2d and all Geode namespaces 
 * to the current scope.
 */
USE_GEODE_NAMESPACE();

class $modify(PlayLayer) {
    void showNewBest(bool, int, int, bool, bool, bool) {
        bool m_isPaused = true;
    }
}; 
