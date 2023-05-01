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
  bool keyStateChanged(bool isKeyDown, juce::Component *originatingComponent) override;

 private:
  static constexpr float COL_STAGGER = 0.25f;
  static constexpr int NUM_KEYS_ROW_1 = 10; // Used for drawing keys
  static constexpr int NUM_PITCH_KEYS = 19;
  static constexpr int NUM_ROWS = 3;
  static constexpr int C1 = 24;
  static constexpr int NUM_DEFAULT_KEYS = 19;

  enum KeyType { PITCH, UNMAPPED };

  typedef struct Key {
    Key(char keyChar, int keyCode) : type(UNMAPPED), keyChar(keyChar), keyCode(keyCode) {}
    Key(char keyChar, int keyCode, int midiNote) : type(PITCH), keyChar(keyChar), keyCode(keyCode), midiNote(midiNote) {}
    bool isPressed = false;
    KeyType type;
    char keyChar;
    int keyCode;
    int midiNote = Utils::PitchClass::NONE;  // Should be relative to C1, only used for PITCH type Keys
    juce::Rectangle<int> rect;
  } Key;

  std::array<Key, NUM_DEFAULT_KEYS> mKeys = {
      Key('Q', 81),                                                    // Q
      Key('W', 87, Utils::PitchClass::Cs),                             // W
      Key('E', 69, Utils::PitchClass::Ds),                             // E
      Key('R', 82),                                                    // R
      Key('T', 84, Utils::PitchClass::Fs),                             // T
      Key('Y', 89, Utils::PitchClass::Gs),                             // Y
      Key('U', 85, Utils::PitchClass::As),                             // U
      Key('I', 73),                                                    // I
      Key('O', 79, Utils::PitchClass::Cs + Utils::NUM_PITCH_CLASSES),  // O
      Key('P', 80),                                                    // P
      Key('A', 65, Utils::PitchClass::C),                              // A
      Key('S', 83, Utils::PitchClass::D),                              // S
      Key('D', 68, Utils::PitchClass::E),                              // D
      Key('F', 70, Utils::PitchClass::F),                              // F
      Key('G', 71, Utils::PitchClass::G),                              // G
      Key('H', 72, Utils::PitchClass::A),                              // H
      Key('J', 74, Utils::PitchClass::B),                              // J
      Key('K', 75, Utils::PitchClass::C + Utils::NUM_PITCH_CLASSES),   // K
      Key('L', 76, Utils::PitchClass::D + Utils::NUM_PITCH_CLASSES)    // L
  };

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(KeyboardComponent)
};
