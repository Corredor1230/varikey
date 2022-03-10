import("stdfaust.lib");

freq = hslider("freq", 1000, 10, 10000, 1);

process = fi.lowpass(2, freq);