/*
  ==============================================================================

    VarikeyLookAndFeel.cpp
    Created: 8 Apr 2022 11:37:15am
    Author:  juanp

  ==============================================================================
*/

#include<JuceHeader.h>
#include "VarikeyLookAndFeel.h"

VarikeyLookAndFeel::VarikeyLookAndFeel()
{
    currentPalette = getColourPalette(vaporwave);
    setSliderPalette(currentPalette, sliderAlpha);
}

VarikeyLookAndFeel::~VarikeyLookAndFeel()
{
}

ColourPalette VarikeyLookAndFeel::getColourPalette(palette paletteType)
{
    switch (paletteType)
    {
    case 0:
        ColourPalette vaporwave;
        vaporwave.activeElement = pink;
        vaporwave.inactiveElement= purp;
        vaporwave.highlightElement = cyan;
        vaporwave.contrastDark= dark;
        vaporwave.globalLight = pale;
        vaporwave.globalDark = black;
        return vaporwave;
    case 1:
        ColourPalette clean;
        clean.activeElement = orange;
        clean.inactiveElement = midGrey;
        clean.highlightElement = lightGrey;
        clean.contrastDark = darkGrey;
        clean.globalLight = almostWhite;
        clean.globalDark = black;
        return clean;
    }
}

void VarikeyLookAndFeel::setSliderPalette(ColourPalette palette, float alpha)
{
    typedef juce::Slider::ColourIds colourIds;

    //Vertical slider
    setColour(colourIds::trackColourId, juce::Colour((juce::uint8)palette.activeElement[0],
        palette.activeElement[1], palette.activeElement[2], alpha));
    setColour(colourIds::backgroundColourId, juce::Colour((juce::uint8)palette.inactiveElement[0],
        palette.inactiveElement[1], palette.inactiveElement[2], alpha));
    setColour(colourIds::thumbColourId, juce::Colour((juce::uint8)palette.highlightElement[0],
        palette.highlightElement[1], palette.highlightElement[2], alpha));

    //Rotary slider
    setColour(colourIds::rotarySliderFillColourId, juce::Colour((juce::uint8)palette.activeElement[0],
        palette.activeElement[1], palette.activeElement[2], alpha));
    setColour(colourIds::rotarySliderOutlineColourId, juce::Colour((juce::uint8)palette.globalLight[0],
        palette.globalLight[1], palette.globalLight[2], alpha));

    //TextBox
    setColour(colourIds::textBoxBackgroundColourId, juce::Colour());
    setColour(colourIds::textBoxHighlightColourId, juce::Colour((juce::uint8)palette.activeElement[0],
        palette.activeElement[1], palette.activeElement[2], alpha));
    setColour(colourIds::textBoxOutlineColourId, juce::Colour());
    setColour(colourIds::textBoxTextColourId, juce::Colour((juce::uint8)palette.globalDark[0],
        palette.globalDark[1], palette.globalDark[2], alpha));

}

void VarikeyLookAndFeel::setColourPalette(palette paletteType)
{
    currentPalette = getColourPalette(paletteType);
}
