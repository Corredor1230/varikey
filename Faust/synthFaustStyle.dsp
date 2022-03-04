import("stdfaust.lib");

//Parameter declarations
freq = vslider("freq[style:knob]",500,200,1000,0.01);
gain = vslider("gain",-20,-60,0,1) : ba.db2linear;
gate = button("gate") : si.smoo;
cutoff = vslider("cutoff[style:knob][scale:log]",1000,110,20000,0.01) : si.smoo : max(20);
vibFreq = vslider("vibFreq",0,0,20,0.02):si.smoo;
vibDepth = vslider("vibDepth[style:knob]",0,0,1,0.001):si.smoo;
tremFreq = vslider("tremFreq",0,0,20,0.02):si.smoo;
tremDepth = vslider("tremDepth[style:knob]",0,0,1,0.001):si.smoo;
pitchWheel = hslider("pitchWheel",0,-1,1,0.001):si.smoo;
detune = hslider("detune",0,0,1,0.001):si.smoo;
lfoFreq = vslider("lfoFreq",0,0,20,0.001):si.smoo;
lfoDepth = vslider("lfoDepth[style:knob]",0,0,20000,1):si.smoo;
midiNote=ba.hz2midikey(freq);

voice(note, detune) = oscillator(note - detune), oscillator(note), oscillator(note + detune) : _ , (_ <: _, _ ), _ : + , + : par(i, 2, _ * 0.5) with {
    oscillator(note) = os.sawtooth(freq) with {
        freq = ba.midikey2hz(note);
    };
};

lfo(freq, depth) = os.osc(freq) * depth;

envelope(gate) = _ * gate;

filter(freq) = fi.lowpass(3, filterFreq) : fi.lowpass(5, 18000) with {
    filterFreq = freq : min(20000) : max(20);
};

tremolo(freq) =  _ * gain with {
    gain = os.osc(freq) - 1 : _ / 2 : _ * tremDepth : _ + 1;
};

masterGain = par(i, 2, _ * gain);

oscFreq=vibrato+wheel with{
    oscillator = os.osc(vibFreq)*vibDepth;
    midiVib=midiNote+oscillator;
    vibrato = ba.midikey2hz(midiVib);
    wheel = ba.midikey2hz(midiNote+pitchWheel);
};

note = midiNote + vibrato + pitchWheel with {
    vibrato = lfo(vibFreq, vibDepth);
};

process = hgroup("Synth", voice(note, detune) : par(i, 2, envelope(gate) : filter(cutoff + lfo(lfoFreq, lfoDepth)) : tremolo(tremFreq) ) : masterGain);
