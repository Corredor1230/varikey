/*
  ==============================================================================

    FilterComponent.h
    Created: 8 Apr 2022 11:36:45am
    Author:  juanp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FilterComponent  : public juce::Component
{
public:

    enum sliderStyle {
        vertical = 0,
        rotary,
        horizontal
    };

    FilterComponent();
    ~FilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void setSliderParams(juce::Slider& slider, juce::Label& label, juce::String name, int style);
    void setCustomLookAndFeel(juce::LookAndFeel_V4* customLookAndFeel);

private:

    juce::Label titleLabel;

    juce::Slider lopCutoffSlider;
    juce::Slider hipCutoffSlider;
    juce::Slider lopQSlider;
    juce::Slider hipQSlider;

    juce::Label lopCutoffLabel;
    juce::Label hipCutoffLabel;
    juce::Label lopQLabel;
    juce::Label hipQLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};
