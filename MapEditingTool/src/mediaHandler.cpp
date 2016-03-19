//
// Created by storm on 19/03/16.
//

# include "mediaHandler.h"

const int   MediaHandler::loadNewTexture(const std::string &path, const std::string &name)
{
    this->_textures.push_back(std::make_pair(path, name));
}
