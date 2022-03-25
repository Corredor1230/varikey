import("stdfaust.lib");

freq = nentry("freq",500,200,1000,0.01) : max(20);
gain = vslider("gain",0.5,0,1,0.001) : si.smoo;
gate = button("gate");
vol = vslider("volume", -20, -60, 0, 1) : si.smoo : ba.db2linear;
att = 10;
//fmDepth = vslider("fmDepth", 100, 10, 3000, 1):si.smoo;
//fmIndex = vslider("fmIndex[style:knob]", 2, 1, 6, 1);
fmDepth = 1000;
fmIndex = 3;


kAtt = vslider("kAtt[scale:log]", 1, 1, 20000, 1);
kFeed = (vslider("kFeed", 0.5, 0, 1, 0.01) / 5) + 0.79;
kSwitch = hslider("kSwitch[style:knob]", 1, 1, 3, 1);

envelope(att, dec, sus, rel, gate) = _ * en.adsr(attack, decay, sustain, release, gate) with{
    attack = att : _ / 1000 : max (0);
    decay = dec : _ / 1000 : max (0);
    sustain = sus : max (0) : min (1);
    release = rel : _ / 1000 : max (0);
};

karplus(thisFreq) = karplusSource : + ~ de.delay(ma.SR, del) * kFeed with{
    fixedClose = envelope(0.1, kAtt, 0, 50, gate);

    noiseGen = (no.noise : fixedClose) * correction / 2 with {
        correction = ((att - 1)*(-2)):max(1);
    };
    fmGen = os.osc(fmFreq) : fixedClose * correction / 24 with {
        fmFreq = thisFreq+os.osc(thisFreq*fmIndex)*fmDepth:min(18000);
        correction = ((att - 1)*(-4)):max(1); 
    };
    pinkGen = (no.pink_noise : fixedClose) * 3.5 * correction with{
        correction = ((att - 1)*(-2)):max(1);
    };

    karplusSource = 
        noiseGen * (kSwitch == 1) + 
        fmGen * (kSwitch == 2) + 
        pinkGen * (kSwitch == 3);

    del = ma.SR / thisFreq; 
};

masterGain(gain) = _ , _: par(i,2, _*gain);

process = 
		karplus(freq) <:
		par(i,2, envelope(10, 40, 0.5, 200, gate) : _ / 5.5) :
		masterGain(vol);
	