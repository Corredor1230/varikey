import("stdfaust.lib");

//Variables
volume = vslider("Volume",1,0,1,0.001):si.smoo;

//Filter
ctFreq = hslider("cutoffFrequency[scale:log][style:knob]",500,50,20000,0.01):si.smoo;
q = hslider("q[style:knob]",1,1,15,0.1):si.smoo;
qRange=((q-1)/4.67)+1;
gainFilt = hslider("gainFilt[style:knob]",1,0,1,0.01):si.smoo;
qGainAdjust=1/qRange;

//Pan
panSquare = vslider("Pan [style:knob]",0.5,0,1,0.0001):si.smoo;

//Midi Input
freq = hslider("freq", 200, 40, 2000, 0.01):si.polySmooth(gate,0.999,2);
gain   = hslider("gain",1,0,1,0.01) : si.polySmooth(gate,0.999,2);
gate   = button("gate") : si.smoo;
freqMid = ba.hz2midikey(freq);
finalFreq = ba.midikey2hz(freqMid+bend);

//Detunes
bend=hslider("PitchBend",0,-1,1,0.001):si.smoo;
detuneMid=hslider("Detune[midi:ctrl 1]",0,0,1,0.001):si.smoo;
detuneHz=ba.midikey2hz(freqMid+bend+detuneMid);
detuneHzNeg=ba.midikey2hz(freqMid+bend-detuneMid);

//Vibrato
vibFreq=hslider("VibratoFreq",0,0,20,0.001):si.smoo;
vibDepth=hslider("VibratoDepth",0,0,1,0.001):si.smoo;
vibratoOsc=(os.osc(vibFreq)*vibDepth)+(freqMid+bend);
vibratoHz=ba.midikey2hz(vibratoOsc)-finalFreq;



synthBasic(x)=(os.sawtooth(x)*gain*gate)/8;
synthOsc=(synthBasic((finalFreq+vibratoHz))+synthBasic((detuneHz+vibratoHz))+synthBasic((detuneHzNeg+vibratoHz)))*qGainAdjust;
synthFilt=synthOsc:fi.resonlp(ctFreq,q,gainFilt);


process = synthFilt*volume<:_*((1-panSquare):sqrt),_*(panSquare:sqrt);