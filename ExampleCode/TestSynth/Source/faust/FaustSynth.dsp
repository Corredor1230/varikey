import("stdfaust.lib");

freq1=hslider("Frequency[scale:log]",200,20,20000,1):si.smoo;
freq2=hslider("Frequency2[scale:log]",300,20,20000,1):si.smoo;
filtCutoff=vslider("Cutoff [scale:log]",1000,20,20000,1):si.smoo;
lowPass=fi.lowpass(3,filtCutoff);
gain=hslider("Gain",0.1,0,1,0.01):si.smoo;
oscillator(x,y)=(os.sawtooth(x)*gain):lowPass;
process = oscillator(freq1),oscillator(freq2);