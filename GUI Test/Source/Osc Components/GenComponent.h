/*
  ==============================================================================

    GenComponent.h
    Created: 16 Apr 2022 12:40:43am
    Author:  juanp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class GenComponent  : public juce::Component
{
public:
    GenComponent();
    ~GenComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GenComponent)
};
