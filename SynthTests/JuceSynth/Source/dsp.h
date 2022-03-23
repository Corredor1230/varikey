/* ------------------------------------------------------------
name: "dsp"
Code generated with Faust 2.32.16 (https://faust.grame.fr)
Compilation options: -lang cpp -es 1 -single -ftz 0
------------------------------------------------------------ */

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

static float mydsp_faustpower2_f(float value) {
	return (value * value);
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class mydsp : public dsp {
	
 private:
	
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fEntry0;
	float fConst3;
	float fRec2[2];
	FAUSTFLOAT fEntry1;
	FAUSTFLOAT fButton0;
	float fRec3[2];
	float fConst4;
	FAUSTFLOAT fEntry2;
	float fRec4[2];
	float fVec0[2];
	float fRec1[2];
	float fRec0[3];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-lang cpp -es 1 -single -ftz 0");
		m->declare("filename", "dsp.dsp");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass0_highpass1:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/tf1:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf1s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1s:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2s:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "0.3");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.3");
		m->declare("name", "dsp");
		m->declare("options", "[nvoices:12]");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "0.1");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "0.1");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
	}

	virtual int getNumInputs() {
		return 0;
	}
	virtual int getNumOutputs() {
		return 2;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = (3.14159274f / fConst0);
		fConst2 = (44.0999985f / fConst0);
		fConst3 = (1.0f - fConst2);
		fConst4 = (1.0f / fConst0);
	}
	
	virtual void instanceResetUserInterface() {
		fEntry0 = FAUSTFLOAT(10000.0f);
		fEntry1 = FAUSTFLOAT(0.5f);
		fButton0 = FAUSTFLOAT(0.0f);
		fEntry2 = FAUSTFLOAT(200.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec2[l0] = 0.0f;
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec3[l1] = 0.0f;
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec4[l2] = 0.0f;
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fVec0[l3] = 0.0f;
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec1[l4] = 0.0f;
		}
		for (int l5 = 0; (l5 < 3); l5 = (l5 + 1)) {
			fRec0[l5] = 0.0f;
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
	
	virtual mydsp* clone() {
		return new mydsp();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("dsp");
		ui_interface->addNumEntry("cutoff", &fEntry0, 10000.0f, 50.0f, 10000.0f, 0.00999999978f);
		ui_interface->addNumEntry("freq", &fEntry2, 200.0f, 50.0f, 1000.0f, 0.00999999978f);
		ui_interface->addNumEntry("gain", &fEntry1, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->addButton("gate", &fButton0);
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = (fConst2 * float(fEntry0));
		float fSlow1 = float(fEntry1);
		float fSlow2 = (fConst2 * float(fButton0));
		float fSlow3 = std::max<float>(1.1920929e-07f, std::fabs(float(fEntry2)));
		float fSlow4 = (fConst4 * fSlow3);
		float fSlow5 = (1.0f - (fConst0 / fSlow3));
		for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
			fRec2[0] = (fSlow0 + (fConst3 * fRec2[1]));
			float fTemp0 = std::tan((fConst1 * fRec2[0]));
			float fTemp1 = (1.0f / fTemp0);
			fRec3[0] = (fSlow2 + (fConst3 * fRec3[1]));
			float fTemp2 = (fSlow4 + (fRec4[1] + -1.0f));
			int iTemp3 = (fTemp2 < 0.0f);
			float fTemp4 = (fSlow4 + fRec4[1]);
			fRec4[0] = (iTemp3 ? fTemp4 : fTemp2);
			float fRec5 = (iTemp3 ? fTemp4 : (fSlow4 + (fRec4[1] + (fSlow5 * fTemp2))));
			float fTemp5 = (fSlow1 * (fRec3[0] * ((2.0f * fRec5) + -1.0f)));
			fVec0[0] = fTemp5;
			fRec1[0] = (0.0f - (((fRec1[1] * (1.0f - fTemp1)) - (fTemp5 + fVec0[1])) / (fTemp1 + 1.0f)));
			float fTemp6 = (((fTemp1 + 1.0f) / fTemp0) + 1.0f);
			fRec0[0] = (fRec1[0] - (((fRec0[2] * (((fTemp1 + -1.0f) / fTemp0) + 1.0f)) + (2.0f * (fRec0[1] * (1.0f - (1.0f / mydsp_faustpower2_f(fTemp0)))))) / fTemp6));
			float fTemp7 = ((fRec0[2] + (fRec0[0] + (2.0f * fRec0[1]))) / fTemp6);
			output0[i0] = FAUSTFLOAT(fTemp7);
			output1[i0] = FAUSTFLOAT(fTemp7);
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
			fRec4[1] = fRec4[0];
			fVec0[1] = fVec0[0];
			fRec1[1] = fRec1[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
		}
	}

};
