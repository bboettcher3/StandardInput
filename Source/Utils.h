#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>

namespace Utils {
static constexpr int PADDING = 5;
static constexpr int ROUNDED_AMOUNT = 5;
static constexpr int BG_COLOUR = 0xffb7b7b7;

enum PitchClass { NONE = -1, C, Cs, D, Ds, E, F, Fs, G, Gs, A, As, B, NUM_PITCH_CLASSES };
static std::array<juce::String, NUM_PITCH_CLASSES> PITCH_CLASS_NAMES = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

enum InputTypeFlags {
  PITCH = 1,
  RHYTHM = 2,
  VELOCITY = 4,
  NUM_INPUT_TYPES = 3
};

// const PitchKey scaleNavPitchKeys[15] = {{87, Cs}, {69, Ds}, {84, Fs}, {89, Gs}, {85, As}, {79, Cs}, {65, C}, {83, D},
//                                        {68, E},  {70, F},  {71, G},  {72, A},  {74, B},  {75, C},  {76, D}};

template <typename CompType, typename CompAttachment>
class AttachedComponent {
 public:
  AttachedComponent<CompType, CompAttachment>(juce::RangedAudioParameter& param, juce::Component& parent,
                                              std::function<void(CompType&)> init = nullptr) {
    attachment.reset(new CompAttachment(param, component));
    parent.addAndMakeVisible(component);
    if (init != nullptr) init(component);
    attachment->sendInitialUpdate();
  }
  CompType component;

 private:
  std::unique_ptr<CompAttachment> attachment;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AttachedComponent)
};

}  // namespace Utils