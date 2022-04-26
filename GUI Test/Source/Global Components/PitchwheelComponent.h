/*
  ==============================================================================

    PitchwheelComponent.h
    Created: 25 Apr 2022 11:36:32pm
    Author:  juanp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class PitchwheelComponent  : public juce::Component
{
public:
    PitchwheelComponent();
    ~PitchwheelComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PitchwheelComponent)
};
