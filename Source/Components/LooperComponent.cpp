#include "LooperComponent.h"

//==============================================================================
LooperComponent::LooperComponent(AudioPluginAudioProcessor& processor)
    : mProcessor(processor), mBtnPitch("pitch"), mBtnRhythm("rhythm"), mBtnVelocity("velocity") {
  mBtnPitch.setColour(juce::TextButton::buttonColourId, juce::Colour(0xffcccccc));
  mBtnPitch.setColour(juce::TextButton::buttonOnColourId, juce::Colours::black);
  mBtnPitch.setColour(juce::TextButton::textColourOffId, juce::Colours::black);
  mBtnPitch.setColour(juce::TextButton::textColourOnId, juce::Colours::white);
  mBtnPitch.setToggleState(mProcessor.params.ui.inputPitch, juce::dontSendNotification);
  mBtnPitch.onClick = [this]() {
    mBtnPitch.setToggleState(!mBtnPitch.getToggleState(), juce::dontSendNotification);
    mProcessor.params.ui.inputPitch = mBtnPitch.getToggleState();
  };
  addAndMakeVisible(mBtnPitch);
  mBtnRhythm.setColour(juce::TextButton::buttonColourId, juce::Colour(0xffcccccc));
  mBtnRhythm.setColour(juce::TextButton::buttonOnColourId, juce::Colours::black);
  mBtnRhythm.setColour(juce::TextButton::textColourOffId, juce::Colours::black);
  mBtnRhythm.setColour(juce::TextButton::textColourOnId, juce::Colours::white);
  mBtnRhythm.setToggleState(mProcessor.params.ui.inputRhythm, juce::dontSendNotification);
  mBtnRhythm.onClick = [this]() {
    mBtnRhythm.setToggleState(!mBtnRhythm.getToggleState(), juce::dontSendNotification);
    mProcessor.params.ui.inputRhythm = mBtnRhythm.getToggleState();
  };
  addAndMakeVisible(mBtnRhythm);
  mBtnVelocity.setColour(juce::TextButton::buttonColourId, juce::Colour(0xffcccccc));
  mBtnVelocity.setColour(juce::TextButton::buttonOnColourId, juce::Colours::black);
  mBtnVelocity.setColour(juce::TextButton::textColourOffId, juce::Colours::black);
  mBtnVelocity.setColour(juce::TextButton::textColourOnId, juce::Colours::white);
  mBtnVelocity.setToggleState(mProcessor.params.ui.inputVelocity, juce::dontSendNotification);
  mBtnVelocity.onClick = [this]() {
    mBtnVelocity.setToggleState(!mBtnVelocity.getToggleState(), juce::dontSendNotification);
    mProcessor.params.ui.inputVelocity = mBtnVelocity.getToggleState();
  };
  addAndMakeVisible(mBtnVelocity);
}

LooperComponent::~LooperComponent() {}

//==============================================================================
void LooperComponent::paint(juce::Graphics& g) {
  // Set font used for key and bar labels
  g.setFont(juce::Font(10.f, juce::Font::plain));

  // Draw line after input type buttons
  g.setColour(juce::Colours::black);
  int btnBottom = mBtnPitch.getBottom() + Utils::PADDING;
  g.drawLine(0, btnBottom, getWidth(), btnBottom, 2);

  // Draw piano roll and lines across timeline
  int keyY = mRectPianoRoll.getBottom();
  int keyHeight = mRectPianoRoll.getHeight() / (mProcessor.params.ui.pianoRollVertScale * NUM_DEFAULT_PIANO_KEYS);
  int pitch = Utils::C;
  juce::Rectangle<int> pianoRoll = mRectPianoRoll;
  int keyBarWidth = getWidth() - Utils::PADDING * 2;
  while (pianoRoll.getHeight() > 0) {
    
    juce::Rectangle<int> keyRect = pianoRoll.removeFromBottom(keyHeight);
    juce::Colour keyCol = isBlackKey((Utils::PitchClass)(pitch % Utils::NUM_PITCH_CLASSES)) ? juce::Colours::black : juce::Colours::white;
    
    // Draw key bar across timeline
    juce::Rectangle<int> keyBar = keyRect.withWidth(keyBarWidth);
    g.setColour(keyCol.withAlpha(0.1f));
    g.fillRect(keyBar);
    g.setColour(juce::Colours::black.withAlpha(0.1f));
    g.drawLine(keyBar.getX(), keyBar.getBottom(), keyBar.getRight(), keyBar.getBottom());
      
    // Draw key
    g.setColour(keyCol);
    g.fillRect(keyRect);
    g.setColour(juce::Colours::black);
    g.drawLine(keyRect.getX(), keyRect.getBottom(), keyRect.getRight(), keyRect.getBottom());
    if (pitch % Utils::NUM_PITCH_CLASSES == Utils::PitchClass::C && keyRect.getHeight() == keyHeight) {
      g.setColour(juce::Colours::black);
      int octave = pitch / (float)Utils::NUM_PITCH_CLASSES;
      g.drawFittedText(Utils::PITCH_CLASS_NAMES[Utils::PitchClass::C] + juce::String(octave), keyRect,
                       juce::Justification::centredLeft, 1);
    }


    pitch++;
  }

  // Draw timeline markers
  int barInterval = mRectTimeline.getWidth() /(int)mProcessor.params.transport.loopLength->get();
  int beatInterval = barInterval / DEFAULT_TIME_SIG_NUM;
  int timelineBottom = mRectTimeline.getBottom() - HEIGHT_LOOP_BAR;
  const float beatDashes[2] = {1.5, 3};
  for (int bar = 0; bar < mProcessor.params.transport.loopLength->get(); ++bar) {
    // Bar tick
    g.setColour(juce::Colours::black.withAlpha(0.7f));
    int barX = mRectTimeline.getX() + (barInterval * bar);
    g.drawLine(barX, mRectTimeline.getY(), barX, timelineBottom);
    g.setColour(juce::Colours::black.withAlpha(0.7f));
    // Bar label and beat ticks
    if (bar > 0) {
      // Beat ticks
      for (int beat = 1; beat < DEFAULT_TIME_SIG_NUM; ++beat) {
        int beatX = barX - (beatInterval * beat);
        juce::Line<float> beatLine(beatX, mRectTimeline.getY(), beatX, timelineBottom);
        g.drawDashedLine(beatLine, beatDashes, 2);
      }
      if (bar < mProcessor.params.transport.loopLength->get() - 1) {
        g.setColour(juce::Colours::black);
        g.drawFittedText(
            juce::String(bar + 1),
            juce::Rectangle<int>(barX - (WIDTH_BAR_LABEL / 2), timelineBottom, WIDTH_BAR_LABEL, HEIGHT_LOOP_BAR).reduced(2, 2),
            juce::Justification::centred, 1);
      }
    } else {
      g.setColour(juce::Colours::black);
      g.drawFittedText(juce::String(bar + 1), juce::Rectangle<int>(barX, timelineBottom, 10, HEIGHT_LOOP_BAR).reduced(2, 2),
                       juce::Justification::centred, 1);
    }

  }

  // Draw timeline border lines
  g.setColour(juce::Colours::black);
  g.drawRect(mRectTimeline.withHeight(HEIGHT_LOOP_BAR));
  g.drawLine(mRectTimeline.getX(), mRectTimeline.getBottom() - HEIGHT_LOOP_BAR, mRectTimeline.getRight(),
             mRectTimeline.getBottom() - HEIGHT_LOOP_BAR);
  g.drawRect(mRectTimeline.withTop(mRectTimeline.getY() + mRectTimeline.getHeight() - HEIGHT_LOOP_BAR));

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

  r.removeFromTop(Utils::PADDING + 2);  // Bottom separator and line thickness
  r.removeFromTop(Utils::PADDING);

  mRectPianoRoll = r.removeFromLeft(WIDTH_PIANO_ROLL).withTrimmedTop(HEIGHT_LOOP_BAR).withTrimmedBottom(HEIGHT_LOOP_BAR);
  mRectTimeline = r;
}
