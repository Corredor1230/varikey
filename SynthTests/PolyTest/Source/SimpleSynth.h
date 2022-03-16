/* ------------------------------------------------------------
name: "SimpleSynth"
Code generated with Faust 2.37.3 (https://faust.grame.fr)
Compilation options: -lang cpp -es 1 -single -ftz 0
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
	
	int iVec0[2];
	int iRec0[2];
	
  public:
	
	int getNumInputsSimpleSynthSIG0() {
		return 0;
	}
	int getNumOutputsSimpleSynthSIG0() {
		return 1;
	}
	
	void instanceInitSimpleSynthSIG0(int sample_rate) {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			iRec0[l1] = 0;
		}
	}
	
	void fillSimpleSynthSIG0(int count, float* table) {
		for (int i1 = 0; (i1 < count); i1 = (i1 + 1)) {
			iVec0[0] = 1;
			iRec0[0] = ((iVec0[1] + iRec0[1]) % 65536);
			table[i1] = std::sin((9.58738019e-05f * float(iRec0[0])));
			iVec0[1] = iVec0[0];
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
	int fSampleRate;
	float fConst1;
	FAUSTFLOAT fHslider1;
	float fRec1[2];
	float fConst2;
	FAUSTFLOAT fVslider0;
	FAUSTFLOAT fCheckbox0;
	float fVec1[2];
	float fRec2[2];
	FAUSTFLOAT fVslider1;
	FAUSTFLOAT fVslider2;
	FAUSTFLOAT fVslider3;
	int iRec3[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.1");
		m->declare("compile_options", "-lang cpp -es 1 -single -ftz 0");
		m->declare("envelopes.lib/adsr:author", "Yann Orlarey and Andrey Bundin");
		m->declare("envelopes.lib/author", "GRAME");
		m->declare("envelopes.lib/copyright", "GRAME");
		m->declare("envelopes.lib/license", "LGPL with exception");
		m->declare("envelopes.lib/name", "Faust Envelope Library");
		m->declare("envelopes.lib/version", "0.1");
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
		return 2;
	}
	
	static void classInit(int sample_rate) {
		SimpleSynthSIG0* sig0 = newSimpleSynthSIG0();
		sig0->instanceInitSimpleSynthSIG0(sample_rate);
		sig0->fillSimpleSynthSIG0(65536, ftbl0SimpleSynthSIG0);
		deleteSimpleSynthSIG0(sig0);
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		float fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = (1.0f / fConst0);
		fConst2 = (0.00100000005f * fConst0);
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.5f);
		fHslider1 = FAUSTFLOAT(440.0f);
		fVslider0 = FAUSTFLOAT(15.0f);
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fVslider1 = FAUSTFLOAT(0.5f);
		fVslider2 = FAUSTFLOAT(15.0f);
		fVslider3 = FAUSTFLOAT(60.0f);
	}
	
	virtual void instanceClear() {
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec1[l2] = 0.0f;
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fVec1[l3] = 0.0f;
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec2[l4] = 0.0f;
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			iRec3[l5] = 0;
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
		ui_interface->addVerticalSlider("att", &fVslider0, FAUSTFLOAT(15.0f), FAUSTFLOAT(10.0f), FAUSTFLOAT(1500.0f), FAUSTFLOAT(1.0f));
		ui_interface->addVerticalSlider("dec", &fVslider2, FAUSTFLOAT(15.0f), FAUSTFLOAT(10.0f), FAUSTFLOAT(1500.0f), FAUSTFLOAT(1.0f));
		ui_interface->addHorizontalSlider("freq", &fHslider1, FAUSTFLOAT(440.0f), FAUSTFLOAT(60.0f), FAUSTFLOAT(1000.0f), FAUSTFLOAT(1.0f));
		ui_interface->addHorizontalSlider("gain", &fHslider0, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00999999978f));
		ui_interface->addCheckButton("gate", &fCheckbox0);
		ui_interface->addVerticalSlider("rel", &fVslider3, FAUSTFLOAT(60.0f), FAUSTFLOAT(10.0f), FAUSTFLOAT(5000.0f), FAUSTFLOAT(1.0f));
		ui_interface->addVerticalSlider("sus", &fVslider1, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00100000005f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = (0.181818187f * float(fHslider0));
		float fSlow1 = (fConst1 * float(fHslider1));
		float fSlow2 = std::max<float>(1.0f, (fConst2 * float(fVslider0)));
		float fSlow3 = (1.0f / fSlow2);
		float fSlow4 = float(fCheckbox0);
		float fSlow5 = float(fVslider1);
		float fSlow6 = ((1.0f - fSlow5) / std::max<float>(1.0f, (fConst2 * float(fVslider2))));
		float fSlow7 = (1.0f / std::max<float>(1.0f, (fConst2 * float(fVslider3))));
		int iSlow8 = (fSlow4 == 0.0f);
		for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
			fRec1[0] = (fSlow1 + (fRec1[1] - std::floor((fSlow1 + fRec1[1]))));
			fVec1[0] = fSlow4;
			fRec2[0] = (fSlow4 + (fRec2[1] * float((fVec1[1] >= fSlow4))));
			iRec3[0] = (iSlow8 * (iRec3[1] + 1));
			float fTemp0 = (fSlow0 * (ftbl0SimpleSynthSIG0[int((65536.0f * fRec1[0]))] * std::max<float>(0.0f, (std::min<float>((fSlow3 * fRec2[0]), std::max<float>((1.0f - (fSlow6 * (fRec2[0] - fSlow2))), fSlow5)) * (1.0f - (fSlow7 * float(iRec3[0])))))));
			output0[i0] = FAUSTFLOAT(fTemp0);
			output1[i0] = FAUSTFLOAT(fTemp0);
			fRec1[1] = fRec1[0];
			fVec1[1] = fVec1[0];
			fRec2[1] = fRec2[0];
			iRec3[1] = iRec3[0];
		}
	}

};

} //namespace faust

#endif
