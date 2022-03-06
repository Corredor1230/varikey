import("stdfaust.lib");

//Parameter declarations
freq = vslider("freq[style:knob]",500,200,1000,0.01) : max(20);
gain = vslider("gain",-20,-60,0,1) : si.smoo: ba.db2linear;
gate = button("gate");
cutoff = vslider("cutoff[style:knob][scale:log]",1000,110,20000,0.01) : si.smoo : max(20);
vibFreq = vslider("vibFreq",0,0,20,0.02):si.smoo;
vibDepth = vslider("vibDepth[style:knob]",0,0,1,0.001);
tremFreq = vslider("tremFreq",0,0,20,0.02):si.smoo;
tremDepth = vslider("tremDepth[style:knob]",0,0,1,0.001);
pitchWheel = hslider("pitchWheel",0,-1,1,0.001):si.smoo;
detune = hslider("detune[midi: ctrl 1]",0,0,1,0.001);
lfoFreq = vslider("lfoFreq",0,0,20,0.001):si.smoo;
lfoDepth = vslider("lfoDepth[style:knob]",0,0,1,0.01):si.smoo;
attack = vslider("attack", 50, 10, 3000, 1);
decay = vslider ("decay", 50, 10, 3000, 1);
sustain = vslider ("sustain", 0.3, 0, 1, 0.001);
release = vslider ("release", 200, 30, 5000, 1);
midiNote = ba.hz2midikey(freq);

//Takes MIDI note and detune value (in cents) and outputs stereo voice.
voice(note, detune) = oscillator(note - detune), oscillator(note), oscillator(note + detune) : _ , (_ <: _, _ ), _ : + , + : par(i, 2, _ * 0.5) with {
    oscillator(note) = os.sawtooth(thisFreq) with {
        thisFreq = ba.midikey2hz(note);
    };
};

//Creates an LFO to control other parameters.
lfo(freq,depth) = os.osc(freq) * depth;

//Creates an Envelope to control a signal's gain.
envelope(att, dec, sus, rel, gate) = _ * en.adsr(attackTime, decayTime, sustain, release, gate) : _ * gate : _ / 5.5 with{
    attackTime = att : _ / 1000 : max (0);
    decayTime = dec : _ / 1000 : max (0);
    sustain = sus : max (0) : min (1);
    release = rel : _ / 1000 : max (0);
};

//Creates a Tremolo limited between 0 and 1 to control an instrument's amplitude.
tremolo(freq) = _*tremGain with{
    tremGain = os.osc(freq) - 1 : _ / 2 : _ * tremDepth : _ + 1 : max (0) : min (1);
};


//Basic filter signal
filter(freq) = fi.lowpass(3, filterFreq) : fi.lowpass(5, 18000) with {
    filterFreq = freq : min(20000) : max (20);
};

//Variable band limited filter signal for LFO control 
lfoFilter(cutoff, lfo) = filter(cutoff+lfoVariation) with{
    distanceToMax = 18000 - cutoff;
    distanceToMin = cutoff - 50;
    lfoVariation = lfo : _ * (distanceToMax, distanceToMin : min);
};

note = midiNote + vibrato + pitchWheel with{
    vibrato = lfo(vibFreq, vibDepth);
};


masterGain(gain) = _ , _: par(i,2, _*gain);

process = hgroup("Synth", vgroup("Note", 
            voice(note, detune)) : 
hgroup("Envelope", par(i,2, 
            envelope(attack, decay, sustain, release, gate)))) : 
hgroup("Filter", par(i, 2, 
            lfoFilter(cutoff, lfo(lfoFreq, lfoDepth))  : 
            tremolo(tremFreq)) : 
            masterGain(gain));
