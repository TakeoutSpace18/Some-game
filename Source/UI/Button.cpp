#include "Button.h"

#include <iostream>
#include <vector>

#include "Window.h"
#include "Application.h"
#include "Signal.hpp"

Button::Button(ID id,
               sf::Vector2f center,
               sf::Vector2f size,
               const std::string& name,
               unsigned int text_size,
               float scale_factor,
               Application& app)
    : m_id(id), m_name(name), _application(&app) {
    m_isActive = false;
    m_inFade = false;
    m_isPressed = false;

    m_shape.setOrigin(size * scale_factor / 2.f);
    m_shape.setPosition(center);
    m_shape.setSize(size * scale_factor);
    m_shape.setFillColor(non_active_fill_color);
    m_shape.setOutlineColor(outline_color);
    m_shape.setOutlineThickness(3 * scale_factor);

    m_rect = m_shape.getGlobalBounds();

    m_text.setFont(_application->getResourses().fonts.get(Fonts::TerminalGrotesque));
    m_text.setCharacterSize(text_size * scale_factor);
    m_text.setFillColor(text_color);
    m_text.setString(name);
    m_text.setOrigin(m_text.getLocalBounds().width / 2 + 2 * scale_factor,
                     m_text.getLocalBounds().height / 2 + 5 * scale_factor);
    m_text.setPosition(center - sf::Vector2f(0, 3 * scale_factor));
}

void Button::input(sf::Event& event, std::vector<Button>& other_buttons) {
    if (m_rect.contains(sf::Vector2f(Window::getMousePosition()))) {
        bool another_button_pressed{false};
        for (int i = 0; i < other_buttons.size(); i++) {
            if (other_buttons[i].isPressed()) {
                another_button_pressed = true;
            }
        }

        if (!m_isActive && !another_button_pressed) {
            m_isActive = true;
            m_inFade = true;
            m_fade = ColorFadeManager(sf::seconds(0.1), non_active_fill_color, active_fill_color);
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                m_isPressed = true;
                m_shape.setScale(press_coef, press_coef);
                m_text.setScale(press_coef, press_coef);
            }
        } else if (event.type == sf::Event::MouseButtonReleased && m_isActive) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                m_isPressed = false;
                m_shape.setScale(1, 1);
                m_text.setScale(1, 1);

                Signal signal;
                signal.type = Signal::ButtonClicked;
                signal.button.id = m_id;
                _application->handleSignal(signal);
            }
        }
    } else {
        if (m_isPressed && event.type == sf::Event::MouseButtonReleased &&
            event.mouseButton.button == sf::Mouse::Left) {
            m_isPressed = false;
            m_shape.setScale(1, 1);
            m_text.setScale(1, 1);
        }

        if (m_isActive && !m_isPressed) {
            m_isActive = false;
            m_inFade = true;
            m_fade = ColorFadeManager(sf::seconds(0.1), active_fill_color, non_active_fill_color);
        }
    }
}

void Button::update() {
    if (m_inFade)
        if (m_fade.isOver()) {
            m_inFade = false;
            m_shape.setFillColor(m_fade.getFinalColor());
        } else
            m_shape.setFillColor(m_fade.getCurrentColor());
}

void Button::setOpacity(sf::Uint8 value) {
    sf::Color col = non_active_fill_color;
    col.a = value;
    m_shape.setFillColor(col);
    col = outline_color;
    col.a = value;
    m_shape.setOutlineColor(col);
    col = text_color;
    col.a = value;
    m_text.setFillColor(col);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_shape, states);
    target.draw(m_text, states);
}
