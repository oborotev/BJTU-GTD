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
    this->_isAlive = true;
    this->_loop = nullptr;
}

GraphicHandler::~GraphicHandler() {
    delete this->_window;
}

void     GraphicHandler::drawer() const
{
    this->_window->draw(*this->_tilesetHandler);
}

void     GraphicHandler::loop()
{
    while (this->_window->isOpen())
    {
        while (this->_window->pollEvent(this->_event))
        {
            if (this->_event.type == sf::Event::Closed)
            {
                this->_mutex.lock();
                this->_isAlive = false;
                this->_mutex.unlock();
                this->_window->close();
            }
        }
        this->_window->clear(sf::Color::Black);
        this->drawer();
        this->_window->display();
    }
}

const int     GraphicHandler::init(MediaHandler *mediaHandler, TilesetHandler *tilesetHandler)
{
    this->_window = new sf::RenderWindow(sf::VideoMode(this->_modeWidth, this->_modeHeight, this->_modeBitsPerPixel), this->_title);
    this->_loop = new sf::Thread(&GraphicHandler::loop, this);
    this->_mediaHandler = mediaHandler;
    this->_tilesetHandler = tilesetHandler;
    return (0);
}

void    GraphicHandler::launch() const
{
    this->_loop->launch();
}

void    GraphicHandler::terminate() const
{
    this->_loop->wait();
    this->_loop->terminate();
}

const bool      GraphicHandler::getIsAlive()
{
    return this->_isAlive;
}