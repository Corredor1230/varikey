/*
  ==============================================================================

    EmbeddedFonts.cpp
    Created: 8 Apr 2022 11:39:18am
    Author:  juanp

  ==============================================================================
*/

#include "EmbeddedFonts.h"

EmbeddedFonts::EmbeddedFonts()
{
    //JosefinSans typeface initialization
    josefinSansRegular = juce::Font(juce::Typeface::createSystemTypefaceFor(BinaryData::JosefinSansRegular_ttf,
        BinaryData::JosefinSansRegular_ttfSize));

    josefinSansBold = juce::Font(juce::Typeface::createSystemTypefaceFor(BinaryData::JosefinSansBold_ttf,
        BinaryData::JosefinSansBold_ttfSize));

    josefinSansItalic = juce::Font(juce::Typeface::createSystemTypefaceFor(BinaryData::JosefinSansItalic_ttf,
        BinaryData::JosefinSansItalic_ttfSize));

    josefinSansMedium = juce::Font(juce::Typeface::createSystemTypefaceFor(BinaryData::JosefinSansMedium_ttf,
        BinaryData::JosefinSansMedium_ttfSize));

    josefinSansSemi = juce::Font(juce::Typeface::createSystemTypefaceFor(BinaryData::JosefinSansSemiBold_ttf,
        BinaryData::JosefinSansSemiBold_ttfSize));
}

/*
* Returns josefinSans font.
* Parameters can be modified using setFontSizeAndStyle method.
* Default parameters return 16.f size plain font.
*/
juce::Font& EmbeddedFonts::getJosefinSans()
{
    switch (fontStyle)
    {
    case regular:
        return josefinSansRegular;
        break;
    case bold:
        return josefinSansBold;
        break;
    case italic:
        return josefinSansItalic;
        break;
    case medium:
        return josefinSansMedium;
        break;
    case semi:
        return josefinSansSemi;
        break;
    }
}

/*
* This method adds different possible styles for the josefinSans font.
* Style keywords include "plain", "bold", "italic", "medium" and "semi".
* Horizontal refers to spacing within the font. 1.f is the default.
* Kerning default is 0.f. Negative values create negative kerning.
*/
void EmbeddedFonts::setFontSizeAndStyle(float height, const juce::String& style, float horizontal, float kerning)
{
    if (style == "plain")
    {
        josefinSansRegular.setSizeAndStyle(height, 0, horizontal, kerning);
        fontStyle = regular;
    }
    else if (style == "bold")
    {
        josefinSansBold.setSizeAndStyle(height, 0, horizontal, kerning);
        fontStyle = bold;
    }
    else if (style == "italic")
    {
        josefinSansItalic.setSizeAndStyle(height, 0, horizontal, kerning);
        fontStyle = italic;
    }
    else if (style == "medium")
    {
        josefinSansMedium.setSizeAndStyle(height, 0, horizontal, kerning);
        fontStyle = medium;
    }
    else if (style == "Semibold")
    {
        josefinSansSemi.setSizeAndStyle(height, 0, horizontal, kerning);
        fontStyle = semi;
    }
    else
    {
        josefinSansRegular.setSizeAndStyle(height, 0, horizontal, kerning);
        fontStyle = regular;
    }
}

/*Possible style strings
* "plain", "bold", "italic",
* "medium", "semi"
for font style */
void EmbeddedFonts::setFontStyle(const juce::String& style)
{
    if (style == "plain")
    {
        fontStyle = regular;
    }
    else if (style == "bold")
    {
        fontStyle = bold;
    }
    else if (style == "italic")
    {
        fontStyle = italic;
    }
    else if (style == "medium")
    {
        fontStyle = medium;
    }
    else if (style == "Semibold")
    {
        fontStyle = semi;
    }
    else
    {
        fontStyle = regular;
    }
}