//
// Created by margoul_1 on 12/03/16.
//

#include "TaiTaiChat.h"

TaiTaiChat::TaiTaiChat()
{
    std::cout << "Contructeur Window" << std::endl;
    this->setFontPath("/home/margoul_1/git/merde/BJTU-GTD/MeiYouCommunicationFramework/fonts/arial_narrow_7.ttf");
    this->windowLoop();
}

TaiTaiChat::~TaiTaiChat()
{

}

int    TaiTaiChat::windowLoop()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::TextEntered)
            {
                if ((event.text.unicode > 30 && (event.text.unicode < 128 || event.text.unicode > 159)))
                {
                    std::cout << static_cast<char>(event.text.unicode) << std::endl;
                    this->_myLastMessage +=  static_cast<char>(event.text.unicode);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
                {
                    if (this->_myLastMessage.length() > 0) {
                        std::cout << static_cast<char>(event.text.unicode) << std::endl;
                        _myLastMessage.pop_back();
                    }
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                {
                    //return to the next line
                }
            }
        }
        window.clear(sf::Color::Black);

        sf::Font font;
        if (!font.loadFromFile(this->getFontPath()))
        {
            std::cout << "Unable to load font.. quitting" << std::endl;
            window.close();
        }

        sf::Text text;
        text.setFont(font); // font is a sf::Font

        text.setString(_myLastMessage);
        text.setCharacterSize(24); // in pixels, not points!
        text.setColor(sf::Color::Red);
        window.draw(text);
        window.display();

    }
}

void    TaiTaiChat::setIncomingMessage(std::string message, bool me)
{
    if (me)
        this->_myLastMessage = message;
    else
        this->_lastIncomingMessage = message;
}

std::string  TaiTaiChat::getIncomingMessage(bool me)
{
    if (me)
        return (this->_myLastMessage);
    else
        return (this->_lastIncomingMessage);
}

void    TaiTaiChat::setWindowName(std::string name)
{
    this->_windowName = name;
}

std::string TaiTaiChat::getWindowName()
{
    return (this->_windowName);
}

void    TaiTaiChat::setFontPath(std::string fontPath)
{
    this->_fontPath = fontPath;
}

std::string TaiTaiChat::getFontPath()
{
    return (this->_fontPath);
}