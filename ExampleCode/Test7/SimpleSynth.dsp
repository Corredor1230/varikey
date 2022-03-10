import("stdfaust.lib");

freq = hslider("freq", 1000, 10, 10000, 1);
gain = hslider("gain", 0.5, 0, 1, 0.01);
gate = checkbox("gate");


process = os.osc(freq) * gain * gate;