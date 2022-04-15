#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() : 
    varikeyLookAndFeel(VarikeyLookAndFeel::palette::clean)
{
    setLookAndFeel(&varikeyLookAndFeel);
    addAndMakeVisible(tuner);
    josefinSans.setFontSizeAndStyle(60.f, "plain", 1.f, 0.f);
    tuner.setCustomLookAndFeel(&varikeyLookAndFeel);
    setSize (600, 600);
}

MainComponent::~MainComponent()
{
    setLookAndFeel(nullptr);
    tuner.setCustomLookAndFeel(nullptr);
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll(varikeyLookAndFeel.getColourFromPalette(VarikeyLookAndFeel::paletteColours::contrast));
    //g.setFont (josefinSans.getCurrentFont());
    g.fillAll(varikeyLookAndFeel.getColourFromPalette(VarikeyLookAndFeel::paletteColours::gDark));
    g.setColour(juce::Colours::white);
    g.drawText ("Hello World!", getLocalBounds(), juce::Justification::centred, true);
}

void MainComponent::resized()
{
    getBounds().removeFromLeft(5);
    getBounds().removeFromRight(5);
    getBounds().removeFromTop(5);
    getBounds().removeFromBottom(5);
    int height = getHeight();
    int width = getWidth();

    int firstRowStartX = 0;
    int firstRowStartY = 0;
    int secondRowStartX = 0;
    int secondRowStartY = height / 3;
    int thirdRowStartX = 0;
    int thirdRowStartY = (height / 3) * 2;

    tuner.setBounds(0, (2 * (height / 3)), getWidth(), getHeight() / 3);
}
