/*
  ==============================================================================

    TuningComponent.h
    Created: 24 Mar 2022 5:26:11am
    Author:  User

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class TuningComponent  : public juce::Component
{
public:
    TuningComponent(juce::AudioProcessorValueTreeState& vts
                    , juce::String cID
                    , juce::String cesID
                    , juce::String dID
                    , juce::String desID
                    , juce::String eID
                    , juce::String fID
                    , juce::String fesID
                    , juce::String gID
                    , juce::String gesID
                    , juce::String aID
                    , juce::String aesID
                    , juce::String bID);

    ~TuningComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    juce::Slider cSlider;
    juce::Slider cesSlider;
    juce::Slider dSlider;
    juce::Slider desSlider;
    juce::Slider eSlider;
    juce::Slider fSlider;
    juce::Slider fesSlider;
    juce::Slider gSlider;
    juce::Slider gesSlider;
    juce::Slider aSlider;
    juce::Slider aesSlider;
    juce::Slider bSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> cAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> cesAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> desAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> eAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fesAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gesAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> aAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> aesAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> bAttachment;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TuningComponent)
};
