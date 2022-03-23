/*
  ==============================================================================

    SynthVoice.h
    Created: 22 Mar 2022 10:48:04pm
    Author:  User

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "Data/AdsrData.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    float alterMidiPitch(int midiNoteNumber);
    float midiToHertz(float midiNoteNumber);
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

    void update(const float attack, const float decay, const float sustain, const float release);

private:

    AdsrData adsr;

    juce::AudioBuffer<float> synthBuffer;

    juce::dsp::Oscillator<float> osc{ [](float x) {return x / juce::MathConstants<float>::pi;  } };
    juce::dsp::Gain<float> gain;
    bool isPrepared{ false };

    //return std::sin(x); 
    //std::sin(x)+(std::sin(2*x)/2)+(std::sin(3*x)/2); //additive
    //return x / MathConstants<float>::pi;
    //return x < 0.0f ? -1.0f : 1.0f;

};