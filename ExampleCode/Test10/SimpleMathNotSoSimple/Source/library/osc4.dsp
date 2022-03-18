import("stdfaust.lib");
declare oscType "os.oscs(freq)";
freq = hslider("freq",1000,100,10000,1);
process = os.oscs(freq);
