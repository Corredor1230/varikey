/* ------------------------------------------------------------
name: "osc5"
Code generated with Faust 2.30.13 (https://faust.grame.fr)
Compilation options: -lang cpp -es 1 -double -ftz 0
------------------------------------------------------------ */

#ifndef  __osc5_H__
#define  __osc5_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

namespace faust {

static double osc5_faustpower2_f(double value) {
	return (value * value);
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS osc5
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class osc5 : public dsp {
	
 private:
	
	int iVec0[2];
	int fSampleRate;
	double fConst0;
	FAUSTFLOAT fHslider0;
	double fRec0[2];
	double fRec1[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-lang cpp -es 1 -double -ftz 0");
		m->declare("filename", "osc5.dsp");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.3");
		m->declare("name", "osc5");
		m->declare("oscType", "os.quadosc(freq)");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.1");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "0.1");
	}

	virtual int getNumInputs() {
		return 0;
	}
	virtual int getNumOutputs() {
		return 2;
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
			case 1: {
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
		fConst0 = (3.1415926535897931 / std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate))));
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(1000.0);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec0[l1] = 0.0;
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec1[l2] = 0.0;
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
	
	virtual osc5* clone() {
		return new osc5();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("osc5");
		ui_interface->addHorizontalSlider("freq", &fHslider0, 1000.0, 100.0, 10000.0, 1.0);
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		double fSlow0 = std::tan((fConst0 * double(fHslider0)));
		double fSlow1 = (2.0 * (fSlow0 / (osc5_faustpower2_f(fSlow0) + 1.0)));
		for (int i = 0; (i < count); i = (i + 1)) {
			iVec0[0] = 1;
			double fTemp0 = (fRec1[1] + (fSlow1 * (fRec0[1] - (fSlow0 * fRec1[1]))));
			fRec0[0] = (iVec0[1] ? (fRec0[1] - (fSlow0 * (fRec1[1] + fTemp0))) : 1.0);
			fRec1[0] = fTemp0;
			output0[i] = FAUSTFLOAT(fRec0[0]);
			output1[i] = FAUSTFLOAT(fRec1[0]);
			iVec0[1] = iVec0[0];
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
		}
	}

};

} // namespace faust

#endif
