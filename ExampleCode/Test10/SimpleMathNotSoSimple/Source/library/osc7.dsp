import("stdfaust.lib");
declare oscType "std::cos";
t = ba.time / ma.SR;
freq = hslider("freq",1000,100,10000,1);
process = cos(2 * ma.PI * freq * t);
