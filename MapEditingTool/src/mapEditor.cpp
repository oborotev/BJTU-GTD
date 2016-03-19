//
// Created by storm on 19/03/16.
//

# include "mapEditor.h"

MapEditor::~MapEditor()
{
    delete _graphicHandler;
    delete _mediaHandler;
    delete _tilesetHandler;
}

const int       MapEditor::init()
{
    this->_graphicHandler = new GraphicHandler("Map Editor");
}

const int       MapEditor::start()
{
    this->_graphicHandler->init();
    return 0;
}