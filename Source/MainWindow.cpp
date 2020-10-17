#include "PluginProcessor.h"
#include "MainWindow.h"

//==============================================================================
MainWindow::MainWindow(Gain& p)
    : AudioProcessorEditor (&p), m_audioProcessor (p)
{
    setSize(400, 300);

    auto& params = m_audioProcessor.getParameters();

    gainParameter = (juce::AudioParameterFloat*)params.getUnchecked(0);
    

    docWindow.reset(new DocWindow());
    
    addAndMakeVisible(m_Documentation);
    m_Documentation.setButtonText("Click here to view the Documentation");
    m_Documentation.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::black);
    m_Documentation.setColour(juce::TextButton::ColourIds::textColourOnId, juce::Colours::white);


    m_Documentation.onClick = [this]
    {
        if(!docWindow->isVisible())
            docWindow->setVisible(true);
    };

    addAndMakeVisible(ml_header);
    ml_header.setText("Plugin : Gain", juce::dontSendNotification);
    ml_header.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    ml_header.setColour(juce::Label::ColourIds::outlineColourId, juce::Colours::blueviolet);
    ml_header.setJustificationType(juce::Justification::horizontallyCentred);
    ml_header.setFont(juce::Font(32.0f, 1));
    ml_header.setEditable(false);

    addAndMakeVisible(mt_switch);
    mt_switch.setColour(juce::ToggleButton::ColourIds::textColourId, juce::Colours::white);
    mt_switch.setColour(juce::ToggleButton::ColourIds::tickColourId, juce::Colours::green);
    mt_switch.setColour(juce::ToggleButton::ColourIds::tickDisabledColourId, juce::Colours::red);
    mt_switch.setButtonText("Switch to DB Control");

    


    addAndMakeVisible(m_gain);
    m_gain.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    m_gain.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    m_gain.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::black);
    m_gain.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::blue);
    m_gain.setRange(gainParameter->range.start, gainParameter->range.end);
    m_gain.setValue(*gainParameter);
    


    addAndMakeVisible(ml_gainValue);
    ml_gainValue.setColour(juce::Label::ColourIds::backgroundColourId, juce::Colours::black);
    ml_gainValue.setColour(juce::Label::ColourIds::outlineColourId, juce::Colours::blue);
    ml_gainValue.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    ml_gainValue.setFont(juce::Font(24.0f, 1));
    ml_gainValue.setJustificationType(juce::Justification::horizontallyCentred);
    ml_gainValue.setEditable(false);

    addAndMakeVisible(mc_presets);
    mc_presets.setColour(juce::ComboBox::ColourIds::arrowColourId, juce::Colours::green);
    mc_presets.setColour(juce::ComboBox::ColourIds::backgroundColourId, juce::Colours::black);
    mc_presets.setColour(juce::ComboBox::ColourIds::outlineColourId, juce::Colours::green);
    mc_presets.setColour(juce::ComboBox::ColourIds::focusedOutlineColourId, juce::Colours::blue);
    mc_presets.setColour(juce::ComboBox::ColourIds::buttonColourId, juce::Colours::black);
    mc_presets.setTextWhenNoChoicesAvailable("Empty");
    mc_presets.setTextWhenNothingSelected("Presets");

    addPresetArray({ "Mute","Max","-6dB" });

    mc_presets.onChange = [this]
    {
        switch (mc_presets.getSelectedId())
        {
            case 1: *gainParameter = 0.0;
                    m_gain.setValue(*gainParameter);
                    setGainValueLabel();
                    break;

            case 2: *gainParameter = 1.0;
                    m_gain.setValue(*gainParameter);
                    setGainValueLabel();
                    break;

            case 3: *gainParameter = 0.5;
                    m_gain.setValue(*gainParameter);
                    setGainValueLabel();
                    break;

            default:setGainValueLabel();
        }           
    };

    

    m_gain.onValueChange = [this]
    {
        *gainParameter = m_gain.getValue();
        setGainValueLabel();
        
    };

    mt_switch.onClick = [this]
    {
        if (mt_switch.getToggleState())
        {
            ml_gainValue.setText(juce::String(20 * (double)log10(m_gain.getValue())) + "dB", juce::dontSendNotification);
            mt_switch.setButtonText("Switch to Linear Gain Control");
        }
        else
        {
            ml_gainValue.setText("Linear Gain : " + juce::String(m_gain.getValue()), juce::dontSendNotification);
            mt_switch.setButtonText("Switch to DB Control");
        }
    };

}

//==============================================================================
MainWindow::~MainWindow()
{

}

//==============================================================================
void MainWindow::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::black);
    g.fillAll();
}

//==============================================================================
void MainWindow::resized()
{
    ml_header.setBounds(0, 0, getRight(), 2 * getBottom() / 10);
    mc_presets.setBounds(3 * getRight() / 4, 2 * getBottom()/10 , getRight() / 4, getBottom() / 10);
    mt_switch.setBounds(0, 2 * getBottom() / 10, getRight() / 2, getBottom() / 10);
    m_gain.setBounds(0, 3 * getBottom() / 10, getRight(), 3 * getBottom() / 10);
    ml_gainValue.setBounds(0, m_gain.getBottom(), getRight(), getBottom() / 10);
    m_Documentation.setBounds(0, 8 * getBottom() / 10, getRight(), 2 * getBottom() / 10);
}

void MainWindow::addPreset(const juce::String& preset)
{
    mc_presets.addItem(preset, mc_presets.getNumItems()+1);
}

void MainWindow::addPresetArray(const juce::StringArray& presets)
{
    mc_presets.addItemList(presets, mc_presets.getNumItems() + 1);
}

void MainWindow::setGainValueLabel()
{
    if (mt_switch.getToggleState())
    {
        ml_gainValue.setText(juce::String(20 * (double)log10(m_gain.getValue())) + "dB", juce::dontSendNotification);
    }
    else
    {
        ml_gainValue.setText("Linear Gain : " + juce::String(m_gain.getValue()), juce::dontSendNotification);
    }
}



