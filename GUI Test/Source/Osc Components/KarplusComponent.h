/*
  ==============================================================================

    KarplusComponent.h
    Created: 8 Apr 2022 11:36:06am
    Author:  juanp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class KarplusComponent  : public juce::Component
{
public:
    KarplusComponent();
    ~KarplusComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KarplusComponent)
};
