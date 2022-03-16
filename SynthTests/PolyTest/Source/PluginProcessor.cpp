/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

using namespace juce;
using namespace std;

//==============================================================================
MidiTestAudioProcessor::MidiTestAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::mono(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    )
#endif
    , voice(new faust::SimpleSynth()), midiCtrl(&midiHandler)
    , voiceGroup(&voice, 8, true, false)
    , vts(*this, nullptr, "Params", buildParameters())
{
    vts.addParameterListener("att", this);
    vts.addParameterListener("dec", this);
    vts.addParameterListener("sus", this);
    vts.addParameterListener("rel", this);
    vts.addParameterListener("gain", this);

    voiceGroup.buildUserInterface(&ctrl);
    
    for (int i = 0; i < ctrl.getParamsCount(); i++) {
        DBG(ctrl.getParamAddress(i));
    }

    voice.buildUserInterface(&midiCtrl);
    //midiCtrl.runAllGuis();
    if (!midiCtrl.run())
        DBG("Midi couldn't start");
}

void MidiTestAudioProcessor::parameterChanged(const juce::String& paramID, float newValue)
{
    DBG(paramID + String(newValue));
    if (paramID == "att")
    {
        ctrl.setParamValue("/SimpleSynth/att", newValue);
    }
    else if (paramID == "sus")
    {
        ctrl.setParamValue("/SimpleSynth/sus", newValue);
    }
    else if (paramID == "rel")
    {
        ctrl.setParamValue("/SimpleSynth/rel", newValue);
    }
    else if (paramID == "dec")
    {
        ctrl.setParamValue("/SimpleSynth/dec", newValue);
    }
    else if (paramID == "gain")
    {
        ctrl.setParamValue("/SimpleSynth/gain", newValue);
    }
    else {
        DBG("Parameter Not Found");
    }
}


MidiTestAudioProcessor::~MidiTestAudioProcessor()
{
}

AudioProcessorValueTreeState::ParameterLayout MidiTestAudioProcessor::buildParameters() {
    AudioProcessorValueTreeState::ParameterLayout layout;

    {
        auto param = make_unique<AudioParameterInt>("att", "att", 10, 1000, 15);
        layout.add(move(param));
    }

    {
        auto param = make_unique<AudioParameterInt>("dec", "dec", 10, 1000, 15);
        layout.add(move(param));
    }

    {
        auto param = make_unique<AudioParameterFloat>("sus", "sus", 0, 1, 0.4);
        layout.add(move(param));
    }

    {
        auto param = make_unique<AudioParameterInt>("rel", "rel", 10, 5000, 60);
        layout.add(move(param));
    }
    {
        auto param = make_unique<AudioParameterFloat>("gain", "gain", 0, 1, 0.7);
        layout.add(move(param));
    }

    return layout;
}


//==============================================================================
const juce::String MidiTestAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MidiTestAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MidiTestAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MidiTestAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MidiTestAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MidiTestAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MidiTestAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MidiTestAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MidiTestAudioProcessor::getProgramName (int index)
{
    return {};
}

void MidiTestAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MidiTestAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    voice.init(sampleRate);
    voiceGroup.init(sampleRate);
}

void MidiTestAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MidiTestAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void MidiTestAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    
    for (const MidiMessageMetadata metadata : midiMessages) {
        if (metadata.getMessage().isNoteOn())
            voiceGroup.keyOn(metadata.data[0], metadata.data[1], metadata.data[2]);
        if (metadata.getMessage().isNoteOff())
            voiceGroup.keyOff(metadata.data[0], metadata.data[1], 0);
    }
    
    midiHandler.decodeBuffer(midiMessages);
    midiHandler.encodeBuffer(midiMessages);
    voice.compute(buffer.getNumSamples(), nullptr, buffer.getArrayOfWritePointers());
    voiceGroup.compute(buffer.getNumSamples(), nullptr, buffer.getArrayOfWritePointers());
}

//==============================================================================
bool MidiTestAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MidiTestAudioProcessor::createEditor()
{
    return new MidiTestAudioProcessorEditor (*this, vts);
}

//==============================================================================
void MidiTestAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = vts.copyState();
    unique_ptr<XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void MidiTestAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
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
    return new MidiTestAudioProcessor();
}
