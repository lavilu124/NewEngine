#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <map>
#include <string>
#include <variant>
#include <stdexcept>

namespace Input {

    using KeyType = std::variant<sf::Keyboard::Key, sf::Joystick::Axis, sf::Mouse::Button>;

    enum class inputType {
        KeyboardKey,
        ControllerButton,
        MouseButton
    };

    enum class inputPart {
        Started,
        Pressed,
        Released
    };

    class InputAction {
        public:
            explicit InputAction(inputType type, KeyType key, std::string name, inputPart part,
                std::function<void()> onInput, std::function<void()> offInput = []() {});

            bool Active(sf::Event event);

        private:
            bool KeyPressed(sf::Event event);
            bool KeyReleased(sf::Event event);
            bool KeyStarted(sf::Event event);

            int checkKeyboardEvent(sf::Keyboard::Key key, sf::Event event);
            int checkMouseEvent(sf::Mouse::Button button, sf::Event event);
            int checkControllerEvent(unsigned int buttonIndex, sf::Event event);

            inputType m_type;
            KeyType m_key;
            std::string m_name;
            inputPart m_part;
            bool m_isPressed;
            std::function<void()> m_onInput;
            std::function<void()> m_offInput;
    };

}



