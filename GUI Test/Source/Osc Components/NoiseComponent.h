/*
  ==============================================================================

    NoiseComponent.h
    Created: 16 Apr 2022 12:40:25am
    Author:  juanp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class NoiseComponent  : public juce::Component
{
public:
    NoiseComponent();
    ~NoiseComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoiseComponent)
};
