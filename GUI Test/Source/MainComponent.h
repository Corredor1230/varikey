#pragma once

#include <JuceHeader.h>
#include "LookAndFeelElements/Fonts/EmbeddedFonts.h"
#include "Global Components/TuningComponent.h"
#include "VarikeyLookAndFeel.h"
#include "Osc Components/AdditiveComponent.h"
#include "Osc Components/GenComponent.h"
#include "Osc Components/KarplusComponent.h"
#include "Osc Components/NoiseComponent.h"
#include "Process Components/FmComponent.h"
#include "Process Components/FilterComponent.h"
#include "Process Components/AdsrComponent.h"
#include "Process Components/ModAdsrComponent.h"
#include "Process Components/LfoComponent.h"
#include "Global Components/PitchwheelComponent.h"

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
    int getComboBoxIndex(juce::String& string);

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

    juce::ComboBox leftOscChoice;
    juce::ComboBox rightOscChoice;


    int leftOscValue = 1;
    int rightOscValue = 1;

    EmbeddedFonts josefinSans;

    //First Row
    AdditiveComponent additiveLeft;
    AdditiveComponent additiveRight;
    GenComponent genLeft;
    GenComponent genRight;
    KarplusComponent karpLeft;
    KarplusComponent karpRight;
    NoiseComponent noiseLeft;
    NoiseComponent noiseRight;

    //FM Row
    FmComponent fmLeft;
    FmComponent fmRight;
    juce::Slider crossSlider;
    juce::Label crossLabel;

    //Second Row
    FilterComponent filters;
    AdsrComponent ampAdsr;
    ModAdsrComponent modAdsr;
    LfoComponent lfo1;
    LfoComponent lfo2;
    PitchwheelComponent pitchwheel;

    //Third Row
    TuningComponent tuner;
    juce::Slider volumeSlider;
    juce::Label volumeLabel;

    VarikeyLookAndFeel varikeyLookAndFeel;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
