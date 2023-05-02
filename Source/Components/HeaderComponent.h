#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "../PluginProcessor.h"

//==============================================================================
class HeaderComponent : public juce::Component {
 public:
  HeaderComponent(AudioPluginAudioProcessor& processor);
  ~HeaderComponent();

  //==============================================================================
  void paint(juce::Graphics&) override;
  void resized() override;

 private:
  static constexpr float TITLE_WIDTH = 0.5f;

  // Components
  juce::DrawableButton mBtnPlay;
  juce::DrawableButton mBtnRecord;
  juce::DrawableButton mBtnDub;
  std::unique_ptr<Utils::AttachedComponent<juce::Slider, juce::SliderParameterAttachment>> mSliderBpm;
  std::unique_ptr<Utils::AttachedComponent<juce::Slider, juce::SliderParameterAttachment>> mSliderLoopLength;

  // Bookkeeping
  AudioPluginAudioProcessor& mProcessor;

  // Rectangles updated when resize is called
  juce::Rectangle<int> mRectTitle;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(HeaderComponent)
};
