#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "../Utils.h"

//==============================================================================
class KeyboardComponent : public juce::Component, public juce::KeyListener {
 public:
  KeyboardComponent();
  ~KeyboardComponent();

  //==============================================================================
  void paint(juce::Graphics&) override;
  void resized() override;

  bool keyPressed(const juce::KeyPress &key, juce::Component *originatingComponent) override;

 private:
  static constexpr float KEY_SIZE = 1.0f / 10.0f;
  static constexpr float COL_STAGGER = 0.25f;

  juce::Array<Utils::Key> mKeys;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(KeyboardComponent)
};
