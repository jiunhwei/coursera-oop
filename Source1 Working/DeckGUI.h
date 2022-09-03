/*
  ==============================================================================

    DeckGUI.h
    Created: 19 Jul 2022 4:48:29pm
    Author:  James

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"

using namespace std;
using namespace juce;

//==============================================================================
/*
*/

//Set of Inheritance relationships
class DeckGUI : public Component,
                public Button::Listener,
                public Slider::Listener,
                public FileDragAndDropTarget,
                public Timer //Inherit Timer class
{
public:
    DeckGUI(DJAudioPlayer* player,
            AudioFormatManager & formatManagerToUse,
            AudioThumbnailCache & cacheToUse);
    ~DeckGUI() override;

    void paint (Graphics&) override;
    void resized() override;

    /** Implement Button::Listener */
    void buttonClicked(Button*) override;

    /** Implement Slider::Listener */
    void sliderValueChanged(Slider* slider) override;

    //Drag and Drop
    bool isInterestedInFileDrag(const StringArray &audioFiles) override;
    void filesDropped(const StringArray& audioFiles, int x, int y) override;

    void timerCallback() override;

private:
    //Buttons in DeckGUI component
    TextButton playButton{ "Play Button" };
    TextButton stopButton{ "Stop Button" };
    TextButton loadButton{ "Load Button" };

    //Sliders in DeckGUI component
    Slider volSlider;
    Slider speedSlider;
    Slider positionSlider;

    FileChooser fChooser{ "Select a file..." };

    DJAudioPlayer* player;

    WaveformDisplay waveformDisplay;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
