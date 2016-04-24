//
// Created by storm on 23/04/16.
//

# include "speechSound.h"
# include <iostream>

SpeechSound::SpeechSound(const sfx::FrameClock *clock)
{
    this->_clock = clock;
    this->_begin = false;
    this->_punctuationSymbolsHalfTime = ",;";
    this->_punctuationSymbols = "?!.";
}

void SpeechSound::clearText()
{
    this->_begin = false;
}

const int SpeechSound::textToSpeech(std::vector<std::string> &dialogs, sf::Text &textObject, sf::Sound *sound, const bool fastForward, const sf::Time &delay)
{
    if (!_begin) {
        this->_currentDialog = dialogs.begin();
        this->_currentTime = delay;
        this->_temp = this->_currentDialog->c_str()[0];
        this->_begin = true;
        this->_punctuation = sf::seconds(1);
    }
    if (this->_currentDialog == dialogs.end())
        return (0);
    if (fastForward)
    {
        this->_temp = this->_currentDialog->c_str();
        textObject.setString(this->_temp);
        sound->play();
        return (1);
    }
    while (this->_currentDialog->compare(this->_temp))
    {
        if (_currentTime < delay || _punctuation < sf::seconds(1)) {
            this->_currentTime += this->_clock->getLastFrameTime();
            this->_punctuation += this->_clock->getLastFrameTime();
        }
        else
        {
            this->_temp += this->_currentDialog->c_str()[this->_temp.size()];
            if (this->_punctuationSymbols.find(this->_temp.back()) != std::string::npos)
                this->_punctuation = sf::seconds(0);
            else if (this->_punctuationSymbolsHalfTime.find(this->_temp.back()) != std::string::npos)
                this->_punctuation = sf::seconds(0.5);
            while (this->_currentDialog->c_str()[this->_temp.size()] == ' ' ||
                    this->_currentDialog->c_str()[this->_temp.size()] == '\n') {
                this->_temp += this->_currentDialog->c_str()[this->_temp.size()];
            }
            textObject.setString(this->_temp);
            sound->play();
            _currentTime = sf::seconds(0);
        }
        return (2);
    }
    _currentDialog++;
    if (this->_currentDialog == dialogs.end())
        return (0);
    this->_temp = "";
    this->_punctuation = sf::seconds(1);
    this->_currentTime = delay;
    return (1);
}