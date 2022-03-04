import("stdfaust.lib");
freq = vslider("freq[style:knob]",500,200,1000,0.01);
gain = vslider("gain",0.5,0,1,0.01) : si.smoo;
gate = button("gate") : si.smoo;
cutoff = vslider("cutoff[style:knob][scale:log]",1000,50,20000,0.01) : si.smoo;
vibFreq=vslider("vibFreq",0,0,20,0.02):si.smoo;
vibDepth=vslider("vibDepth[style:knob]",0,0,1,0.001):si.smoo;
tremFreq=vslider("tremFreq",0,0,20,0.02):si.smoo;
tremDepth=vslider("tremDepth[style:knob]",0,0,1,0.001):si.smoo;
pitchWheel=hslider("pitchWheel",0,-1,1,0.001):si.smoo;
detune = hslider("detune",0,0,1,0.001):si.smoo;
lfoFreq = vslider("lfoFreq[style:knob]",0,0,20,0.001):si.smoo;
lfoDepth = vslider("lfoDepth[style:knob]",0,0,48,0.001):si.smoo;
midiNote=ba.hz2midikey(freq);

oscFreq=vibrato+wheel with{
    oscillator = os.osc(vibFreq)*vibDepth;
    midiVib=midiNote+oscillator;
    vibrato = ba.midikey2hz(midiVib);
    wheel = ba.midikey2hz(midiNote+pitchWheel);
};

oscGain=tremolo*0.3 with{
    tremolo = (((os.osc(tremFreq)-1)/2)*tremDepth)+1;
};

/*lfoFilt=filter with{
    lfoOsc=os.osc(lfoFreq)*lfoDepth;
    midiCutoff = ba.hz2midikey(cutoff);
    lfoSumFreq= ba.midikey2hz(lfoOsc+midiCutoff);

    filter = fi.lowpass(3,lfoSumFreq);
};*/

oscWithStereoDetune = sawOsc(oscFreq)<:(_+sawOsc(oscFreq+detuneLeft))/2,(_+sawOsc(oscFreq+detuneRight))/2 with{
    detuneLeft=ba.midikey2hz(midiNote)-ba.midikey2hz(midiNote+detune);
    detuneRight=ba.midikey2hz(midiNote+detune)-ba.midikey2hz(midiNote);
    phaseReset=((detune*(-1))+1);
    sawOsc(x) = (os.lf_sawpos_phase(x, phaseReset)-0.5)*oscGain*gate:fi.lowpass(3,cutoff):fi.lowpass(5,18000);
};

process = oscWithStereoDetune:_*gain,_*gain;
//process = os.sawtooth(oscFreq)*oscGain*gate : fi.lowpass(3,cutoff) : fi.lowpass(5,18000)<: _,_;