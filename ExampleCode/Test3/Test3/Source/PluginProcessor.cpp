/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Test3AudioProcessor::Test3AudioProcessor()
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
, vts(*this, nullptr, "parma", buildParameterLayout())
{
    vts.addParameterListener("freq", this);
    osc.buildUserInterface(&ctrl);
}

Test3AudioProcessor::~Test3AudioProcessor()
{
}

juce::AudioProcessorValueTreeState::ParameterLayout Test3AudioProcessor::buildParameterLayout() {
    using namespace std;
    using namespace juce;
    
    AudioProcessorValueTreeState::ParameterLayout layout;
    
    {
        auto param = make_unique<AudioParameterFloat>("freq", "Frequency", 2e1, 2e4, 1e3);
        layout.add(move(param));
    }
    
    return layout;
}

//==============================================================================
const juce::String Test3AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Test3AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Test3AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Test3AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Test3AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Test3AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Test3AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Test3AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Test3AudioProcessor::getProgramName (int index)
{
    return {};
}

void Test3AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Test3AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    osc.init(sampleRate);
}

void Test3AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Test3AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Test3AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    osc.compute(buffer.getNumSamples(), nullptr, buffer.getArrayOfWritePointers());
    
    buffer.applyGain(0.1);
}


void Test3AudioProcessor::parameterChanged (const juce::String& parameterID, float newValue)
{
    if (parameterID == "freq") {
        ctrl.setParamValue("/Oscillator/freq", newValue);
    }
}

//==============================================================================
bool Test3AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Test3AudioProcessor::createEditor()
{
    return new Test3AudioProcessorEditor (*this);
}

//==============================================================================
void Test3AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Test3AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Test3AudioProcessor();
}
