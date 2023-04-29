#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

namespace Utils {
static constexpr int PADDING = 5;
static constexpr int C1 = 24;
static constexpr int NUM_DEFAULT_PITCH_KEYS = 19;

enum PitchClass { NONE = -1, C, Cs, D, Ds, E, F, Fs, G, Gs, A, As, B, COUNT };

typedef struct PitchKey {
  int keyCode;
  int midiNote;  // Should be relative to C1
};

const PitchKey DEFAULT_PITCH_KEYS[NUM_DEFAULT_PITCH_KEYS] = {
    {81, NONE},                    // Q
    {87, Cs},                      // W
    {69, Ds},                      // E
    {82, NONE},                    // R
    {84, Fs},                      // T
    {89, Gs},                      // Y
    {85, As},                      // U
    {73, NONE},                    // I
    {79, Cs + PitchClass::COUNT},  // O
    {80, NONE},                    // P
    {65, C},                       // A
    {83, D},                       // S
    {68, E},                       // D
    {70, F},                       // F
    {71, G},                       // G
    {72, A},                       // H
    {74, B},                       // J
    {75, C + PitchClass::COUNT},   // K
    {76, D + PitchClass::COUNT}    // L
};
//const PitchKey scaleNavPitchKeys[15] = {{87, Cs}, {69, Ds}, {84, Fs}, {89, Gs}, {85, As}, {79, Cs}, {65, C}, {83, D},
//                                       {68, E},  {70, F},  {71, G},  {72, A},  {74, B},  {75, C},  {76, D}};



typedef struct Key {
  Key(int keyCode) : keyCode(keyCode), isPressed(false) {}
  bool isPressed;
  int keyCode;
} Key;

}  // namespace Utils