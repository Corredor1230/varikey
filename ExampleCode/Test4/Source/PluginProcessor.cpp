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
, vts(*this, nullptr, "Params", buildParameters())
{
    vts.addParameterListener("att", this);
    vts.addParameterListener("rel", this);
    vts.addParameterListener("threshold", this);
    vts.addParameterListener("ratio", this);
    
    dsp.buildUserInterface(&ctrl);
    
    for (int i = 0; i < ctrl.getParamsCount(); i++) {
        DBG(ctrl.getParamAddress(i));
    }
}

Test4AudioProcessor::~Test4AudioProcessor()
{
}

AudioProcessorValueTreeState::ParameterLayout Test4AudioProcessor::buildParameters() {
    AudioProcessorValueTreeState::ParameterLayout layout;
    {
        auto param = make_unique<AudioParameterFloat>("att", "Attack", 1, 100, 10);
        layout.add(move(param));
    }
    {
        auto param = make_unique<AudioParameterFloat>("rel", "Release", 10, 1000, 100);
        layout.add(move(param));
    }
    {
        auto param = make_unique<AudioParameterFloat>("threshold", "Threshold", -40, 0, -20);
        layout.add(move(param));
    }
    {
        auto param = make_unique<AudioParameterFloat>("ratio", "Ratio", 1, 10, 2);
        layout.add(move(param));
    }
    return layout;
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
    
    
    for (auto it = midiMessages.begin(); it != midiMessages.end(); it++) {
    }
    
    
    int nSamples = buffer.getNumSamples();
    float** data = buffer.getArrayOfWritePointers();
    for (int n = 0; n < nSamples; n++) {
        float curFrame[2][1] = {{data[0][n]},{data[1][n]}};
        dsp.compute(1, (float**)curFrame, (float**)curFrame);
        data[0][n] = curFrame[0][n];
        data[1][n] = curFrame[1][n];
    }
}

void Test4AudioProcessor::parameterChanged (const juce::String& paramID, float newValue)
{
    DBG(paramID + ": " + String(newValue));
    std::string address;
    if (paramID == "att"){
        address = "/Compressor/Attack";
        ctrl.setParamValue(address, newValue);
    } else if (paramID == "rel"){
        address = "/Compressor/Release";
        ctrl.setParamValue(address, newValue);
    } else if (paramID == "threshold"){
        address = "/Compressor/Threshold";
        ctrl.setParamValue(address, newValue);
    } else if (paramID == "ratio"){
        address = "/Compressor/Ratio";
        ctrl.setParamValue(address, newValue);
    } else {
        DBG("Parameter Not Found");
    }
    DBG("FaustValue " + paramID + ": " + String(ctrl.getParamValue(address)));
}

//==============================================================================
bool Test4AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Test4AudioProcessor::createEditor()
{
    return new Test4AudioProcessorEditor (*this, vts);
}

//==============================================================================
void Test4AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = vts.copyState();
    std::unique_ptr<XmlElement> xml (state.createXml());
    copyXmlToBinary(*xml, destData);
}

void Test4AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    unique_ptr<XmlElement> xml (getXmlFromBinary(data, sizeInBytes));
    if (xml.get() != nullptr) {
        vts.replaceState(juce::ValueTree::fromXml(*xml));
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Test4AudioProcessor();
}
