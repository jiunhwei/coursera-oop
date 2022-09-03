/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 24 Jul 2022 1:37:31am
    Author:  James

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"

//==============================================================================
PlaylistComponent::PlaylistComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    trackTitles.push_back("Track 1");
    trackTitles.push_back("Track 2");
    trackTitles.push_back("Track 3");
    trackTitles.push_back("Track 4");
    trackTitles.push_back("Track 5");
    trackTitles.push_back("Track 6");
    
    tableComponent.getHeader().addColumn("Track Title", 1, 300);
    tableComponent.getHeader().addColumn("Duration", 2, 75);
    tableComponent.getHeader().addColumn("Load Deck1", 3, 75);
    tableComponent.getHeader().addColumn("Load Deck2", 4, 75);
    tableComponent.getHeader().addColumn("Play", 5, 50);
    tableComponent.getHeader().addColumn("Load", 6, 50);
    //tableComponent.getHeader().addColumn("", 3, 200);

    tableComponent.setModel(this);

    addAndMakeVisible(tableComponent);
}

PlaylistComponent::~PlaylistComponent()
{
}

void PlaylistComponent::paint (juce::Graphics& g)
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
    g.drawText ("PlaylistComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void PlaylistComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    tableComponent.setBounds(0, 0, getWidth(), getHeight());
}

int PlaylistComponent::getNumRows() 
{
    return trackTitles.size();
}

void PlaylistComponent::paintRowBackground(Graphics& g, 
                                           int rowNumber, 
                                           int width, 
                                           int height, 
                                           bool rowIsSelected)
{
    if (rowIsSelected)
    {
        g.fillAll(Colours::orange);
    }
    else
    {
        g.fillAll(Colours::darkgrey);
    }
}

void PlaylistComponent::paintCell(Graphics& g, 
                                 int rowNumber, 
                                 int columnId, 
                                 int width, 
                                 int height, 
                                 bool rowIsSelected)
{ 
    g.drawText(trackTitles[rowNumber], 
               2, 
               1, 
               width - 4, 
               height, 
               Justification::centredLeft,
               true);
}

Component* PlaylistComponent::refreshComponentForCell(int rowNumber,
                                                      int columnId,
                                                      bool isRowSelected,
                                                      Component *existingComponentToUpdate)
{   
    if (columnId == 5)
    {
        if (existingComponentToUpdate == nullptr)
        {
            TextButton* btn = new TextButton{"PLAY"};
            String id{to_string(rowNumber)};
            btn->setComponentID(id);

            btn->addListener(this);
            existingComponentToUpdate = btn;
        }
    }
    return existingComponentToUpdate;
}

void PlaylistComponent::buttonClicked(Button* button)
{
    int id = stoi(button->getComponentID().toStdString());
    cout << "PlaylistComponent::buttonClicked " << trackTitles[id] << endl;
}