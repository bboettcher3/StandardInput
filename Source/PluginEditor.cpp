#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor& p)
    : AudioProcessorEditor(&p), processorRef(p) {
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
  g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void AudioPluginAudioProcessorEditor::resized() { 
  juce::Rectangle<int> r = getLocalBounds(); 

  mHeader.setBounds(r.removeFromTop(75));
  juce::Rectangle<int> keyMousePanel = r.removeFromBottom(175);
  mLooper.setBounds(r);
  mKeyboard.setBounds(keyMousePanel.removeFromLeft(keyMousePanel.getWidth() / 2));
  mMouse.setBounds(keyMousePanel);
}
