#include "KeyboardComponent.h"

//==============================================================================
KeyboardComponent::KeyboardComponent() {
  for (int i = 0; i < Utils::NUM_DEFAULT_PITCH_KEYS; ++i) {
    mKeys.add(Utils::Key(Utils::DEFAULT_PITCH_KEYS[i].keyCode));
  }
}

KeyboardComponent::~KeyboardComponent() {}

//==============================================================================
void KeyboardComponent::paint(juce::Graphics& g) {


#ifdef OVERLAY_LABELS
  g.fillAll(juce::Colours::dimgrey);
  g.setColour(juce::Colours::white);
  g.setFont(15.0f);
  g.drawFittedText("Keyboard", getLocalBounds(), juce::Justification::centred, 1);
#endif
  g.setColour(juce::Colours::black);
  g.drawRect(getLocalBounds());
}

void KeyboardComponent::resized() {

}

bool KeyboardComponent::keyPressed(const juce::KeyPress& keyPress, juce::Component* originatingComponent) {
  int code = keyPress.getKeyCode();
  auto key = std::find_if(mKeys.begin(), mKeys.end(), [code](const Utils::Key& key) { return key.keyCode == code; });
  if (key != mKeys.end()) {
    key->isPressed = keyPress.isCurrentlyDown();
  }
  return true; 
}
