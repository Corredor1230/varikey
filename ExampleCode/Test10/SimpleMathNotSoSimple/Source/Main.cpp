/*
  ==============================================================================

    This file contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include <JuceHeader.h>

#include <faust/misc.h>
#include <faust/gui/MapUI.h>
#include <faust/dsp/dsp.h>
#include <faust/dsp/dsp-bench.h>

#ifdef BENCH_SAMPLE_RATE
#undef BENCH_SAMPLE_RATE
#endif
#define BENCH_SAMPLE_RATE 48000
#define BENCH_BUFFER_SIZE 512
#define BENCH_DURATION_IN_SEC 10
#define RANDOM_CONTROL true
#define LOG_TRACE true

#include "osc1.h"
#include "osc2.h"
#include "osc3.h"
#include "osc4.h"
#include "osc5.h"
#include "osc6.h"
#include "osc7.h"


using namespace std;
using namespace juce;
using namespace faust;

//==============================================================================
int main (int argc, char* argv[])
{
    vector<dsp*> dsps;
    
    dsps.push_back(new osc1());
    dsps.push_back(new osc2());
    dsps.push_back(new osc3());
    dsps.push_back(new osc4());
    dsps.push_back(new osc5());
    dsps.push_back(new osc6());
    dsps.push_back(new osc7());
    
    string sep = "===========================================";
    {
        MY_Meta data;
        dsps[0]->metadata(&data);
        cout << sep << endl;
        cout << "Starting benchmark" << endl;
        cout << "Compilation Options" << data["compile_options"] << endl;
    }
    cout << sep << endl;
    for (dsp* dsp : dsps) {
        MY_Meta data;
        dsp->metadata(&data);
        dsp->init(BENCH_SAMPLE_RATE);
        cout << endl << "Benchmarking " << data["name"] << endl;
        
        // Wraps it with a 'measure_dsp' decorator
                //   dsp - the dsp to be measured.
                //   buffer_size - the buffer size used when calling 'computeAll'
                //   duration_in_sec - the wanted duration used in 'computeAll'
                //   trace - whether to log the trace
                //   control - whether to activate random changes of all control values at each cycle
        measure_dsp mes(dsp,
                        BENCH_BUFFER_SIZE,
                        BENCH_DURATION_IN_SEC,
                        LOG_TRACE,
                        RANDOM_CONTROL);
        // Measure the CPU use
        mes.measure();
        
        cout << "Results of: " << data["name"] << endl;
        cout << "Type: " << data["oscType"] << endl;
        cout << "Throughput: " << mes.getStats() << " CPU MB/s" << endl;
        cout << "CPU Load: " << mes.getCPULoad() * 100 << " %" << endl << endl;
        
        cout << sep << endl;
    }
    
    return 0;
}
