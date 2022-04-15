/*
  ==============================================================================

    VarikeyLookAndFeel.h
    Created: 8 Apr 2022 11:37:15am
    Author:  juanp

  ==============================================================================
*/

#pragma once

#include<JuceHeader.h>
#include"LookAndFeelElements/Fonts/EmbeddedFonts.h"

struct ColourPalette
{
    std::array<int, 3> activeElement;
    std::array<int, 3> inactiveElement;
    std::array<int, 3> highlightElement;
    std::array<int, 3> contrastDark;
    std::array<int, 3> globalLight;
    std::array<int, 3> globalDark;
};


class VarikeyLookAndFeel : public juce::LookAndFeel_V4
{
public:

    enum palette
    {
        vaporwave = 0,
        clean,
        darkPalette,
        vintagePC,
        tech
    };

    enum paletteColours
    {
        active = 0,
        inactive,
        highlight,
        contrast,
        gLight,
        gDark
    };

    VarikeyLookAndFeel();
    ~VarikeyLookAndFeel() override;

    void setSliderPalette(ColourPalette palette, float alpha = 0.95f);
    void setColourPalette(palette paletteType);
    void setComponentPalette(ColourPalette palette, float alpha = 1.0f);
    void setFont(juce::Font& font);
    void setDistanceToSlider(float distance);

    //Overriding look and feel to create new defaults
    juce::Slider::SliderLayout getSliderLayout(juce::Slider& slider) override;
    juce::Font getLabelFont(juce::Label&) override;
    juce::BorderSize<int> getLabelBorderSize(juce::Label&) override;
    
    
    ColourPalette getColourPalette(palette paletteType);
    juce::Colour getColourFromPalette(paletteColours colour, float alpha = 1.0f);
    

private: 


    struct ColourPalette currentPalette;

    //Colour Palettes
    float sliderAlpha = 0.9;
    float componentAlpha = 1.0;
    float distanceToSlider = 7.0;
    //Vaporwave Palette
    std::array<int, 3> cyan{ 174, 235, 254 };
    std::array<int, 3> purp{ 105, 98, 212 };
    std::array<int, 3> pink{ 253, 169, 247 };
    std::array<int, 3> pale{ 234, 246, 242 };
    std::array<int, 3> dark{ 45, 35, 82 };
    std::array<int, 3> black{ 0, 0, 0 };

    //Clean Palette
    std::array<int, 3> orange{ 255, 65, 102 };
    std::array<int, 3> midGrey{ 88, 88, 88 };
    std::array<int, 3> lightGrey{ 139, 139, 139 };
    std::array<int, 3> darkGrey{ 42, 42, 42 };
    std::array<int, 3> almostWhite{ 243, 243, 243 };
    //Black


    //Fonts
    juce::Font customFont;
    EmbeddedFonts josefinSans;

    //Shapes
    juce::BorderSize<int> labelBorder;
};

