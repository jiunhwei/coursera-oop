/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 18 Jul 2022 12:46:58am
    Author:  James

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

using namespace juce;
using namespace std;

class DJAudioPlayer : public AudioSource
{
    public:

        DJAudioPlayer(AudioFormatManager& _formatManager);
        ~DJAudioPlayer();

        //Implementation of the AudioSource class
        void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
        void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
        void releaseResources() override;

        //High Level functions
        void loadURL(URL audioURL);
        void setGain(double gain);
        void setSpeed(double ratio);
        void setPosition(double positionInSeconds);
        void setPositionRelative(double position);

        void start();
        void stop();

        //Get the relative position of the playhead
        double getPositionRelative();

    private:
        AudioFormatManager& formatManager;
        unique_ptr<AudioFormatReaderSource> readerSource;
        AudioTransportSource transportSource;
        ResamplingAudioSource resampleSource{&transportSource, false, 2};

};

