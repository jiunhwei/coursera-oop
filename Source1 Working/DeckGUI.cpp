/*
  ==============================================================================

    DeckGUI.cpp
    Created: 19 Jul 2022 4:48:29pm
    Author:  James

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player,
                 AudioFormatManager& formatManagerToUse,
                 AudioThumbnailCache& cacheToUse) 
                 : player(_player),
                 waveformDisplay(formatManagerToUse, cacheToUse)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);

    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(positionSlider);

    addAndMakeVisible(waveformDisplay);

    //Adding listener events to the buttons and sliders
    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);

    volSlider.addListener(this);
    speedSlider.addListener(this);
    positionSlider.addListener(this);

    //Min and max ranges for sliders
    volSlider.setRange(0.0, 1.0);
    speedSlider.setRange(0.0, 100.0);
    positionSlider.setRange(0.0, 1.0);

    startTimer(1000); //1000 = 1 second
}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("DeckGUI", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void DeckGUI::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    double rowHeight = getHeight() / 8;
    playButton.setBounds(0, 0, getWidth(), rowHeight);
    stopButton.setBounds(0, rowHeight, getWidth(), rowHeight);
    loadButton.setBounds(0, rowHeight * 7, getWidth(), rowHeight);

    volSlider.setBounds(0, rowHeight * 2, getWidth(), rowHeight);
    speedSlider.setBounds(0, rowHeight * 3, getWidth(), rowHeight);
    positionSlider.setBounds(0, rowHeight * 4, getWidth(), rowHeight);

    waveformDisplay.setBounds(0, rowHeight * 5, getWidth(), rowHeight*2);
}

void DeckGUI::buttonClicked(Button* button)
{
    if (button == &playButton)
    {
        cout << "Play Button was clicked " << endl;
        //transportSource.start();
        player->start();
    }
    else if (button == &stopButton)
    {
        cout << "Stop Button was clicked " << endl;
        //transportSource.stop();
        player->stop();
    }
    else if (button == &loadButton)
    {
        //cout << "Load Button was clicked " << endl;
        // this does work in 6.1 but the syntax is a little funky
        // https://docs.juce.com/master/classFileChooser.html#ac888983e4abdd8401ba7d6124ae64ff3
        // - configure the dialogue
        auto fileChooserFlags = FileBrowserComponent::canSelectFiles;

        // - launch out of the main thread
        // - note how we use a lambda function which you've probably
        // not seen before. Please do not worry too much about that. 
        fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
        {
            File chosenFile = chooser.getResult();
            //loadURL(URL{chosenFile});
            player->loadURL(URL{ chosenFile });
            waveformDisplay.loadURL(URL{ chosenFile });
        });
    }
}

void DeckGUI::sliderValueChanged(Slider* slider)
{
    if (slider == &volSlider)
    {
        player->setGain(slider->getValue());
    }
    else if (slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
    }
    else if (slider == &positionSlider)
    {
        player->setPositionRelative(slider->getValue());
    }
}

bool DeckGUI::isInterestedInFileDrag(const StringArray& audioFiles)
{
    /*
    cout << "DeckGUI::isInterestedInFileDrag" << endl;
    return true;
    */

    
    for (auto audioFileSelected : audioFiles)
    {
        if (audioFileSelected.contains(".mp3") || audioFileSelected.contains(".wav"))
        {
            cout << "DeckGUI::isInterestedInFileDrag" << endl;
            return true;
        }
    }
    
}

void DeckGUI::filesDropped(const StringArray& audioFiles, int x, int y) 
{
    /*
    cout << "DeckGUI::filesDropped" << endl;
    if (audioFiles.size() == 1)
    {
        URL audioFileURL = URL{File{audioFiles[0]}};
        player->loadURL(audioFileURL);
    }
    */

    
    for (auto audioFileDropped : audioFiles)
    {
        if(isInterestedInFileDrag(audioFileDropped))
        {
            cout << "DeckGUI::filesDropped: " << audioFileDropped << endl;
            URL audioFileURL = URL{File{audioFiles[0]}};
            player->loadURL(audioFileURL);
            return;
        }
    }
    
}

void DeckGUI::timerCallback()
{
    waveformDisplay.setPositionRelative(
            player->getPositionRelative());
}