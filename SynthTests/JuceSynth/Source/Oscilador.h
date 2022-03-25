/* ------------------------------------------------------------
name: "osc"
Code generated with Faust 2.37.3 (https://faust.grame.fr)
Compilation options: -lang cpp -es 1 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __Oscilador_H__
#define  __Oscilador_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

class OsciladorSIG0 {
	
  private:
	
	int iVec0[2];
	int iRec0[2];
	
  public:
	
	int getNumInputsOsciladorSIG0() {
		return 0;
	}
	int getNumOutputsOsciladorSIG0() {
		return 1;
	}
	
	void instanceInitOsciladorSIG0(int sample_rate) {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			iRec0[l1] = 0;
		}
	}
	
	void fillOsciladorSIG0(int count, float* table) {
		for (int i1 = 0; (i1 < count); i1 = (i1 + 1)) {
			iVec0[0] = 1;
			iRec0[0] = ((iVec0[1] + iRec0[1]) % 65536);
			table[i1] = std::sin((9.58738019e-05f * float(iRec0[0])));
			iVec0[1] = iVec0[0];
			iRec0[1] = iRec0[0];
		}
	}

};

static OsciladorSIG0* newOsciladorSIG0() { return (OsciladorSIG0*)new OsciladorSIG0(); }
static void deleteOsciladorSIG0(OsciladorSIG0* dsp) { delete dsp; }

static float ftbl0OsciladorSIG0[65536];

#ifndef FAUSTCLASS 
#define FAUSTCLASS Oscilador
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class Oscilador : public dsp {
	
 private:
	
	int fSampleRate;
	float fConst0;
	float fRec1[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.1");
		m->declare("compile_options", "-lang cpp -es 1 -single -ftz 0");
		m->declare("filename", "osc.dsp");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.3");
		m->declare("name", "osc");
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
		OsciladorSIG0* sig0 = newOsciladorSIG0();
		sig0->instanceInitOsciladorSIG0(sample_rate);
		sig0->fillOsciladorSIG0(65536, ftbl0OsciladorSIG0);
		deleteOsciladorSIG0(sig0);
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = (220.0f / std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate))));
	}
	
	virtual void instanceResetUserInterface() {
	}
	
	virtual void instanceClear() {
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec1[l2] = 0.0f;
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
	
	virtual Oscilador* clone() {
		return new Oscilador();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("osc");
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
			fRec1[0] = (fConst0 + (fRec1[1] - std::floor((fConst0 + fRec1[1]))));
			float fTemp0 = (0.5f * ftbl0OsciladorSIG0[int((65536.0f * fRec1[0]))]);
			output0[i0] = FAUSTFLOAT(fTemp0);
			output1[i0] = FAUSTFLOAT(fTemp0);
			fRec1[1] = fRec1[0];
		}
	}

};

#endif
