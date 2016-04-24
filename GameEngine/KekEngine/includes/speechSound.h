//
// Created by storm on 23/04/16.


#ifndef GAMEENGINE_SPEECHSOUND_H_H
#define GAMEENGINE_SPEECHSOUND_H_H

# include <SFML/Graphics.hpp>
# include <SFML/Audio.hpp>
# include "frameClock.h"

class SpeechSound
{
public:
    SpeechSound(const sfx::FrameClock *clock);
    const int textToSpeech(std::vector<std::string> &dialogs, sf::Text &textObject, sf::Sound *sound, const bool fastForward=false, const sf::Time &delay=sf::seconds(0.05));
    void clearText();
private:
    const sfx::FrameClock *_clock;
    std::string _temp;
    sf::Time _currentTime;
    std::vector<std::string>::iterator _currentDialog;
    std::vector<std::string> _dialogs;
    bool _begin;
    sf::Time _punctuation;
    std::string _punctuationSymbols;
    std::string _punctuationSymbolsHalfTime;
};

#endif //GAMEENGINE_SPEECHSOUND_H_H
