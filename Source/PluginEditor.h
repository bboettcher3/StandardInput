#pragma once

#include "PluginProcessor.h"
#include "Components/HeaderComponent.h"
#include "Components/LooperComponent.h"
#include "Components/KeyboardComponent.h"
#include "Components/MouseComponent.h"

// If active, show component names instead of content
#define OVERLAY_LABELS

//==============================================================================
class AudioPluginAudioProcessorEditor : public juce::AudioProcessorEditor {
 public:
  explicit AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor&);
  ~AudioPluginAudioProcessorEditor() override;

  //==============================================================================
  void paint(juce::Graphics&) override;
  void resized() override;

 private:
  // This reference is provided as a quick way for your editor to
  // access the processor object that created it.
  AudioPluginAudioProcessor& processorRef;

  // Components
  HeaderComponent mHeader;
  LooperComponent mLooper;
  KeyboardComponent mKeyboard;
  MouseComponent mMouse;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginAudioProcessorEditor)
};
