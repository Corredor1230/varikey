/*
  ==============================================================================

    GlobalComponents.h
    Created: 8 Apr 2022 11:35:45am
    Author:  juanp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class GlobalComponents  : public juce::Component
{
public:
    GlobalComponents();
    ~GlobalComponents() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GlobalComponents)
};
