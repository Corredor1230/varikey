import("stdfaust.lib");
// gain = hslider("Gain",-20,-60,0,1) : ba.db2linear;
// gain = hslider("Gain",-20,-60,0,1) : ba.db2linear : si.smoo;
gain = hslider("Gain",-20,-60,0,1) : si.smoo : ba.db2linear;

// process = _, _:> _;
process = _ * gain;
