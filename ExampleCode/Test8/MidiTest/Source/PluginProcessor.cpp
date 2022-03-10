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

//==============================================================================
MidiTestAudioProcessor::MidiTestAudioProcessor()
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
, voice(new faust::SimpleSynth()), midiCtrl(&midiHandler)
{
    voice.buildUserInterface(&midiCtrl);
    midiCtrl.runAllGuis();
    if (!midiCtrl.run())
        DBG("Midi couldn't start");
}

MidiTestAudioProcessor::~MidiTestAudioProcessor()
{
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
            voice.keyOn(metadata.data[1], metadata.data[2]);
        if (metadata.getMessage().isNoteOff())
            voice.keyOff();
    }
    
    midiHandler.decodeBuffer(midiMessages);
    midiHandler.encodeBuffer(midiMessages);
    voice.compute(buffer.getNumSamples(), nullptr, buffer.getArrayOfWritePointers());
}

//==============================================================================
bool MidiTestAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MidiTestAudioProcessor::createEditor()
{
    return new MidiTestAudioProcessorEditor (*this);
}

//==============================================================================
void MidiTestAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MidiTestAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MidiTestAudioProcessor();
}
