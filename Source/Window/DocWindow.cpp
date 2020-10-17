/*
  ==============================================================================

    Documentation.cpp
    Created: 23 Sep 2020 1:48:40am
    Author:  arsen

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DocWindow.h"

//==============================================================================
DocWindow::DocWindow() :
    DocumentWindow("Documentation", juce::Colour(juce::Colours::white), juce::DocumentWindow::closeButton, true)
{
    setUsingNativeTitleBar(true);
    setContentOwned(new Docs(), true);
    centreWithSize(getWidth(), getHeight());
    setVisible(false);
}

DocWindow::~DocWindow()
{
}






