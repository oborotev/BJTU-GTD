//
// Created by storm on 18/03/16.
//

#include "graphicHandler.h"

GraphicHandler::GraphicHandler(const std::string &title, const std::string &mainFontPath, unsigned int modeWidth, unsigned int modeHeight, unsigned int modeBitsPerPixel,
                const bool fixedSize, const bool fpsDebug)
{
    this->_modeBitsPerPixel = !modeBitsPerPixel ? sf::VideoMode::getDesktopMode().bitsPerPixel : modeBitsPerPixel;
    this->_modeWidth = modeWidth;
    this->_modeHeight = modeHeight;
    this->_fixedSize = fixedSize;
    this->_title = title;
    this->_isAlive = true;
    this->_loop = nullptr;
    this->_mediaHandler = new MediaHandler();
    this->_baseMap = new TilesetHandler();
    this->_mainFontPath = mainFontPath;
    this->_fpsDebug = fpsDebug;
}

GraphicHandler::~GraphicHandler() {
    delete this->_window;
    delete this->_mediaHandler;
    delete this->_baseMap;
    delete this->_clock;
    delete this->_clockHUD;
}

TilesetHandler*     GraphicHandler::getBaseMap()
{
    return (this->_baseMap);
}

MediaHandler*       GraphicHandler::getMediaHandler()
{
    return (this->_mediaHandler);
}

void     GraphicHandler::drawBaseMap() const
{
    this->_window->draw(*this->_baseMap);
}

void     GraphicHandler::draw(const sf::Drawable &drawable) const
{
    this->_window->draw(drawable);
}

void     GraphicHandler::loop()
{
    if (!this->_isAlive)
    {
        this->_window->close();
        return;
    }
    if (this->_fpsDebug)
        this->_window->draw(*this->_clockHUD);
    this->_window->display();
    this->_window->clear(sf::Color::Black);
    this->_clock->endFrame();
}

void          GraphicHandler::setFpsDebug(const bool &option)
{
    this->_fpsDebug = option;
}

const int     GraphicHandler::init()
{
    this->_window = new sf::RenderWindow(sf::VideoMode(this->_modeWidth, this->_modeHeight, this->_modeBitsPerPixel), this->_title, sf::Style::Close);
    if (this->_mainFontPath != "")
        if (!this->_mainFont.loadFromFile(this->_mainFontPath))
        {
            std::cout << "Couldn't load font from path " << this->_mainFontPath << std::endl;
            return (1);
        }
    this->_clock = new sfx::FrameClock();
    this->_clockHUD = new ClockHUD(*this->_clock, this->_mainFont);
    this->_window->setFramerateLimit(60);
    return (0);
}



void    GraphicHandler::launch()
{
    //this->_loop->launch();
    this->_isAlive = true;

}

void    GraphicHandler::terminate()
{
    this->_isAlive = false;
}

const bool      GraphicHandler::pollEvent()
{
    bool        temp;

    this->_clock->beginFrame();
    temp = this->_window->pollEvent(this->_event);
    return (temp);
}

const bool      GraphicHandler::eventTriggered(const sf::Event::EventType& eventType) const
{
    if (this->_event.type == eventType)
        return (true);
    return (false);
}

const bool      GraphicHandler::getIsAlive()
{
    return this->_isAlive;
}