#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible(tuner);
    setSize (600, 400);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colour::Colour());

    josefinSans.setFontSizeAndStyle(60.f, "semi", 1.f, 0.f);
    changeAllSlidersColour(cyan, purp, pale, 0.9);
    g.setFont (josefinSans.getJosefinSans());
    g.setColour (juce::Colours::white);
    g.drawText ("Hello World!", getLocalBounds(), juce::Justification::centred, true);
}

void MainComponent::resized()
{
    getBounds().reduced(10, 10);
    int height = getHeight();
    int width = getWidth();

    int firstRowStartX = 0;
    int firstRowStartY = 0;
    int secondRowStartX = 0;
    int secondRowStartY = height / 3;
    int thirdRowStartX = 0;
    int thirdRowStartY = (height / 3) * 2;

    tuner.setBounds(0, 0, getWidth(), getHeight());
}

void MainComponent::changeAllSlidersColour(std::array<int, 3> track, std::array<int, 3> stem, std::array<int, 3> thumb, float alpha)
{
    getLookAndFeel().setColour(juce::Slider::ColourIds::trackColourId, juce::Colour::Colour((juce::uint8)track[0], track[1], track[2], alpha));
    getLookAndFeel().setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colour::Colour((juce::uint8)stem[0], stem[1], stem[2], alpha));
    getLookAndFeel().setColour(juce::Slider::ColourIds::thumbColourId, juce::Colour::Colour((juce::uint8)thumb[0], thumb[1], thumb[2], alpha));
}