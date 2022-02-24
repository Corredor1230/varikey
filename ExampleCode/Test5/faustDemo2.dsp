import("stdfaust.lib");

lowFreq = hslider("lowFreq",20,20,100,0.01);
hiFreq = hslider("hiFreq",20000,10000,20000,0.01);

parametric(i) = fi.peak_eq(gdB(i), freq(i), q(i)) with {
    gdB(i) = hslider("gain %i[scale:log]",0,-12,12,0.1);
    freq(i) = hslider("freq %i",1000,20,20000,0.1);
    q(i) = hslider("q %i",1,0.01,100,0.01);
};

process = fi.lowpass(2, lowFreq) : seq(i, 10, parametric(i)) : fi.highpass(2, hiFreq) : _ * 0.001;
