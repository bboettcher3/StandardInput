#include "KeyboardComponent.h"

//==============================================================================
KeyboardComponent::KeyboardComponent() {
}

KeyboardComponent::~KeyboardComponent() {}

//==============================================================================
void KeyboardComponent::paint(juce::Graphics& g) {
  // Draw key rects
  juce::Font noteFont(16.0f, juce::Font::bold);
  juce::Font letterFont(10.0f, juce::Font::plain);
  for (Key& key : mKeys) {
    juce::Colour col = key.isPressed ? juce::Colours::lightgrey : juce::Colours::white;
    g.setColour(col);
    g.fillRoundedRectangle(key.rect.toFloat(), Utils::ROUNDED_AMOUNT);
    g.setColour(juce::Colours::black);
    int charWidth = key.rect.getWidth() / 5;
    g.setFont(letterFont);
    g.drawFittedText(juce::String(&key.keyChar, 1), key.rect.withSize(charWidth, charWidth).translated(2, 2),
                     juce::Justification::centred, 1);
    if (key.midiNote != Utils::NONE) {
      g.setFont(noteFont);
      g.drawFittedText(Utils::PITCH_CLASS_NAMES[key.midiNote % Utils::NUM_PITCH_CLASSES], key.rect, juce::Justification::centred,
                       1);
    }
  }

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
  juce::Rectangle<int> r = getLocalBounds();
  r.reduce(Utils::PADDING, Utils::PADDING);
  const float keySize = (r.getWidth() - (Utils::PADDING * (NUM_KEYS_ROW_1 - 1))) / NUM_KEYS_ROW_1;
  juce::Rectangle<int> rows[3] = {r.removeFromTop(keySize + Utils::PADDING).withTrimmedBottom(Utils::PADDING),
                                  r.removeFromTop(keySize + Utils::PADDING).withTrimmedBottom(Utils::PADDING), r};
  rows[1] = rows[1].withTrimmedLeft(keySize / 4.0f);
  for (int i = 0; i < mKeys.size(); ++i) {
    int row = (i >= NUM_KEYS_ROW_1);
    if (i >= NUM_PITCH_KEYS) row = 2;
    mKeys[i].rect = rows[row].removeFromLeft(keySize);
    rows[row].removeFromLeft(Utils::PADDING);
  }
}

bool KeyboardComponent::keyPressed(const juce::KeyPress& key, juce::Component* originatingComponent) { return false; }

bool KeyboardComponent::keyStateChanged(bool isKeyDown, juce::Component* originatingComponent) {
  for (Key& key : mKeys) {
    key.isPressed = juce::KeyPress::isKeyCurrentlyDown(key.keyCode);
  }
  repaint();
  return true;
}
