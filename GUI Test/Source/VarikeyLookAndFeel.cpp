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
    josefinSans.setFontSizeAndStyle(20.0f, "semi", 1.0f, 0.0f);
    customFont = josefinSans.getCurrentFont();
    setDefaultSansSerifTypeface(josefinSans.getCurrentTypeface());
    setSliderPalette(currentPalette);
    setComponentPalette(currentPalette);
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

/*
Sets current palette to sliders globally.
Alpha must be manually introduced for this function.
*/
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
    setColour(colourIds::textBoxOutlineColourId, juce::Colour((juce::uint8)0, 0, 0, 0.f));
    setColour(colourIds::textBoxTextColourId, juce::Colour((juce::uint8)palette.highlightElement[0],
        palette.highlightElement[1], palette.highlightElement[2], alpha));
    setColour(juce::TextEditor::ColourIds::textColourId, juce::Colour((juce::uint8)palette.highlightElement[0],
        palette.highlightElement[1], palette.highlightElement[2], alpha));

}

void VarikeyLookAndFeel::setColourPalette(palette paletteType)
{
    currentPalette = getColourPalette(paletteType);
}

/*
 Sets colours from current palette for various buttons and components.
*/
void VarikeyLookAndFeel::setComponentPalette(ColourPalette palette, float alpha)
{
    //ToggleButton Colour
    setColour(juce::ToggleButton::ColourIds::textColourId, juce::Colour((juce::uint8)palette.globalDark[0],
        palette.globalDark[1], palette.globalDark[2], alpha));
    setColour(juce::ToggleButton::ColourIds::tickColourId, juce::Colour((juce::uint8)palette.activeElement[0],
        palette.activeElement[1], palette.activeElement[2], alpha));
    setColour(juce::ToggleButton::ColourIds::tickDisabledColourId, juce::Colour((juce::uint8)palette.inactiveElement[0],
        palette.inactiveElement[1], palette.inactiveElement[2], alpha));

    //TabbedComponent Colour
    setColour(juce::TabbedComponent::ColourIds::backgroundColourId, juce::Colour((juce::uint8)palette.contrastDark[0],
        palette.contrastDark[1], palette.contrastDark[2], alpha));
    setColour(juce::TabbedComponent::ColourIds::outlineColourId, juce::Colour((juce::uint8)palette.highlightElement[0],
        palette.highlightElement[1], palette.highlightElement[2], alpha));

    setColour(juce::ResizableWindow::ColourIds::backgroundColourId, juce::Colour((juce::uint8)palette.globalDark[0],
        palette.globalDark[1], palette.globalDark[2], alpha));
}

/*
 String with possible colours from a standardized colour palette.
 Possible enums: active, inactive, highlight 
 contrast, gLight, gDark.
 Alpha parameter is optional.
 Returns colours from current palette.
*/
juce::Colour VarikeyLookAndFeel::getColourFromPalette(paletteColours colour, float alpha)
{
    juce::Colour activeColour;
    juce::Colour inactiveColour;
    juce::Colour highlightColour;
    juce::Colour contrastColour;
    juce::Colour gLightColour;
    juce::Colour gDarkColour;

    switch (colour)
    {
    case 0:
        activeColour = juce::Colour((juce::uint8)currentPalette.activeElement[0],
            currentPalette.activeElement[1], currentPalette.activeElement[2], alpha);
        return activeColour;
    case 1:
        inactiveColour = juce::Colour((juce::uint8)currentPalette.inactiveElement[0],
            currentPalette.inactiveElement[1], currentPalette.inactiveElement[2], alpha);
        return inactiveColour;
    case 2:
        highlightColour = juce::Colour((juce::uint8)currentPalette.highlightElement[0],
            currentPalette.highlightElement[1], currentPalette.highlightElement[2], alpha);
        return highlightColour;
    case 3:
        contrastColour = juce::Colour((juce::uint8)currentPalette.contrastDark[0],
            currentPalette.contrastDark[1], currentPalette.contrastDark[2], alpha);
        return activeColour;
    case 4:
        gLightColour = juce::Colour((juce::uint8)currentPalette.globalLight[0],
            currentPalette.globalLight[1], currentPalette.globalLight[2], alpha);
        return gLightColour;
    case 5:
        gDarkColour = juce::Colour((juce::uint8)currentPalette.globalDark[0],
            currentPalette.globalDark[1], currentPalette.globalDark[2], alpha);
        return gDarkColour;
    default:
        jassertfalse;
    }

}

void VarikeyLookAndFeel::setFont(juce::Font& font)
{
    customFont = font;
}

juce::Font VarikeyLookAndFeel::getLabelFont(juce::Label& label)
{
    return customFont;
}