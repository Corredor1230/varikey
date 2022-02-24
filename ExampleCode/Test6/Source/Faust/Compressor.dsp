import("stdfaust.lib");

// faust Compressor.dsp -cn Compressor -ns faust -o ../CompressorSimple.h

att = hslider("Attackp[style:knob]",10,1,100,1) / 1000;
rel = hslider("Release[style:knob]",100,10,1000,1) / 1000;
threshold = hslider("Threshold[style:knob]",-20,-40,0,0.1);
ratio = hslider("Ratio[style:knob]",2,1,10,0.1);

compressor = _ <: _, sideChain : * : _ ;
sideChain = levelEstimator : gainComputer with {
    levelEstimator = an.amp_follower_ar(att, rel);
    gainComputer = ba.linear2db : _ - threshold : max(0) : _ * (1/ratio - 1) : ba.db2linear;
};

process = hgroup("Compressor", compressor);
