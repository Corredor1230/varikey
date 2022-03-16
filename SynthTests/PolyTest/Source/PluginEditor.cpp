/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

using namespace juce;
using namespace std;

//==============================================================================
MidiTestAudioProcessorEditor::MidiTestAudioProcessorEditor (MidiTestAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), audioProcessor (p), vts(vts)
    ,attAttachment(vts, "att", attSlider)
    , relAttachment(vts, "rel", relSlider)
    , decAttachment(vts, "dec", decSlider)
    , susAttachment(vts, "sus", susSlider)
    , gainAttachment(vts, "gain", gainSlider)
{
    addAndMakeVisible(attSlider);
    addAndMakeVisible(relSlider);
    addAndMakeVisible(decSlider);
    addAndMakeVisible(susSlider);
    addAndMakeVisible(gainSlider);

    attSlider.setSliderStyle(Slider::LinearBarVertical);
    relSlider.setSliderStyle(Slider::LinearBarVertical);
    decSlider.setSliderStyle(Slider::LinearBarVertical);
    susSlider.setSliderStyle(Slider::LinearBarVertical);
    gainSlider.setSliderStyle(Slider::LinearBarVertical);



    setSize (400, 300);
}

MidiTestAudioProcessorEditor::~MidiTestAudioProcessorEditor()
{
}

//==============================================================================
void MidiTestAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void MidiTestAudioProcessorEditor::resized()
{
    auto box = getBounds();
    box.reduced(20, 20);
    auto width = getWidth() / 5;
    attSlider.setBounds(box.removeFromLeft(width));
    decSlider.setBounds(box.removeFromLeft(width));
    susSlider.setBounds(box.removeFromLeft(width));
    relSlider.setBounds(box.removeFromLeft(width));
    gainSlider.setBounds(box.removeFromLeft(width));

}
