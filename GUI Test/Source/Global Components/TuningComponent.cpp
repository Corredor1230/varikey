/*
  ==============================================================================

    TuningComponent.cpp
    Created: 8 Apr 2022 11:35:01am
    Author:  juanp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TuningComponent.h"

//==============================================================================
TuningComponent::TuningComponent(EmbeddedFonts font)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    //tuningFont = fonts.getJosefinSans();
    customFont = font.getJosefinSans();
    customFont.setSizeAndStyle(20.f, "plain", 1.0f, 0.0f);
    setSliderParams(slider0, label0, "Test", vertical);
    setSliderParams(slider1, label1, "This", vertical);
    setSliderParams(slider2, label2, "Font", vertical);
    setSliderParams(slider3, label3, "3", vertical);
    setSliderParams(slider4, label4, "4", vertical);
    setSliderParams(slider5, label5, "5", vertical);
    setSliderParams(slider6, label6, "6", vertical);
    setSliderParams(slider7, label7, "7", vertical);
    setSliderParams(slider8, label8, "8", vertical);
    setSliderParams(slider9, label9, "9", vertical);
    setSliderParams(slider10, label10, "10", vertical);
    setSliderParams(slider11, label11, "11", vertical);

}

TuningComponent::~TuningComponent()
{
}

void TuningComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colour());
    g.setFont(customFont);
}

void TuningComponent::resized()
{
    getBounds().reduced(10, 10);
    int height = getHeight();
    int width = getWidth();
    int padding = 10;
    int sliderLabel = height / 9;
    int title = height / 9;
    int sliderHeight = height - sliderLabel - title;
    int sliderWidth = (width / 12) - padding;
    int sliderStartX = padding;
    int sliderStartY = sliderLabel + title;

    slider0.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    slider1.setBounds(slider0.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    slider2.setBounds(slider1.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    slider3.setBounds(slider2.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    slider4.setBounds(slider3.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    slider5.setBounds(slider4.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    slider6.setBounds(slider5.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    slider7.setBounds(slider6.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    slider8.setBounds(slider7.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    slider9.setBounds(slider8.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    slider10.setBounds(slider9.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    slider11.setBounds(slider10.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);

}

void TuningComponent::setSliderParams(juce::Slider& slider, juce::Label& label, std::string name, int style)
{
    addAndMakeVisible(slider);
    addAndMakeVisible(label);
    slider.setNormalisableRange(juce::NormalisableRange<double>(-1.0, 1.0, 0.01));
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 25);
    label.setFont(customFont);
    label.setText(name, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    label.attachToComponent(&slider, false);
    //label.setFont(tuningFont);

    switch (style)
    {
    case vertical:
        slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
        break;
    case rotary:
        slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        break;
    case horizontal:
        slider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
        break;
    default:
        slider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
        break;
    }
}

void TuningComponent::setCustomLookAndFeel(juce::LookAndFeel_V4* customLookAndFeel)
{
    setLookAndFeel(customLookAndFeel);
}

void TuningComponent::setFont(juce::Font& font)
{
    customFont = font;
}
