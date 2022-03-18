import("stdfaust.lib");
declare oscType "os.oscw(freq)";
freq = hslider("freq",1000,100,10000,1);
process = os.oscw(freq);
