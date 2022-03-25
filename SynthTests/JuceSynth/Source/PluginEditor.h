/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/AdsrComponent.h"
#include "UI/OscComponent.h"

//==============================================================================
/**
*/
class JuceSynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    JuceSynthAudioProcessorEditor (JuceSynthAudioProcessor&);
    ~JuceSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:

    juce::ComboBox selBox;
    juce::Slider gainSlider;


    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> selAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;

    JuceSynthAudioProcessor& audioProcessor;
    OscComponent osc;
    AdsrComponent adsr;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceSynthAudioProcessorEditor)
};
