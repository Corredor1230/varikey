/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

using namespace juce;

//==============================================================================
/**
*/
class MidiTestAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    MidiTestAudioProcessorEditor (MidiTestAudioProcessor&, juce::AudioProcessorValueTreeState& vts);
    ~MidiTestAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MidiTestAudioProcessor& audioProcessor;
    juce::AudioProcessorValueTreeState& vts;

    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;


    juce::Slider attSlider;
    juce::Slider relSlider;
    juce::Slider decSlider;
    juce::Slider susSlider;
    juce::Slider gainSlider;

    SliderAttachment attAttachment;
    SliderAttachment relAttachment;
    SliderAttachment decAttachment;
    SliderAttachment susAttachment;
    SliderAttachment gainAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiTestAudioProcessorEditor)
};
