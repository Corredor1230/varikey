/* ------------------------------------------------------------
name: "Compressor"
Code generated with Faust 2.30.13 (https://faust.grame.fr)
Compilation options: -lang cpp -es 1 -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __Compressor_H__
#define  __Compressor_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

namespace faust {


#ifndef FAUSTCLASS 
#define FAUSTCLASS Compressor
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class Compressor : public dsp {
	
 private:
	
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	int fSampleRate;
	float fConst0;
	FAUSTFLOAT fHslider2;
	float fRec1[2];
	float fRec0[2];
	FAUSTFLOAT fHslider3;
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "0.1");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.1");
		m->declare("compile_options", "-lang cpp -es 1 -scal -ftz 0");
		m->declare("filename", "Compressor.dsp");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.3");
		m->declare("name", "Compressor");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "0.1");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
	}

	virtual int getNumInputs() {
		return 1;
	}
	virtual int getNumOutputs() {
		return 1;
	}
	virtual int getInputRate(int channel) {
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
		fConst0 = (1.0f / std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate))));
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(2.0f);
		fHslider1 = FAUSTFLOAT(10.0f);
		fHslider2 = FAUSTFLOAT(100.0f);
		fHslider3 = FAUSTFLOAT(-20.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec1[l0] = 0.0f;
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec0[l1] = 0.0f;
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
	
	virtual Compressor* clone() {
		return new Compressor();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openHorizontalBox("Compressor");
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->addHorizontalSlider("Attackp", &fHslider1, 10.0f, 1.0f, 100.0f, 1.0f);
		ui_interface->declare(&fHslider0, "style", "knob");
		ui_interface->addHorizontalSlider("Ratio", &fHslider0, 2.0f, 1.0f, 10.0f, 0.100000001f);
		ui_interface->declare(&fHslider2, "style", "knob");
		ui_interface->addHorizontalSlider("Release", &fHslider2, 100.0f, 10.0f, 1000.0f, 1.0f);
		ui_interface->declare(&fHslider3, "style", "knob");
		ui_interface->addHorizontalSlider("Threshold", &fHslider3, -20.0f, -40.0f, 0.0f, 0.100000001f);
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = (0.0500000007f * ((1.0f / float(fHslider0)) + -1.0f));
		float fSlow1 = (0.00100000005f * float(fHslider1));
		int iSlow2 = (std::fabs(fSlow1) < 1.1920929e-07f);
		float fSlow3 = (iSlow2 ? 0.0f : std::exp((0.0f - (fConst0 / (iSlow2 ? 1.0f : fSlow1)))));
		float fSlow4 = (0.00100000005f * float(fHslider2));
		int iSlow5 = (std::fabs(fSlow4) < 1.1920929e-07f);
		float fSlow6 = (iSlow5 ? 0.0f : std::exp((0.0f - (fConst0 / (iSlow5 ? 1.0f : fSlow4)))));
		float fSlow7 = float(fHslider3);
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = float(input0[i]);
			float fTemp1 = std::fabs(fTemp0);
			float fTemp2 = ((fRec0[1] > fTemp1) ? fSlow6 : fSlow3);
			fRec1[0] = ((fRec1[1] * fTemp2) + (fTemp1 * (1.0f - fTemp2)));
			fRec0[0] = fRec1[0];
			output0[i] = FAUSTFLOAT((fTemp0 * std::pow(10.0f, (fSlow0 * std::max<float>(0.0f, ((20.0f * std::log10(fRec0[0])) - fSlow7))))));
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
		}
	}

};

} // namespace faust

#endif
