#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() : tuner(josefinSans)
{
    varikeyLookAndFeel.setColourPalette(VarikeyLookAndFeel::palette::vaporwave);
    setLookAndFeel(&varikeyLookAndFeel);
    addAndMakeVisible(tuner);
    josefinSans.setFontSizeAndStyle(60.f, "italic", 1.f, 0.f);
    tuner.setCustomLookAndFeel(&varikeyLookAndFeel);
    //tuner.setFont(josefinSans.getJosefinSans());
    setSize (600, 400);
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
    g.setFont (josefinSans.getCurrentFont());
    g.setColour(juce::Colours::white);
    g.drawText ("Hello World!", getLocalBounds(), juce::Justification::centred, true);
}

void MainComponent::resized()
{
    getBounds().reduce(10, 10);
    int height = getHeight();
    int width = getWidth();

    int firstRowStartX = 0;
    int firstRowStartY = 0;
    int secondRowStartX = 0;
    int secondRowStartY = height / 3;
    int thirdRowStartX = 0;
    int thirdRowStartY = (height / 3) * 2;

    tuner.setBounds(-5, (2 * (height / 3) - 5), getWidth(), getHeight() / 3);
}
