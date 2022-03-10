import("stdfaust.lib");

declare options "[nvoices:8]";
declare options "[midi:on]";

//Synth Control

//Note parameters
freq = hgroup("Pitch", nentry("freq[style:knob]",500,200,1000,0.01) : max(20));
vFreq = hgroup("Pitch",vslider("vFreq",0,0,20,0.02):si.smoo);
vDepth = hgroup("Pitch", vslider("vDepth[style:knob]",0,0,1,0.001));
pWheel = hgroup("Pitch", hslider("pWheel",0,-1,1,0.001):si.smoo);
detune = hgroup("Pitch", hslider("detune[midi: ctrl 1]",0,0,1,0.001));

//Envelope/Gain parameters
gain = hgroup("Envelope", vslider("[5]gain",-60,-60,0,1) : si.smoo: ba.db2linear);
gate = button("gate");
att = hgroup("Envelope", vslider("[1]att", 50, 10, 3000, 1));
dec = hgroup("Envelope", vslider ("[2]dec", 50, 10, 3000, 1));
sus = hgroup("Envelope", vslider ("[3]sus", 0.3, 0, 1, 0.001));
rel = hgroup("Envelope", vslider ("[4]rel", 200, 30, 5000, 1));

//Processing parameters
//Tremolo
tFreq = vslider("tFreq",0,0,20,0.02):si.smoo;
tDepth = vslider("tDepth[style:knob]",0,0,1,0.001);

//Filter
cutoff = hgroup("Filter", vslider("cutoff[style:knob][scale:log]",1000,110,20000,0.01) : si.smoo : max(20));
lfoF = hgroup("Filter", vslider("lfoF",0,0,20,0.001));
lfoD = hgroup("Filter", vslider("lfoD[style:knob]",0,0,1,0.01));

midiNote = ba.hz2midikey(freq):int;

//Midi note controls 
// tuningSliders = hgroup("Note tuning", par(i, 12, vslider("tune", 0, -1, 1, 0.001)));
tuningSliders = vgroup("Tuning", hgroup("[1]Note Tuning", c, ces, d, des, e, f, fes, g, ges, a, as, b)) with{
c = vslider("[1]c", 0, -1, 1, 0.001):si.smoo;
ces = vslider("[2]ces", 0, -1, 1, 0.001):si.smoo;
d = vslider("[3]d", 0, -1, 1, 0.001):si.smoo;
des = vslider("[4]des", 0, -1, 1, 0.001):si.smoo;
e = vslider("[5]e", 0, -1, 1, 0.001):si.smoo;
f = vslider("[6]f", 0, -1, 1, 0.001):si.smoo;
fes = vslider("[7]fes", 0, -1, 1, 0.001):si.smoo;
g = vslider("[8]g", 0, -1, 1, 0.001):si.smoo;
ges = vslider("[9]ges", 0, -1, 1, 0.001):si.smoo;
a = vslider("[]a", 0, -1, 1, 0.001):si.smoo;
as = vslider("[]as", 0, -1, 1, 0.001):si.smoo;
b = vslider("[]b", 0, -1, 1, 0.001):si.smoo;
};

offset = vgroup("Tuning", hslider("offset[2]",0,0,11,1));

// tuningSliders = hgroup("Note tuning", par(i, 12, vslider("tune", 0, -1, 1, 0.001)));

//Identifies the MIDI input note and modifies it accordingly
notePitch = noteDifference with{
    noteDifference = tuningSliders : par(i, 12, _ * (ma.modulo(midiNote-offset, 12) == i)) :> _;
};

//Takes MIDI note and detune value (in cents) and outputs stereo voice.
voice(note, detune) = oscillator(note - detune), oscillator(note), oscillator(note + detune) : _ , (_ <: _, _ ), _ : + , + : par(i, 2, _ * 0.5) with {
    oscillator(note) = os.sawtooth(thisFreq) with {
        thisFreq = ba.midikey2hz(note);
    };
};

//Creates an LFO to control other parameters.
lfo(freq,depth) = os.osc(freq) * depth;

//Creates an Envelope to control a signal's gain.
envelope(att, dec, sus, rel, gate) = _ * en.adsr(attack, decay, sustain, release, gate) : _ * gate : _ / 5.5 with{
    attack = att : _ / 1000 : max (0);
    decay = dec : _ / 1000 : max (0);
    sustain = sus : max (0) : min (1);
    release = rel : _ / 1000 : max (0);
};

//Creates a Tremolo limited between 0 and 1 to control an instrument's amplitude.
tremolo(freq) = _*tremGain with{
    tremGain = os.osc(freq) - 1 : _ / 2 : _ * tDepth : _ + 1 : max (0) : min (1);
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

//Alters original midi input and adds different pitch control parameters
note = midiNote + vibrato + pWheel + notePitch with{
    vibrato = lfo(vFreq, vDepth);
};


masterGain(gain) = _ , _: par(i,2, _*gain);

process = 
            voice(note, detune) : 
        hgroup("Processing", 
            par(i,2, envelope(att, dec, sus, rel, gate)) : 
            par(i, 2, lfoFilter(cutoff, lfo(lfoF, lfoD))  : 
            tremolo(tFreq))) : 
        hgroup("Processing", 
            masterGain(gain));


