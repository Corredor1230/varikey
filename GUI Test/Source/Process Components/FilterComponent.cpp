/*
  ==============================================================================

    FilterComponent.cpp
    Created: 8 Apr 2022 11:36:45am
    Author:  juanp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"

//==============================================================================
FilterComponent::FilterComponent()
{
    addAndMakeVisible(titleLabel);
    titleLabel.setText("Filter", juce::dontSendNotification);

    setSliderParams(lopCutoffSlider, lopCutoffLabel, "LOP Cutoff", rotary);
    lopCutoffSlider.setRange(20.0, 20000.0f, 1.0f);
    lopCutoffSlider.setSkewFactorFromMidPoint(1000.0f);
    setSliderParams(hipCutoffSlider, hipCutoffLabel, "HIP Cutoff", rotary);
    hipCutoffSlider.setRange(20.0f, 20000.0f, 1.0f);
    hipCutoffSlider.setSkewFactorFromMidPoint(1000.0f);
    setSliderParams(lopQSlider, lopQLabel, "Q", rotary);
    lopQSlider.setRange(1.0f, 10.0f, 0.1f);
    setSliderParams(hipQSlider, hipQLabel, "Q", rotary);
    hipQSlider.setRange(1.0f, 10.0f, 0.1f);
}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colour());
    juce::Rectangle<float> border;
    border.setBounds(5, 5, getWidth() - 10, getHeight() - 10);
    g.setColour(getLookAndFeel().findColour(juce::ToggleButton::ColourIds::tickDisabledColourId));
    g.drawRect(border, 1.0f);

    auto bounds = getBounds().reduced(5, 5);
    int height = bounds.getHeight();
    int width = bounds.getWidth();
    int padding = 10;
    int titleHeight = 18;
    int title = height / 6;
    int sliderLabelWidth = width / 5;
    int sliderLabelHeight = height / 4;

    int sliderWidth = width / 2;
    int sliderHeight = height / 2;
    int sliderDiameter = std::min(sliderWidth, sliderHeight);
    
}

void FilterComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void FilterComponent::setSliderParams(juce::Slider& slider, juce::Label& label, juce::String name, int style)
{
    addAndMakeVisible(slider);
    addAndMakeVisible(label);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    label.setText(name, juce::dontSendNotification);

    switch (style)
    {
    case vertical:
        label.attachToComponent(&slider, false);
        slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
        break;
    case rotary:
        slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        label.setJustificationType(juce::Justification::centredRight);
        break;
    case horizontal:
        slider.setTextBoxStyle(juce::Slider::NoTextBox, true, 50, 25);
        slider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
        break;
    default:
        slider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
        break;
    }
}

void FilterComponent::setCustomLookAndFeel(juce::LookAndFeel_V4* customLookAndFeel)
{
    setLookAndFeel(customLookAndFeel);
}