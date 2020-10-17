#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Window/DocWindow.h"
#include <cmath>

//==============================================================================
/*
* Plugin User Interface , Contains Plugin's User Interface Controls.
*/
class MainWindow  : public juce::AudioProcessorEditor
{
public:
    MainWindow  (Gain&);
    ~MainWindow() override;
 
//  Handles Design of Plugin Window
    void paint (juce::Graphics&) override;

//  Handles Resizing of UI Controls when the Window is Maximized , Minimized or Resized
    void resized() override;


//==============================================================================
private:
//  Gain Audio Processor Reference to handle the processing object
    Gain& m_audioProcessor;

//  Audio Parameter Float to get the reference of the Gain Parameter in the Processor Object
    juce::AudioParameterFloat* gainParameter;
    
//==============================================================================

/*  User Interface Controls
*/

//  Documentation Window Pointer, is Initialized at Run Time
    std::unique_ptr<DocWindow> docWindow;
//  Plugin UserInterface Controls
    juce::TextButton m_Documentation;
    juce::Slider m_gain;
    juce::Label ml_header;
    juce::Label ml_gainValue;
    juce::ComboBox mc_presets;
    juce::ToggleButton mt_switch;

//==============================================================================

/*  Private Functions
*/

//  Preset Management Functions
    void addPreset(const juce::String& preset);
    void addPresetArray(const juce::StringArray& presets);

    void setGainValueLabel();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
};
