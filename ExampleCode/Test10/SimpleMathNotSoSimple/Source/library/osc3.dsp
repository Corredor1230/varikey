import("stdfaust.lib");
declare oscType "os.oscrs(freq)";
freq = hslider("freq",1000,100,10000,1);
process = os.oscrs(freq);
