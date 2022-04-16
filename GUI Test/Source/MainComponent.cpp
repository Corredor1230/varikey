#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() : 
    varikeyLookAndFeel(VarikeyLookAndFeel::palette::vaporwave)
{
    setLookAndFeel(&varikeyLookAndFeel);
    addAndMakeVisible(tuner);
    addAndMakeVisible(additiveLeft);
    addAndMakeVisible(additiveRight);
    addAndMakeVisible(leftOscChoice);
    addAndMakeVisible(rightOscChoice);

    josefinSans.setFontSizeAndStyle(60.f, "plain", 1.f, 0.f);

    tuner.setCustomLookAndFeel(&varikeyLookAndFeel);
    additiveLeft.setCustomLookAndFeel(&varikeyLookAndFeel);
    additiveRight.setCustomLookAndFeel(&varikeyLookAndFeel);

    juce::String rightRegionTitle = "Osc 2: ";
    additiveRight.setRegionTitle(rightRegionTitle);
    std::initializer_list<const char*> synthList{ "Generator", "Additive", "Karplus", "Noise" };
    leftOscChoice.addItemList(juce::StringArray(synthList), 1);
    leftOscChoice.setJustificationType(juce::Justification::centred);
    rightOscChoice.addItemList(juce::StringArray(synthList), 1);
    rightOscChoice.setJustificationType(juce::Justification::centred);
    setSize (600, 600);
}

MainComponent::~MainComponent()
{
    setLookAndFeel(nullptr);
    tuner.setCustomLookAndFeel(nullptr);
    additiveLeft.setCustomLookAndFeel(nullptr);
    additiveRight.setCustomLookAndFeel(nullptr);
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll(varikeyLookAndFeel.getColourFromPalette(VarikeyLookAndFeel::paletteColours::contrast));
    //g.setFont (josefinSans.getCurrentFont());
    g.fillAll(varikeyLookAndFeel.getColourFromPalette(VarikeyLookAndFeel::paletteColours::gDark));

}

void MainComponent::resized()
{
    getBounds().removeFromLeft(5);
    getBounds().removeFromRight(5);
    getBounds().removeFromTop(5);
    getBounds().removeFromBottom(5);
    int height = getHeight();
    int width = getWidth();

    int padding = 10;
    int firstRowStartX = 0;
    int firstRowStartY = 0;
    int firstRowHeight = 2 * (height / 9);
    int secondRowStartX = 0;
    int secondRowStartY = height / 3;
    int thirdRowStartX = 0;
    int thirdRowStartY = (height / 3) * 2;
    int firstColumnWidth = width / 3;
    int secondColumnWidth = width / 3;
    int oscChoiceWidth = (secondColumnWidth / 2) - padding;
    int oscChoiceHeight = (firstRowHeight / 4) - 1.5 * padding;

    tuner.setBounds(0, thirdRowStartY, getWidth(), getHeight() / 3);
    additiveLeft.setBounds(firstRowStartX, firstRowStartY, firstColumnWidth, firstRowHeight);
    additiveRight.setBounds(additiveLeft.getRight() + secondColumnWidth, firstRowStartY, firstColumnWidth, firstRowHeight);
    leftOscChoice.setBounds(additiveLeft.getRight() + (padding / 2), additiveLeft.getBottom() - oscChoiceHeight - (padding / 1.5), 
        oscChoiceWidth, oscChoiceHeight);
    rightOscChoice.setBounds(leftOscChoice.getRight() + padding, additiveLeft.getBottom() - oscChoiceHeight - (padding / 1.5), 
        oscChoiceWidth, oscChoiceHeight);

}
