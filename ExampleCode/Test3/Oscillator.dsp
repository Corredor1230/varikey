import("stdfaust.lib");
// faust -a arch.cpp -i -cn Oscillator Oscillator.dsp -o Test3/Source/Oscillator.h
freq = hslider("freq",1000,20,20000,1);
gain = hslider("gain",-12,-60,0,1) : ba.db2linear;

process = os.osc(freq) * gain <: _, _;
