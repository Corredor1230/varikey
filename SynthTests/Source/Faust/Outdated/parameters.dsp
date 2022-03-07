//Synth Control

//Note parameters
freq = hgroup("Pitch", nentry("freq[style:knob]",500,200,1000,0.01) : max(20));
vibFreq = hgroup("Pitch",vslider("vibFreq",0,0,20,0.02):si.smoo);
vibDepth = hgroup("Pitch", vslider("vibDepth[style:knob]",0,0,1,0.001));
pitchWheel = hgroup("Pitch", hslider("pitchWheel",0,-1,1,0.001):si.smoo);
detune = hgroup("Pitch", hslider("detune[midi: ctrl 1]",0,0,1,0.001));

//Envelope parameters
gain = hgroup("Envelope", vslider("[5]gain",-20,-60,0,1) : si.smoo: ba.db2linear);
gate = button("gate");
cutoff = hgroup("Filter", vslider("cutoff[style:knob][scale:log]",1000,110,20000,0.01) : si.smoo : max(20));

tremFreq = vslider("tremFreq",0,0,20,0.02):si.smoo;
tremDepth = vslider("tremDepth[style:knob]",0,0,1,0.001);

lfoFreq = hgroup("Filter", vslider("lfoFreq",0,0,20,0.001));
lfoDepth = hgroup("Filter", vslider("lfoDepth[style:knob]",0,0,1,0.01));
attack = hgroup("Envelope", vslider("[1]attack", 50, 10, 3000, 1));
decay = hgroup("Envelope", vslider ("[2]decay", 50, 10, 3000, 1));
sustain = hgroup("Envelope", vslider ("[3]sustain", 0.3, 0, 1, 0.001));
release = hgroup("Envelope", vslider ("[4]release", 200, 30, 5000, 1));
midiNote = ba.hz2midikey(freq):int;

//Midi note controls 
// tuningSliders = hgroup("Note tuning", par(i, 12, vslider("tune", 0, -1, 1, 0.001)));

tuningSliders = hgroup("Note Tuning", cSlider, cesSlider, dSlider, desSlider, eSlider, fSlider, fesSlider, gSlider, gesSlider, aSlider, asSlider, bSlider) with{
cSlider = vslider("C", 0, -1, 1, 0.001):si.smoo;
cesSlider = vslider("C#/Db", 0, -1, 1, 0.001):si.smoo;
dSlider = vslider("D", 0, -1, 1, 0.001):si.smoo;
desSlider = vslider("D#/Eb", 0, -1, 1, 0.001):si.smoo;
eSlider = vslider("E", 0, -1, 1, 0.001):si.smoo;
fSlider = vslider("F", 0, -1, 1, 0.001):si.smoo;
fesSlider = vslider("F#/Gb", 0, -1, 1, 0.001):si.smoo;
gSlider = vslider("G", 0, -1, 1, 0.001):si.smoo;
gesSlider = vslider("G#/Ab", 0, -1, 1, 0.001):si.smoo;
aSlider = vslider("A", 0, -1, 1, 0.001):si.smoo;
asSlider = vslider("A#/Bb", 0, -1, 1, 0.001):si.smoo;
bSlider = vslider("B", 0, -1, 1, 0.001):si.smoo;
};

// tuningSliders = hgroup("Note tuning", par(i, 12, vslider("tune", 0, -1, 1, 0.001)));