/*
  ==============================================================================

    Parameters.cpp
    Created: 10 Aug 2021 6:47:57pm
    Author:  brady

  ==============================================================================
*/

#include "Parameters.h"

void ParamTransport::addParams(juce::AudioProcessor& p) {
  p.addParameter(bpm = new juce::AudioParameterFloat(ParamIDs::bpm, "bpm", ParamRanges::BPM, ParamDefaults::BPM));
  p.addParameter(loopLength = new juce::AudioParameterFloat(ParamIDs::loopLength, "loop length", ParamRanges::LOOP_LENGTH, ParamDefaults::LOOP_LENGTH));
}