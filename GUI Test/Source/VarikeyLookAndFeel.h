/*
  ==============================================================================

    VarikeyLookAndFeel.h
    Created: 8 Apr 2022 11:37:15am
    Author:  juanp

  ==============================================================================
*/

#pragma once

#include<JuceHeader.h>

struct ColourPalette
{
    std::array<int, 3> set1light;
    std::array<int, 3> set1dark;
    std::array<int, 3> set2light;
    std::array<int, 3> set2dark;
    std::array<int, 3> globalLight;
    std::array<int, 3> globalDark;
};

class VarikeyLookAndFeel : juce::LookAndFeel_V4
{
public:
    VarikeyLookAndFeel();

private:

    struct ColourPalette vaporwave;

    //Colour Palette

    std::array<int, 3> teal{ 109, 237, 230 };
    std::array<int, 3> cyan{ 174, 235, 254 };
    std::array<int, 3> purp{ 105, 98, 212 };
    std::array<int, 3> pink{ 253, 169, 247 };
    std::array<int, 3> pale{ 234, 246, 242 };
    std::array<int, 3> dark{ 45, 35, 82 };

};