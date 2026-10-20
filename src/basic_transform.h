// maybe something here...
#include "vector_util.h"
#include <SFML/System/Vector2.hpp>

struct BasicTransform {
    // methods...

    BasicTransform(sf::Vector2f scale = {1.f, 1.f}, sf::Vector2f translation = {0.f, 0.f})
        : scale(scale), translation(translation) {};

    sf::Vector2f applyPoint(const sf::Vector2f& p) const {
        return {p.x * scale.x + translation.x, p.y * scale.y + translation.y};
    };
    sf::Vector2f applyVector(const sf::Vector2f& p) const {
        return {p.x * scale.x, p.y * scale.y};
    };

    bool operator==(const BasicTransform& other) const {
        return scale == other.scale && translation == other.translation;
    }
    sf::Vector2f scale;
    sf::Vector2f translation;
};
