import("stdfaust.lib");
declare oscType "os.quadosc(freq)";
freq = hslider("freq",1000,100,10000,1);
process = os.quadosc(freq);
