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
class Test4AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Test4AudioProcessorEditor (Test4AudioProcessor&, juce::AudioProcessorValueTreeState& vts);
    ~Test4AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Test4AudioProcessor& audioProcessor;
    juce::AudioProcessorValueTreeState& vts;
    
    typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
        
    juce::Slider attSlider;
    juce::Slider relSlider;
    juce::Slider thrSlider;
    juce::Slider ratSlider;
    
    SliderAttachment attAttachment;
    SliderAttachment relAttachment;
    SliderAttachment thrAttachment;
    SliderAttachment ratAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Test4AudioProcessorEditor)
};
