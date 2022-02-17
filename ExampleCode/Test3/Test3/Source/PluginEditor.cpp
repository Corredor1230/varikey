/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Test3AudioProcessorEditor::Test3AudioProcessorEditor (Test3AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
, vts(p.vts), freqAttachment(vts, "freq", freqSlider)
{
    addAndMakeVisible(freqSlider);
    setSize (400, 300);
}

Test3AudioProcessorEditor::~Test3AudioProcessorEditor()
{
}

//==============================================================================
void Test3AudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void Test3AudioProcessorEditor::resized()
{
    freqSlider.setBounds(getBounds());
}
