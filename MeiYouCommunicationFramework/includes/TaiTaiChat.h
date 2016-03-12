//
// Created by margoul_1 on 12/03/16.
//

#ifndef MEIYOUCOMMUNICATION_TAITAICHAT_H
#define MEIYOUCOMMUNICATION_TAITAICHAT_H

# include <iostream>
# include <string>
# include <SFML/Graphics.hpp>

class TaiTaiChat {
public:
    TaiTaiChat();
    ~TaiTaiChat();
    void        setIncomingMessage(std::string, bool);
    std::string getIncomingMessage(bool);
    void        setWindowName(std::string);
    std::string getWindowName();
    void        setFontPath(std::string);
    std::string getFontPath();
private:
    int windowLoop();
    std::string _lastIncomingMessage;
    std::string _myLastMessage;
    std::string _windowName;
    std::string _fontPath;
};


#endif //MEIYOUCOMMUNICATION_TAITAICHAT_H
