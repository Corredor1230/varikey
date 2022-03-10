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
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p, 
    AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), audioProcessor (p), vts(vts),
freqAttachment(vts, "freq", freqSlider),
vFreqAttachment(vts, "vFreq", vFreqSlider),
vDepthAttachment(vts, "vDepth", vDepthSlider),
pWheelAttachment(vts, "pWheel", pWheelSlider),
detuneAttachment(vts, "detune", detuneSlider),
gainAttachment(vts, "gain", gainSlider),
attAttachment(vts, "att", attSlider),
decAttachment(vts, "dec", decSlider),
susAttachment(vts, "sus", susSlider),
relAttachment(vts, "rel", relSlider),
tFreqAttachment(vts, "tFreq", tFreqSlider),
tDepthAttachment(vts, "tDepth", tDepthSlider),
cutoffAttachment(vts, "cutoff", cutoffSlider),
lfoFAttachment(vts, "lfoF", lfoFSlider),
lfoDAttachment(vts, "lfoD", lfoDSlider),
cAttachment(vts, "c", cSlider),
cesAttachment(vts, "ces", cesSlider),
dAttachment(vts, "d", dSlider),
desAttachment(vts, "des", desSlider),
eAttachment(vts, "e", eSlider),
fAttachment(vts, "f", fSlider),
fesAttachment(vts, "fes", fesSlider),
gAttachment(vts, "g", gSlider),
gesAttachment(vts, "ges", gesSlider),
aAttachment(vts, "a", aSlider),
asAttachment(vts, "as", asSlider),
bAttachment(vts, "b", bSlider),
offsetAttachment(vts, "offset", offsetSlider),
gateAttachment(vts, "gate", gateButton)


{
    addAndMakeVisible(freqSlider);
    freqSlider.setSkewFactorFromMidPoint(220);
    freqSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    freqSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, getWidth()/10, getHeight()/30);
    addAndMakeVisible(freqLabel);
    freqLabel.attachToComponent(&freqSlider, false);
    freqLabel.setText("Frequency", dontSendNotification);

    addAndMakeVisible(vFreqSlider);
    vFreqSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    vFreqSlider.setSkewFactorFromMidPoint(5);
    vFreqSlider.TextBoxBelow;
    addAndMakeVisible(vFreqLabel);
    vFreqLabel.setText("Vibrato Freq", dontSendNotification);
    vFreqLabel.attachToComponent(&vFreqSlider, false);

    addAndMakeVisible(vDepthSlider);
    vDepthSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    vDepthSlider.TextBoxBelow;
    addAndMakeVisible(vDepthLabel);
    vDepthLabel.setText("Depth", dontSendNotification);
    vDepthLabel.attachToComponent(&vDepthSlider, false);

    addAndMakeVisible(pWheelSlider);
    pWheelSlider.setSliderStyle(Slider::SliderStyle::LinearBar);
    addAndMakeVisible(pWheelLabel);
    pWheelLabel.setText("Global Pitch", dontSendNotification);
    pWheelLabel.attachToComponent(&pWheelSlider, false);

    addAndMakeVisible(detuneSlider);
    detuneSlider.setSliderStyle(Slider::SliderStyle::LinearBar);
    addAndMakeVisible(detuneLabel);
    detuneLabel.setText("Detune", dontSendNotification);
    detuneLabel.attachToComponent(&detuneSlider, false);

    addAndMakeVisible(gainSlider);
    gainSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    addAndMakeVisible(gainLabel);
    gainLabel.setText("Master", dontSendNotification);
    gainLabel.attachToComponent(&gainSlider, false);

    addAndMakeVisible(attSlider);
    attSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    addAndMakeVisible(attLabel);
    attLabel.setText("Attack", dontSendNotification);
    attLabel.attachToComponent(&attSlider, false);

    addAndMakeVisible(decSlider);
    decSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    addAndMakeVisible(decLabel);
    decLabel.setText("Decay", dontSendNotification);
    decLabel.attachToComponent(&decSlider, false);

    addAndMakeVisible(susSlider);
    susSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    addAndMakeVisible(susLabel);
    susLabel.setText("Sustain", dontSendNotification);
    susLabel.attachToComponent(&susSlider, false);

    addAndMakeVisible(relSlider);
    relSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    addAndMakeVisible(relLabel);
    relLabel.setText("Release", dontSendNotification);
    relLabel.attachToComponent(&relSlider, false);

    addAndMakeVisible(tFreqSlider);
    tFreqSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    tFreqSlider.setSkewFactorFromMidPoint(5);
    addAndMakeVisible(tFreqLabel);
    tFreqLabel.setText("Tremolo Frequency", dontSendNotification);
    tFreqLabel.attachToComponent(&tFreqSlider, false);

    addAndMakeVisible(tDepthSlider);
    tDepthSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(tDepthLabel);
    tDepthLabel.setText("Depth", dontSendNotification);
    tDepthLabel.attachToComponent(&tDepthSlider, false);

    addAndMakeVisible(cutoffSlider);
    cutoffSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    cutoffSlider.setSkewFactorFromMidPoint(1000);
    cutoffSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 40, 20);
    addAndMakeVisible(cutoffLabel);
    cutoffLabel.setText("Cutoff", dontSendNotification);
    cutoffLabel.attachToComponent(&cutoffSlider, false);

    addAndMakeVisible(lfoFSlider);
    lfoFSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    lfoFSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 40, 20);
    addAndMakeVisible(lfoFLabel);
    lfoFLabel.setText("Lfo Frequency", dontSendNotification);
    lfoFLabel.attachToComponent(&lfoFSlider, false);

    addAndMakeVisible(lfoDSlider);
    lfoDSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    lfoDSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 40, 20);
    addAndMakeVisible(lfoDLabel);
    lfoDLabel.setText("Lfo Depth", dontSendNotification);
    lfoDLabel.attachToComponent(&lfoDSlider, false);

    addAndMakeVisible(cSlider);
    cSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    addAndMakeVisible(cLabel);
    cLabel.setText("C", dontSendNotification);
    cLabel.attachToComponent(&cSlider, false);

    addAndMakeVisible(cesSlider);
    cesSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    addAndMakeVisible(cesLabel);
    cesLabel.setText("C#/Db", dontSendNotification);
    cesLabel.attachToComponent(&cesSlider, false);

    addAndMakeVisible(dSlider);
    dSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    addAndMakeVisible(dLabel);
    dLabel.setText("D", dontSendNotification);
    dLabel.attachToComponent(&dSlider, false);

    addAndMakeVisible(desSlider);
    desSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    addAndMakeVisible(desLabel);
    desLabel.setText("D#/Eb", dontSendNotification);
    desLabel.attachToComponent(&desSlider, false);

    addAndMakeVisible(eSlider);
    eSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    addAndMakeVisible(eLabel);
    eLabel.setText("E", dontSendNotification);
    eLabel.attachToComponent(&eSlider, false);

    addAndMakeVisible(fSlider);
    fSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    addAndMakeVisible(fLabel);
    fLabel.setText("F", dontSendNotification);
    fLabel.attachToComponent(&fSlider, false);

    addAndMakeVisible(fesSlider);
    fesSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    addAndMakeVisible(fesLabel);
    fesLabel.setText("F#/Gb", dontSendNotification);
    fesLabel.attachToComponent(&fesSlider, false);

    addAndMakeVisible(gSlider);
    gSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    addAndMakeVisible(gLabel);
    gLabel.setText("G", dontSendNotification);
    gLabel.attachToComponent(&gSlider, false);

    addAndMakeVisible(gesSlider);
    gesSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    addAndMakeVisible(gesLabel);
    gesLabel.setText("G#/Ab", dontSendNotification);
    gesLabel.attachToComponent(&gesSlider, false);

    addAndMakeVisible(aSlider);
    aSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    addAndMakeVisible(aLabel);
    aLabel.setText("A", dontSendNotification);
    aLabel.attachToComponent(&aSlider, false);

    addAndMakeVisible(asSlider);
    asSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    addAndMakeVisible(asLabel);
    asLabel.setText("A#/Bb", dontSendNotification);
    asLabel.attachToComponent(&asSlider, false);

    addAndMakeVisible(bSlider);
    bSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    addAndMakeVisible(bLabel);
    bLabel.setText("B", dontSendNotification);
    bLabel.attachToComponent(&bSlider, false);

    addAndMakeVisible(offsetSlider);
    offsetSlider.setSliderStyle(Slider::SliderStyle::LinearBar);
    addAndMakeVisible(offsetLabel);
    offsetLabel.setText("Transpose", dontSendNotification);
    offsetLabel.attachToComponent(&offsetSlider, false);

    addAndMakeVisible(gateButton);
    addAndMakeVisible(gateLabel);
    gateLabel.setText("Gate", dontSendNotification);
    gateLabel.attachToComponent(&gateButton, false);

    setResizable(true, true);
    setSize (600, 600);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    //g.setColour (juce::Colours::white);
    //g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);

    g.fillAll(juce::Colours::darkgrey);


}

void NewProjectAudioProcessorEditor::resized()
{


    float verticalMargin{ getHeight() * 0.05f };
    float horizontalMargin{ getHeight() * 0.05f };
    float totalWidth{ getWidth() - horizontalMargin };
    float totalHeight{ getHeight() - verticalMargin };
    float midBox = totalHeight / 7;
    float tuneSliderPos{ totalWidth / 12 };
    float tuneSliderWidth{ totalWidth / 24 };
    float secondThird{ verticalMargin + totalHeight / 4 };
    float finalThird{ secondThird + totalHeight / 4 };
    float tuneSliderH{ finalThird + 3 * verticalMargin };


    freqSlider.setBounds(horizontalMargin, verticalMargin, midBox, midBox);
    gateButton.setBounds(horizontalMargin, verticalMargin + midBox, midBox, midBox);
    vFreqSlider.setBounds(horizontalMargin + totalWidth / 4, verticalMargin, midBox, midBox);
    vDepthSlider.setBounds(horizontalMargin + totalWidth / 4, verticalMargin + midBox, midBox, midBox);
    detuneSlider.setBounds(horizontalMargin + totalWidth / 2, verticalMargin, 2 * midBox, midBox / 2);
    pWheelSlider.setBounds(horizontalMargin + totalWidth / 2, verticalMargin + midBox, 2 * midBox, midBox / 2);
    attSlider.setBounds(horizontalMargin, secondThird, totalWidth / 20, 2*midBox);
    decSlider.setBounds(horizontalMargin+totalWidth/10, secondThird, totalWidth / 20, 2*midBox);
    susSlider.setBounds(horizontalMargin+totalWidth/5, secondThird, totalWidth / 20, 2*midBox);
    relSlider.setBounds(horizontalMargin+totalWidth*0.3, secondThird, totalWidth / 20, 2*midBox);
    gainSlider.setBounds(horizontalMargin+totalWidth*0.39, secondThird, totalWidth / 20, 2*midBox);
    cutoffSlider.setBounds(horizontalMargin + totalWidth/2, secondThird*1.3, midBox/1.2, midBox/1.2);
    lfoFSlider.setBounds(horizontalMargin + 2*totalWidth/3, secondThird, midBox, midBox);
    lfoDSlider.setBounds(horizontalMargin + 2*totalWidth/3, secondThird * 1.5, midBox, midBox);
    tFreqSlider.setBounds(horizontalMargin + 5 * totalWidth / 6, secondThird, midBox, midBox);
    tDepthSlider.setBounds(horizontalMargin + 5 * totalWidth / 6, secondThird * 1.5, midBox, midBox);
    offsetSlider.setBounds(horizontalMargin, finalThird+verticalMargin, totalWidth*0.95, verticalMargin);
    cSlider.setBounds(horizontalMargin, tuneSliderH, tuneSliderWidth, totalHeight / 5);
    cesSlider.setBounds(horizontalMargin + tuneSliderPos, tuneSliderH, tuneSliderWidth, totalHeight / 5);
    dSlider.setBounds(horizontalMargin + 2*tuneSliderPos, tuneSliderH, tuneSliderWidth, totalHeight / 5);
    desSlider.setBounds(horizontalMargin + 3*tuneSliderPos, tuneSliderH, tuneSliderWidth, totalHeight / 5);
    eSlider.setBounds(horizontalMargin + 4*tuneSliderPos, tuneSliderH, tuneSliderWidth, totalHeight / 5);
    fSlider.setBounds(horizontalMargin + 5*tuneSliderPos, tuneSliderH, tuneSliderWidth, totalHeight / 5);
    fesSlider.setBounds(horizontalMargin + 6*tuneSliderPos, tuneSliderH, tuneSliderWidth, totalHeight / 5);
    gSlider.setBounds(horizontalMargin + 7*tuneSliderPos, tuneSliderH, tuneSliderWidth, totalHeight / 5);
    gesSlider.setBounds(horizontalMargin + 8*tuneSliderPos, tuneSliderH, tuneSliderWidth, totalHeight / 5);
    aSlider.setBounds(horizontalMargin + 9*tuneSliderPos, tuneSliderH, tuneSliderWidth, totalHeight / 5);
    asSlider.setBounds(horizontalMargin + 10*tuneSliderPos, tuneSliderH, tuneSliderWidth, totalHeight / 5);
    bSlider.setBounds(horizontalMargin + 11*tuneSliderPos, tuneSliderH, tuneSliderWidth, totalHeight / 5);

}
