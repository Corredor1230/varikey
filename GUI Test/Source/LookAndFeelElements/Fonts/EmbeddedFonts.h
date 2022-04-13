/*
  ==============================================================================

    EmbeddedFonts.h
    Created: 8 Apr 2022 11:39:18am
    Author:  juanp

  ==============================================================================
*/

#pragma once
#include<JuceHeader.h>

class EmbeddedFonts
{
public:

    enum fontStyle
    {
        regular = 0,
        bold,
        italic,
        medium,
        semi
    };

    EmbeddedFonts();
    juce::Font& getJosefinSans();
    void setFontSizeAndStyle(float height, const juce::String& style, 
        float horizontal, float kerning);
    void setFontStyle(const juce::String& style);
private:

    int fontStyle = 0;

    juce::Font josefinSansRegular;
    juce::Font josefinSansBold;
    juce::Font josefinSansItalic;
    juce::Font josefinSansMedium;
    juce::Font josefinSansSemi;


};