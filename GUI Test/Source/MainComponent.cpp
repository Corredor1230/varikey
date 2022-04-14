#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    varikeyLookAndFeel.setColourPalette(VarikeyLookAndFeel::palette::vaporwave);
    setLookAndFeel(&varikeyLookAndFeel);
    addAndMakeVisible(tuner);
    setSize (600, 400);
}

MainComponent::~MainComponent()
{
    setLookAndFeel(nullptr);
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(varikeyLookAndFeel.getColourFromPalette(VarikeyLookAndFeel::paletteColours::gDark));
    josefinSans.setFontSizeAndStyle(60.f, "semi", 1.f, 0.f);
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
