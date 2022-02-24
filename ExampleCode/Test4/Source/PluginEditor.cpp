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
Test4AudioProcessorEditor::Test4AudioProcessorEditor (Test4AudioProcessor& p, AudioProcessorValueTreeState& vts)
: AudioProcessorEditor (&p), audioProcessor (p), vts(vts),
attAttachment(vts, "att", attSlider),
relAttachment(vts, "rel", relSlider),
thrAttachment(vts, "threshold", thrSlider),
ratAttachment(vts, "ratio", ratSlider)
{
    addAndMakeVisible(attSlider);
    addAndMakeVisible(relSlider);
    addAndMakeVisible(thrSlider);
    addAndMakeVisible(ratSlider);
    
    attSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    attSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    relSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    relSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    thrSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    thrSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    ratSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    ratSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    
    setSize (400, 300);
}

Test4AudioProcessorEditor::~Test4AudioProcessorEditor()
{
}

//==============================================================================
void Test4AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    
}

void Test4AudioProcessorEditor::resized()
{
    auto box = getBounds();
    box.reduced(20, 20);
    auto width = box.getWidth() / 4;
    attSlider.setBounds(box.removeFromLeft(width));
    relSlider.setBounds(box.removeFromLeft(width));
    thrSlider.setBounds(box.removeFromLeft(width));
    ratSlider.setBounds(box.removeFromLeft(width));
}
