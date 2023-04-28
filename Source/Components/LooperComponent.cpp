#include "LooperComponent.h"

//==============================================================================
LooperComponent::LooperComponent() {}

LooperComponent::~LooperComponent() {}

//==============================================================================
void LooperComponent::paint(juce::Graphics& g) {
#ifdef OVERLAY_LABELS
  g.fillAll(juce::Colours::darkgrey);

  g.setColour(juce::Colours::white);
  g.setFont(15.0f);
  g.drawFittedText("Looper", getLocalBounds(), juce::Justification::centred, 1);
#endif
  g.setColour(juce::Colours::black);
  g.drawRect(getLocalBounds());
}

void LooperComponent::resized() {}
