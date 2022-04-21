/*
  ==============================================================================

    LfoComponent.cpp
    Created: 8 Apr 2022 11:36:54am
    Author:  juanp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LfoComponent.h"

//==============================================================================
LfoComponent::LfoComponent()
{
    setSliderParams(freq1Slider, freq1Label, "Freq", rotary);
    setSliderParams(depth1Slider, depth1Label, "Depth", rotary);
    setSliderParams(shape1Slider, shape1Label, "Shape", vertical);
    setSliderParams(freq2Slider, freq2Label, "Freq", rotary);
    setSliderParams(depth2Slider, depth2Label, "Depth", rotary);
    setSliderParams(shape2Slider, shape2Label, "Shape", vertical);
    addAndMakeVisible(lfo1Label);
    addAndMakeVisible(lfo2Label);
    addAndMakeVisible(routeBox);
    addAndMakeVisible(routeLabel);
    addAndMakeVisible(routeBox2);
    addAndMakeVisible(routeLabel2);
    routeLabel.setText("Route", juce::dontSendNotification);
    routeLabel2.setText("Route", juce::dontSendNotification);
    routeLabel.setInterceptsMouseClicks(false, false);
    routeLabel2.setInterceptsMouseClicks(false, false);
    routeBox.setColour(juce::ComboBox::ColourIds::textColourId, juce::Colour());
    routeBox2.setColour(juce::ComboBox::ColourIds::textColourId, juce::Colour());

    std::initializer_list<const char*> synthList
    {
        "none",
        "gen1Noise", "gen2Noise",
        "noise1Tone", "noise2Tone",
        "mix",
        "fm1Ratio", "fm1Depth",
        "fm2Ratio", "fm2Depth",
        "lopCutoff", "lopQ",
        "hipCutoff", "hipQ",
        "detune", "volume"
    };
    routeBox.addItemList(juce::StringArray(synthList), 1);

}

LfoComponent::~LfoComponent()
{
}

void LfoComponent::paint (juce::Graphics& g)
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
    int sliderLabel = height / 6;
    int sliderLabelWidth = 50;
    int titleHeight = height / 5;

    int rotaryWidth = (width / 2) - padding;
    int rotaryHeight = height - sliderLabel - titleHeight;
    int rotaryDiameter = std::min(rotaryWidth, rotaryHeight) - padding;

    int horizontalHeight = 25;
    int sliderWidth = (width / 2) - padding;
    int sliderHeight = height - horizontalHeight - titleHeight - sliderLabel;
    int sliderStartX = padding;
    int labelStartX = (padding * 2) / 1.1;
    int labelStartY = titleHeight + sliderLabel + padding;
    int topStartY = 3;

    lfo1Label.setText(lfoString + region1Index, juce::dontSendNotification);
    lfo1Label.setJustificationType(juce::Justification::centredLeft);
    lfo2Label.setText(lfoString + region2Index, juce::dontSendNotification);
    lfo2Label.setJustificationType(juce::Justification::centredLeft);

    lfo1Label.setBounds(sliderStartX, padding / 1.5, width / 6, titleHeight);
    routeLabel.setBounds(lfo1Label.getRight(), padding / 1.5, width / 4, titleHeight);
    routeBox.setBounds(routeLabel.getRight() - 2 * padding, padding, width / 8, titleHeight - padding / 2);
    lfo2Label.setBounds(width / 2 + padding / 2, padding / 1.5, width / 6, titleHeight);
    routeLabel2.setBounds(lfo2Label.getRight() + padding / 2, padding / 1.5, width / 4, titleHeight);
    routeBox2.setBounds(routeLabel2.getRight() - 2 * padding, padding, width / 8, titleHeight - padding / 2);

}

void LfoComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void LfoComponent::setSliderParams(juce::Slider& slider, juce::Label& label, juce::String name, int style)
{
    addAndMakeVisible(slider);
    addAndMakeVisible(label);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    label.setText(name, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    //label.attachToComponent(&slider, false);

    switch (style)
    {
    case vertical:
        label.attachToComponent(&slider, false);
        slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
        break;
    case rotary:
        label.attachToComponent(&slider, false);
        slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
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

void LfoComponent::setCustomLookAndFeel(juce::LookAndFeel_V4* customLookAndFeel)
{
    setLookAndFeel(customLookAndFeel);
}

void LfoComponent::setRegionTitle(juce::String& region1, juce::String& region2)
{
    region1Index = region1;
    region2Index = region2;
}
