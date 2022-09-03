/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 22 Jul 2022 10:31:16pm
    Author:  James

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveformDisplay.h"

using namespace std;
using namespace juce;

//==============================================================================
WaveformDisplay::WaveformDisplay(AudioFormatManager& formatManagerToUse,
                                AudioThumbnailCache& cacheToUse)
                                : audioThumb(1000, formatManagerToUse, cacheToUse),
                                fileLoaded(false),
                                localPosition(0) //Sets default position to 0
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    audioThumb.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::orange);

    if (fileLoaded)
    {
        audioThumb.drawChannel(g,
                   getLocalBounds(),
                   0,
                   audioThumb.getTotalLength(),
                   0,
                   1.0f);
        g.setColour(Colours::lightgreen);
        g.drawRect(localPosition * getWidth(), 0, getWidth() / 20, getHeight());
    }
    else
    {
        g.setFont (20.0f);
        g.drawText ("File not loaded.........", getLocalBounds(),
                    juce::Justification::centred, true);   // draw some placeholder text

    }  
}

void WaveformDisplay::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void WaveformDisplay::loadURL(URL audioURL)
{
    audioThumb.clear();
    fileLoaded = audioThumb.setSource(new URLInputSource(audioURL));
    if (fileLoaded)
    {
        cout << "WaveformDisplay::loadURL " << endl;
        repaint();
    }
    else
    {
        cout << "Invalid URL " << endl;
    }
}

void WaveformDisplay::changeListenerCallback(ChangeBroadcaster* source)
{
    cout << "WaveformDisplay::changeListenerCallback CHANGE RECEIVED " << endl;
    repaint();
}

void WaveformDisplay::setPositionRelative(double position)
{
    if (position != localPosition)
    {
        localPosition = position;
        repaint();
    }
}