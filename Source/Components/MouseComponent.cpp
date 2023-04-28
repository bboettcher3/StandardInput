#include "MouseComponent.h"

//==============================================================================
MouseComponent::MouseComponent() {}

MouseComponent::~MouseComponent() {}

//==============================================================================
void MouseComponent::paint(juce::Graphics& g) {
#ifdef OVERLAY_LABELS
  g.fillAll(juce::Colours::darkslategrey);

  g.setColour(juce::Colours::white);
  g.setFont(15.0f);
  g.drawFittedText("Mouse", getLocalBounds(), juce::Justification::centred, 1);
#endif
  g.setColour(juce::Colours::black);
  g.drawRect(getLocalBounds());
}

void MouseComponent::resized() {}
