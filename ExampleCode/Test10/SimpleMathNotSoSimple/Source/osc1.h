/* ------------------------------------------------------------
name: "osc1"
Code generated with Faust 2.30.13 (https://faust.grame.fr)
Compilation options: -lang cpp -es 1 -double -ftz 0
------------------------------------------------------------ */

#ifndef  __osc1_H__
#define  __osc1_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

namespace faust {

class osc1SIG0 {
	
  private:
	
	int iRec0[2];
	
  public:
	
	int getNumInputsosc1SIG0() {
		return 0;
	}
	int getNumOutputsosc1SIG0() {
		return 1;
	}
	int getInputRateosc1SIG0(int channel) {
		int rate;
		switch ((channel)) {
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	int getOutputRateosc1SIG0(int channel) {
		int rate;
		switch ((channel)) {
			case 0: {
				rate = 0;
				break;
			}
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	
	void instanceInitosc1SIG0(int sample_rate) {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iRec0[l0] = 0;
		}
	}
	
	void fillosc1SIG0(int count, double* table) {
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec0[0] = (iRec0[1] + 1);
			table[i] = std::sin((9.5873799242852573e-05 * double((iRec0[0] + -1))));
			iRec0[1] = iRec0[0];
		}
	}

};

static osc1SIG0* newosc1SIG0() { return (osc1SIG0*)new osc1SIG0(); }
static void deleteosc1SIG0(osc1SIG0* dsp) { delete dsp; }

static double ftbl0osc1SIG0[65536];

#ifndef FAUSTCLASS 
#define FAUSTCLASS osc1
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class osc1 : public dsp {
	
 private:
	
	int fSampleRate;
	double fConst0;
	FAUSTFLOAT fHslider0;
	double fRec1[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.1");
		m->declare("compile_options", "-lang cpp -es 1 -double -ftz 0");
		m->declare("filename", "osc1.dsp");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.3");
		m->declare("name", "osc1");
		m->declare("oscType", "os.osc(freq)");
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
		osc1SIG0* sig0 = newosc1SIG0();
		sig0->instanceInitosc1SIG0(sample_rate);
		sig0->fillosc1SIG0(65536, ftbl0osc1SIG0);
		deleteosc1SIG0(sig0);
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = (1.0 / std::min<double>(192000.0, std::max<double>(1.0, double(fSampleRate))));
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(1000.0);
	}
	
	virtual void instanceClear() {
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec1[l1] = 0.0;
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
	
	virtual osc1* clone() {
		return new osc1();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("osc1");
		ui_interface->addHorizontalSlider("freq", &fHslider0, 1000.0, 100.0, 10000.0, 1.0);
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		double fSlow0 = (fConst0 * double(fHslider0));
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec1[0] = (fSlow0 + (fRec1[1] - std::floor((fSlow0 + fRec1[1]))));
			output0[i] = FAUSTFLOAT(ftbl0osc1SIG0[int((65536.0 * fRec1[0]))]);
			fRec1[1] = fRec1[0];
		}
	}

};

} // namespace faust

#endif
