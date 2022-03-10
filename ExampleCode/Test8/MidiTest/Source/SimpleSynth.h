/* ------------------------------------------------------------
name: "SimpleSynth"
Code generated with Faust 2.30.13 (https://faust.grame.fr)
Compilation options: -lang cpp -es 1 -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __SimpleSynth_H__
#define  __SimpleSynth_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

namespace faust {

class SimpleSynthSIG0 {
	
  private:
	
	int iRec0[2];
	
  public:
	
	int getNumInputsSimpleSynthSIG0() {
		return 0;
	}
	int getNumOutputsSimpleSynthSIG0() {
		return 1;
	}
	int getInputRateSimpleSynthSIG0(int channel) {
		int rate;
		switch ((channel)) {
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	int getOutputRateSimpleSynthSIG0(int channel) {
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
	
	void instanceInitSimpleSynthSIG0(int sample_rate) {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iRec0[l0] = 0;
		}
	}
	
	void fillSimpleSynthSIG0(int count, float* table) {
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec0[0] = (iRec0[1] + 1);
			table[i] = std::sin((9.58738019e-05f * float((iRec0[0] + -1))));
			iRec0[1] = iRec0[0];
		}
	}

};

static SimpleSynthSIG0* newSimpleSynthSIG0() { return (SimpleSynthSIG0*)new SimpleSynthSIG0(); }
static void deleteSimpleSynthSIG0(SimpleSynthSIG0* dsp) { delete dsp; }

static float ftbl0SimpleSynthSIG0[65536];

#ifndef FAUSTCLASS 
#define FAUSTCLASS SimpleSynth
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class SimpleSynth : public dsp {
	
 private:
	
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fCheckbox0;
	int fSampleRate;
	float fConst0;
	FAUSTFLOAT fHslider1;
	float fRec1[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.1");
		m->declare("compile_options", "-lang cpp -es 1 -scal -ftz 0");
		m->declare("filename", "SimpleSynth.dsp");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.3");
		m->declare("name", "SimpleSynth");
		m->declare("options", "[midi:on]");
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
		SimpleSynthSIG0* sig0 = newSimpleSynthSIG0();
		sig0->instanceInitSimpleSynthSIG0(sample_rate);
		sig0->fillSimpleSynthSIG0(65536, ftbl0SimpleSynthSIG0);
		deleteSimpleSynthSIG0(sig0);
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = (1.0f / std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate))));
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.5f);
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fHslider1 = FAUSTFLOAT(440.0f);
	}
	
	virtual void instanceClear() {
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec1[l1] = 0.0f;
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
	
	virtual SimpleSynth* clone() {
		return new SimpleSynth();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("SimpleSynth");
		ui_interface->addHorizontalSlider("freq", &fHslider1, 440.0f, 60.0f, 1000.0f, 1.0f);
		ui_interface->addHorizontalSlider("gain", &fHslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addCheckButton("gate", &fCheckbox0);
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = (float(fHslider0) * float(fCheckbox0));
		float fSlow1 = (fConst0 * float(fHslider1));
		for (int i = 0; (i < count); i = (i + 1)) {
			fRec1[0] = (fSlow1 + (fRec1[1] - std::floor((fSlow1 + fRec1[1]))));
			output0[i] = FAUSTFLOAT((fSlow0 * ftbl0SimpleSynthSIG0[int((65536.0f * fRec1[0]))]));
			fRec1[1] = fRec1[0];
		}
	}

};

} // namespace faust

#endif
