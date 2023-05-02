#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Utils.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor& p)
    : AudioProcessorEditor(&p), processorRef(p), mParamUI(p.ui), mLooper(p) {
  juce::ignoreUnused(processorRef);

  addAndMakeVisible(mHeader);
  addAndMakeVisible(mLooper);
  addKeyListener(&mKeyboard);
  addAndMakeVisible(mKeyboard);
  addKeyListener(&mMouse);
  addAndMakeVisible(mMouse);

  setWantsKeyboardFocus(true);
  setSize(800, 500);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor() {}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint(juce::Graphics& g) {
  // (Our component is opaque, so we must completely fill the background with a solid colour)
  g.fillAll(juce::Colour(Utils::BG_COLOUR));
}

void AudioPluginAudioProcessorEditor::resized() { 
  juce::Rectangle<int> r = getLocalBounds(); 

  mHeader.setBounds(r.removeFromTop(40));
  juce::Rectangle<int> keyMousePanel = r.removeFromBottom(130);
  mLooper.setBounds(r);
  mKeyboard.setBounds(keyMousePanel.removeFromLeft(keyMousePanel.getWidth() / 2));
  mMouse.setBounds(keyMousePanel);
}
