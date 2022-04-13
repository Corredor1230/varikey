#pragma once

#include <JuceHeader.h>
#include "LookAndFeelElements/Fonts/EmbeddedFonts.h"
#include "Global Components/TuningComponent.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void changeAllSlidersColour(std::array<int, 3> track, std::array<int, 3> stem, std::array<int, 3> thumb, float alpha);

private:
    //==============================================================================
    // Your private member variables go here...


    //Colours
    float alphaValue = 0.8;
    int sliderAlpha = 0.8;
    std::array<int, 3> teal{ 109, 237, 230 };
    std::array<int, 3> cyan{ 174, 235, 254 };
    std::array<int, 3> purp{ 105, 98, 212 };
    std::array<int, 3> pink{ 253, 169, 247 };
    std::array<int, 3> pale{ 234, 246, 242 };

    EmbeddedFonts josefinSans;
    TuningComponent tuner;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
