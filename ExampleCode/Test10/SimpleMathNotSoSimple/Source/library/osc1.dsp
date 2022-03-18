import("stdfaust.lib");
declare oscType "os.osc(freq)";
freq = hslider("freq",1000,100,10000,1);
process = os.osc(freq);
// https://vicanek.de/articles/QuadOsc.pdf
