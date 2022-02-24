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
Test4AudioProcessorEditor::Test4AudioProcessorEditor (Test4AudioProcessor& p)
: AudioProcessorEditor (&p), audioProcessor (p), gui(audioProcessor.gui), gui2(audioProcessor.gui2)
{
    addAndMakeVisible(gui);
    addAndMakeVisible(gui2);
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
    DBG(box.getHeight());
    auto topBox = box.removeFromTop(getHeight()/2);
    DBG(box.getHeight());
    gui.setBounds(topBox);
    gui2.setBounds(box);
}
