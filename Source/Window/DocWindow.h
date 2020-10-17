/*
  ==============================================================================

    Documentation.h
    Created: 23 Sep 2020 1:48:40am
    Author:  arsen

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Components/Docs.h"

//==============================================================================
/*
* Opens a New Window using Native OS Title Bar and Displays JUCE's Component on it
*/
class DocWindow  : public juce::DocumentWindow
{
public:
    DocWindow();
    ~DocWindow() override;
    void closeButtonPressed()
    {
        setVisible(false);
    }
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DocWindow)
};
