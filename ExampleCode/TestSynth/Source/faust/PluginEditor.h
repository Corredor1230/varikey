/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class TestSynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    TestSynthAudioProcessorEditor (TestSynthAudioProcessor&, juce::AudioProcessorValueTreeState& vts);
    ~TestSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.

    TestSynthAudioProcessor& audioProcessor;
    juce::AudioProcessorValueTreeState& vts;

    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;

    //Esto debe ir arriba
    juce::Slider Freq1Slider;
    juce::Slider Freq2Slider;
    juce::Slider CutoffSlider;
    juce::Slider GainSlider;
    //De los attachments
    SliderAttachment Freq1Attachment;
    SliderAttachment Freq2Attachment;
    SliderAttachment CutoffAttachment;
    SliderAttachment GainAttachment;

    //Minuto 32:50

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestSynthAudioProcessorEditor)
};
