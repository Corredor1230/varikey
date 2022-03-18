import("stdfaust.lib");
declare oscType "os.oscb(freq)";
freq = hslider("freq",1000,100,10000,1);
process = os.oscb(freq);
