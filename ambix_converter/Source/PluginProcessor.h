/*
  ==============================================================================

   This file is part of the ambix Ambisonic plug-in suite.
   Copyright (c) 2013/2014 - Matthias Kronlachner
   www.matthiaskronlachner.com
   
   Permission is granted to use this software under the terms of:
   the GPL v2 (or any later version)

   Details of these licenses can be found at: www.gnu.org/licenses

   ambix is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  ==============================================================================
*/

#ifndef __PLUGINPROCESSOR_H_9173E00A__
#define __PLUGINPROCESSOR_H_9173E00A__

#include "JuceHeader.h"


//==============================================================================
/**
*/
class Ambix_converterAudioProcessor  : public AudioProcessor,
                                       public ChangeBroadcaster
{
public:
    //==============================================================================
    Ambix_converterAudioProcessor();
    ~Ambix_converterAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();

    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);

    //==============================================================================
    AudioProcessorEditor* createEditor();
    bool hasEditor() const;

    //==============================================================================
    const String getName() const;

    int getNumParameters();

    float getParameter (int index);
    void setParameter (int index, float newValue);

    const String getParameterName (int index);
    const String getParameterText (int index);

    const String getInputChannelName (int channelIndex) const;
    const String getOutputChannelName (int channelIndex) const;
    bool isInputChannelStereoPair (int index) const;
    bool isOutputChannelStereoPair (int index) const;

    bool acceptsMidi() const;
    bool producesMidi() const;
    bool silenceInProducesSilenceOut() const;
    double getTailLengthSeconds() const;

    enum Parameters
	{
		InSeqParam,
        OutSeqParam,
        InNormParam,
		OutNormParam,
        FlipCsParam,
        FlipParam,
        FlopParam,
        FlapParam,
        In2DParam,
        Out2DParam,
		totalNumParams
	};
    
    /*
    // for later.... mixed order
     InHOrderParam,
     OutHOrderParam,
     InVOrderParam,
     OutVOrderParam,
     */
    
    //==============================================================================
    int getNumPrograms();
    int getCurrentProgram();
    void setCurrentProgram (int index);
    const String getProgramName (int index);
    void changeProgramName (int index, const String& newName);

    //==============================================================================
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);

    unsigned int active_preset; // for gui...
    
    String box_presets_text; // for save state...
    
private:
    void setNormalizationScheme();
    
    
    void setChannelSequence();
    
    AudioSampleBuffer output_buffer;
    const unsigned int* in_ch_seq;
    const unsigned int* out_ch_seq;
    
    const unsigned int* in_2d_ch_seq;
    const unsigned int* out_2d_ch_seq;
    
    const float* in_ch_norm; // holds normalization conversion array
    
    const int* acn_cs; // holds condon-shortley conversion map
    
    float in_seq_param; // channel sequence acn, fuma, sid
    float out_seq_param;
    float in_norm_param;
    float out_norm_param;
    
    bool flip_cs_phase; // flip condon-shortley phase -> apply (-1)^m to output channels
    
    bool flip_param; // mirror left-right
    bool flop_param; // mirror front-back
    bool flap_param; // mirror ceiling-floor
    
    bool in_2d; // input is 2d ambisonics (fill with empty channels)
    bool out_2d; // output is 2d ambisonics (channels will be thrown away)
    
    bool ch_norm_flat;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Ambix_converterAudioProcessor)
};

#endif  // __PLUGINPROCESSOR_H_9173E00A__
