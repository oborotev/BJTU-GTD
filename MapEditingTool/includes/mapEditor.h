//
// Created by storm on 19/03/16.
//

#ifndef MAPEDITINGTOOL_MAPEDITOR_H_H
#define MAPEDITINGTOOL_MAPEDITOR_H_H

# include <iostream>
# include "mediaHandler.h"
# include "tilesetHandler.h"
# include "graphicHandler.h"

class MapEditor
{
public:
    MapEditor() {};
    ~MapEditor();
    const int   init();
    const int   start();
private:
    GraphicHandler *_graphicHandler;
    MediaHandler   *_mediaHandler;
    TilesetHandler *_tilesetHandler;
};

#endif //MAPEDITINGTOOL_MAPEDITOR_H_H
