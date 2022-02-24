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
    Test4AudioProcessorEditor (Test4AudioProcessor&);
    ~Test4AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Test4AudioProcessor& audioProcessor;
    JuceGUI& gui;
    JuceGUI& gui2;

        
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Test4AudioProcessorEditor)
};
