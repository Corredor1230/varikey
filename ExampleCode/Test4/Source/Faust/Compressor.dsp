import("stdfaust.lib");

att = hslider("Attack",10,1,100,1) / 1000;
rel = hslider("Release",100,10,1000,1) / 1000;
threshold = hslider("Threshold",-20,-40,0,0.1);
ratio = hslider("Ratio",2,1,10,0.1);

compressor = _ <: _, sideChain : * : _ ;
sideChain = levelEstimator : gainComputer with {
    levelEstimator = an.amp_follower_ar(att, rel);
    gainComputer = ba.linear2db : _ - threshold : max(0) : _ * (1/ratio - 1) : ba.db2linear;
};

process = compressor * 0.0001;
