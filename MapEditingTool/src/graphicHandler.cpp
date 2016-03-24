//
// Created by storm on 18/03/16.
//

#include "graphicHandler.h"

GraphicHandler::GraphicHandler(const std::string &title, const std::string &mainFontPath, unsigned int modeWidth, unsigned int modeHeight, unsigned int modeBitsPerPixel,
                const bool fixedSize, const bool fpsDebug, const float cameraSpeed)
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
    this->_mainCamera = new CameraHandler();
    this->_mainFontPath = mainFontPath;
    this->_fpsDebug = fpsDebug;
    this->_cameraSpeed = cameraSpeed;
}

GraphicHandler::~GraphicHandler() {
    delete this->_window;
    delete this->_mediaHandler;
    delete this->_baseMap;
    delete this->_clock;
    delete this->_clockHUD;
    delete this->_mainCamera;
}

TilesetHandler*     GraphicHandler::getBaseMap()
{
    return (this->_baseMap);
}

MediaHandler*       GraphicHandler::getMediaHandler()
{
    return (this->_mediaHandler);
}

CameraHandler*      GraphicHandler::getCamera()
{
    return (this->_mainCamera);
}

void     GraphicHandler::drawBaseMap() const
{
    this->draw(*this->_baseMap);
}

void     GraphicHandler::draw(const sf::Drawable &drawable) const
{
    if (this->_isAlive)
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
    this->_window->setView(*this->_mainCamera->getView());
    this->_window->display();
    this->_window->clear(sf::Color::Black);
    this->_clock->endFrame();
}

void          GraphicHandler::moveCamera(const Directions &direction)
{
    int     coef = (this->_cameraSpeed * 0.1) * this->_clock->getLastFrameTime().asMilliseconds();

    if (direction == Directions::UP)
        this->_mainCamera->getView()->move(0.0, -coef);
    else if (direction == Directions::DOWN)
        this->_mainCamera->getView()->move(0.0, coef);
    else if (direction == Directions::LEFT)
        this->_mainCamera->getView()->move(-coef, 0.0);
    else if (direction == Directions::RIGHT)
        this->_mainCamera->getView()->move(coef, 0.0);
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
    this->_mainCamera->init(sf::FloatRect(0, 0, this->_window->getSize().x, this->_window->getSize().y));
    this->_window->setView(*this->_mainCamera->getView());
    return (0);
}

void    GraphicHandler::launch()
{
    //this->_loop->launch();
    this->_isAlive = true;
}

void    GraphicHandler::terminate()
{
    this->_mediaHandler->wipeAll();
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