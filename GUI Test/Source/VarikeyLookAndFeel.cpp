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