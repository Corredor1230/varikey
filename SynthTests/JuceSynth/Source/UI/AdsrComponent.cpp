/*
  ==============================================================================

    AdsrComponent.cpp
    Created: 23 Mar 2022 12:03:15pm
    Author:  User

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AdsrComponent.h"

//==============================================================================
AdsrComponent::AdsrComponent(juce::AudioProcessorValueTreeState& vts)
{
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    attAttachment = std::make_unique<SliderAttachment>(vts, "Att", attSlider);
    decAttachment = std::make_unique<SliderAttachment>(vts, "Dec", decSlider);
    susAttachment = std::make_unique<SliderAttachment>(vts, "Sus", susSlider);
    relAttachment = std::make_unique<SliderAttachment>(vts, "Rel", relSlider);


    setSliderParams(attSlider);
    setSliderParams(decSlider);
    setSliderParams(susSlider);
    setSliderParams(relSlider);
}

AdsrComponent::~AdsrComponent()
{
}

void AdsrComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void AdsrComponent::resized()
{
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth() / 4 - padding;
    const auto sliderHeight = bounds.getHeight();
    const auto sliderStartX = 0;
    const auto sliderStartY = 0;

    attSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    decSlider.setBounds(attSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    susSlider.setBounds(decSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    relSlider.setBounds(susSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);

}

void AdsrComponent::setSliderParams(juce::Slider& slider)
{
    addAndMakeVisible(slider);
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
}
