import("stdfaust.lib");

freq = vslider("freq", 220, 40, 1000, 1);
gate = button("gate");
gain = vslider("gain", 1, 0, 1, 0.001);

process = os.sawtooth(freq)*0.2<:_,_;