#include "PluginProcessor.h"
#include "MainWindow.h"

//==============================================================================
Gain::Gain()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    addParameter(gainParameter = new juce::AudioParameterFloat("gain", "Gain", 0.0f, 1.0f, 0.5f));
    
    mGainSmoothed = gainParameter->get();
}

Gain::~Gain()
{
}

//==============================================================================
const juce::String Gain::getName() const
{
    return JucePlugin_Name;
}

bool Gain::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Gain::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Gain::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Gain::getTailLengthSeconds() const
{
    return 0.0;
}

int Gain::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Gain::getCurrentProgram()
{
    return 0;
}

void Gain::setCurrentProgram (int index)
{
}

const juce::String Gain::getProgramName (int index)
{
    return {};
}

void Gain::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Gain::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    
}

void Gain::releaseResources()
{
    
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Gain::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Gain::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    
   
        float* channelLeft = buffer.getWritePointer(0);
        float* channelRight = buffer.getWritePointer(1);

        for (int sample = 0; sample < buffer.getNumSamples(); sample++)
        {  
            mGainSmoothed = mGainSmoothed - 0.05 * (mGainSmoothed - gainParameter->get()); //May Cause Overflow
            channelLeft[sample] *= mGainSmoothed;
            channelRight[sample] *= mGainSmoothed;    
        }
        
    
}

//==============================================================================
bool Gain::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Gain::createEditor()
{
    return new MainWindow(*this);
}

//==============================================================================
void Gain::getStateInformation (juce::MemoryBlock& destData)
{
    
}

void Gain::setStateInformation (const void* data, int sizeInBytes)
{
    
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Gain();
}




