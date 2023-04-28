#include "KeyboardComponent.h"

//==============================================================================
KeyboardComponent::KeyboardComponent() {}

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

void KeyboardComponent::resized() {}
