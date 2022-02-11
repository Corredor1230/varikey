/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Test2AudioProcessor::Test2AudioProcessor()
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
, vts(*this, nullptr, "ID", buildParameters())
{
//    vts.addParameterListener("hola", this);
}

Test2AudioProcessor::~Test2AudioProcessor()
{
//    Should I call destruct or params?
}

juce::AudioProcessorValueTreeState::ParameterLayout buildParameters()
{
    using namespace std;
    using namespace juce;
    
//    AudioParameterInt* param = new AudioParameterInt("asdf", "asdf", 0, 10, 1);
//    vector<RangedAudioParameter*> paramList;
//    paramList.push_back(param);
//    for (int n = 0; n < 8; n++) {
//        String paramID = "Pan " + String(n + 1);
//        String name = "Panner of Channel " + String(n + 1);
//        NormalisableRange<float> range(0, 1);
//        AudioParameterFloat* p = new AudioParameterFloat(paramID, name, range, 0);
//        paramList.push_back(p);
//    }
//    AudioParameterInt* paramPtr = reinterpret_cast<AudioParameterInt*>(paramList[0]);
    
    vector<unique_ptr<RangedAudioParameter>> paramList;
    std::unique_ptr<AudioParameterInt> uniqueParam = std::make_unique<AudioParameterInt>("id", "name", DefaultParameters::defaultLowValueFirstParameter, 10, 1);
    paramList.push_back(move(uniqueParam));

    
    return {paramList.begin(), paramList.end()};
}


//==============================================================================
const juce::String Test2AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Test2AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Test2AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Test2AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Test2AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Test2AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Test2AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Test2AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Test2AudioProcessor::getProgramName (int index)
{
    return {};
}

void Test2AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Test2AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void Test2AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Test2AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void Test2AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool Test2AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Test2AudioProcessor::createEditor()
{
    return new Test2AudioProcessorEditor (*this);
}

//==============================================================================
void Test2AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Test2AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Test2AudioProcessor();
}

