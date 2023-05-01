#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include "../DSP/MouseSignals.h"

//==============================================================================
class MouseComponent : public juce::AnimatedAppComponent, public juce::KeyListener {
 public:
  MouseComponent();
  ~MouseComponent();

  //==============================================================================
  void paint(juce::Graphics&) override;
  void resized() override;

  void setIsActive(bool active) { mIsActive = active; }

  void mouseMove(const juce::MouseEvent& e) override;
  void mouseDrag(const juce::MouseEvent& e) override;
  void mouseUp(const juce::MouseEvent& e) override;
  void mouseExit(const juce::MouseEvent& e) override;

  bool keyPressed(const juce::KeyPress& key, juce::Component* originatingComponent) override;


  void update() override;

 private:
   // Bookkeeping
  bool mIsActive = false;
  juce::Point<float> mMousePosition;
  juce::MouseInputSource* mMouse = nullptr;
  MouseSignals mMouseSigs;

  // Rectangles updated on resized()
  juce::Rectangle<int> mRectMouseVis;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MouseComponent)
};
