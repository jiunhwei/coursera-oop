/*
  ==============================================================================

    WaveformDisplay.h
    Created: 22 Jul 2022 10:31:16pm
    Author:  James

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

using namespace std;
using namespace juce;

//==============================================================================
/*
*/
class WaveformDisplay  : public juce::Component,
                         public ChangeListener
{
public:
    WaveformDisplay(AudioFormatManager& formatManagerToUse,
                    AudioThumbnailCache& cacheToUse);
    ~WaveformDisplay() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void changeListenerCallback(ChangeBroadcaster* source) override;

    void loadURL(URL audioURL);

    //Set the relative position of the playhead
    void setPositionRelative(double position);

private:
    AudioThumbnail audioThumb;
    bool fileLoaded;
    double localPosition;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
