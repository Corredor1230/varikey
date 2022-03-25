/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JuceSynthAudioProcessor::JuceSynthAudioProcessor()
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
    ,vts(*this, nullptr, "Params", buildParams())
{
    int numVoices = 8;

    synth.addSound(new SynthSound());
    for (int i = 0; i < numVoices; i++)
    {
        synth.addVoice(new SynthVoice());
    }
    juce::Decibels::decibelsToGain(10);

}

juce::AudioProcessorValueTreeState::ParameterLayout JuceSynthAudioProcessor::buildParams()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    //OSC Select
    params.push_back(std::make_unique<juce::AudioParameterChoice>("Sel",
        "Selector",
        juce::StringArray{ "Sine", "Saw", "Square" },
        0));

    //ADSR
    params.push_back(std::make_unique<juce::AudioParameterFloat>("Att", "Attack", 
        juce::NormalisableRange<float> {0.1f, 1.0f, }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("Dec", "Decay", 
        juce::NormalisableRange<float> {0.1f, 1.0f, }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("Sus", "Sustain", 
        juce::NormalisableRange<float> {0.1f, 1.0f, }, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("Rel", "Release", 
        juce::NormalisableRange<float> {0.1f, 1.0f, }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("Gain", "Gain",
        juce::NormalisableRange<float> {0.0f, 1.0f, }, 0.0f));

    params.push_back(std::make_unique<juce::AudioParameterChoice>("Osc1Wavetype",
        "Osc1 Wavetype",
        juce::StringArray{ "Sine", "Saw", "Square" },
        0));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("c", "cNote",
        juce::NormalisableRange<float>{-1.0f, 1.0f, }, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ces", "cesNote",
        juce::NormalisableRange<float>{-1.0f, 1.0f, }, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("d", "dNote",
        juce::NormalisableRange<float>{-1.0f, 1.0f, }, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("des", "desNote",
        juce::NormalisableRange<float>{-1.0f, 1.0f, }, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("e", "eNote",
        juce::NormalisableRange<float>{-1.0f, 1.0f, }, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("f", "fNote",
        juce::NormalisableRange<float>{-1.0f, 1.0f, }, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("fes", "fesNote",
        juce::NormalisableRange<float>{-1.0f, 1.0f, }, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("g", "gNote",
        juce::NormalisableRange<float>{-1.0f, 1.0f, }, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ges", "gesNote",
        juce::NormalisableRange<float>{-1.0f, 1.0f, }, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("a", "aNote",
        juce::NormalisableRange<float>{-1.0f, 1.0f, }, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("aes", "aesNote",
        juce::NormalisableRange<float>{-1.0f, 1.0f, }, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("b", "bNote",
        juce::NormalisableRange<float>{-1.0f, 1.0f, }, 0.0f));

    return { params.begin(), params.end() };
}

JuceSynthAudioProcessor::~JuceSynthAudioProcessor()
{
}

//==============================================================================
const juce::String JuceSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool JuceSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool JuceSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool JuceSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double JuceSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int JuceSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int JuceSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void JuceSynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String JuceSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void JuceSynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void JuceSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);

    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }

    }
}

void JuceSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool JuceSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void JuceSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            auto& attack = *vts.getRawParameterValue("Att");
            auto& decay = *vts.getRawParameterValue("Dec");
            auto& sustain = *vts.getRawParameterValue("Sus");
            auto& release = *vts.getRawParameterValue("Rel");
            auto& gain = *vts.getRawParameterValue("Gain");

            auto& oscWave = *vts.getRawParameterValue("Osc1Wavetype");

            auto& cNote = *vts.getRawParameterValue("c");
            auto& cesNote = *vts.getRawParameterValue("ces");
            auto& dNote = *vts.getRawParameterValue("d");
            auto& desNote = *vts.getRawParameterValue("des");
            auto& eNote = *vts.getRawParameterValue("e");
            auto& fNote = *vts.getRawParameterValue("f");
            auto& fesNote = *vts.getRawParameterValue("fes");
            auto& gNote = *vts.getRawParameterValue("g");
            auto& gesNote = *vts.getRawParameterValue("ges");
            auto& aNote = *vts.getRawParameterValue("a");
            auto& aesNote = *vts.getRawParameterValue("aes");
            auto& bNote = *vts.getRawParameterValue("b");


            voice->update(attack.load(), decay.load(), sustain.load(), release.load());
            voice->getOscillator().setWaveType(oscWave);
            voice->getTuning().alterMidiPitch(cNote, cesNote, dNote, desNote, eNote, fNote,
                fesNote, gNote, gesNote, aNote, aesNote, bNote);
        }

    }

    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool JuceSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* JuceSynthAudioProcessor::createEditor()
{
    return new JuceSynthAudioProcessorEditor (*this);
}

//==============================================================================
void JuceSynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void JuceSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JuceSynthAudioProcessor();
}
