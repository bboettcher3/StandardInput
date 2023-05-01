#include "LooperComponent.h"

//==============================================================================
LooperComponent::LooperComponent(ParamUI& paramUI) : mParamUI(paramUI), mBtnPitch("pitch"), mBtnRhythm("rhythm"), mBtnVelocity("velocity") {
  mBtnPitch.setColour(juce::TextButton::buttonColourId, juce::Colour(0xffcccccc));
  mBtnPitch.setColour(juce::TextButton::buttonOnColourId, juce::Colours::black);
  mBtnPitch.setColour(juce::TextButton::textColourOffId, juce::Colours::black);
  mBtnPitch.setColour(juce::TextButton::textColourOnId, juce::Colours::white);
  mBtnPitch.setToggleState(mParamUI.inputPitch, juce::dontSendNotification);
  mBtnPitch.onClick = [this]() {
    mBtnPitch.setToggleState(!mBtnPitch.getToggleState(), juce::dontSendNotification);
    mParamUI.inputPitch = mBtnPitch.getToggleState();
  };
  addAndMakeVisible(mBtnPitch);
  mBtnRhythm.setColour(juce::TextButton::buttonColourId, juce::Colour(0xffcccccc));
  mBtnRhythm.setColour(juce::TextButton::buttonOnColourId, juce::Colours::black);
  mBtnRhythm.setColour(juce::TextButton::textColourOffId, juce::Colours::black);
  mBtnRhythm.setColour(juce::TextButton::textColourOnId, juce::Colours::white);
  mBtnRhythm.setToggleState(mParamUI.inputRhythm, juce::dontSendNotification);
  mBtnRhythm.onClick = [this]() {
    mBtnRhythm.setToggleState(!mBtnRhythm.getToggleState(), juce::dontSendNotification);
    mParamUI.inputRhythm = mBtnRhythm.getToggleState();
  };
  addAndMakeVisible(mBtnRhythm);
  mBtnVelocity.setColour(juce::TextButton::buttonColourId, juce::Colour(0xffcccccc));
  mBtnVelocity.setColour(juce::TextButton::buttonOnColourId, juce::Colours::black);
  mBtnVelocity.setColour(juce::TextButton::textColourOffId, juce::Colours::black);
  mBtnVelocity.setColour(juce::TextButton::textColourOnId, juce::Colours::white);
  mBtnVelocity.setToggleState(mParamUI.inputVelocity, juce::dontSendNotification);
  mBtnVelocity.onClick = [this]() {
    mBtnVelocity.setToggleState(!mBtnVelocity.getToggleState(), juce::dontSendNotification);
    mParamUI.inputVelocity = mBtnVelocity.getToggleState();
  };
  addAndMakeVisible(mBtnVelocity);
}

LooperComponent::~LooperComponent() {}

//==============================================================================
void LooperComponent::paint(juce::Graphics& g) {
  // Draw line after input type buttons
  g.setColour(juce::Colours::black);
  int btnBottom = mBtnPitch.getBottom() + Utils::PADDING;
  g.drawLine(0, btnBottom, getWidth(), btnBottom, 2);

  // Draw piano roll
  int keyY = mRectPianoRoll.getBottom();
  int keyHeight = mRectPianoRoll.getHeight() / (mParamUI.pianoRollVertScale * NUM_DEFAULT_PIANO_KEYS);
  int pitch = Utils::C;
  juce::Rectangle<int> pianoRoll = mRectPianoRoll;
  while (pianoRoll.getHeight() >= keyHeight) {
    juce::Rectangle<int> keyRect = pianoRoll.removeFromBottom(keyHeight);
    g.setColour(isBlackKey((Utils::PitchClass)(pitch % 12)) ? juce::Colours::black : juce::Colours::white);
    g.fillRect(keyRect);
    g.setColour(juce::Colours::black);
    g.drawLine(keyRect.getX(), keyRect.getBottom(), keyRect.getRight(), keyRect.getBottom());
    pitch++;
  }

#ifdef OVERLAY_LABELS
  g.fillAll(juce::Colours::darkgrey);

  g.setColour(juce::Colours::white);
  g.setFont(15.0f);
  g.drawFittedText("Looper", getLocalBounds(), juce::Justification::centred, 1);
#endif
  g.setColour(juce::Colours::black);
  g.drawRect(getLocalBounds());
}

void LooperComponent::resized() { 
  juce::Rectangle<int> r = getLocalBounds().reduced(Utils::PADDING); 

  juce::Rectangle<int> inputTypesPanel = r.removeFromTop(30);
  int btnWidth = (inputTypesPanel.getWidth() - (Utils::PADDING * (Utils::NUM_INPUT_TYPES - 1))) / Utils::NUM_INPUT_TYPES;
  mBtnPitch.setBounds(inputTypesPanel.removeFromLeft(btnWidth));
  inputTypesPanel.removeFromLeft(Utils::PADDING);
  mBtnRhythm.setBounds(inputTypesPanel.removeFromLeft(btnWidth));
  inputTypesPanel.removeFromLeft(Utils::PADDING);
  mBtnVelocity.setBounds(inputTypesPanel);
  r.removeFromTop(Utils::PADDING + 2); // Bottom separator and line thickness

  mRectPianoRoll = r.removeFromLeft(WIDTH_PIANO_ROLL);
}
