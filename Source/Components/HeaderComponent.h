#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

//==============================================================================
class HeaderComponent : public juce::Component {
 public:
  HeaderComponent();
  ~HeaderComponent();

  //==============================================================================
  void paint(juce::Graphics&) override;
  void resized() override;

 private:
  static constexpr float TITLE_WIDTH = 0.5f;

  // Components
  juce::DrawableButton mBtnRecord;

  // Rectangles updated when resize is called
  juce::Rectangle<int> mRectTitle;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HeaderComponent)
};
