/*
  ==============================================================================

    SynthVoice.cpp
    Created: 22 Mar 2022 10:48:04pm
    Author:  User

  ==============================================================================
*/

#include "SynthVoice.h"


bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

float SynthVoice::alterMidiPitch(int midiNoteNumber)
{
    float newPitch{};
    float pitchArray[12]{ 
        0.3, //C
        -0.2, //C#
        -0.2, //D
        0.2, //D#
        -0.15, //E
        -0.1, //F
        0.33, //F#
        -0.1, //G
        0.25, //G#
        -0.05, //A
        0.11, //A#
        0 //B
    };
    int pitchModulus = midiNoteNumber % 12; //Number of different pitches

    switch (pitchModulus)
    {
    case 0:
        newPitch = midiNoteNumber + pitchArray[0];
        break;
    case 1:
        newPitch = midiNoteNumber + pitchArray[1];
        break;
    case 2:
        newPitch = midiNoteNumber + pitchArray[2];
        break;
    case 3:
        newPitch = midiNoteNumber + pitchArray[3];
        break;
    case 4:
        newPitch = midiNoteNumber + pitchArray[4];
        break;
    case 5:
        newPitch = midiNoteNumber + pitchArray[5];
        break;
    case 6:
        newPitch = midiNoteNumber + pitchArray[6];
        break;
    case 7:
        newPitch = midiNoteNumber + pitchArray[7];
        break;
    case 8:
        newPitch = midiNoteNumber + pitchArray[8];
        break;
    case 9:
        newPitch = midiNoteNumber + pitchArray[9];
        break;
    case 10:
        newPitch = midiNoteNumber + pitchArray[10];
        break;
    case 11:
        newPitch = midiNoteNumber + pitchArray[11];
        break;
    default:
        DBG("Error");
        break;
    }
    return newPitch;
}

float SynthVoice::midiToHertz(float newMidi)
{
    float hertz = 440.f * pow(2.f, (newMidi - 69.f) / 12.f);
    return hertz;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    float newMidi = alterMidiPitch(midiNoteNumber);
    float oscFreq = midiToHertz(newMidi);
    osc.setFrequency(oscFreq);
    adsr.noteOn();
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    adsr.noteOff();
    if (!allowTailOff || !adsr.isActive())
    {
        clearCurrentNote();
    }
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{


}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{


}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    adsr.setSampleRate(sampleRate);

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    osc.prepare(spec);
    gain.prepare(spec);

    gain.setGainLinear(0.3f);

    isPrepared = true;

}

void SynthVoice::update(const float attack, const float decay, const float sustain, const float release)
{
    adsr.updateADSR(attack, decay, sustain, release);
}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    jassert(isPrepared);

    if (!isVoiceActive())
        return;

    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    synthBuffer.clear();

    juce::dsp::AudioBlock<float> audioBlock{ synthBuffer };
    osc.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());

    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);

        if (!adsr.isActive())
        {
            clearCurrentNote();
        }
    }
}
