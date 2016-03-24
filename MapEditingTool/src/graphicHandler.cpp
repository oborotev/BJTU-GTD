//
// Created by storm on 18/03/16.
//

#include "graphicHandler.h"

GraphicHandler::GraphicHandler(const std::string &title, const std::string &mainFontPath, unsigned int modeWidth, unsigned int modeHeight, const bool cameraDelimited, const sf::IntRect &cameraDelimitation, unsigned int modeBitsPerPixel,
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
    this->_cameraDelimitation = cameraDelimitation;
    this->_cameraDelimited = cameraDelimited;
    this->_keyStates.fill(false);
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
    this->_mainCamera->updatePositionCenter();
    this->_window->setView(*this->_mainCamera->getView());
    this->_window->display();
    this->_window->clear(sf::Color::Black);
    this->_clock->endFrame();
}

bool          GraphicHandler::isKeyDown(const sf::Keyboard::Key &key)
{
    if (this->_event.type == sf::Event::KeyReleased && this->_event.key.code == key)
        this->_keyStates[key] = false;
    if (sf::Keyboard::isKeyPressed(key) && !this->_keyStates[key])
    {
        this->_keyStates[key] = true;
        return (true);
    }
    else if (this->_keyStates[key])
        return (true);
}

void            GraphicHandler::moveStaticObjects(const sf::Vector2i &vector)
{
    std::vector<std::pair<sf::Transformable *, MediaHandler::t_staticParameters>> staticElems = this->_mediaHandler->getStaticElems();

    for (std::vector<std::pair<sf::Transformable *, MediaHandler::t_staticParameters>>::iterator it = staticElems.begin(); it < staticElems.end(); it++)
    {
        std::cout << "offset x :" << it->second.offsets.x << std::endl;
        it->first->setPosition(
                (this->_mainCamera->getCenterX() - (this->_window->getSize().x / 2)) + it->second.offsets.x,
                (this->_mainCamera->getCenterY() - (this->_window->getSize().y / 2)) +
                it->second.offsets.y);
    }
}

void             GraphicHandler::moveCamera(const Directions &direction)
{
    int          coef = (this->_cameraSpeed * 0.1) * this->_clock->getLastFrameTime().asMilliseconds();
    sf::Vector2i offset(0, 0);
    bool moved = false;

    if (direction == Directions::UP)
    {
        offset = this->_mainCamera->move(0.0, -coef, true);
        moved = true;
    }
    else if (direction == Directions::DOWN)
    {
        offset = this->_mainCamera->move(0.0, coef, true);
        moved = true;
    }
    else if (direction == Directions::LEFT)
    {
        offset = this->_mainCamera->move(-coef, 0.0, true);
        moved = true;
    }
    else if (direction == Directions::RIGHT)
    {
        offset = this->_mainCamera->move(coef, 0.0, true);
        moved = true;
    }
    this->_window->setView(*this->_mainCamera->getView());
    if (moved)
        this->moveStaticObjects(offset);
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
    this->_mainCamera->init(this->_window->getSize().x, this->_window->getSize().y,sf::FloatRect(0, 0, this->_window->getSize().x, this->_window->getSize().y), this->_cameraDelimited, this->_cameraDelimitation);
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