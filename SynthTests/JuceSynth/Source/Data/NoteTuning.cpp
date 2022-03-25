/*
  ==============================================================================

    NoteTuning.cpp
    Created: 24 Mar 2022 5:25:44am
    Author:  User

  ==============================================================================
*/

#include "NoteTuning.h"


int NoteTuning::getModulus(const int midiNoteNumber)
{
    int pitchModulus{};
    pitchModulus = midiNoteNumber % 12; //Number of different pitches
    return pitchModulus;
}

float NoteTuning::alterMidiPitch(const float c
,const float ces
,const float d
,const float des
,const float e
,const float f
,const float fes
,const float g
,const float ges
,const float a
,const float aes
,const float b)
{
    float newPitch{};
    int midiNoteNumber{};
    int pitchModulus = getModulus(midiNoteNumber);

    switch (pitchModulus)
    {
    case 0:
        newPitch = midiNoteNumber + c;
        break;
    case 1:
        newPitch = midiNoteNumber + ces;
        break;
    case 2:
        newPitch = midiNoteNumber + d;
        break;
    case 3:
        newPitch = midiNoteNumber + des;
        break;
    case 4:
        newPitch = midiNoteNumber + e;
        break;
    case 5:
        newPitch = midiNoteNumber + f;
        break;
    case 6:
        newPitch = midiNoteNumber + fes;
        break;
    case 7:
        newPitch = midiNoteNumber + g;
        break;
    case 8:
        newPitch = midiNoteNumber + ges;
        break;
    case 9:
        newPitch = midiNoteNumber + a;
        break;
    case 10:
        newPitch = midiNoteNumber + aes;
        break;
    case 11:
        newPitch = midiNoteNumber + b;
        break;
    default:
        DBG("Error");
        break;
    }
    return newPitch;
}

float NoteTuning::midiToHertz(const float midiNoteNumber)
{
    float hertz = 440.f * pow(2.f, (midiNoteNumber - 69.f) / 12.f);
    return hertz;
}