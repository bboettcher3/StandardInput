#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

namespace Utils {
static constexpr int PADDING = 5;
static constexpr int ROUNDED_AMOUNT = 5;

enum PitchClass { NONE = -1, C, Cs, D, Ds, E, F, Fs, G, Gs, A, As, B, COUNT };

// const PitchKey scaleNavPitchKeys[15] = {{87, Cs}, {69, Ds}, {84, Fs}, {89, Gs}, {85, As}, {79, Cs}, {65, C}, {83, D},
//                                        {68, E},  {70, F},  {71, G},  {72, A},  {74, B},  {75, C},  {76, D}};

}  // namespace Utils