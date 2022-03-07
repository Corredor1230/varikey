/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

using namespace std;
using namespace juce;

//==============================================================================
NewProjectAudioProcessor::NewProjectAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
    , vts(*this, nullptr, "Params", buildParameters())
{
    vts.addParameterListener("freq", this);
    vts.addParameterListener("vFreq", this);
    vts.addParameterListener("vDepth", this);
    vts.addParameterListener("pWheel", this);
    vts.addParameterListener("detune", this);
    vts.addParameterListener("gain", this);
    vts.addParameterListener("gate", this);
    vts.addParameterListener("att", this);
    vts.addParameterListener("dec", this);
    vts.addParameterListener("sus", this);
    vts.addParameterListener("rel", this);
    vts.addParameterListener("tFreq", this);
    vts.addParameterListener("tDepth", this);
    vts.addParameterListener("cutoff", this);
    vts.addParameterListener("lfoF", this);
    vts.addParameterListener("lfoD", this);
    vts.addParameterListener("c", this);
    vts.addParameterListener("ces", this);
    vts.addParameterListener("d", this);
    vts.addParameterListener("des", this);
    vts.addParameterListener("e", this);
    vts.addParameterListener("f", this);
    vts.addParameterListener("fes", this);
    vts.addParameterListener("g", this);
    vts.addParameterListener("ges", this);
    vts.addParameterListener("a", this);
    vts.addParameterListener("as", this);
    vts.addParameterListener("b", this);
    vts.addParameterListener("offset", this);

    dsp.buildUserInterface(&ctrl);

    for (int i = 0; i < ctrl.getParamsCount(); i++) {
        DBG(ctrl.getParamAddress(i));
    }
}

NewProjectAudioProcessor::~NewProjectAudioProcessor()
{
}

AudioProcessorValueTreeState::ParameterLayout NewProjectAudioProcessor::buildParameters() {
    AudioProcessorValueTreeState::ParameterLayout layout;
    {
        
        {
            auto param = make_unique<AudioParameterBool>("gate","gate", true); 
            layout.add(move(param));
        }
        
        {
            auto param = make_unique<AudioParameterInt>("offset","offset", 0, 11, 0); 
            layout.add(move(param));
        }
        
        {   auto param = make_unique<AudioParameterFloat>("freq","freq", 50, 1000, 200); 
            layout.add(move(param));
        }
        
        {   auto param = make_unique<AudioParameterFloat>("vFreq","vFreq", 0, 20, 0); 
            layout.add(move(param));
        }
        
        {   auto param = make_unique<AudioParameterFloat>("vDepth","vDepth", 0, 1, 0); 
            layout.add(move(param));
        }
        
        {   auto param = make_unique<AudioParameterFloat>("pWheel","pWheel", -1, 1, 0); 
            layout.add(move(param));
        }
        
        {
            auto param = make_unique<AudioParameterFloat>("detune","detune", 0, 1, 0); 
            layout.add(move(param));
        }
        
        {
            auto param = make_unique<AudioParameterFloat>("gain","gain", -60, 0, -20); 
            layout.add(move(param));
        }
        
        {
            auto param = make_unique<AudioParameterFloat>("att","att", 10, 3000, 50); 
            layout.add(move(param));
        }
        
        {
            auto param = make_unique<AudioParameterFloat>("dec","dec", 10, 3000, 50); 
            layout.add(move(param));
        }
        
        {
            auto param = make_unique<AudioParameterFloat>("sus","sus", 0, 1, 0.5); 
            layout.add(move(param));
        }
      
        {
            auto param = make_unique<AudioParameterFloat>("rel","rel", 30, 5000, 200); 
            layout.add(move(param));
        }

        {
            auto param = make_unique<AudioParameterFloat>("tFreq","tFreq", 0, 20, 0); 
            layout.add(move(param));
        }
        
        {
            auto param = make_unique<AudioParameterFloat>("tDepth","tDepth", 0, 1, 0); 
            layout.add(move(param));
        }
        
        {
            auto param = make_unique<AudioParameterFloat>("cutoff", "cutoff", 50, 20000, 1000);
            layout.add(move(param));
        }

        {
            auto param = make_unique<AudioParameterFloat>("lfoF","lfoF", 0, 20, 0); 
            layout.add(move(param));
        }
        
        {
            auto param = make_unique<AudioParameterFloat>("lfoD","lfoD", 0, 1, 0); 
            layout.add(move(param));
        }
        
        {
            auto param = make_unique<AudioParameterFloat>("c","c", -1, 1, 0); 
            layout.add(move(param));
        }
        
        {
            auto param = make_unique<AudioParameterFloat>("ces","ces", -1, 1, 0); 
            layout.add(move(param));
        }
        
        {
            auto param = make_unique<AudioParameterFloat>("d","d", -1, 1, 0); 
            layout.add(move(param));
        }
        
        {
            auto param = make_unique<AudioParameterFloat>("des","des", -1, 1, 0); 
            layout.add(move(param));
        }
        
        {
            auto param = make_unique<AudioParameterFloat>("e","e", -1, 1, 0); 
            layout.add(move(param));
        }
        
        {
            auto param = make_unique<AudioParameterFloat>("f","f", -1, 1, 0); 
            layout.add(move(param));
        }
        
        {
            auto param = make_unique<AudioParameterFloat>("fes","fes", -1, 1, 0); 
            layout.add(move(param));
        }
        
        {
            auto param = make_unique<AudioParameterFloat>("g","g", -1, 1, 0); 
            layout.add(move(param));
        }
        
        {
            auto param = make_unique<AudioParameterFloat>("ges","ges", -1, 1, 0); 
            layout.add(move(param));
        }

        {
            auto param = make_unique<AudioParameterFloat>("a", "a", -1, 1, 0);
            layout.add(move(param));
        }

        {
            auto param = make_unique<AudioParameterFloat>("as", "as", -1, 1, 0);
            layout.add(move(param));
        }

        {
            auto param = make_unique<AudioParameterFloat>("b", "b", -1, 1, 0);
            layout.add(move(param));
        }

        return layout;

    }

}

//==============================================================================
const juce::String NewProjectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool NewProjectAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool NewProjectAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool NewProjectAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double NewProjectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NewProjectAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int NewProjectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NewProjectAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String NewProjectAudioProcessor::getProgramName (int index)
{
    return {};
}

void NewProjectAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void NewProjectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    dsp.init(sampleRate);
}

void NewProjectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NewProjectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void NewProjectAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    int nSamples = buffer.getNumSamples();
    float** data = buffer.getArrayOfWritePointers();
    dsp.compute(nSamples, nullptr, data);
    
}

void NewProjectAudioProcessor::parameterChanged(const juce::String& paramID, float newValue) {
    
    DBG(paramID + String(newValue));
    
    if (paramID == "freq")
    {
        ctrl.setParamValue("/Synthesizer/Pitch/freq", newValue);
    }
    else if (paramID == "vFreq")
    {
        ctrl.setParamValue("/Synthesizer/Pitch/vFreq", newValue);

    }
    else if (paramID == "vDepth")
    {
        ctrl.setParamValue("/Synthesizer/Pitch/vDepth", newValue);

    }
    else if (paramID == "pWheel")
    {
        ctrl.setParamValue("/Synthesizer/Pitch/pWheel", newValue);

    }
    else if (paramID == "detune")
    {
        ctrl.setParamValue("/Synthesizer/Pitch/detune", newValue);

    }
    else if (paramID == "gain")
    {
        ctrl.setParamValue("/Synthesizer/Processing/Envelope/gain", newValue);

    }
    else if (paramID == "gate")
    {
        ctrl.setParamValue("/Synthesizer/Processing/gate", newValue);

    }
    else if (paramID == "att")
    {
        ctrl.setParamValue("/Synthesizer/Processing/Envelope/att", newValue);

    }
    else if (paramID == "dec")
    {
        ctrl.setParamValue("/Synthesizer/Processing/Envelope/dec", newValue);

    }
    else if (paramID == "sus")
    {
        ctrl.setParamValue("/Synthesizer/Processing/Envelope/sus", newValue);

    }
    else if (paramID == "rel")
    {
        ctrl.setParamValue("/Synthesizer/Processing/Envelope/rel", newValue);

    }
    else if (paramID == "tFreq")
    {
        ctrl.setParamValue("/Synthesizer/Processing/tFreq", newValue);

    }
    else if (paramID == "tDepth")
    {
        ctrl.setParamValue("/Synthesizer/Processing/tDepth", newValue);

    }
    else if (paramID == "cutoff")
    {
        ctrl.setParamValue("/Synthesizer/Processing/Filter/cutoff", newValue);

    }
    else if (paramID == "lfoF")
    {
        ctrl.setParamValue("/Synthesizer/Processing/Filter/lfoF", newValue);

    }
    else if (paramID == "lfoD")
    {
        ctrl.setParamValue("/Synthesizer/Processing/Filter/lfoD", newValue);

    }
    else if (paramID == "c")
    {
        ctrl.setParamValue("/Synthesizer/Tuning/Note Tuning/c", newValue);

    }
    else if (paramID == "ces")
    {
        ctrl.setParamValue("/Synthesizer/Tuning/Note Tuning/ces", newValue);

    }
    else if (paramID == "d")
    {
        ctrl.setParamValue("/Synthesizer/Tuning/Note Tuning/d", newValue);

    }
    else if (paramID == "des")
    {
        ctrl.setParamValue("/Synthesizer/Tuning/Note Tuning/des", newValue);

    }
    else if (paramID == "e")
    {
        ctrl.setParamValue("/Synthesizer/Tuning/Note Tuning/e", newValue);

    }
    else if (paramID == "f")
    {
        ctrl.setParamValue("/Synthesizer/Tuning/Note Tuning/f", newValue);

    }
    else if (paramID == "fes")
    {
        ctrl.setParamValue("/Synthesizer/Tuning/Note Tuning/fes", newValue);

    }
    else if (paramID == "g")
    {
        ctrl.setParamValue("/Synthesizer/Tuning/Note Tuning/g", newValue);

    }
    else if (paramID == "ges")
    {
        ctrl.setParamValue("/Synthesizer/Tuning/Note Tuning/ges", newValue);

    }
    else if (paramID == "a")
    {
        ctrl.setParamValue("/Synthesizer/Tuning/Note Tuning/a", newValue);

    }
    else if (paramID == "as")
    {
        ctrl.setParamValue("/Synthesizer/Tuning/Note Tuning/as", newValue);

    }
    else if (paramID == "b")
    {
        ctrl.setParamValue("/Synthesizer/Tuning/Note Tuning/b", newValue);

    }
    else if (paramID == "offset")
    {
        ctrl.setParamValue("/Synthesizer/Tuning/offset", newValue);

    }
    else
    {
    DBG("Parameter not found");

    }

}

//==============================================================================
bool NewProjectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* NewProjectAudioProcessor::createEditor()
{
    return new NewProjectAudioProcessorEditor (*this, vts);
}

//==============================================================================
void NewProjectAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    /*auto state = vts.copyState();
    unique_ptr<XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);*/
}

void NewProjectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    /*unique_ptr<XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
    if (xml.get() != nullptr) {
        vts.replaceState(ValueTree::fromXml(*xml));
    }*/
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NewProjectAudioProcessor();
}
