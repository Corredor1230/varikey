import("stdfaust.lib");

gain(i) = hslider("Gain %i",-20,-60,0,1) : si.smoo : ba.db2linear;
O = 3;
M = 1;
ftop = 16000 / sqrt(2);
N = 9;

process = _ : fi.mth_octave_filterbank(O,M,ftop,N) : par(i, N, _ * gain(i)) :> _ ;
