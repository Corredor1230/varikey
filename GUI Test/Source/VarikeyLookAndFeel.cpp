/*
  ==============================================================================

    VarikeyLookAndFeel.cpp
    Created: 8 Apr 2022 11:37:15am
    Author:  juanp

  ==============================================================================
*/

#include<JuceHeader.h>
#include "VarikeyLookAndFeel.h"

VarikeyLookAndFeel::VarikeyLookAndFeel(palette paletteType)
{
    currentPalette = getColourPalette(paletteType);
    //These parameters define the font for most components
    //Modify them wisely!
    josefinSans.setFontSizeAndStyle(22.0f, "medium", 1.0f, 0.0f);
    customFont = josefinSans.getCurrentFont();
    setDefaultSansSerifTypeface(josefinSans.getCurrentTypeface());
    setSliderPalette(currentPalette);
    setComponentPalette(currentPalette);
    labelBorder.setBottom(0);
    labelBorder.setTop(0);
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
        vaporwave.highlightElement = pale;
        vaporwave.contrastDark= dark;
        vaporwave.globalLight = cyan;
        vaporwave.globalDark = black;
        return vaporwave;
    case 1:
        ColourPalette clean;
        clean.activeElement = orange;
        clean.inactiveElement = midGrey;
        clean.highlightElement = pale;
        clean.contrastDark = darkGrey;
        clean.globalLight = almostWhite;
        clean.globalDark = almostBlack;
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
    setColour(juce::ToggleButton::ColourIds::textColourId, juce::Colour((juce::uint8)palette.inactiveElement[0],
        palette.inactiveElement[1], palette.inactiveElement[2], alpha));
    setColour(juce::ToggleButton::ColourIds::tickColourId, juce::Colour((juce::uint8)palette.activeElement[0],
        palette.activeElement[1], palette.activeElement[2], alpha));
    setColour(juce::ToggleButton::ColourIds::tickDisabledColourId, juce::Colour((juce::uint8)palette.inactiveElement[0],
        palette.inactiveElement[1], palette.inactiveElement[2], alpha));

    //TabbedComponent Colour
    setColour(juce::TabbedComponent::ColourIds::backgroundColourId, juce::Colour((juce::uint8)palette.contrastDark[0],
        palette.contrastDark[1], palette.contrastDark[2], alpha));
    setColour(juce::TabbedComponent::ColourIds::outlineColourId, juce::Colour((juce::uint8)palette.highlightElement[0],
        palette.highlightElement[1], palette.highlightElement[2], alpha));

    setColour(juce::Label::ColourIds::textColourId, juce::Colour((juce::uint8)palette.highlightElement[0],
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

juce::BorderSize<int> VarikeyLookAndFeel::getLabelBorderSize(juce::Label& label)
{
    labelBorder = juce::BorderSize<int>::BorderSize(0, 0, 0, 0);
    label.setBorderSize(labelBorder);
    return label.getBorderSize();
}


void VarikeyLookAndFeel::setDistanceToSlider(float distance, juce::String& type)
{
    if (type == "vertical") verticalDistanceToSlider = distance;
    else if (type == "horizontal") horizontalDistanceToSlider = distance;
}


juce::Slider::SliderLayout VarikeyLookAndFeel::getSliderLayout(juce::Slider& slider)
{
    // 1. compute the actually visible textBox size from the slider textBox size and some additional constraints

    int minXSpace = 0;
    int minYSpace = 0;

    auto textBoxPos = slider.getTextBoxPosition();

    if (textBoxPos == juce::Slider::TextBoxLeft || textBoxPos == juce::Slider::TextBoxRight)
        minXSpace = 30;
    else
        minYSpace = 15;

    juce::Rectangle<int> localBounds = slider.getLocalBounds();

    auto textBoxWidth = juce::jmax(0, juce::jmin(slider.getTextBoxWidth(), localBounds.getWidth() - minXSpace));
    auto textBoxHeight = juce::jmax(0, juce::jmin(slider.getTextBoxHeight(), localBounds.getHeight() - minYSpace));

    juce::Slider::SliderLayout layout;

    // 2. set the textBox bounds

    if (textBoxPos != juce::Slider::NoTextBox)
    {
        if (slider.isBar())
        {
            layout.textBoxBounds = localBounds;
        }
        else
        {
            layout.textBoxBounds.setWidth(textBoxWidth);
            layout.textBoxBounds.setHeight(textBoxHeight);

            if (textBoxPos == juce::Slider::TextBoxLeft) { 
                layout.textBoxBounds.setX(0);
                layout.textBoxBounds.removeFromBottom(3);
            }
            else if (textBoxPos == juce::Slider::TextBoxRight)     layout.textBoxBounds.setX(localBounds.getWidth() - textBoxWidth);
            else /* above or below -> centre horizontally */ layout.textBoxBounds.setX((localBounds.getWidth() - textBoxWidth) / 2);

            if (textBoxPos == juce::Slider::TextBoxAbove)          layout.textBoxBounds.setY(0);
            else if (textBoxPos == juce::Slider::TextBoxBelow)     layout.textBoxBounds.setY(localBounds.getHeight() - textBoxHeight);
            else /* left or right -> centre vertically */    layout.textBoxBounds.setY((localBounds.getHeight() - textBoxHeight) / 2);
        }
    }

    // 3. set the slider bounds

    layout.sliderBounds = localBounds;

    if (slider.isBar())
    {
        layout.sliderBounds.reduce(1, 1);   // bar border
    }
    else
    {
        if (textBoxPos == juce::Slider::TextBoxLeft)       layout.sliderBounds.removeFromLeft(textBoxWidth - 15 + horizontalDistanceToSlider);
        else if (textBoxPos == juce::Slider::TextBoxRight) layout.sliderBounds.removeFromRight(textBoxWidth);
        else if (textBoxPos == juce::Slider::TextBoxAbove) layout.sliderBounds.removeFromTop(textBoxHeight);
        else if (textBoxPos == juce::Slider::TextBoxBelow) layout.sliderBounds.removeFromBottom(textBoxHeight - 15 + verticalDistanceToSlider);

        const int thumbIndent = getSliderThumbRadius(slider);

        if (slider.isHorizontal())    layout.sliderBounds.reduce(thumbIndent, 0);
        else if (slider.isVertical()) layout.sliderBounds.reduce(0, thumbIndent);
    }

    return layout;
}