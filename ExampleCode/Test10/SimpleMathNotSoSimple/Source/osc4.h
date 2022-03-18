/* ------------------------------------------------------------
name: "osc4"
Code generated with Faust 2.30.13 (https://faust.grame.fr)
Compilation options: -lang cpp -es 1 -double -ftz 0
------------------------------------------------------------ */

#ifndef  __osc4_H__
#define  __osc4_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

namespace faust {


#ifndef FAUSTCLASS 
#define FAUSTCLASS osc4
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class osc4 : public dsp {
	
 private:
	
	int fSampleRate;
	double fConst0;
	FAUSTFLOAT fHslider0;
	int iVec0[2];
	double fRec2[2];
	double fRec1[2];
	double fRec0[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-lang cpp -es 1 -double -ftz 0");
		m->declare("filename", "osc4.dsp");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.3");
		m->declare("name", "osc4");
		m->declare("oscType", "os.oscs(freq)");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.1");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "0.1");
	}

	virtual int getNumInputs() {
		return 0;
	}
	virtual int getNumOutputs() {
		return 1;
	}
	virtual int getInputRate(int channel) {
		int rate;
		switch ((channel)) {
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	virtual int getOutputRate(int channel) {
		int rate;
		switch ((channel)) {
			case 0: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = (6.2831853071795862 / std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate))));
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(1000.0);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec2[l1] = 0.0;
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec1[l2] = 0.0;
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec0[l3] = 0.0;
		}
	}
	
	virtual void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	virtual void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual osc4* clone() {
		return new osc4();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("osc4");
		ui_interface->addHorizontalSlider("freq", &fHslider0, 1000.0, 100.0, 10000.0, 1.0);
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		double fSlow0 = (fConst0 * double(fHslider0));
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			fRec2[0] = (fRec2[1] + (fSlow0 * (0.0 - fRec0[1])));
			fRec1[0] = ((fSlow0 * fRec2[0]) + (double((1 - iVec0[1])) + fRec1[1]));
			fRec0[0] = fRec1[0];
			output0[i] = FAUSTFLOAT(fRec0[0]);
			iVec0[1] = iVec0[0];
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
		}
	}

};

} // namespace faust

#endif
