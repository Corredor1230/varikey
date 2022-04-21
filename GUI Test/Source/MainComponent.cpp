#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() : 
    varikeyLookAndFeel(VarikeyLookAndFeel::palette::vaporwave)
{
    setLookAndFeel(&varikeyLookAndFeel);
    addAndMakeVisible(tuner);

    addAndMakeVisible(additiveLeft);
    addAndMakeVisible(additiveRight);
    addAndMakeVisible(genLeft);
    addAndMakeVisible(genRight);
    addAndMakeVisible(karpLeft);
    addAndMakeVisible(karpRight);
    addAndMakeVisible(noiseLeft);
    addAndMakeVisible(noiseRight);

    addAndMakeVisible(leftOscChoice);
    addAndMakeVisible(rightOscChoice);

    addAndMakeVisible(fmLeft);
    addAndMakeVisible(fmRight);
    addAndMakeVisible(crossSlider);
    addAndMakeVisible(crossLabel);

    addAndMakeVisible(filters);

    crossSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    crossSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 25);
    crossSlider.setRange(-1.0, 1.0, 0.01);
    crossLabel.setText("Mix", juce::sendNotification);
    crossLabel.setJustificationType(juce::Justification::centred);

    josefinSans.setFontSizeAndStyle(60.f, "plain", 1.f, 0.f);


    juce::String rightRegionTitle = "Osc 2: ";
    additiveRight.setRegionTitle(rightRegionTitle);
    genRight.setRegionTitle(rightRegionTitle);
    karpRight.setRegionTitle(rightRegionTitle);
    noiseRight.setRegionTitle(rightRegionTitle);

    std::initializer_list<const char*> synthList{ "Generator", "Additive", "Karplus", "Noise" };
    leftOscChoice.addItemList(juce::StringArray(synthList), 1);
    leftOscChoice.setJustificationType(juce::Justification::centred);
    leftOscChoice.setTextWhenNothingSelected("Generator");
    rightOscChoice.addItemList(juce::StringArray(synthList), 1);
    rightOscChoice.setJustificationType(juce::Justification::centred);
    rightOscChoice.setTextWhenNothingSelected("Generator");
    
    tuner.setCustomLookAndFeel(&varikeyLookAndFeel);
    additiveLeft.setCustomLookAndFeel(&varikeyLookAndFeel);
    additiveRight.setCustomLookAndFeel(&varikeyLookAndFeel);
    genLeft.setCustomLookAndFeel(&varikeyLookAndFeel);
    genRight.setCustomLookAndFeel(&varikeyLookAndFeel);
    karpLeft.setCustomLookAndFeel(&varikeyLookAndFeel);
    karpRight.setCustomLookAndFeel(&varikeyLookAndFeel);
    noiseLeft.setCustomLookAndFeel(&varikeyLookAndFeel);
    noiseRight.setCustomLookAndFeel(&varikeyLookAndFeel);
    fmLeft.setCustomLookAndFeel(&varikeyLookAndFeel);
    fmRight.setCustomLookAndFeel(&varikeyLookAndFeel);
    filters.setCustomLookAndFeel(&varikeyLookAndFeel);

    setSize (600, 700);
}

MainComponent::~MainComponent()
{
    setLookAndFeel(nullptr);
    tuner.setCustomLookAndFeel(nullptr);
    additiveLeft.setCustomLookAndFeel(nullptr);
    additiveRight.setCustomLookAndFeel(nullptr);
    genLeft.setCustomLookAndFeel(nullptr);
    genRight.setCustomLookAndFeel(nullptr);
    karpLeft.setCustomLookAndFeel(nullptr);
    karpRight.setCustomLookAndFeel(nullptr);
    noiseLeft.setCustomLookAndFeel(nullptr);
    noiseRight.setCustomLookAndFeel(nullptr);
    fmLeft.setCustomLookAndFeel(nullptr);
    fmRight.setCustomLookAndFeel(nullptr);
    filters.setCustomLookAndFeel(nullptr);
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll(varikeyLookAndFeel.getColourFromPalette(VarikeyLookAndFeel::paletteColours::gDark));

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
    int firstColumnWidth = width / 3;
    int secondColumnWidth = width / 3;

    int fmRowHeight = 1 * (height / 9);
    int labelHeight = 18;
    int labelWidth = 50;
    int labelStartX = firstColumnWidth + (secondColumnWidth / 2) - (labelWidth / 2);
    int crossHeight = fmRowHeight - labelHeight;

    int secondRowStartX = 0;
    int secondRowStartY = height / 3;

    int thirdRowStartX = 0;
    int thirdRowStartY = (height / 3) * 2;


    int oscChoiceWidth = (secondColumnWidth / 2) - padding;
    int oscChoiceHeight = (firstRowHeight / 4) - 1.5 * padding;

    tuner.setBounds(0, thirdRowStartY, getWidth(), getHeight() / 3);
    leftOscChoice.setBounds(firstColumnWidth + (padding / 2), firstRowHeight - oscChoiceHeight - (padding / 1.5),
        oscChoiceWidth, oscChoiceHeight);
    rightOscChoice.setBounds(leftOscChoice.getRight() + padding, firstRowHeight - oscChoiceHeight - (padding / 1.5),
        oscChoiceWidth, oscChoiceHeight);


    switch (getComboBoxIndex(leftOscChoice.getText()))
    {
    case 0:
        genLeft.setBounds(firstRowStartX, firstRowStartY, firstColumnWidth, firstRowHeight);
        additiveLeft.setBounds(0, 0, 0, 0);
        karpLeft.setBounds(0, 0, 0, 0);
        noiseLeft.setBounds(0, 0, 0, 0);
        break;
    case 1:
        genLeft.setBounds(0, 0, 0, 0);
        additiveLeft.setBounds(firstRowStartX, firstRowStartY, firstColumnWidth, firstRowHeight);
        karpLeft.setBounds(0, 0, 0, 0);
        noiseLeft.setBounds(0, 0, 0, 0);
        break;
    case 2:
        genLeft.setBounds(0, 0, 0, 0);
        additiveLeft.setBounds(0, 0, 0, 0);
        karpLeft.setBounds(firstRowStartX, firstRowStartY, firstColumnWidth, firstRowHeight);
        noiseLeft.setBounds(0, 0, 0, 0);
        break;
    case 3:
        genLeft.setBounds(0, 0, 0, 0);
        additiveLeft.setBounds(0, 0, 0, 0);
        karpLeft.setBounds(0, 0, 0, 0);
        noiseLeft.setBounds(firstRowStartX, firstRowStartY, firstColumnWidth, firstRowHeight);
        break;
    default:
        genLeft.setBounds(firstRowStartX, firstRowStartY, firstColumnWidth, firstRowHeight);
        additiveLeft.setBounds(0, 0, 0, 0);
        karpLeft.setBounds(0, 0, 0, 0);
        noiseLeft.setBounds(0, 0, 0, 0);
        break;
    }

    switch (getComboBoxIndex(rightOscChoice.getText()))
    {
    case 0:
        genRight.setBounds(firstColumnWidth + secondColumnWidth, firstRowStartY, firstColumnWidth, firstRowHeight);
        additiveRight.setBounds(0, 0, 0, 0);
        karpRight.setBounds(0, 0, 0, 0);
        noiseRight.setBounds(0, 0, 0, 0);
        break;
    case 1:
        genRight.setBounds(0, 0, 0, 0);
        additiveRight.setBounds(firstColumnWidth + secondColumnWidth, firstRowStartY, firstColumnWidth, firstRowHeight);
        karpRight.setBounds(0, 0, 0, 0);
        noiseRight.setBounds(0, 0, 0, 0);
        break;
    case 2:
        genRight.setBounds(0, 0, 0, 0);
        additiveRight.setBounds(0, 0, 0, 0);
        karpRight.setBounds(firstColumnWidth + secondColumnWidth, firstRowStartY, firstColumnWidth, firstRowHeight);
        noiseRight.setBounds(0, 0, 0, 0);
        break;
    case 3:
        genRight.setBounds(0, 0, 0, 0);
        additiveRight.setBounds(0, 0, 0, 0);
        karpRight.setBounds(0, 0, 0, 0);
        noiseRight.setBounds(firstColumnWidth + secondColumnWidth, firstRowStartY, firstColumnWidth, firstRowHeight);
        break;
    default:
        genRight.setBounds(firstColumnWidth + secondColumnWidth, firstRowStartY, firstColumnWidth, firstRowHeight);
        additiveRight.setBounds(0, 0, 0, 0);
        karpRight.setBounds(0, 0, 0, 0);
        noiseRight.setBounds(0, 0, 0, 0);
        break;
    }

    fmLeft.setBounds(firstRowStartX, firstRowHeight - padding, firstColumnWidth, fmRowHeight + padding);
    fmRight.setBounds(firstColumnWidth + secondColumnWidth, firstRowHeight - padding, firstColumnWidth, fmRowHeight + padding);
    crossSlider.setBounds(firstColumnWidth, crossLabel.getBottom(), secondColumnWidth, crossHeight);
    crossLabel.setBounds(labelStartX, firstRowHeight, labelWidth, labelHeight);



}

void MainComponent::resized()
{


}

int MainComponent::getComboBoxIndex(juce::String& string)
{
    if (string == "Generator")
        return 0;
    else if (string == "Additive")
        return 1;
    else if (string == "Karplus")
        return 2;
    else if (string == "Noise")
        return 3;
    else
        return 0;
}