/*
  ==============================================================================

    MouseSignals.h
    Created: 25 Mar 2023 12:11:35pm
    Author:  brady

  ==============================================================================
*/

#pragma once

#include <juce_core/juce_core.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_basics/juce_audio_basics.h>

class MouseSignals {
 public:
  MouseSignals();
  ~MouseSignals() {}

  /* class Signal {
    public:
     Signal(juce::String name, int midiCC);
     ~Signal();

     juce::String name;
     int midiCC;
     bool sendMidi = false;
     bool sendOsc = false;
     bool sendMapper = false;
   }; */

  juce::MidiBuffer updatePosition(float x, float y);
  juce::MidiBuffer updatePressure(float pressure);

  // MIDI CC 102-119 are undefined, so we'll use them
  static constexpr int MIDI_CC_POS = 102;
  static constexpr int MIDI_CC_POS_X = 103;
  static constexpr int MIDI_CC_ANGLE = 104;
  static constexpr int MIDI_CC_SPEED = 105;
  static constexpr int MIDI_CC_SPEED_X = 106;
  static constexpr int MIDI_CC_SPEED_Y = 107;
  static constexpr int MIDI_CC_PRESSURE = 108;

  juce::Point<float> getPosition() { return mPos; }
  float getMoveAngle() { return mMoveAngle; }
  float getSpeed() { return mSpeed; }
  float getSpeedX() { return mSpeedX; }
  float getSpeedY() { return mSpeedY; }
  float getPressure() { return mPressure; }

 private:
  // Position-based signals
  juce::Point<float> mPos;         // Position on the screen
  float mMoveAngle;                // Movement angle in radians
  float mSpeedX, mSpeedY, mSpeed;  // Speed in each direction and total
  float mPressure;                 // Pen pressure
  // Misc. signals
  // clicks, scrolls, etc.
};