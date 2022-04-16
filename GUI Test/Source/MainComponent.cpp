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

    addAndMakeVisible(leftOscChoice);
    addAndMakeVisible(rightOscChoice);

    josefinSans.setFontSizeAndStyle(60.f, "plain", 1.f, 0.f);


    juce::String rightRegionTitle = "Osc 2: ";
    additiveRight.setRegionTitle(rightRegionTitle);
    genRight.setRegionTitle(rightRegionTitle);

    std::initializer_list<const char*> synthList{ "Generator", "Additive", "Karplus", "Noise" };
    leftOscChoice.addItemList(juce::StringArray(synthList), 1);
    leftOscChoice.setJustificationType(juce::Justification::centred);
    rightOscChoice.addItemList(juce::StringArray(synthList), 1);
    rightOscChoice.setJustificationType(juce::Justification::centred);
    
    tuner.setCustomLookAndFeel(&varikeyLookAndFeel);
    additiveLeft.setCustomLookAndFeel(&varikeyLookAndFeel);
    additiveRight.setCustomLookAndFeel(&varikeyLookAndFeel);
    genLeft.setCustomLookAndFeel(&varikeyLookAndFeel);
    genRight.setCustomLookAndFeel(&varikeyLookAndFeel);

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
    int secondRowStartX = 0;
    int secondRowStartY = height / 3;
    int thirdRowStartX = 0;
    int thirdRowStartY = (height / 3) * 2;
    int firstColumnWidth = width / 3;
    int secondColumnWidth = width / 3;
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
        break;
    case 1:
        genLeft.setBounds(0, 0, 0, 0);
        additiveLeft.setBounds(firstRowStartX, firstRowStartY, firstColumnWidth, firstRowHeight);
        break;
    default:
        genLeft.setBounds(firstRowStartX, firstRowStartY, firstColumnWidth, firstRowHeight);
        additiveLeft.setBounds(0, 0, 0, 0);
        break;
    }

    switch (getComboBoxIndex(rightOscChoice.getText()))
    {
    case 0:
        genRight.setBounds(firstColumnWidth + secondColumnWidth, firstRowStartY, firstColumnWidth, firstRowHeight);
        additiveRight.setBounds(0, 0, 0, 0);
        break;
    case 1:
        genRight.setBounds(0, 0, 0, 0);
        additiveRight.setBounds(firstColumnWidth + secondColumnWidth, firstRowStartY, firstColumnWidth, firstRowHeight);
        break;
    default:
        genRight.setBounds(firstColumnWidth + secondColumnWidth, firstRowStartY, firstColumnWidth, firstRowHeight);
        additiveRight.setBounds(0, 0, 0, 0);
        break;
    }

    //additiveLeft.setBounds(firstRowStartX, firstRowStartY, firstColumnWidth, firstRowHeight);
    //additiveRight.setBounds(additiveLeft.getRight() + secondColumnWidth, firstRowStartY, firstColumnWidth, firstRowHeight);
    //genLeft.setBounds(firstRowStartX, firstRowStartY, firstColumnWidth, firstRowHeight);
    //genRight.setBounds(genLeft.getRight() + secondColumnWidth, firstRowStartY, firstColumnWidth, firstRowHeight);

}

void MainComponent::resized()
{
    //Comentado por ahora porque necesito introducir lógica
    //y switch statements a la interfaz gráfica.
    //No estaba funcionando dentro de resized()


    //getBounds().removeFromLeft(5);
    //getBounds().removeFromRight(5);
    //getBounds().removeFromTop(5);
    //getBounds().removeFromBottom(5);
    //int height = getHeight();
    //int width = getWidth();

    //int padding = 10;
    //int firstRowStartX = 0;
    //int firstRowStartY = 0;
    //int firstRowHeight = 2 * (height / 9);
    //int secondRowStartX = 0;
    //int secondRowStartY = height / 3;
    //int thirdRowStartX = 0;
    //int thirdRowStartY = (height / 3) * 2;
    //int firstColumnWidth = width / 3;
    //int secondColumnWidth = width / 3;
    //int oscChoiceWidth = (secondColumnWidth / 2) - padding;
    //int oscChoiceHeight = (firstRowHeight / 4) - 1.5 * padding;

    //tuner.setBounds(0, thirdRowStartY, getWidth(), getHeight() / 3);
    ////additiveLeft.setBounds(firstRowStartX, firstRowStartY, firstColumnWidth, firstRowHeight);
    ////additiveRight.setBounds(additiveLeft.getRight() + secondColumnWidth, firstRowStartY, firstColumnWidth, firstRowHeight);
    //genLeft.setBounds(firstRowStartX, firstRowStartY, firstColumnWidth, firstRowHeight);
    //genRight.setBounds(genLeft.getRight() + secondColumnWidth, firstRowStartY, firstColumnWidth, firstRowHeight);
    //leftOscChoice.setBounds(additiveLeft.getRight() + (padding / 2), additiveLeft.getBottom() - oscChoiceHeight - (padding / 1.5), 
    //    oscChoiceWidth, oscChoiceHeight);
    //rightOscChoice.setBounds(leftOscChoice.getRight() + padding, additiveLeft.getBottom() - oscChoiceHeight - (padding / 1.5), 
    //    oscChoiceWidth, oscChoiceHeight);

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