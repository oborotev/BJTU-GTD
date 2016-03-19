//
// Created by storm on 18/03/16.
//

#include "graphicHandler.h"

GraphicHandler::GraphicHandler(const std::string &title, unsigned int modeWidth, unsigned int modeHeight, unsigned int modeBitsPerPixel,
                const bool fixedSize)
{
    this->_modeBitsPerPixel = !modeBitsPerPixel ? sf::VideoMode::getDesktopMode().bitsPerPixel : modeBitsPerPixel;
    this->_modeWidth = modeWidth;
    this->_modeHeight = modeHeight;
    this->_fixedSize = fixedSize;
    this->_title = title;
}

GraphicHandler::~GraphicHandler() {
    delete this->_window;
}

const int     GraphicHandler::init()
{
    this->_window = new sf::RenderWindow(sf::VideoMode(this->_modeWidth, this->_modeHeight, this->_modeBitsPerPixel), this->_title);
    while (this->_window->isOpen())
    {
        while (this->_window->pollEvent(this->_event))
        {
            if (this->_event.type == sf::Event::Closed)
                this->_window->close();
        }
        this->_window->clear(sf::Color::Black);
        this->_window->display();
    }
    return (0);
}