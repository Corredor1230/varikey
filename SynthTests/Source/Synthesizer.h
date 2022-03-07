/* ------------------------------------------------------------
name: "Synthesizer"
Code generated with Faust 2.37.3 (https://faust.grame.fr)
Compilation options: -a arch.cpp -lang cpp -es 1 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __Synthesizer_H__
#define  __Synthesizer_H__

// faust -a arch.cpp -i -cn synthesizer synthesizer.dsp -o ../synthesizer.h

/************************** BEGIN misc.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __misc__
#define __misc__

#include <algorithm>
#include <map>
#include <cstdlib>
#include <string.h>
#include <fstream>
#include <string>

/************************** BEGIN meta.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __meta__
#define __meta__

/**
 The base class of Meta handler to be used in dsp::metadata(Meta* m) method to retrieve (key, value) metadata.
 */
struct Meta
{
    virtual ~Meta() {};
    virtual void declare(const char* key, const char* value) = 0;
};

#endif
/**************************  END  meta.h **************************/

using std::max;
using std::min;

struct XXXX_Meta : std::map<const char*, const char*>
{
    void declare(const char* key, const char* value) { (*this)[key] = value; }
};

struct MY_Meta : Meta, std::map<const char*, const char*>
{
    void declare(const char* key, const char* value) { (*this)[key] = value; }
};

static int lsr(int x, int n) { return int(((unsigned int)x) >> n); }

static int int2pow2(int x) { int r = 0; while ((1<<r) < x) r++; return r; }

static long lopt(char* argv[], const char* name, long def)
{
    for (int i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return std::atoi(argv[i+1]);
    return def;
}

static long lopt1(int argc, char* argv[], const char* longname, const char* shortname, long def)
{
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i-1], shortname) == 0 || strcmp(argv[i-1], longname) == 0) {
            return atoi(argv[i]);
        }
    }
    return def;
}

static const char* lopts(char* argv[], const char* name, const char* def)
{
    for (int i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return argv[i+1];
    return def;
}

static const char* lopts1(int argc, char* argv[], const char* longname, const char* shortname, const char* def)
{
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i-1], shortname) == 0 || strcmp(argv[i-1], longname) == 0) {
            return argv[i];
        }
    }
    return def;
}

static bool isopt(char* argv[], const char* name)
{
    for (int i = 0; argv[i]; i++) if (!strcmp(argv[i], name)) return true;
    return false;
}

static std::string pathToContent(const std::string& path)
{
    std::ifstream file(path.c_str(), std::ifstream::binary);
    
    file.seekg(0, file.end);
    int size = int(file.tellg());
    file.seekg(0, file.beg);
    
    // And allocate buffer to that a single line can be read...
    char* buffer = new char[size + 1];
    file.read(buffer, size);
    
    // Terminate the string
    buffer[size] = 0;
    std::string result = buffer;
    file.close();
    delete [] buffer;
    return result;
}

#endif

/**************************  END  misc.h **************************/
/************************** BEGIN MapUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef FAUST_MAPUI_H
#define FAUST_MAPUI_H

#include <vector>
#include <map>
#include <string>
#include <stdio.h>

/************************** BEGIN UI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2020 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __UI_H__
#define __UI_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

/*******************************************************************************
 * UI : Faust DSP User Interface
 * User Interface as expected by the buildUserInterface() method of a DSP.
 * This abstract class contains only the method that the Faust compiler can
 * generate to describe a DSP user interface.
 ******************************************************************************/

struct Soundfile;

template <typename REAL>
struct UIReal
{
    UIReal() {}
    virtual ~UIReal() {}
    
    // -- widget's layouts
    
    virtual void openTabBox(const char* label) = 0;
    virtual void openHorizontalBox(const char* label) = 0;
    virtual void openVerticalBox(const char* label) = 0;
    virtual void closeBox() = 0;
    
    // -- active widgets
    
    virtual void addButton(const char* label, REAL* zone) = 0;
    virtual void addCheckButton(const char* label, REAL* zone) = 0;
    virtual void addVerticalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    virtual void addHorizontalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    virtual void addNumEntry(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    
    // -- passive widgets
    
    virtual void addHorizontalBargraph(const char* label, REAL* zone, REAL min, REAL max) = 0;
    virtual void addVerticalBargraph(const char* label, REAL* zone, REAL min, REAL max) = 0;
    
    // -- soundfiles
    
    virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) = 0;
    
    // -- metadata declarations
    
    virtual void declare(REAL* zone, const char* key, const char* val) {}
    
    // To be used by LLVM client
    virtual int sizeOfFAUSTFLOAT() { return sizeof(FAUSTFLOAT); }
};

struct UI : public UIReal<FAUSTFLOAT>
{
    UI() {}
    virtual ~UI() {}
};

#endif
/**************************  END  UI.h **************************/
/************************** BEGIN PathBuilder.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef FAUST_PATHBUILDER_H
#define FAUST_PATHBUILDER_H

#include <vector>
#include <string>
#include <algorithm>

/*******************************************************************************
 * PathBuilder : Faust User Interface
 * Helper class to build complete hierarchical path for UI items.
 ******************************************************************************/

class PathBuilder
{

    protected:
    
        std::vector<std::string> fControlsLevel;
       
    public:
    
        PathBuilder() {}
        virtual ~PathBuilder() {}
    
        std::string replaceCharList(std::string str, const std::vector<char>& ch1, char ch2)
        {
            std::vector<char>::const_iterator beg = ch1.begin();
            std::vector<char>::const_iterator end = ch1.end();
            for (size_t i = 0; i < str.length(); ++i) {
                if (std::find(beg, end, str[i]) != end) {
                    str[i] = ch2;
                }
            }
            return str;
        }
    
        std::string buildPath(const std::string& label) 
        {
            std::string res = "/";
            for (size_t i = 0; i < fControlsLevel.size(); i++) {
                res += fControlsLevel[i];
                res += "/";
            }
            res += label;
            std::vector<char> rep = {' ', '#', '*', ',', '/', '?', '[', ']', '{', '}', '(', ')'};
            replaceCharList(res, rep, '_');
            return res;
        }
    
        void pushLabel(const std::string& label) { fControlsLevel.push_back(label); }
        void popLabel() { fControlsLevel.pop_back(); }
    
};

#endif  // FAUST_PATHBUILDER_H
/**************************  END  PathBuilder.h **************************/

/*******************************************************************************
 * MapUI : Faust User Interface
 * This class creates a map of complete hierarchical path and zones for each UI items.
 ******************************************************************************/

class MapUI : public UI, public PathBuilder
{
    
    protected:
    
        // Complete path map
        std::map<std::string, FAUSTFLOAT*> fPathZoneMap;
    
        // Label zone map
        std::map<std::string, FAUSTFLOAT*> fLabelZoneMap;
    
    public:
        
        MapUI() {}
        virtual ~MapUI() {}
        
        // -- widget's layouts
        void openTabBox(const char* label)
        {
            pushLabel(label);
        }
        void openHorizontalBox(const char* label)
        {
            pushLabel(label);
        }
        void openVerticalBox(const char* label)
        {
            pushLabel(label);
        }
        void closeBox()
        {
            popLabel();
        }
        
        // -- active widgets
        void addButton(const char* label, FAUSTFLOAT* zone)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        
        // -- passive widgets
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
    
        // -- soundfiles
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}
        
        // -- metadata declarations
        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {}
        
        // setParamValue/getParamValue
        void setParamValue(const std::string& path, FAUSTFLOAT value)
        {
            if (fPathZoneMap.find(path) != fPathZoneMap.end()) {
                *fPathZoneMap[path] = value;
            } else if (fLabelZoneMap.find(path) != fLabelZoneMap.end()) {
                *fLabelZoneMap[path] = value;
            } else {
                fprintf(stderr, "ERROR : setParamValue '%s' not found\n", path.c_str());
            }
        }
        
        FAUSTFLOAT getParamValue(const std::string& path)
        {
            if (fPathZoneMap.find(path) != fPathZoneMap.end()) {
                return *fPathZoneMap[path];
            } else if (fLabelZoneMap.find(path) != fLabelZoneMap.end()) {
                return *fLabelZoneMap[path];
            } else {
                fprintf(stderr, "ERROR : getParamValue '%s' not found\n", path.c_str());
                return 0;
            }
        }
    
        // map access 
        std::map<std::string, FAUSTFLOAT*>& getMap() { return fPathZoneMap; }
        
        int getParamsCount() { return int(fPathZoneMap.size()); }
        
        std::string getParamAddress(int index)
        {
            if (index < 0 || index > int(fPathZoneMap.size())) {
                return "";
            } else {
                auto it = fPathZoneMap.begin();
                while (index-- > 0 && it++ != fPathZoneMap.end()) {}
                return it->first;
            }
        }
        
        const char* getParamAddress1(int index)
        {
            if (index < 0 || index > int(fPathZoneMap.size())) {
                return nullptr;
            } else {
                auto it = fPathZoneMap.begin();
                while (index-- > 0 && it++ != fPathZoneMap.end()) {}
                return it->first.c_str();
            }
        }
    
        std::string getParamAddress(FAUSTFLOAT* zone)
        {
            for (const auto& it : fPathZoneMap) {
                if (it.second == zone) return it.first;
            }
            return "";
        }
    
        FAUSTFLOAT* getParamZone(const std::string& str)
        {
            if (fPathZoneMap.find(str) != fPathZoneMap.end()) {
                return fPathZoneMap[str];
            } else if (fLabelZoneMap.find(str) != fLabelZoneMap.end()) {
                return fLabelZoneMap[str];
            }
            return nullptr;
        }
    
        FAUSTFLOAT* getParamZone(int index)
        {
            if (index < 0 || index > int(fPathZoneMap.size())) {
                return nullptr;
            } else {
                auto it = fPathZoneMap.begin();
                while (index-- > 0 && it++ != fPathZoneMap.end()) {}
                return it->second;
            }
        }
    
        static bool endsWith(const std::string& str, const std::string& end)
        {
            size_t l1 = str.length();
            size_t l2 = end.length();
            return (l1 >= l2) && (0 == str.compare(l1 - l2, l2, end));
        }
};


#endif // FAUST_MAPUI_H
/**************************  END  MapUI.h **************************/
/************************** BEGIN dsp.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __dsp__
#define __dsp__

#include <string>
#include <vector>

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

struct UI;
struct Meta;

/**
 * DSP memory manager.
 */

struct dsp_memory_manager {
    
    virtual ~dsp_memory_manager() {}
    
    virtual void* allocate(size_t size) = 0;
    virtual void destroy(void* ptr) = 0;
    
};

/**
* Signal processor definition.
*/

class dsp {

    public:

        dsp() {}
        virtual ~dsp() {}

        /* Return instance number of audio inputs */
        virtual int getNumInputs() = 0;
    
        /* Return instance number of audio outputs */
        virtual int getNumOutputs() = 0;
    
        /**
         * Trigger the ui_interface parameter with instance specific calls
         * to 'openTabBox', 'addButton', 'addVerticalSlider'... in order to build the UI.
         *
         * @param ui_interface - the user interface builder
         */
        virtual void buildUserInterface(UI* ui_interface) = 0;
    
        /* Return the sample rate currently used by the instance */
        virtual int getSampleRate() = 0;
    
        /**
         * Global init, calls the following methods:
         * - static class 'classInit': static tables initialization
         * - 'instanceInit': constants and instance state initialization
         *
         * @param sample_rate - the sampling rate in Hz
         */
        virtual void init(int sample_rate) = 0;

        /**
         * Init instance state
         *
         * @param sample_rate - the sampling rate in Hz
         */
        virtual void instanceInit(int sample_rate) = 0;
    
        /**
         * Init instance constant state
         *
         * @param sample_rate - the sampling rate in Hz
         */
        virtual void instanceConstants(int sample_rate) = 0;
    
        /* Init default control parameters values */
        virtual void instanceResetUserInterface() = 0;
    
        /* Init instance state (like delay lines...) but keep the control parameter values */
        virtual void instanceClear() = 0;
 
        /**
         * Return a clone of the instance.
         *
         * @return a copy of the instance on success, otherwise a null pointer.
         */
        virtual dsp* clone() = 0;
    
        /**
         * Trigger the Meta* parameter with instance specific calls to 'declare' (key, value) metadata.
         *
         * @param m - the Meta* meta user
         */
        virtual void metadata(Meta* m) = 0;
    
        /**
         * DSP instance computation, to be called with successive in/out audio buffers.
         *
         * @param count - the number of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
         *
         */
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) = 0;
    
        /**
         * DSP instance computation: alternative method to be used by subclasses.
         *
         * @param date_usec - the timestamp in microsec given by audio driver.
         * @param count - the number of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (either float, double or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (either float, double or quad)
         *
         */
        virtual void compute(double /*date_usec*/, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
       
};

/**
 * Generic DSP decorator.
 */

class decorator_dsp : public dsp {

    protected:

        dsp* fDSP;

    public:

        decorator_dsp(dsp* dsp = nullptr):fDSP(dsp) {}
        virtual ~decorator_dsp() { delete fDSP; }

        virtual int getNumInputs() { return fDSP->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP->getNumOutputs(); }
        virtual void buildUserInterface(UI* ui_interface) { fDSP->buildUserInterface(ui_interface); }
        virtual int getSampleRate() { return fDSP->getSampleRate(); }
        virtual void init(int sample_rate) { fDSP->init(sample_rate); }
        virtual void instanceInit(int sample_rate) { fDSP->instanceInit(sample_rate); }
        virtual void instanceConstants(int sample_rate) { fDSP->instanceConstants(sample_rate); }
        virtual void instanceResetUserInterface() { fDSP->instanceResetUserInterface(); }
        virtual void instanceClear() { fDSP->instanceClear(); }
        virtual decorator_dsp* clone() { return new decorator_dsp(fDSP->clone()); }
        virtual void metadata(Meta* m) { fDSP->metadata(m); }
        // Beware: subclasses usually have to overload the two 'compute' methods
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(count, inputs, outputs); }
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(date_usec, count, inputs, outputs); }
    
};

/**
 * DSP factory class, used with LLVM and Interpreter backends
 * to create DSP instances from a compiled DSP program.
 */

class dsp_factory {
    
    protected:
    
        // So that to force sub-classes to use deleteDSPFactory(dsp_factory* factory);
        virtual ~dsp_factory() {}
    
    public:
    
        virtual std::string getName() = 0;
        virtual std::string getSHAKey() = 0;
        virtual std::string getDSPCode() = 0;
        virtual std::string getCompileOptions() = 0;
        virtual std::vector<std::string> getLibraryList() = 0;
        virtual std::vector<std::string> getIncludePathnames() = 0;
    
        virtual dsp* createDSPInstance() = 0;
    
        virtual void setMemoryManager(dsp_memory_manager* manager) = 0;
        virtual dsp_memory_manager* getMemoryManager() = 0;
    
};

// Denormal handling

#if defined (__SSE__)
#include <xmmintrin.h>
#endif

class ScopedNoDenormals
{
    private:
    
        intptr_t fpsr;
        
        void setFpStatusRegister(intptr_t fpsr_aux) noexcept
        {
        #if defined (__arm64__) || defined (__aarch64__)
           asm volatile("msr fpcr, %0" : : "ri" (fpsr_aux));
        #elif defined (__SSE__)
            _mm_setcsr(static_cast<uint32_t>(fpsr_aux));
        #endif
        }
        
        void getFpStatusRegister() noexcept
        {
        #if defined (__arm64__) || defined (__aarch64__)
            asm volatile("mrs %0, fpcr" : "=r" (fpsr));
        #elif defined ( __SSE__)
            fpsr = static_cast<intptr_t>(_mm_getcsr());
        #endif
        }
    
    public:
    
        ScopedNoDenormals() noexcept
        {
        #if defined (__arm64__) || defined (__aarch64__)
            intptr_t mask = (1 << 24 /* FZ */);
        #else
            #if defined(__SSE__)
            #if defined(__SSE2__)
                intptr_t mask = 0x8040;
            #else
                intptr_t mask = 0x8000;
            #endif
            #else
                intptr_t mask = 0x0000;
            #endif
        #endif
            getFpStatusRegister();
            setFpStatusRegister(fpsr | mask);
        }
        
        ~ScopedNoDenormals() noexcept
        {
            setFpStatusRegister(fpsr);
        }

};

#define AVOIDDENORMALS ScopedNoDenormals();

#endif

/************************** END dsp.h **************************/
/************************** BEGIN midi.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __midi__
#define __midi__

#include <vector>
#include <string>
#include <algorithm>
#include <assert.h>

class MapUI;

/**
 * A timestamped short MIDI message used with SOUL.
 */

// Force contiguous memory layout
#pragma pack (push, 1)
struct MIDIMessage
{
    uint32_t frameIndex;
    uint8_t byte0, byte1, byte2;
};
#pragma pack (pop)

/**
 * For timestamped MIDI messages.
 */
struct DatedMessage {
    
    double fDate;
    unsigned char fBuffer[3];
    size_t fSize;
    
    DatedMessage(double date, unsigned char* buffer, size_t size)
    :fDate(date), fSize(size)
    {
        assert(size <= 3);
        memcpy(fBuffer, buffer, size);
    }
    
    DatedMessage():fDate(0.0), fSize(0)
    {}
    
};

/**
 * MIDI processor definition.
 *
 * MIDI input or output handling classes will implement this interface,
 * so the same method names (keyOn, keyOff, ctrlChange...) will be used either
 * when decoding MIDI input or encoding MIDI output events.
 * MIDI channel is numbered in [0..15] in this layer.
 */
class midi {

    public:

        midi() {}
        virtual ~midi() {}

        // Additional time-stamped API for MIDI input
        virtual MapUI* keyOn(double, int channel, int pitch, int velocity)
        {
            return keyOn(channel, pitch, velocity);
        }
        
        virtual void keyOff(double, int channel, int pitch, int velocity = 0)
        {
            keyOff(channel, pitch, velocity);
        }
    
        virtual void keyPress(double, int channel, int pitch, int press)
        {
            keyPress(channel, pitch, press);
        }
        
        virtual void chanPress(double date, int channel, int press)
        {
            chanPress(channel, press);
        }
    
        virtual void pitchWheel(double, int channel, int wheel)
        {
            pitchWheel(channel, wheel);
        }
           
        virtual void ctrlChange(double, int channel, int ctrl, int value)
        {
            ctrlChange(channel, ctrl, value);
        }
    
        virtual void ctrlChange14bits(double, int channel, int ctrl, int value)
        {
            ctrlChange14bits(channel, ctrl, value);
        }
    
        virtual void rpn(double, int channel, int ctrl, int value)
        {
            rpn(channel, ctrl, value);
        }

        virtual void progChange(double, int channel, int pgm)
        {
            progChange(channel, pgm);
        }
    
        virtual void sysEx(double, std::vector<unsigned char>& message)
        {
            sysEx(message);
        }

        // MIDI sync
        virtual void startSync(double date)  {}
        virtual void stopSync(double date)   {}
        virtual void clock(double date)  {}

        // Standard MIDI API
        virtual MapUI* keyOn(int channel, int pitch, int velocity)      { return nullptr; }
        virtual void keyOff(int channel, int pitch, int velocity)       {}
        virtual void keyPress(int channel, int pitch, int press)        {}
        virtual void chanPress(int channel, int press)                  {}
        virtual void ctrlChange(int channel, int ctrl, int value)       {}
        virtual void ctrlChange14bits(int channel, int ctrl, int value) {}
        virtual void rpn(int channel, int ctrl, int value)              {}
        virtual void pitchWheel(int channel, int wheel)                 {}
        virtual void progChange(int channel, int pgm)                   {}
        virtual void sysEx(std::vector<unsigned char>& message)         {}

        enum MidiStatus {
            // channel voice messages
            MIDI_NOTE_OFF = 0x80,
            MIDI_NOTE_ON = 0x90,
            MIDI_CONTROL_CHANGE = 0xB0,
            MIDI_PROGRAM_CHANGE = 0xC0,
            MIDI_PITCH_BEND = 0xE0,
            MIDI_AFTERTOUCH = 0xD0,         // aka channel pressure
            MIDI_POLY_AFTERTOUCH = 0xA0,    // aka key pressure
            MIDI_CLOCK = 0xF8,
            MIDI_START = 0xFA,
            MIDI_CONT = 0xFB,
            MIDI_STOP = 0xFC,
            MIDI_SYSEX_START = 0xF0,
            MIDI_SYSEX_STOP = 0xF7
        };

        enum MidiCtrl {
            ALL_NOTES_OFF = 123,
            ALL_SOUND_OFF = 120
        };
    
        enum MidiNPN {
            PITCH_BEND_RANGE = 0
        };

};

/**
 * A class to decode NRPN and RPN messages, adapted from JUCE forum message:
 * https://forum.juce.com/t/14bit-midi-controller-support/11517
 */
class MidiNRPN {
    
    private:
    
        bool ctrlnew;
        int ctrlnum;
        int ctrlval;
        
        int nrpn_lsb, nrpn_msb;
        int data_lsb, data_msb;
        
        enum
        {
            midi_nrpn_lsb = 98,
            midi_nrpn_msb = 99,
            midi_rpn_lsb  = 100,
            midi_rpn_msb  = 101,
            midi_data_lsb = 38,
            midi_data_msb = 6
        };
    
    public:
        
        MidiNRPN(): ctrlnew(false), nrpn_lsb(-1), nrpn_msb(-1), data_lsb(-1), data_msb(-1)
        {}
        
        // return true if the message has been filtered
        bool process(int data1, int data2)
        {
            switch (data1)
            {
                case midi_nrpn_lsb: nrpn_lsb = data2; return true;
                case midi_nrpn_msb: nrpn_msb = data2; return true;
                case midi_rpn_lsb: {
                    if (data2 == 127) {
                        nrpn_lsb = data_lsb = -1;
                    } else {
                        nrpn_lsb = 0;
                        data_lsb = -1;
                    }
                    return true;
                }
                case midi_rpn_msb: {
                    if (data2 == 127) {
                        nrpn_msb = data_msb = -1;
                    } else {
                        nrpn_msb = 0;
                        data_msb = -1;
                    }
                    return true;
                }
                case midi_data_lsb:
                case midi_data_msb:
                {
                    if (data1 == midi_data_msb) {
                        if (nrpn_msb < 0) {
                            return false;
                        }
                        data_msb = data2;
                    } else { // midi_data_lsb
                        if (nrpn_lsb < 0) {
                            return false;
                        }
                        data_lsb = data2;
                    }
                    if (data_lsb >= 0 && data_msb >= 0) {
                        ctrlnum = (nrpn_msb << 7) | nrpn_lsb;
                        ctrlval = (data_msb << 7) | data_lsb;
                        data_lsb = data_msb = -1;
                        nrpn_msb = nrpn_lsb = -1;
                        ctrlnew = true;
                    }
                    return true;
                }
                default: return false;
            };
        }
        
        bool hasNewNRPN() { bool res = ctrlnew; ctrlnew = false; return res; }
        
        // results in [0, 16383]
        int getCtrl() const { return ctrlnum; }
        int getVal() const { return ctrlval; }
    
};

/**
 * A pure interface for MIDI handlers that can send/receive MIDI messages to/from 'midi' objects.
 */
struct midi_interface {
    virtual void addMidiIn(midi* midi_dsp)      = 0;
    virtual void removeMidiIn(midi* midi_dsp)   = 0;
    virtual ~midi_interface() {}
};

/****************************************************
 * Base class for MIDI input handling.
 *
 * Shared common code used for input handling:
 * - decoding Real-Time messages: handleSync
 * - decoding one data byte messages: handleData1
 * - decoding two data byte messages: handleData2
 * - getting ready messages in polling mode
 ****************************************************/
class midi_handler : public midi, public midi_interface {

    protected:

        std::vector<midi*> fMidiInputs;
        std::string fName;
        MidiNRPN fNRPN;
    
        int range(int min, int max, int val) { return (val < min) ? min : ((val >= max) ? max : val); }
  
    public:

        midi_handler(const std::string& name = "MIDIHandler"):midi_interface(), fName(name) {}
        virtual ~midi_handler() {}

        void addMidiIn(midi* midi_dsp) { if (midi_dsp) fMidiInputs.push_back(midi_dsp); }
        void removeMidiIn(midi* midi_dsp)
        {
            std::vector<midi*>::iterator it = std::find(fMidiInputs.begin(), fMidiInputs.end(), midi_dsp);
            if (it != fMidiInputs.end()) {
                fMidiInputs.erase(it);
            }
        }

        // Those 2 methods have to be implemented by subclasses
        virtual bool startMidi() { return true; }
        virtual void stopMidi() {}
    
        void setName(const std::string& name) { fName = name; }
        std::string getName() { return fName; }
    
        // To be used in polling mode
        virtual int recvMessages(std::vector<MIDIMessage>* message) { return 0; }
        virtual void sendMessages(std::vector<MIDIMessage>* message, int count) {}
    
        // MIDI Real-Time
        void handleClock(double time)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->clock(time);
            }
        }
        
        void handleStart(double time)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->startSync(time);
            }
        }
        
        void handleStop(double time)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->stopSync(time);
            }
        }
    
        void handleSync(double time, int type)
        {
            if (type == MIDI_CLOCK) {
                handleClock(time);
            // We can consider start and continue as identical messages
            } else if ((type == MIDI_START) || (type == MIDI_CONT)) {
                handleStart(time);
            } else if (type == MIDI_STOP) {
                handleStop(time);
            }
        }
    
        // MIDI 1 data
        void handleProgChange(double time, int channel, int data1)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->progChange(time, channel, data1);
            }
        }
    
        void handleAfterTouch(double time, int channel, int data1)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->chanPress(time, channel, data1);
            }
        }

        void handleData1(double time, int type, int channel, int data1)
        {
            if (type == MIDI_PROGRAM_CHANGE) {
                handleProgChange(time, channel, data1);
            } else if (type == MIDI_AFTERTOUCH) {
                handleAfterTouch(time, channel, data1);
            }
        }
    
        // MIDI 2 datas
        void handleKeyOff(double time, int channel, int data1, int data2)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->keyOff(time, channel, data1, data2);
            }
        }
        
        void handleKeyOn(double time, int channel, int data1, int data2)
        {
            if (data2 == 0) {
                handleKeyOff(time, channel, data1, data2);
            } else {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->keyOn(time, channel, data1, data2);
                }
            }
        }
    
        void handleCtrlChange(double time, int channel, int data1, int data2)
        {
            // Special processing for NRPN and RPN
            if (fNRPN.process(data1, data2)) {
                if (fNRPN.hasNewNRPN()) {
                    for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                        fMidiInputs[i]->rpn(time, channel, fNRPN.getCtrl(), fNRPN.getVal());
                    }
                }
            } else {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->ctrlChange(time, channel, data1, data2);
                }
            }
        }
        
        void handlePitchWheel(double time, int channel, int data1, int data2)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->pitchWheel(time, channel, (data2 << 7) + data1);
            }
        }
    
        void handlePitchWheel(double time, int channel, int bend)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->pitchWheel(time, channel, bend);
            }
        }
        
        void handlePolyAfterTouch(double time, int channel, int data1, int data2)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->keyPress(time, channel, data1, data2);
            }
        }
  
        void handleData2(double time, int type, int channel, int data1, int data2)
        {
            if (type == MIDI_NOTE_OFF) {
                handleKeyOff(time, channel,  data1, data2);
            } else if (type == MIDI_NOTE_ON) {
                handleKeyOn(time, channel, data1, data2);
            } else if (type == MIDI_CONTROL_CHANGE) {
                handleCtrlChange(time, channel, data1, data2);
            } else if (type == MIDI_PITCH_BEND) {
                handlePitchWheel(time, channel, data1, data2);
            } else if (type == MIDI_POLY_AFTERTOUCH) {
                handlePolyAfterTouch(time, channel, data1, data2);
            }
        }
    
        // SysEx
        void handleSysex(double time, std::vector<unsigned char>& message)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->sysEx(time, message);
            }
        }
    
        void handleMessage(double time, int type, std::vector<unsigned char>& message)
        {
            if (type == MIDI_SYSEX_START) {
                handleSysex(time, message);
            }
        }
  
};

#endif // __midi__
/**************************  END  midi.h **************************/
#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

class SynthesizerSIG0 {
	
  private:
	
	int iVec0[2];
	int iRec6[2];
	
  public:
	
	int getNumInputsSynthesizerSIG0() {
		return 0;
	}
	int getNumOutputsSynthesizerSIG0() {
		return 1;
	}
	
	void instanceInitSynthesizerSIG0(int sample_rate) {
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			iVec0[l1] = 0;
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			iRec6[l2] = 0;
		}
	}
	
	void fillSynthesizerSIG0(int count, float* table) {
		for (int i1 = 0; (i1 < count); i1 = (i1 + 1)) {
			iVec0[0] = 1;
			iRec6[0] = ((iVec0[1] + iRec6[1]) % 65536);
			table[i1] = std::sin((9.58738019e-05f * float(iRec6[0])));
			iVec0[1] = iVec0[0];
			iRec6[1] = iRec6[0];
		}
	}

};

static SynthesizerSIG0* newSynthesizerSIG0() { return (SynthesizerSIG0*)new SynthesizerSIG0(); }
static void deleteSynthesizerSIG0(SynthesizerSIG0* dsp) { delete dsp; }

static float ftbl0SynthesizerSIG0[65536];
static float Synthesizer_faustpower2_f(float value) {
	return (value * value);
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS Synthesizer
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class Synthesizer : public dsp {
	
 private:
	
	int fSampleRate;
	float fConst0;
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
	float fConst7;
	float fConst8;
	FAUSTFLOAT fVslider0;
	float fConst9;
	float fRec5[2];
	FAUSTFLOAT fVslider1;
	float fConst10;
	FAUSTFLOAT fVslider2;
	float fRec7[2];
	FAUSTFLOAT fButton0;
	float fVec1[2];
	FAUSTFLOAT fEntry0;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fVslider3;
	float fRec10[2];
	FAUSTFLOAT fVslider4;
	float fRec11[2];
	FAUSTFLOAT fVslider5;
	float fRec12[2];
	FAUSTFLOAT fVslider6;
	float fRec13[2];
	FAUSTFLOAT fVslider7;
	float fRec14[2];
	FAUSTFLOAT fVslider8;
	float fRec15[2];
	FAUSTFLOAT fVslider9;
	float fRec16[2];
	FAUSTFLOAT fVslider10;
	float fRec17[2];
	FAUSTFLOAT fVslider11;
	float fRec18[2];
	FAUSTFLOAT fVslider12;
	float fRec19[2];
	FAUSTFLOAT fVslider13;
	float fRec20[2];
	FAUSTFLOAT fHslider1;
	float fRec21[2];
	FAUSTFLOAT fVslider14;
	FAUSTFLOAT fVslider15;
	float fRec23[2];
	float fRec22[2];
	FAUSTFLOAT fVslider16;
	float fRec24[2];
	FAUSTFLOAT fHslider2;
	float fRec8[2];
	float fRec25[2];
	FAUSTFLOAT fVslider17;
	float fRec27[2];
	FAUSTFLOAT fVslider18;
	FAUSTFLOAT fVslider19;
	FAUSTFLOAT fVslider20;
	int iRec28[2];
	float fVec2[2];
	float fRec4[2];
	float fRec3[3];
	float fVec3[2];
	float fRec2[2];
	float fConst11;
	float fConst12;
	float fRec1[3];
	float fConst13;
	float fRec0[3];
	FAUSTFLOAT fVslider21;
	FAUSTFLOAT fVslider22;
	float fRec30[2];
	float fRec29[2];
	FAUSTFLOAT fVslider23;
	float fRec31[2];
	float fRec37[2];
	float fVec4[2];
	float fRec36[2];
	float fRec35[3];
	float fVec5[2];
	float fRec34[2];
	float fRec33[3];
	float fRec32[3];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.1");
		m->declare("compile_options", "-a arch.cpp -lang cpp -es 1 -single -ftz 0");
		m->declare("envelopes.lib/adsr:author", "Yann Orlarey and Andrey Bundin");
		m->declare("envelopes.lib/author", "GRAME");
		m->declare("envelopes.lib/copyright", "GRAME");
		m->declare("envelopes.lib/license", "LGPL with exception");
		m->declare("envelopes.lib/name", "Faust Envelope Library");
		m->declare("envelopes.lib/version", "0.1");
		m->declare("filename", "Synthesizer.dsp");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "MIT-style STK-4.3 license");
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
		m->declare("name", "Synthesizer");
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
		SynthesizerSIG0* sig0 = newSynthesizerSIG0();
		sig0->instanceInitSynthesizerSIG0(sample_rate);
		sig0->fillSynthesizerSIG0(65536, ftbl0SynthesizerSIG0);
		deleteSynthesizerSIG0(sig0);
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));
		float fConst1 = std::tan((56548.668f / fConst0));
		float fConst2 = (1.0f / fConst1);
		fConst3 = (1.0f / (((fConst2 + 0.618034005f) / fConst1) + 1.0f));
		fConst4 = (1.0f / (((fConst2 + 1.61803401f) / fConst1) + 1.0f));
		fConst5 = (1.0f / (fConst2 + 1.0f));
		fConst6 = (1.0f - fConst2);
		fConst7 = (3.14159274f / fConst0);
		fConst8 = (44.0999985f / fConst0);
		fConst9 = (1.0f - fConst8);
		fConst10 = (1.0f / fConst0);
		fConst11 = (((fConst2 + -1.61803401f) / fConst1) + 1.0f);
		fConst12 = (2.0f * (1.0f - (1.0f / Synthesizer_faustpower2_f(fConst1))));
		fConst13 = (((fConst2 + -0.618034005f) / fConst1) + 1.0f);
	}
	
	virtual void instanceResetUserInterface() {
		fVslider0 = FAUSTFLOAT(1000.0f);
		fVslider1 = FAUSTFLOAT(0.0f);
		fVslider2 = FAUSTFLOAT(0.0f);
		fButton0 = FAUSTFLOAT(0.0f);
		fEntry0 = FAUSTFLOAT(500.0f);
		fHslider0 = FAUSTFLOAT(0.0f);
		fVslider3 = FAUSTFLOAT(0.0f);
		fVslider4 = FAUSTFLOAT(0.0f);
		fVslider5 = FAUSTFLOAT(0.0f);
		fVslider6 = FAUSTFLOAT(0.0f);
		fVslider7 = FAUSTFLOAT(0.0f);
		fVslider8 = FAUSTFLOAT(0.0f);
		fVslider9 = FAUSTFLOAT(0.0f);
		fVslider10 = FAUSTFLOAT(0.0f);
		fVslider11 = FAUSTFLOAT(0.0f);
		fVslider12 = FAUSTFLOAT(0.0f);
		fVslider13 = FAUSTFLOAT(0.0f);
		fHslider1 = FAUSTFLOAT(0.0f);
		fVslider14 = FAUSTFLOAT(0.0f);
		fVslider15 = FAUSTFLOAT(0.0f);
		fVslider16 = FAUSTFLOAT(0.0f);
		fHslider2 = FAUSTFLOAT(0.0f);
		fVslider17 = FAUSTFLOAT(50.0f);
		fVslider18 = FAUSTFLOAT(0.29999999999999999f);
		fVslider19 = FAUSTFLOAT(50.0f);
		fVslider20 = FAUSTFLOAT(200.0f);
		fVslider21 = FAUSTFLOAT(0.0f);
		fVslider22 = FAUSTFLOAT(0.0f);
		fVslider23 = FAUSTFLOAT(-60.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fRec5[l0] = 0.0f;
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec7[l3] = 0.0f;
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fVec1[l4] = 0.0f;
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec10[l5] = 0.0f;
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec11[l6] = 0.0f;
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec12[l7] = 0.0f;
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec13[l8] = 0.0f;
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec14[l9] = 0.0f;
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec15[l10] = 0.0f;
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec16[l11] = 0.0f;
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec17[l12] = 0.0f;
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec18[l13] = 0.0f;
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec19[l14] = 0.0f;
		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec20[l15] = 0.0f;
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fRec21[l16] = 0.0f;
		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec23[l17] = 0.0f;
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fRec22[l18] = 0.0f;
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec24[l19] = 0.0f;
		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec8[l20] = 0.0f;
		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fRec25[l21] = 0.0f;
		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fRec27[l22] = 0.0f;
		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			iRec28[l23] = 0;
		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fVec2[l24] = 0.0f;
		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fRec4[l25] = 0.0f;
		}
		for (int l26 = 0; (l26 < 3); l26 = (l26 + 1)) {
			fRec3[l26] = 0.0f;
		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fVec3[l27] = 0.0f;
		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fRec2[l28] = 0.0f;
		}
		for (int l29 = 0; (l29 < 3); l29 = (l29 + 1)) {
			fRec1[l29] = 0.0f;
		}
		for (int l30 = 0; (l30 < 3); l30 = (l30 + 1)) {
			fRec0[l30] = 0.0f;
		}
		for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			fRec30[l31] = 0.0f;
		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			fRec29[l32] = 0.0f;
		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fRec31[l33] = 0.0f;
		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fRec37[l34] = 0.0f;
		}
		for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			fVec4[l35] = 0.0f;
		}
		for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			fRec36[l36] = 0.0f;
		}
		for (int l37 = 0; (l37 < 3); l37 = (l37 + 1)) {
			fRec35[l37] = 0.0f;
		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fVec5[l38] = 0.0f;
		}
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			fRec34[l39] = 0.0f;
		}
		for (int l40 = 0; (l40 < 3); l40 = (l40 + 1)) {
			fRec33[l40] = 0.0f;
		}
		for (int l41 = 0; (l41 < 3); l41 = (l41 + 1)) {
			fRec32[l41] = 0.0f;
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
	
	virtual Synthesizer* clone() {
		return new Synthesizer();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("Synthesizer");
		ui_interface->openHorizontalBox("Pitch");
		ui_interface->declare(&fHslider2, "midi", "ctrl 1");
		ui_interface->addHorizontalSlider("detune", &fHslider2, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00100000005f));
		ui_interface->declare(&fEntry0, "style", "knob");
		ui_interface->addNumEntry("freq", &fEntry0, FAUSTFLOAT(500.0f), FAUSTFLOAT(200.0f), FAUSTFLOAT(1000.0f), FAUSTFLOAT(0.00999999978f));
		ui_interface->addHorizontalSlider("pWheel", &fHslider1, FAUSTFLOAT(0.0f), FAUSTFLOAT(-1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00100000005f));
		ui_interface->declare(&fVslider14, "style", "knob");
		ui_interface->addVerticalSlider("vDepth", &fVslider14, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00100000005f));
		ui_interface->addVerticalSlider("vFreq", &fVslider15, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(20.0f), FAUSTFLOAT(0.0199999996f));
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Processing");
		ui_interface->openHorizontalBox("Envelope");
		ui_interface->declare(&fVslider17, "1", "");
		ui_interface->addVerticalSlider("att", &fVslider17, FAUSTFLOAT(50.0f), FAUSTFLOAT(10.0f), FAUSTFLOAT(3000.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fVslider19, "2", "");
		ui_interface->addVerticalSlider("dec", &fVslider19, FAUSTFLOAT(50.0f), FAUSTFLOAT(10.0f), FAUSTFLOAT(3000.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fVslider18, "3", "");
		ui_interface->addVerticalSlider("sus", &fVslider18, FAUSTFLOAT(0.300000012f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00100000005f));
		ui_interface->declare(&fVslider20, "4", "");
		ui_interface->addVerticalSlider("rel", &fVslider20, FAUSTFLOAT(200.0f), FAUSTFLOAT(30.0f), FAUSTFLOAT(5000.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fVslider23, "5", "");
		ui_interface->addVerticalSlider("gain", &fVslider23, FAUSTFLOAT(-60.0f), FAUSTFLOAT(-60.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->openHorizontalBox("Filter");
		ui_interface->declare(&fVslider0, "scale", "log");
		ui_interface->declare(&fVslider0, "style", "knob");
		ui_interface->addVerticalSlider("cutoff", &fVslider0, FAUSTFLOAT(1000.0f), FAUSTFLOAT(110.0f), FAUSTFLOAT(20000.0f), FAUSTFLOAT(0.00999999978f));
		ui_interface->declare(&fVslider1, "style", "knob");
		ui_interface->addVerticalSlider("lfoD", &fVslider1, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00999999978f));
		ui_interface->addVerticalSlider("lfoF", &fVslider2, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(20.0f), FAUSTFLOAT(0.00100000005f));
		ui_interface->closeBox();
		ui_interface->addButton("gate", &fButton0);
		ui_interface->declare(&fVslider21, "style", "knob");
		ui_interface->addVerticalSlider("tDepth", &fVslider21, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00100000005f));
		ui_interface->addVerticalSlider("tFreq", &fVslider22, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(20.0f), FAUSTFLOAT(0.0199999996f));
		ui_interface->closeBox();
		ui_interface->openVerticalBox("Tuning");
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("Note Tuning");
		ui_interface->declare(&fVslider12, "1", "");
		ui_interface->addVerticalSlider("c", &fVslider12, FAUSTFLOAT(0.0f), FAUSTFLOAT(-1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00100000005f));
		ui_interface->declare(&fVslider10, "2", "");
		ui_interface->addVerticalSlider("ces", &fVslider10, FAUSTFLOAT(0.0f), FAUSTFLOAT(-1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00100000005f));
		ui_interface->declare(&fVslider11, "3", "");
		ui_interface->addVerticalSlider("d", &fVslider11, FAUSTFLOAT(0.0f), FAUSTFLOAT(-1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00100000005f));
		ui_interface->declare(&fVslider13, "4", "");
		ui_interface->addVerticalSlider("des", &fVslider13, FAUSTFLOAT(0.0f), FAUSTFLOAT(-1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00100000005f));
		ui_interface->declare(&fVslider16, "5", "");
		ui_interface->addVerticalSlider("e", &fVslider16, FAUSTFLOAT(0.0f), FAUSTFLOAT(-1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00100000005f));
		ui_interface->declare(&fVslider7, "6", "");
		ui_interface->addVerticalSlider("f", &fVslider7, FAUSTFLOAT(0.0f), FAUSTFLOAT(-1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00100000005f));
		ui_interface->declare(&fVslider8, "7", "");
		ui_interface->addVerticalSlider("fes", &fVslider8, FAUSTFLOAT(0.0f), FAUSTFLOAT(-1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00100000005f));
		ui_interface->declare(&fVslider6, "8", "");
		ui_interface->addVerticalSlider("g", &fVslider6, FAUSTFLOAT(0.0f), FAUSTFLOAT(-1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00100000005f));
		ui_interface->declare(&fVslider5, "9", "");
		ui_interface->addVerticalSlider("ges", &fVslider5, FAUSTFLOAT(0.0f), FAUSTFLOAT(-1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00100000005f));
		ui_interface->declare(&fVslider9, "", "");
		ui_interface->addVerticalSlider("a", &fVslider9, FAUSTFLOAT(0.0f), FAUSTFLOAT(-1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00100000005f));
		ui_interface->declare(&fVslider3, "", "");
		ui_interface->addVerticalSlider("as", &fVslider3, FAUSTFLOAT(0.0f), FAUSTFLOAT(-1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00100000005f));
		ui_interface->declare(&fVslider4, "", "");
		ui_interface->addVerticalSlider("b", &fVslider4, FAUSTFLOAT(0.0f), FAUSTFLOAT(-1.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.00100000005f));
		ui_interface->closeBox();
		ui_interface->declare(&fHslider0, "2", "");
		ui_interface->addHorizontalSlider("offset", &fHslider0, FAUSTFLOAT(0.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(11.0f), FAUSTFLOAT(1.0f));
		ui_interface->closeBox();
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = (fConst8 * float(fVslider0));
		float fSlow1 = float(fVslider1);
		float fSlow2 = (fConst10 * float(fVslider2));
		float fSlow3 = float(fButton0);
		float fSlow4 = (0.0909090936f * fSlow3);
		float fSlow5 = float(int(((17.3123398f * std::log((0.0022727272f * std::max<float>(20.0f, float(fEntry0))))) + 69.0f)));
		float fSlow6 = std::fmod((std::fmod((fSlow5 - float(fHslider0)), 12.0f) + 12.0f), 12.0f);
		float fSlow7 = float((fSlow6 == 10.0f));
		float fSlow8 = (fConst8 * float(fVslider3));
		float fSlow9 = float((fSlow6 == 11.0f));
		float fSlow10 = (fConst8 * float(fVslider4));
		float fSlow11 = float((fSlow6 == 8.0f));
		float fSlow12 = (fConst8 * float(fVslider5));
		float fSlow13 = float((fSlow6 == 7.0f));
		float fSlow14 = (fConst8 * float(fVslider6));
		float fSlow15 = float((fSlow6 == 5.0f));
		float fSlow16 = (fConst8 * float(fVslider7));
		float fSlow17 = float((fSlow6 == 6.0f));
		float fSlow18 = (fConst8 * float(fVslider8));
		float fSlow19 = float((fSlow6 == 9.0f));
		float fSlow20 = (fConst8 * float(fVslider9));
		float fSlow21 = float((fSlow6 == 1.0f));
		float fSlow22 = (fConst8 * float(fVslider10));
		float fSlow23 = float((fSlow6 == 2.0f));
		float fSlow24 = (fConst8 * float(fVslider11));
		float fSlow25 = float((fSlow6 == 0.0f));
		float fSlow26 = (fConst8 * float(fVslider12));
		float fSlow27 = float((fSlow6 == 3.0f));
		float fSlow28 = (fConst8 * float(fVslider13));
		float fSlow29 = (fConst8 * float(fHslider1));
		float fSlow30 = float(fVslider14);
		float fSlow31 = (fConst8 * float(fVslider15));
		float fSlow32 = float((fSlow6 == 4.0f));
		float fSlow33 = (fConst8 * float(fVslider16));
		float fSlow34 = float(fHslider2);
		float fSlow35 = std::max<float>(1.0f, (fConst0 * std::max<float>(0.0f, (0.00100000005f * float(fVslider17)))));
		float fSlow36 = (1.0f / fSlow35);
		float fSlow37 = std::min<float>(1.0f, std::max<float>(0.0f, float(fVslider18)));
		float fSlow38 = ((1.0f - fSlow37) / std::max<float>(1.0f, (fConst0 * std::max<float>(0.0f, (0.00100000005f * float(fVslider19))))));
		float fSlow39 = (1.0f / std::max<float>(1.0f, (fConst0 * std::max<float>(0.0f, (0.00100000005f * float(fVslider20))))));
		int iSlow40 = (fSlow3 == 0.0f);
		float fSlow41 = (0.5f * float(fVslider21));
		float fSlow42 = (fConst8 * float(fVslider22));
		float fSlow43 = (fConst8 * float(fVslider23));
		float fSlow44 = (fSlow34 + fSlow5);
		for (int i0 = 0; (i0 < count); i0 = (i0 + 1)) {
			fRec5[0] = (fSlow0 + (fConst9 * fRec5[1]));
			float fTemp0 = std::max<float>(20.0f, fRec5[0]);
			fRec7[0] = (fSlow2 + (fRec7[1] - std::floor((fSlow2 + fRec7[1]))));
			float fTemp1 = std::tan((fConst7 * std::max<float>(20.0f, std::min<float>(20000.0f, (fTemp0 + (fSlow1 * (ftbl0SynthesizerSIG0[int((65536.0f * fRec7[0]))] * std::min<float>((18000.0f - fTemp0), (fTemp0 + -50.0f)))))))));
			float fTemp2 = (1.0f / fTemp1);
			float fTemp3 = (1.0f - fTemp2);
			fVec1[0] = fSlow3;
			fRec10[0] = (fSlow8 + (fConst9 * fRec10[1]));
			fRec11[0] = (fSlow10 + (fConst9 * fRec11[1]));
			fRec12[0] = (fSlow12 + (fConst9 * fRec12[1]));
			fRec13[0] = (fSlow14 + (fConst9 * fRec13[1]));
			fRec14[0] = (fSlow16 + (fConst9 * fRec14[1]));
			fRec15[0] = (fSlow18 + (fConst9 * fRec15[1]));
			fRec16[0] = (fSlow20 + (fConst9 * fRec16[1]));
			fRec17[0] = (fSlow22 + (fConst9 * fRec17[1]));
			fRec18[0] = (fSlow24 + (fConst9 * fRec18[1]));
			fRec19[0] = (fSlow26 + (fConst9 * fRec19[1]));
			fRec20[0] = (fSlow28 + (fConst9 * fRec20[1]));
			fRec21[0] = (fSlow29 + (fConst9 * fRec21[1]));
			fRec23[0] = (fSlow31 + (fConst9 * fRec23[1]));
			float fTemp4 = (fRec22[1] + (fConst10 * fRec23[0]));
			fRec22[0] = (fTemp4 - std::floor(fTemp4));
			fRec24[0] = (fSlow33 + (fConst9 * fRec24[1]));
			float fTemp5 = (((fSlow7 * fRec10[0]) + ((fSlow9 * fRec11[0]) + ((fSlow11 * fRec12[0]) + ((fSlow13 * fRec13[0]) + ((fSlow15 * fRec14[0]) + ((fSlow17 * fRec15[0]) + ((fSlow19 * fRec16[0]) + ((fSlow21 * fRec17[0]) + ((fSlow23 * fRec18[0]) + ((fSlow25 * fRec19[0]) + ((fSlow27 * fRec20[0]) + ((fRec21[0] + (fSlow30 * ftbl0SynthesizerSIG0[int((65536.0f * fRec22[0]))])) + (fSlow32 * fRec24[0]))))))))))))) + -69.0f);
			float fTemp6 = std::max<float>(1.1920929e-07f, std::fabs((440.0f * std::pow(2.0f, (0.0833333358f * (fSlow5 + (fTemp5 - fSlow34)))))));
			float fTemp7 = (fRec8[1] + (fConst10 * fTemp6));
			float fTemp8 = (fTemp7 + -1.0f);
			int iTemp9 = (fTemp8 < 0.0f);
			fRec8[0] = (iTemp9 ? fTemp7 : fTemp8);
			float fThen1 = (fTemp7 + (fTemp8 * (1.0f - (fConst0 / fTemp6))));
			float fRec9 = (iTemp9 ? fTemp7 : fThen1);
			float fTemp10 = std::max<float>(1.1920929e-07f, std::fabs((440.0f * std::pow(2.0f, (0.0833333358f * (fSlow5 + fTemp5))))));
			float fTemp11 = (fConst10 * fTemp10);
			float fTemp12 = (fRec25[1] + fTemp11);
			float fTemp13 = (fTemp12 + -1.0f);
			int iTemp14 = (fTemp13 < 0.0f);
			fRec25[0] = (iTemp14 ? fTemp12 : fTemp13);
			float fThen3 = (fTemp11 + (fRec25[1] + (fTemp13 * (1.0f - (fConst0 / fTemp10)))));
			float fRec26 = (iTemp14 ? fTemp12 : fThen3);
			fRec27[0] = (fSlow3 + (fRec27[1] * float((fVec1[1] >= fSlow3))));
			iRec28[0] = (iSlow40 * (iRec28[1] + 1));
			float fTemp15 = std::max<float>(0.0f, (std::min<float>((fSlow36 * fRec27[0]), std::max<float>(((fSlow38 * (fSlow35 - fRec27[0])) + 1.0f), fSlow37)) * (1.0f - (fSlow39 * float(iRec28[0])))));
			float fTemp16 = (fSlow4 * ((0.0f - (2.0f * (1.0f - (fRec9 + fRec26)))) * fTemp15));
			fVec2[0] = fTemp16;
			float fTemp17 = (fTemp2 + 1.0f);
			fRec4[0] = (0.0f - (((fRec4[1] * fTemp3) - (fTemp16 + fVec2[1])) / fTemp17));
			float fTemp18 = (((fTemp2 + -1.0f) / fTemp1) + 1.0f);
			float fTemp19 = (1.0f - (1.0f / Synthesizer_faustpower2_f(fTemp1)));
			float fTemp20 = (((fTemp2 + 1.0f) / fTemp1) + 1.0f);
			fRec3[0] = (fRec4[0] - (((fRec3[2] * fTemp18) + (2.0f * (fRec3[1] * fTemp19))) / fTemp20));
			float fTemp21 = ((fRec3[2] + (fRec3[0] + (2.0f * fRec3[1]))) / fTemp20);
			fVec3[0] = fTemp21;
			fRec2[0] = (0.0f - (fConst5 * ((fConst6 * fRec2[1]) - (fTemp21 + fVec3[1]))));
			fRec1[0] = (fRec2[0] - (fConst4 * ((fConst11 * fRec1[2]) + (fConst12 * fRec1[1]))));
			fRec0[0] = ((fConst4 * (fRec1[2] + (fRec1[0] + (2.0f * fRec1[1])))) - (fConst3 * ((fConst13 * fRec0[2]) + (fConst12 * fRec0[1]))));
			fRec30[0] = (fSlow42 + (fConst9 * fRec30[1]));
			float fTemp22 = (fRec29[1] + (fConst10 * fRec30[0]));
			fRec29[0] = (fTemp22 - std::floor(fTemp22));
			float fTemp23 = std::min<float>(1.0f, std::max<float>(0.0f, ((fSlow41 * (ftbl0SynthesizerSIG0[int((65536.0f * fRec29[0]))] + -1.0f)) + 1.0f)));
			fRec31[0] = (fSlow43 + (fConst9 * fRec31[1]));
			float fTemp24 = std::pow(10.0f, (0.0500000007f * fRec31[0]));
			output0[i0] = FAUSTFLOAT((fConst3 * (((fRec0[2] + (fRec0[0] + (2.0f * fRec0[1]))) * fTemp23) * fTemp24)));
			float fTemp25 = std::max<float>(1.1920929e-07f, std::fabs((440.0f * std::pow(2.0f, (0.0833333358f * (fSlow44 + fTemp5))))));
			float fTemp26 = (fConst10 * fTemp25);
			float fTemp27 = (fRec37[1] + fTemp26);
			float fTemp28 = (fTemp27 + -1.0f);
			int iTemp29 = (fTemp28 < 0.0f);
			fRec37[0] = (iTemp29 ? fTemp27 : fTemp28);
			float fThen5 = (fRec37[1] + (fTemp26 + (fTemp28 * (1.0f - (fConst0 / fTemp25)))));
			float fRec38 = (iTemp29 ? fTemp27 : fThen5);
			float fTemp30 = (fSlow4 * (fTemp15 * (0.0f - (2.0f * (1.0f - (fRec26 + fRec38))))));
			fVec4[0] = fTemp30;
			fRec36[0] = (0.0f - (((fTemp3 * fRec36[1]) - (fTemp30 + fVec4[1])) / fTemp17));
			fRec35[0] = (fRec36[0] - (((fTemp18 * fRec35[2]) + (2.0f * (fTemp19 * fRec35[1]))) / fTemp20));
			float fTemp31 = ((fRec35[2] + (fRec35[0] + (2.0f * fRec35[1]))) / fTemp20);
			fVec5[0] = fTemp31;
			fRec34[0] = (0.0f - (fConst5 * ((fConst6 * fRec34[1]) - (fTemp31 + fVec5[1]))));
			fRec33[0] = (fRec34[0] - (fConst4 * ((fConst11 * fRec33[2]) + (fConst12 * fRec33[1]))));
			fRec32[0] = ((fConst4 * (fRec33[2] + (fRec33[0] + (2.0f * fRec33[1])))) - (fConst3 * ((fConst13 * fRec32[2]) + (fConst12 * fRec32[1]))));
			output1[i0] = FAUSTFLOAT((fConst3 * ((fTemp23 * fTemp24) * (fRec32[2] + (fRec32[0] + (2.0f * fRec32[1]))))));
			fRec5[1] = fRec5[0];
			fRec7[1] = fRec7[0];
			fVec1[1] = fVec1[0];
			fRec10[1] = fRec10[0];
			fRec11[1] = fRec11[0];
			fRec12[1] = fRec12[0];
			fRec13[1] = fRec13[0];
			fRec14[1] = fRec14[0];
			fRec15[1] = fRec15[0];
			fRec16[1] = fRec16[0];
			fRec17[1] = fRec17[0];
			fRec18[1] = fRec18[0];
			fRec19[1] = fRec19[0];
			fRec20[1] = fRec20[0];
			fRec21[1] = fRec21[0];
			fRec23[1] = fRec23[0];
			fRec22[1] = fRec22[0];
			fRec24[1] = fRec24[0];
			fRec8[1] = fRec8[0];
			fRec25[1] = fRec25[0];
			fRec27[1] = fRec27[0];
			iRec28[1] = iRec28[0];
			fVec2[1] = fVec2[0];
			fRec4[1] = fRec4[0];
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			fVec3[1] = fVec3[0];
			fRec2[1] = fRec2[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			fRec30[1] = fRec30[0];
			fRec29[1] = fRec29[0];
			fRec31[1] = fRec31[0];
			fRec37[1] = fRec37[0];
			fVec4[1] = fVec4[0];
			fRec36[1] = fRec36[0];
			fRec35[2] = fRec35[1];
			fRec35[1] = fRec35[0];
			fVec5[1] = fVec5[0];
			fRec34[1] = fRec34[0];
			fRec33[2] = fRec33[1];
			fRec33[1] = fRec33[0];
			fRec32[2] = fRec32[1];
			fRec32[1] = fRec32[0];
		}
	}

};

#endif
