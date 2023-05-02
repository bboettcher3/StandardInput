#include "HeaderComponent.h"
#include "BinaryData.h"
#include "../Utils.h"

//==============================================================================
HeaderComponent::HeaderComponent()
    : mBtnRecord("record", juce::DrawableButton::ImageOnButtonBackground),
      mBtnPlay("play", juce::DrawableButton::ImageOnButtonBackground),
      mBtnDub("dub", juce::DrawableButton::ImageOnButtonBackground) {
  std::unique_ptr<juce::Drawable> recSvg =
      juce::Drawable::createFromImageData(BinaryData::record_svg, BinaryData::record_svgSize);
  recSvg->replaceColour(juce::Colours::black, juce::Colours::white);
  mBtnRecord.setImages(recSvg.get());
  addAndMakeVisible(mBtnRecord);

  std::unique_ptr<juce::Drawable> playSvg = juce::Drawable::createFromImageData(BinaryData::play_svg, BinaryData::play_svgSize);
  playSvg->replaceColour(juce::Colours::black, juce::Colours::white);
  mBtnPlay.setImages(playSvg.get());
  addAndMakeVisible(mBtnPlay);

  std::unique_ptr<juce::Drawable> dubSvg =
      juce::Drawable::createFromImageData(BinaryData::overdub_svg, BinaryData::overdub_svgSize);
  dubSvg->replaceColour(juce::Colours::black, juce::Colours::white);
  mBtnDub.setImages(dubSvg.get());
  addAndMakeVisible(mBtnDub);

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
}
