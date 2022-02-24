/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

using namespace juce;
using namespace std;

list<GUI*> GUI::fGuiList;

//==============================================================================
Test4AudioProcessor::Test4AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::mono(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::mono(), true)
                     #endif
                       )
#endif
, paramUI(this)
{
    dsp.buildUserInterface(&gui);
    dsp2.buildUserInterface(&gui2);
    dsp.buildUserInterface(&paramUI);
//    dsp2.buildUserInterface(&paramUI);
}

Test4AudioProcessor::~Test4AudioProcessor()
{
}


//==============================================================================
const juce::String Test4AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Test4AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Test4AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Test4AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Test4AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Test4AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Test4AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Test4AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Test4AudioProcessor::getProgramName (int index)
{
    return {};
}

void Test4AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Test4AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    dsp.init(sampleRate);
    dsp2.init(sampleRate);
}

void Test4AudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Test4AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    if (layouts.getMainInputChannels() != 1)
        return false;
    if (layouts.getMainOutputChannels() != 1)
        return false;
    return true;
}
#endif




void Test4AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;

    int nSamples = buffer.getNumSamples();
    float** data = buffer.getArrayOfWritePointers();
    dsp.compute(nSamples, data, data);
    dsp2.compute(nSamples, data, data);
}

//==============================================================================
bool Test4AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Test4AudioProcessor::createEditor()
{
    return new Test4AudioProcessorEditor (*this);
}

//==============================================================================
void Test4AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
}

void Test4AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Test4AudioProcessor();
}
