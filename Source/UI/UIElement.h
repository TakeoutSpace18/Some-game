#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

class UIElement : public sf::Drawable, public sf::Transformable {
   public:
    enum class Align {
        None,
        Center,
        Top,
        Bottom,
        Left,
        Right,
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };

    UIElement() = default;
    virtual ~UIElement() = default;

    void setScaleFactor(float factor);
    void setAlign(UIElement::Align align);
    void resize(sf::Vector2f newSize);

    void addChild(std::unique_ptr<UIElement> child);

   protected:
    void bindDrawable(sf::Drawable* drawable);
    sf::Transform _scaleFactorTransform;

   private:
    void updatePosition(const sf::Vector2f& parentSize);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    // TODO: initialization?
    UIElement::Align _align;
    sf::Vector2f _size;

    std::vector<sf::Drawable*> _drawableShapes;
    std::vector<std::unique_ptr<UIElement>> _children;
};