import("stdfaust.lib");
declare options "[midi:on]";
declare options "[nvoices:8]";

freq = hslider("freq", 440, 60, 1000, 1);
gain = hslider("gain", 0.5, 0, 1, 0.01);
gate = checkbox("gate");

att = vslider("att", 15, 10, 1500, 1) / 1000;
dec = vslider("dec", 15, 10, 1500, 1) / 1000;
sus = vslider("sus", 0.5, 0, 1, 0.001);
rel = vslider("rel", 60, 10, 5000, 1) / 1000;

envelope(attack, decay, sustain, release, gate) = _ * en.adsr(attack, decay, sustain, release, gate);

masterGain(gain) = _ , _: par(i,2, _*gain / 5.5);


process = os.osc(freq)
        <: par(i,2, envelope(att,dec,sus,rel,gate)):
        masterGain(gain);
