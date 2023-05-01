/*
  ==============================================================================

    MouseSignals.cpp
    Created: 25 Mar 2023 12:11:35pm
    Author:  brady

  ==============================================================================
*/

#include "MouseSignals.h"
#include <cmath>

MouseSignals::MouseSignals() : mPos(0, 0) {}

juce::MidiBuffer MouseSignals::updatePosition(float x, float y) {
  juce::MidiBuffer buffer;

  // Update movement angle
  mMoveAngle = std::atan2f(x - mPos.x, mPos.y - y);
  // buffer.addEvent(juce::MidiMessage::controllerEvent(1, MIDI_CC_ANGLE, mMoveAngle / juce::MathConstants<float>::twoPi), 0);

  // Update speed
  mSpeed = std::sqrtf(std::powf(mPos.x + x, 2) + std::powf(mPos.y + y, 2));

  // Finally update the position
  mPos.x = x;
  mPos.y = y;

  return buffer;
}

juce::MidiBuffer MouseSignals::updatePressure(float pressure) {
  juce::MidiBuffer buffer;

  mPressure = pressure;

  buffer.addEvent(juce::MidiMessage::controllerEvent(1, MIDI_CC_PRESSURE, mPressure * 127.0f), 0);

  return buffer;
}