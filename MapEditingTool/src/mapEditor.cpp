//
// Created by storm on 19/03/16.
//

# include "mapEditor.h"

MapEditor::~MapEditor()
{
    delete _graphicHandler;
}

const int       MapEditor::init()
{
    sf::Texture test;
    const int level[] =
            {
                    0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                    0, 1, 1, 1, 1, 1, 1, 20, 0, 0, 0, 2, 0, 0, 0, 0,
                    1, 1, 0, 0, 0, 0, 0, 20, 3, 3, 3, 3, 3, 3, 3, 3,
                    0, 1, 0, 0, 2, 0, 3, 3, 23, 0, 1, 1, 1, 0, 0, 0,
                    0, 1, 1, 0, 3, 3, 3, 20, 54, 0, 1, 1, 1, 2, 0, 0,
                    0, 0, 1, 0, 3, 0, 2, 2, 20, 0, 1, 1, 1, 1, 2, 0,
                    2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
                    0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
            };

    this->_graphicHandler = new GraphicHandler("Map Editor");
    this->_tilesetHandler = this->_graphicHandler->getTilesetHandler();
    this->_mediaHandler = this->_graphicHandler->getMediaHandler();
    this->_mediaHandler->addNewTexture("../media/textures/tileset.gif", "map_tileset");
    this->_tilesetHandler->init(this->_mediaHandler->getTexture("map_tileset"), sf::Vector2u(32, 32), level, 16, 8);
    return 0;
}

const int       MapEditor::start()
{
    bool        running = true;

    if (this->_graphicHandler->init())
    {
        std::cout << "There was a problem with the graphical initialization" << std::endl;
        return 1;
    }
    this->_graphicHandler->launch();
    while (running)
    {
        this->_graphicHandler->_mutex.lock();
        if (!this->_graphicHandler->getIsAlive())
            running = false;
        this->_graphicHandler->_mutex.unlock();
        sf::sleep(sf::microseconds(10000));
    }
    this->_graphicHandler->terminate();
    return 0;
}