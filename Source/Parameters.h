/*
  ==============================================================================

    Parameters.h
    Created: 10 Aug 2021 6:27:45pm
    Author:  brady

  ==============================================================================
*/

#pragma once

#include <juce_core/juce_core.h>
#include <juce_dsp/juce_dsp.h>
#include <juce_audio_processors/juce_audio_processors.h>

#include "Utils.h"

namespace ParamIDs {
static juce::String bpm{"bpm"};
static juce::String loopLength{"loopLength"};
}  // namespace ParamIDs

namespace ParamRanges {
static juce::NormalisableRange<float> BPM(0.01f, 300.0f, 0.1f);
static juce::NormalisableRange<float> LOOP_LENGTH(0.01f, 32.0f, 0.1f);
}  // namespace ParamRanges

namespace ParamDefaults {
static double BPM = 120.0;
static double LOOP_LENGTH = 4.0; // In bars
}  // namespace ParamDefaults

struct ParamHelper {
  static juce::String getParamID(juce::AudioProcessorParameter* param) {
    if (auto paramWithID = dynamic_cast<juce::AudioProcessorParameterWithID*>(param)) return paramWithID->paramID;

    return param->getName(50);
  }
  // Utility function to avoid ugly dereferencing code before sending norm value
  // to host
  static void setParam(juce::AudioParameterFloat* param, float newValue) { *param = newValue; }
  static void setParam(juce::AudioParameterInt* param, int newValue) { *param = newValue; }
  static void setParam(juce::AudioParameterBool* param, bool newValue) { *param = newValue; }
  static void setParam(juce::AudioParameterChoice* param, int newValue) { *param = newValue; }
};

/**
 * The current transport settings (bpm, loop length, etc.)
 */
class ParamTransport {
 public:
  ParamTransport() {}
  ~ParamTransport() {}

  void addParams(juce::AudioProcessor& p);

  void addListener(juce::AudioProcessorParameter::Listener* listener) {
    bpm->addListener(listener);
    loopLength->addListener(listener);
  }
  void removeListener(juce::AudioProcessorParameter::Listener* listener) {
    bpm->removeListener(listener);
    loopLength->removeListener(listener);
  }

  void resetParams(bool fullClear = true) {
    ParamHelper::setParam(bpm, ParamDefaults::BPM);
    ParamHelper::setParam(loopLength, ParamDefaults::LOOP_LENGTH);
  }

  juce::AudioParameterFloat* bpm;
  juce::AudioParameterFloat* loopLength;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ParamTransport)
};

/**
 * A representation of the last UI settings to restore it when loading the
 * editor. The Synth owns this and used to allow state to be saved properly as
 * the UI is open and closed.
 */
struct ParamUI {
  ParamUI() = default;

  // Get it from the plugin state
  // will only set xml-able items (floats/int/strings)
  void setXml(juce::XmlElement* xml) {
    if (xml != nullptr) {
      inputPitch = xml->getBoolAttribute("inputPitch");
      inputRhythm = xml->getBoolAttribute("inputRhythm");
      inputVelocity = xml->getBoolAttribute("inputVelocity");
      pianoRollVertScale = xml->getDoubleAttribute("pianoRollVertScale");
    }
  }

  // Build the XML representation to save in plugin state.
  juce::XmlElement* getXml() {
    juce::XmlElement* xml = new juce::XmlElement("ParamUI");
    xml->setAttribute("inputPitch", inputPitch);
    xml->setAttribute("inputRhythm", inputRhythm);
    xml->setAttribute("inputVelocity", inputVelocity);
    xml->setAttribute("pianoRollVertScale", pianoRollVertScale);
    return xml;
  }

  bool inputPitch = false;
  bool inputRhythm = false;
  bool inputVelocity = false;
  double pianoRollVertScale = 1.0f;
};

typedef struct Parameters {
  ParamUI ui;
  ParamTransport transport;
} Parameters;