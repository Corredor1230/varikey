/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <faust/dsp/dsp.h>
#include <faust/dsp/poly-dsp.h>
#include <faust/misc.h>
#include <faust/gui/MapUI.h>
#include <faust/gui/MidiUI.h>
#include <faust/midi/midi.h>
#include <faust/midi/juce-midi.h>
#include "SimpleSynth.h"

//==============================================================================
/**
*/
class MidiTestAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    MidiTestAudioProcessor();
    ~MidiTestAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    //==============================================================================
    
    juce_midi_handler midiHandler;
    dsp_voice voice;
    MidiUI midiCtrl; // Only Needed for other Midi Parameter mapping
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiTestAudioProcessor)
};
