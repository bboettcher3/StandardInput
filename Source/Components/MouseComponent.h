#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

//==============================================================================
class MouseComponent : public juce::Component {
 public:
  MouseComponent();
  ~MouseComponent();

  //==============================================================================
  void paint(juce::Graphics&) override;
  void resized() override;

 private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MouseComponent)
};
