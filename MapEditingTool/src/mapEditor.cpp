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
    std::array<int, 171> tileDefinition;

    tileDefinition.fill(1);
    tileDefinition[3] = TilesetHandler::FREE;
    this->_graphicHandler = new GraphicHandler("Map Editor", "../../common/media/fonts/DTM-Mono.otf", 1024, 768, false, true, sf::IntRect(0,0, 1200, 800));
    this->_tilesetHandler = this->_graphicHandler->getBaseMap();
    this->_mediaHandler = this->_graphicHandler->getMediaHandler();
    this->_mediaHandler->addNewTexture("../media/textures/tileset.gif", "map_tileset");
    this->_mediaHandler->addNewTexture("../media/textures/arrow-right.png", "arrow_right");
    //Player Init
    this->_mediaHandler->addNewTexture("../../common/media/textures/frisk.png", "frisky");
    this->_graphicHandler->initPlayer(500, 500, 20, true, sf::seconds(0.2), this->_mediaHandler->getTexture("frisky"));
    this->_graphicHandler->getPlayer()->addFrameState(LivingEntity::Direction::STILL, sf::IntRect(0, 0, 20, 30));
    //Player Init End
    this->_mediaHandler->addNewShape(new sf::RectangleShape(sf::Vector2f(240, 768)), "tile_choose_bg", true, sf::Vector2i(804, 0));
    this->_mediaHandler->getShape("tile_choose_bg")->setFillColor(sf::Color(0, 31, 63));
    this->_mediaHandler->addNewSprite(this->_mediaHandler->getTexture("arrow_right"), "arrow_right");
    this->_mediaHandler->getSprite("arrow_right")->setPosition(940, 680);
    this->_tilesetHandler->init(this->_mediaHandler->getTexture("map_tileset"), sf::Vector2u(32, 32), "../media/maps/base", 0, 0, tileDefinition.data());
    return 0;
}

const int       MapEditor::start()
{
    if (this->_graphicHandler->init())
    {
        std::cout << "There was a problem with the graphical initialization" << std::endl;
        return 1;
    }
    this->_graphicHandler->launch();
    while (this->_graphicHandler->getIsAlive())
    {
        while (this->_graphicHandler->pollEvent())
            if (this->_graphicHandler->eventTriggered(sf::Event::Closed))
                this->_graphicHandler->terminate();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            this->_graphicHandler->moveCamera(GraphicHandler::Directions::LEFT);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            this->_graphicHandler->moveCamera(GraphicHandler::Directions::RIGHT);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            this->_graphicHandler->moveCamera(GraphicHandler::Directions::UP);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            this->_graphicHandler->moveCamera(GraphicHandler::Directions::DOWN);
        this->_graphicHandler->drawBaseMap();
        this->_graphicHandler->draw(*this->_graphicHandler->getPlayer()->getAnimation());
        this->_graphicHandler->draw(*this->_mediaHandler->getShape("tile_choose_bg"));
        this->_graphicHandler->draw(*this->_mediaHandler->getSprite("arrow_right"));
        this->_graphicHandler->loop();
    }
    return 0;
}