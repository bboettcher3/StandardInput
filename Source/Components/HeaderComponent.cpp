#include "HeaderComponent.h"
#include "BinaryData.h"
#include "../Utils.h"

//==============================================================================
HeaderComponent::HeaderComponent(AudioPluginAudioProcessor& processor)
    : mProcessor(processor), 
      mBtnRecord("record", juce::DrawableButton::ImageOnButtonBackground),
      mBtnPlay("play", juce::DrawableButton::ImageOnButtonBackground),
      mBtnDub("dub", juce::DrawableButton::ImageOnButtonBackground) {
  std::unique_ptr<juce::Drawable> recSvg =
      juce::Drawable::createFromImageData(BinaryData::record_svg, BinaryData::record_svgSize);
  recSvg->replaceColour(juce::Colours::black, juce::Colours::white);
  mBtnRecord.setImages(recSvg.get());
  mBtnRecord.onClick = [this]() {};
  addAndMakeVisible(mBtnRecord);

  std::unique_ptr<juce::Drawable> playSvg = juce::Drawable::createFromImageData(BinaryData::play_svg, BinaryData::play_svgSize);
  playSvg->replaceColour(juce::Colours::black, juce::Colours::white);
  mBtnPlay.setImages(playSvg.get());
  mBtnPlay.onClick = [this]() { 
  };
  addAndMakeVisible(mBtnPlay);

  std::unique_ptr<juce::Drawable> dubSvg =
      juce::Drawable::createFromImageData(BinaryData::overdub_svg, BinaryData::overdub_svgSize);
  dubSvg->replaceColour(juce::Colours::black, juce::Colours::white);
  mBtnDub.setImages(dubSvg.get());
  mBtnPlay.onClick = [this]() {};
  addAndMakeVisible(mBtnDub);

  mSliderBpm = std::make_unique<Utils::AttachedComponent<juce::Slider, juce::SliderParameterAttachment> >(
      *mProcessor.params.transport.bpm, *this, [](juce::Slider& slider) {
        slider.setTextBoxStyle(juce::Slider::TextBoxRight, true, 0, 0);
        slider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
        slider.setTextValueSuffix(" bpm");
        slider.setRange(ParamRanges::BPM.start, ParamRanges::BPM.end, 0.1);
      });
  mSliderBpm->component.onValueChange = [this] { };

  mSliderLoopLength = std::make_unique<Utils::AttachedComponent<juce::Slider, juce::SliderParameterAttachment> >(
      *mProcessor.params.transport.loopLength, *this, [](juce::Slider& slider) {
        slider.setTextBoxStyle(juce::Slider::TextBoxRight, true, 0, 0);
        slider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
        slider.setTextValueSuffix(" bars");
        slider.setRange(ParamRanges::LOOP_LENGTH.start, ParamRanges::LOOP_LENGTH.end, 0.01);
      });
  mSliderLoopLength->component.onValueChange = [this] {};
}

HeaderComponent::~HeaderComponent() {}

//==============================================================================
void HeaderComponent::paint(juce::Graphics& g) {
  // Draw title
  g.setColour(juce::Colours::black);
  g.setFont(juce::Font(juce::String("monospace"), 35.0f, juce::Font::FontStyleFlags::bold));
  g.drawFittedText("std::input", mRectTitle, juce::Justification::centred, 1);


#ifdef OVERLAY_LABELS
  g.fillAll(juce::Colours::grey);

  g.setColour(juce::Colours::white);
  g.setFont(15.0f);
  g.drawFittedText("Header", getLocalBounds(), juce::Justification::centred, 1);
#endif
  g.setColour(juce::Colours::black);
  g.drawRect(getLocalBounds());
}

void HeaderComponent::resized() { 
  juce::Rectangle<int> r = getLocalBounds().reduced(Utils::PADDING);

  mRectTitle = r.removeFromLeft(TITLE_WIDTH * r.getWidth());
  mBtnPlay.setBounds(r.removeFromLeft(r.getHeight()));
  r.removeFromLeft(Utils::PADDING);
  mBtnRecord.setBounds(r.removeFromLeft(r.getHeight()));
  r.removeFromLeft(Utils::PADDING);
  mBtnDub.setBounds(r.removeFromLeft(r.getHeight()));
  r.removeFromLeft(Utils::PADDING);
  mSliderBpm->component.setBounds(r.removeFromLeft(80));
  r.removeFromLeft(Utils::PADDING);
  mSliderLoopLength->component.setBounds(r.removeFromLeft(60));
}
