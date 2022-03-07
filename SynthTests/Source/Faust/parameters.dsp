//Synth Control

//Note parameters
freq = hgroup("Pitch", nentry("freq[style:knob]",500,200,1000,0.01) : max(20));
vibFreq = hgroup("Pitch",vslider("vibFreq",0,0,20,0.02):si.smoo);
vibDepth = hgroup("Pitch", vslider("vibDepth[style:knob]",0,0,1,0.001));
pitchWheel = hgroup("Pitch", hslider("pitchWheel",0,-1,1,0.001):si.smoo);
detune = hgroup("Pitch", hslider("detune[midi: ctrl 1]",0,0,1,0.001));

//Envelope/Gain parameters
gain = hgroup("Envelope", vslider("[5]gain",-60,-60,0,1) : si.smoo: ba.db2linear);
gate = button("gate");
attack = hgroup("Envelope", vslider("[1]attack", 50, 10, 3000, 1));
decay = hgroup("Envelope", vslider ("[2]decay", 50, 10, 3000, 1));
sustain = hgroup("Envelope", vslider ("[3]sustain", 0.3, 0, 1, 0.001));
release = hgroup("Envelope", vslider ("[4]release", 200, 30, 5000, 1));

//Processing parameters
//Tremolo
tremFreq = vslider("tremFreq",0,0,20,0.02):si.smoo;
tremDepth = vslider("tremDepth[style:knob]",0,0,1,0.001);

//Filter
cutoff = hgroup("Filter", vslider("cutoff[style:knob][scale:log]",1000,110,20000,0.01) : si.smoo : max(20));
lfoFreq = hgroup("Filter", vslider("lfoFreq",0,0,20,0.001));
lfoDepth = hgroup("Filter", vslider("lfoDepth[style:knob]",0,0,1,0.01));

midiNote = ba.hz2midikey(freq):int;

//Midi note controls 
// tuningSliders = hgroup("Note tuning", par(i, 12, vslider("tune", 0, -1, 1, 0.001)));
tuningSliders = vgroup("Tuning", hgroup("[1]Note Tuning", cSlider, cesSlider, dSlider, desSlider, eSlider, fSlider, fesSlider, gSlider, gesSlider, aSlider, asSlider, bSlider)) with{
cSlider = vslider("[1]C", 0, -1, 1, 0.001):si.smoo;
cesSlider = vslider("[2]C#/Db", 0, -1, 1, 0.001):si.smoo;
dSlider = vslider("[3]D", 0, -1, 1, 0.001):si.smoo;
desSlider = vslider("[4]D#/Eb", 0, -1, 1, 0.001):si.smoo;
eSlider = vslider("[5]E", 0, -1, 1, 0.001):si.smoo;
fSlider = vslider("[6]F", 0, -1, 1, 0.001):si.smoo;
fesSlider = vslider("[7]F#/Gb", 0, -1, 1, 0.001):si.smoo;
gSlider = vslider("[8]G", 0, -1, 1, 0.001):si.smoo;
gesSlider = vslider("[9]G#/Ab", 0, -1, 1, 0.001):si.smoo;
aSlider = vslider("[]A", 0, -1, 1, 0.001):si.smoo;
asSlider = vslider("[]A#/Bb", 0, -1, 1, 0.001):si.smoo;
bSlider = vslider("[]B", 0, -1, 1, 0.001):si.smoo;
};

offset = vgroup("Tuning", hslider("offset[2]",0,0,11,1));

// tuningSliders = hgroup("Note tuning", par(i, 12, vslider("tune", 0, -1, 1, 0.001)));