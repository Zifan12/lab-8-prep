#ifndef SPRITE_H
#define SPRITE_H

#include <array>

#include "basic_transform.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
class Sprite {  // could derive from sf::Drawable if you're willing to pay for a vptr, but not
                // necessary.
public:
    Sprite(const sf::Texture& texture) {
        mTexture = &texture;
        mMinPointTex = {0, 0};
        mMaxPointTex = sf::Vector2f(texture.getSize());
        mVertexArray.setPrimitiveType(sf::PrimitiveType::Triangles);
        recomputeVertexArray();
    }

    Sprite(const sf::Texture& texture, const sf::Vector2f& texMinPoint,
           const sf::Vector2f& texMaxPoint) {
        mTexture = &texture;
        mMinPointTex = texMinPoint;
        mMaxPointTex = texMaxPoint;
        mVertexArray.setPrimitiveType(sf::PrimitiveType::Triangles);
        recomputeVertexArray();
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.texture = mTexture;
        recomputeVertexArray();
        target.draw(mVertexArray, states);
    }

    sf::Vector2f& position() { return mTransform.translation; }
    const sf::Vector2f& position() const { return mTransform.translation; }
    sf::Vector2f& scale() { return mTransform.scale; }
    const sf::Vector2f& scale() const { return mTransform.scale; }
    sf::Vector2f& origin() { return mOrigin; }
    const sf::Vector2f& origin() const { return mOrigin; }

private:
    // It may help you to write this, which is an array of 6 vertices:
    //   - the first 3 correspond to the vertices of the top-left triangle of a "default rectangle"
    //     ranging from [0, 1] in both dimensions.
    //   - the next 3 correspond to the vertices of the bottom-right triangle. of the default
    //     rectangle.
    static constexpr std::array<sf::Vector2f, 6> DEFAULT_VERTICES = {
        sf::Vector2f{0, 0}, {0, 1}, {1, 1}, {0, 0}, {1, 1}, {1, 0}};  // TODO

    // if mTexture is valid, recomputes the positions and coords of sf::Vertex for each
    // of 6 possible entries in mVertexArray.
    void recomputeVertexArray() const {
        // TODO
        const sf::Vector2f size = mMaxPointTex - mMinPointTex;
        mVertexArray.clear();
        for (const sf::Vector2f& d : DEFAULT_VERTICES) {
            sf::Vector2f uv = mMinPointTex + d * size;
            sf::Vector2f position = mTransform.applyPoint(d * size - mOrigin);
            mVertexArray.append({position, sf::Color::White, uv});
        }
    }

    const sf::Texture* mTexture;
    mutable sf::VertexArray mVertexArray;  // geometry, uv coords -- mutable means it can be changed
                                           //  even in const methods.
    sf::Vector2f mMinPointTex;             // AABB for subtexture min point along both x, y
    sf::Vector2f mMaxPointTex;             // AABB for subtexture max point along both x, y
    sf::Vector2f mOrigin;  // position in tex coords of the sprite origin, relative to minPoint
    BasicTransform mTransform;
};

#endif
