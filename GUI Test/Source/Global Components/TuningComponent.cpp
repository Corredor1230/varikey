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
TuningComponent::TuningComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    setSliderParams(slider0, label0, "Test", vertical);
    setSliderParams(slider1, label1, "Test", vertical);
    setSliderParams(slider2, label2, "Test", vertical);
    setSliderParams(slider3, label3, "3", vertical);
    setSliderParams(slider4, label4, "4", vertical);
    setSliderParams(slider5, label5, "5", vertical);
    setSliderParams(slider6, label6, "6", vertical);
    setSliderParams(slider7, label7, "7", vertical);
    setSliderParams(slider8, label8, "8", vertical);
    setSliderParams(slider9, label9, "9", vertical);

}

TuningComponent::~TuningComponent()
{
}

void TuningComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    g.setColour(juce::Colour());

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
    int sliderWidth = (width / 10) - padding;
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

}

void TuningComponent::setSliderParams(juce::Slider& slider, juce::Label& label, std::string name, int style)
{
    addAndMakeVisible(slider);
    addAndMakeVisible(label);
    slider.setNormalisableRange(juce::NormalisableRange<double>(-1.0, 1.0, 0.01));
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 25);
    label.setText(name, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    label.attachToComponent(&slider, false);

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

//void TuningComponent::drawSliders(juce::Slider& slider, int sliderStartX, int numSliders, int sliderStartY, int sliderWidth, int sliderHeight, int padding = 10)
//{
//    int widthCount{};
//
//    for (int i = 0; i < numSliders; i++)
//    {
//        if (i == 0)
//        {
//            slider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
//            widthCount = sliderWidth + padding;
//        }
//        else
//        {
//            slider.setBounds(widthCount * i, sliderStartY, sliderWidth, sliderHeight);
//        }
//    }
//}
