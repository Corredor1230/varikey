/*
  ==============================================================================

    TuningComponent.cpp
    Created: 24 Mar 2022 5:26:11am
    Author:  User

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TuningComponent.h"

//==============================================================================
TuningComponent::TuningComponent(juce::AudioProcessorValueTreeState& vts
    , juce::String cID
    , juce::String cesID
    , juce::String dID
    , juce::String desID
    , juce::String eID
    , juce::String fID
    , juce::String fesID
    , juce::String gID
    , juce::String gesID
    , juce::String aID
    , juce::String aesID
    , juce::String bID)
{
    addAndMakeVisible(cSlider);
    cSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    cSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 25);

    addAndMakeVisible(cesSlider);
    cesSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    cesSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 25);

    addAndMakeVisible(dSlider);
    dSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    dSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 25);

    addAndMakeVisible(desSlider);
    desSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    desSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 25);

    addAndMakeVisible(eSlider);
    eSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    eSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 25);

    addAndMakeVisible(fSlider);
    fSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    fSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 25);

    addAndMakeVisible(fesSlider);
    fesSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    fesSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 25);

    addAndMakeVisible(gSlider);
    gSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    gSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 25);

    addAndMakeVisible(gesSlider);
    gesSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    gesSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 25);

    addAndMakeVisible(aSlider);
    aSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    aSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 25);

    addAndMakeVisible(aesSlider);
    aesSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    aesSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 25);

    addAndMakeVisible(bSlider);
    bSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    bSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 25);
}

void TuningComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void TuningComponent::resized()
{


}
