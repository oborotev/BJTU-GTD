//
// Created by storm on 18/03/16.
//

#ifndef MAPEDITINGTOOL_GRAPHICHANDLER_H
# define MAPEDITINGTOOL_GRAPHICHANDLER_H

# include <string>
# include <SFML/Window.hpp>
# include <SFML/Graphics.hpp>
# include <SFML/System.hpp>
# include "tilesetHandler.h"
# include "mediaHandler.h"
# include "frameClock.h"
# include "clockHUD.h"

class GraphicHandler
{
public:
    GraphicHandler(const std::string &title, const std::string &mainFontPath, unsigned int modeWidth = 1024, unsigned int modeHeight = 768, unsigned int modeBitsPerPixel=0, const bool fixedSize = true, const bool fpsDebug = false);
    ~GraphicHandler();
    const int   init();
    void        loop();
    void        launch();
    void        terminate();
    void        drawBaseMap() const;
    const bool  getIsAlive();
    TilesetHandler* getBaseMap();
    MediaHandler*   getMediaHandler();
    //Events
    const bool  pollEvent();
    const bool  eventTriggered(const sf::Event::EventType& eventType) const;
    //Debug
    void        setFpsDebug(const bool &option);
    //Drawing
    void        draw(const sf::Drawable &drawable) const;
    //Mutex
    sf::Mutex   _mutex;
private:
    //Window object
    sf::RenderWindow  *_window;
    //Window properties
    unsigned int _modeWidth;
    unsigned int _modeHeight;
    unsigned int _modeBitsPerPixel;
    std::string  _title;
    //Window options
    bool         _fixedSize;
    //Event object
    sf::Event    _event;
    //Thread loop
    sf::Thread   *_loop;
    //Handlers
    MediaHandler   *_mediaHandler;
    TilesetHandler *_baseMap;
    //Cycle
    bool         _isAlive;
    //Clock
    sfx::FrameClock *_clock;
    ClockHUD        *_clockHUD;
    //Fonts
    std::string      _mainFontPath;
    sf::Font         _mainFont;
    //Debug
    bool             _fpsDebug;
};

#endif //MAPEDITINGTOOL_GRAPHICHANDLER_H
