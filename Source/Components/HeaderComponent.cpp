#include "HeaderComponent.h"
#include "BinaryData.h"
#include "../Utils.h"

//==============================================================================
HeaderComponent::HeaderComponent(): mBtnRecord("record", juce::DrawableButton::ImageOnButtonBackground) {
  std::unique_ptr<juce::Drawable> recEmpty =
      juce::Drawable::createFromImageData(BinaryData::record_empty_svg, BinaryData::record_empty_svgSize);
  std::unique_ptr<juce::Drawable> recFilled =
      juce::Drawable::createFromImageData(BinaryData::record_filled_svg, BinaryData::record_filled_svgSize);
  mBtnRecord.setImages(recFilled.get(), recFilled.get(), recFilled.get(), recFilled.get(), recFilled.get(), recFilled.get(),
                       recFilled.get(), recFilled.get());
  addAndMakeVisible(mBtnRecord);

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
  juce::Rectangle<int> r = getLocalBounds();

  mRectTitle = r.removeFromLeft(TITLE_WIDTH * r.getWidth());
  juce::Rectangle<int> recordPanel = r;
  mBtnRecord.setBounds(recordPanel.withSizeKeepingCentre(recordPanel.getHeight(), recordPanel.getHeight()).reduced(Utils::PADDING));
}
