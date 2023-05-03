#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "../Utils.h"
#include "../Parameters.h"
#include "../PluginProcessor.h"

//==============================================================================
class LooperComponent : public juce::Component {
 public:
  LooperComponent(AudioPluginAudioProcessor& processor);
  ~LooperComponent();

  //==============================================================================
  void paint(juce::Graphics&) override;
  void resized() override;

 private:
  static constexpr int HEIGHT_INPUT_TYPES = 30;
  static constexpr int HEIGHT_LOOP_BAR = 10;
  static constexpr int WIDTH_PIANO_ROLL = 50;
  static constexpr int NUM_DEFAULT_PIANO_KEYS = 24;
  static constexpr int DEFAULT_TIME_SIG_NUM= 4;
  static constexpr int DEFAULT_TIME_SIG_DENOM = 4;

  // Components
  juce::TextButton mBtnPitch;
  juce::TextButton mBtnRhythm;
  juce::TextButton mBtnVelocity;

  // Bookkeeping
  AudioPluginAudioProcessor& mProcessor;

  // Rectangles updated on resized()
  juce::Rectangle<int> mRectPianoRoll;
  juce::Rectangle<int> mRectTimeline;

  inline bool isBlackKey(Utils::PitchClass pitchClass) { return ((1 << (pitchClass)) & 0x054a) != 0; }

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LooperComponent)
};
