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
    currentPalette = loadColourPalettes(vaporwave);
    setSliderPalette(currentPalette, sliderAlpha);
}

ColourPalette VarikeyLookAndFeel::loadColourPalettes(palette paletteType)
{
    switch (paletteType)
    {
    case 0:
        ColourPalette vaporwave;
        vaporwave.set1light = cyan;
        vaporwave.set1dark = purp;
        vaporwave.set2light = pink;
        vaporwave.set2dark = dark;
        vaporwave.globalLight = pale;
        vaporwave.globalDark = black;
        return vaporwave;
    case 1:
        ColourPalette clean;
        clean.set1light = orange;
        clean.set1dark = midGrey;
        clean.set2light = lightGrey;
        clean.set2dark = darkGrey;
        clean.globalLight = almostWhite;
        clean.globalDark = black;
        return clean;
    }
}

void VarikeyLookAndFeel::setSliderPalette(ColourPalette palette, float alpha)
{
    typedef juce::Slider::ColourIds colourIds;

    //Vertical slider
    setColour(colourIds::trackColourId, juce::Colour((juce::uint8)palette.set1light[0],
        palette.set1light[1], palette.set1light[2], alpha));
    setColour(colourIds::backgroundColourId, juce::Colour((juce::uint8)palette.set1dark[0],
        palette.set1dark[1], palette.set1dark[2], alpha));
    setColour(colourIds::thumbColourId, juce::Colour((juce::uint8)palette.set2light[0],
        palette.set2light[1], palette.set2light[2], alpha));

    //Rotary slider
    setColour(colourIds::rotarySliderFillColourId, juce::Colour((juce::uint8)palette.set1light[0],
        palette.set1light[1], palette.set1light[2], alpha));
    setColour(colourIds::rotarySliderOutlineColourId, juce::Colour((juce::uint8)palette.globalLight[0],
        palette.globalLight[1], palette.globalLight[2], alpha));

    //TextBox
    setColour(colourIds::textBoxBackgroundColourId, juce::Colour());
    setColour(colourIds::textBoxHighlightColourId, juce::Colour((juce::uint8)palette.set1light[0],
        palette.set1light[1], palette.set1light[2], alpha));
    setColour(colourIds::textBoxOutlineColourId, juce::Colour());
    setColour(colourIds::textBoxTextColourId, juce::Colour((juce::uint8)palette.globalDark[0],
        palette.globalDark[1], palette.globalDark[2], alpha));
}