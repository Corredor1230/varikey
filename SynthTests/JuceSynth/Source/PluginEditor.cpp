/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JuceSynthAudioProcessorEditor::JuceSynthAudioProcessorEditor (JuceSynthAudioProcessor& p)
    : AudioProcessorEditor (&p)
    , audioProcessor (p)
    , osc(audioProcessor.vts, "Osc1Wavetype")
    , adsr(audioProcessor.vts)
{
    setSize (400, 300);

    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
        (audioProcessor.vts, "Gain", gainSlider);

    addAndMakeVisible(adsr);
    addAndMakeVisible(osc);

    addAndMakeVisible(gainSlider);
    gainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
}

JuceSynthAudioProcessorEditor::~JuceSynthAudioProcessorEditor()
{
}

//==============================================================================
void JuceSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::black);

}

void JuceSynthAudioProcessorEditor::resized()
{
    osc.setBounds(10, 10, 100, 30);
    adsr.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight() / 2);

}

