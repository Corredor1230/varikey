import("stdfaust.lib");

//Parameter declarations
freq = vslider("freq[style:knob]",500,200,1000,0.01);
gain = vslider("gain",0.5,0,1,0.01) : si.smoo;
gate = button("gate") : si.smoo;
cutoff = vslider("cutoff[style:knob][scale:log]",1000,110,20000,0.01) : si.smoo;
vibFreq=vslider("vibFreq",0,0,20,0.02):si.smoo;
vibDepth=vslider("vibDepth[style:knob]",0,0,1,0.001):si.smoo;
tremFreq=vslider("tremFreq",0,0,20,0.02):si.smoo;
tremDepth=vslider("tremDepth[style:knob]",0,0,1,0.001):si.smoo;
pitchWheel=hslider("pitchWheel",0,-1,1,0.001):si.smoo;
detune = hslider("detune",0,0,1,0.001):si.smoo;
lfoFreq = vslider("lfoFreq",0,0,20,0.001):si.smoo;
lfoDepth = vslider("lfoDepth[style:knob]",0,0,1,0.0001):si.smoo;
midiNote=ba.hz2midikey(freq);

//Adds pitch wheel and vibrato to frequency
oscFreq=vibrato+wheel with{
    oscillator = os.osc(vibFreq)*vibDepth;
    midiVib=midiNote+oscillator;
    vibrato = ba.midikey2hz(midiVib);
    wheel = ba.midikey2hz(midiNote+pitchWheel);
};

//Adds tremolo to gain
oscGain=tremolo*gain*0.5 with{
    tremolo = (((os.osc(tremFreq)-1)/2)*tremDepth)+1;
};

//Creates lfo-controlled low-pass filter frequency
lfoFilt=filter with{
    maxValue=18000;
    minValue=100;
    cutoffMid=cutoff;
    distanceToMin=cutoff-minValue;
    distanceToMax=maxValue-cutoff;
    isMaxSmallerThan=distanceToMax<distanceToMin;
    width=distanceToMin,distanceToMax:select2(isMaxSmallerThan):_:si.smoo;
    lfoGain=width*lfoDepth;
    lfoFreqOsc=os.osc(lfoFreq)*lfoGain;
    filter=cutoff+lfoFreqOsc;

};

//Adds stereo detune to the synthesizer
oscWithStereoDetune = sawOsc(oscFreq)<:(_+sawOsc(oscFreq+detuneLeft))/2,(_+sawOsc(oscFreq+detuneRight))/2 with{
    detuneLeft=ba.midikey2hz(midiNote)-ba.midikey2hz(midiNote+detune);
    detuneRight=ba.midikey2hz(midiNote+detune)-ba.midikey2hz(midiNote);
    phaseReset=((detune*(-1))+1);
    sawOsc(x) = (os.lf_sawpos_phase(x, phaseReset)-0.5)*oscGain*gate:fi.lowpass(3,lfoFilt):fi.lowpass(5,18000);
};

process = oscWithStereoDetune;