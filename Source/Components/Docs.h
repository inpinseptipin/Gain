/*
  ==============================================================================

    Docs.h
    Created: 23 Sep 2020 3:14:54am
    Author:  arsen

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
* Wrapper Over the JUCE's Web Browser Component to Display The Plugin's Documentation on Github
*/
class Docs  : public juce::Component
{
public:
    Docs();
    ~Docs() override;
    void paint (juce::Graphics&) override;
    void resized() override;
private:
    std::unique_ptr<juce::WebBrowserComponent> m_webBrowser;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Docs)
};
