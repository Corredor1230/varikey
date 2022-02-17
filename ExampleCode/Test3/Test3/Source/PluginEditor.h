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
class Test3AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Test3AudioProcessorEditor (Test3AudioProcessor&);
    ~Test3AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    Test3AudioProcessor& audioProcessor;
    juce::AudioProcessorValueTreeState& vts;
    
    juce::Slider freqSlider;
    SliderAttachment freqAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Test3AudioProcessorEditor)
};
