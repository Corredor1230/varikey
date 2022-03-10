import("stdfaust.lib");
declare options "[midi:on]";

freq = hslider("freq", 440, 60, 1000, 1);
gain = hslider("gain", 0.5, 0, 1, 0.01);
gate = checkbox("gate");


process = os.osc(freq) * gain * gate;