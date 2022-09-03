/*
  ==============================================================================

    DJAudioPlayer.cpp
    Created: 18 Jul 2022 12:46:58am
    Author:  James

  ==============================================================================
*/

#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(AudioFormatManager& _formatManager)  
                           : formatManager(_formatManager)
{

}

DJAudioPlayer::~DJAudioPlayer() 
{

}

void DJAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate) 
{
    //formatManager.registerBasicFormats();
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void DJAudioPlayer::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) 
{
    //transportSource.getNextAudioBlock(bufferToFill);
    resampleSource.getNextAudioBlock(bufferToFill);
}

void DJAudioPlayer::releaseResources() 
{
    transportSource.releaseResources();
    resampleSource.releaseResources();
}

void DJAudioPlayer::loadURL(URL audioURL) 
{
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    if (reader != nullptr) //good file
    {
        std::unique_ptr<AudioFormatReaderSource> newSource(new AudioFormatReaderSource(reader, true));
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset(newSource.release());
    }
}

void DJAudioPlayer::setGain(double gain) 
{
    if (gain < 0 || gain > 1.0)
    {
        cout << "DJAudioPlayer::setGain gain should be between 0 and 1.0" << endl;
    }
    else
    {
        transportSource.setGain(gain);
    }
}

void DJAudioPlayer::setSpeed(double ratio) 
{
    if (ratio < 0 || ratio > 100.0)
    {
        cout << "DJAudioPlayer::setSpeed ratio should be between 0 and 100.0" << endl;
    }
    else
    {
        resampleSource.setResamplingRatio(ratio);
    }
}
void DJAudioPlayer::setPosition(double positionInSeconds) 
{
    transportSource.setPosition(positionInSeconds);
}

void DJAudioPlayer::setPositionRelative(double position)
{
    if (position < 0 || position > 1.0)
    {
        cout << "DJAudioPlayer::setPositionRelative position should be between 0 and 1.0" << endl;
    }
    else
    {
        double positionInSeconds = transportSource.getLengthInSeconds() * position;
        setPosition(positionInSeconds);
    }
}

void DJAudioPlayer::start() 
{
    transportSource.start();
}

void DJAudioPlayer::stop() 
{
    transportSource.stop();
}

double DJAudioPlayer::getPositionRelative()
{
    if (transportSource.getCurrentPosition() == 0)
    {
        return 0;
    }
    else 
    {
        return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
    }
    //return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}
