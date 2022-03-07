/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

using namespace juce;
using namespace std;

//==============================================================================
/**
*/
class NewProjectAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    NewProjectAudioProcessorEditor(NewProjectAudioProcessor&, AudioProcessorValueTreeState& vts);
    NewProjectAudioProcessorEditor (NewProjectAudioProcessor&);
    ~NewProjectAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    NewProjectAudioProcessor& audioProcessor;
    AudioProcessorValueTreeState& vts;

    typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;

    juce::Slider freqSlider;
    juce::Slider vFreqSlider;
    juce::Slider vDepthSlider;
    juce::Slider pWheelSlider;
    juce::Slider detuneSlider;
    juce::Slider gainSlider;
    juce::Slider attSlider;
    juce::Slider decSlider;
    juce::Slider susSlider;
    juce::Slider relSlider;
    juce::Slider tFreqSlider;
    juce::Slider tDepthSlider;
    juce::Slider cutoffSlider;
    juce::Slider lfoFSlider;
    juce::Slider lfoDSlider;
    juce::Slider cSlider;
    juce::Slider cesSlider;
    juce::Slider dSlider;
    juce::Slider desSlider;
    juce::Slider eSlider;
    juce::Slider fSlider;
    juce::Slider fesSlider;
    juce::Slider gSlider;
    juce::Slider gesSlider;
    juce::Slider aSlider;
    juce::Slider asSlider;
    juce::Slider bSlider;
    juce::Slider offsetSlider;
    juce::ToggleButton gateButton;

    Label freqLabel;
    Label vFreqLabel;
    Label vDepthLabel;
    Label pWheelLabel;
    Label detuneLabel;
    Label gainLabel;
    Label attLabel;
    Label decLabel;
    Label susLabel;
    Label relLabel;
    Label tFreqLabel;
    Label tDepthLabel;
    Label cutoffLabel;
    Label lfoFLabel;
    Label lfoDLabel;
    Label cLabel;
    Label cesLabel;
    Label dLabel;
    Label desLabel;
    Label eLabel;
    Label fLabel;
    Label fesLabel;
    Label gLabel;
    Label gesLabel;
    Label aLabel;
    Label asLabel;
    Label bLabel;
    Label offsetLabel;
    Label gateLabel;

    SliderAttachment freqAttachment;
    SliderAttachment vFreqAttachment;
    SliderAttachment vDepthAttachment;
    SliderAttachment pWheelAttachment;
    SliderAttachment detuneAttachment;
    SliderAttachment gainAttachment;
    SliderAttachment attAttachment;
    SliderAttachment decAttachment;
    SliderAttachment susAttachment;
    SliderAttachment relAttachment;
    SliderAttachment tFreqAttachment;
    SliderAttachment tDepthAttachment;
    SliderAttachment cutoffAttachment;
    SliderAttachment lfoFAttachment;
    SliderAttachment lfoDAttachment;
    SliderAttachment cAttachment;
    SliderAttachment cesAttachment;
    SliderAttachment dAttachment;
    SliderAttachment desAttachment;
    SliderAttachment eAttachment;
    SliderAttachment fAttachment;
    SliderAttachment fesAttachment;
    SliderAttachment gAttachment;
    SliderAttachment gesAttachment;
    SliderAttachment aAttachment;
    SliderAttachment asAttachment;
    SliderAttachment bAttachment;
    SliderAttachment offsetAttachment;
    ButtonAttachment gateAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewProjectAudioProcessorEditor)
};
