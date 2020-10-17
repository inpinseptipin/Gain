/*
  ==============================================================================

    Docs.cpp
    Created: 23 Sep 2020 3:14:54am
    Author:  arsen

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Docs.h"

//==============================================================================
Docs::Docs()
{
    m_webBrowser.reset(new juce::WebBrowserComponent());
    setSize(800, 600);
    addAndMakeVisible(m_webBrowser.get());
    m_webBrowser->goToURL("https://github.com/inpinseptipin/Gain");
    m_webBrowser->refresh();
}

Docs::~Docs()
{
}

void Docs::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::grey);
}

void Docs::resized()
{
   m_webBrowser->setBounds(0, 0, 800, 600);
}
