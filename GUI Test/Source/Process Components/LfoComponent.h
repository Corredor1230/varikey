/*
  ==============================================================================

    LfoComponent.h
    Created: 8 Apr 2022 11:36:54am
    Author:  juanp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class LfoComponent  : public juce::Component
{
public:
    LfoComponent();
    ~LfoComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LfoComponent)
};
