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

class GraphicHandler
{
public:
    GraphicHandler(const std::string &title, unsigned int modeWidth = 1024, unsigned int modeHeight = 768, unsigned int modeBitsPerPixel=0, const bool fixedSize = true);
    ~GraphicHandler();
    const int   init();
    void        loop();
    void        launch() const;
    void        terminate() const;
    void        drawer() const;
    const bool  getIsAlive();
    TilesetHandler* getTilesetHandler();
    MediaHandler*   getMediaHandler();
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
    TilesetHandler *_tilesetHandler;
    //Cycle
    bool         _isAlive;
};

#endif //MAPEDITINGTOOL_GRAPHICHANDLER_H
