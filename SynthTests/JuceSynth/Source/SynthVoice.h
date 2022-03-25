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
#include "Data/OscData.h"
#include "Data/NoteTuning.h"
#include <faust/misc.h>
#include <faust/dsp/dsp.h>
#include <faust/gui/MapUI.h>
#include "Oscilador.h"
#include "SimpleSynth.h"
#include "Test.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

    void update(const float attack, const float decay, const float sustain, const float release);
    OscData& getOscillator() { return osc; }
    NoteTuning& getTuning() { return tuning; }

private:
    SimpleSynth karplus;
    Oscilador oscil;
    Test test;
    MapUI ctrl;


    AdsrData adsr;

    juce::AudioBuffer<float> synthBuffer;

    OscData osc;
    NoteTuning tuning;
    juce::dsp::Gain<float> gain;
    bool isPrepared{ false };



};