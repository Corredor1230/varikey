/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

using namespace juce;
using namespace std;

//==============================================================================
TestSynthAudioProcessor::TestSynthAudioProcessor()
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

, vts(*this, nullptr, "Params", buildParameters())
{
    vts.addParameterListener("freq1", this);
    vts.addParameterListener("freq2", this);
    vts.addParameterListener("filtCutoff", this);
    vts.addParameterListener("gain", this);

    dsp.buildUserInterface(&ctrl);

    for (int i = 0; i < ctrl.getParamsCount(); i++)
    {
        DBG(ctrl.getParamAddress(i));
    }


}

TestSynthAudioProcessor::~TestSynthAudioProcessor()
{
}

AudioProcessorValueTreeState::ParameterLayout TestSynthAudioProcessor::buildParameters() {
    AudioProcessorValueTreeState::ParameterLayout layout;

    {
        auto param = make_unique<AudioParameterFloat>("freq1", "Frequency", 20, 20000, 200);
        layout.add(move(param));
    }

    {
        auto param = make_unique<AudioParameterFloat>("freq2", "Frequency2", 20, 20000, 200);
        layout.add(move(param));

    }
     
    {
        auto param = make_unique<AudioParameterFloat>("filtCutoff", "cutoff", 20, 20000, 200);
        layout.add(move(param));

    }

    {
        auto param = make_unique<AudioParameterFloat>("gain", "gain", 20, 20000, 200);
        layout.add(move(param));

    }

    return layout;
}

//==============================================================================
const juce::String TestSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TestSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TestSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TestSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TestSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TestSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TestSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TestSynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String TestSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void TestSynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void TestSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    dsp.init(sampleRate);
}

void TestSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TestSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    if (layouts.getMainInputChannels() != 2)
        return false;
    if (layouts.getMainOutputChannels() != 2)
        return false;
    return true;
}
#endif

void TestSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (int channel = 0; channel < totalNumOutputChannels; ++channel)
    {
        int nSamples = buffer.getNumSamples();
        float** data = buffer.getArrayOfWritePointers();
        
    }
}

void TestSynthAudioProcessor::parameterChanged(const juce::String& paramID, float newValue)
{

    DBG(paramID + ": " + String(newValue));

    if (paramID == "freq1")
    {
        ctrl.setParamValue("/FaustSynth/freq1", newValue);
    }
    else if (paramID == "freq2")
    {
        ctrl.setParamValue("/FaustSynth/freq2", newValue);
    }
    else if (paramID == "filtCutoff")
    {
        ctrl.setParamValue("/FaustSynth/filtCutoff", newValue);
    }
    else if (paramID == "gain")
    {
        ctrl.setParamValue("/FaustSynth/gain", newValue);
    }
    else
    {
        DBG("Parameter not found");
    }

}

//==============================================================================
bool TestSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* TestSynthAudioProcessor::createEditor()
{
    return new TestSynthAudioProcessorEditor (*this, vts);
}

//==============================================================================
void TestSynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = vts.copyState();
    std::unique_ptr<XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);

}

void TestSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    unique_ptr<XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
    if (xml.get() != nullptr) {
        vts.replaceState(juce::ValueTree::fromXml(*xml));
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TestSynthAudioProcessor();
}
