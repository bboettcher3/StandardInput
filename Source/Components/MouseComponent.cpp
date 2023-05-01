#include "MouseComponent.h"

//==============================================================================
MouseComponent::MouseComponent() {
  juce::Desktop::getInstance().addGlobalMouseListener(this);
  setFramesPerSecond(30);
}

MouseComponent::~MouseComponent() {}

//==============================================================================
void MouseComponent::paint(juce::Graphics& g) {
  g.fillAll(juce::Colours::black);
  g.setColour(mIsActive ? juce::Colours::lawngreen : juce::Colours::red);
  g.drawLine(mRectMouseVis.getCentreX(), mRectMouseVis.getCentreY(), mMousePosition.x, mMousePosition.y, 2);
  g.drawRect(mRectMouseVis, 1);  // draw an outline around the component

#ifdef OVERLAY_LABELS
  g.fillAll(juce::Colours::darkslategrey);

  g.setColour(juce::Colours::white);
  g.setFont(15.0f);
  g.drawFittedText("Mouse", getLocalBounds(), juce::Justification::centred, 1);
#endif
  g.setColour(juce::Colours::black);
  g.drawRect(getLocalBounds());
}

void MouseComponent::resized() { 
  juce::Rectangle<int> r = getLocalBounds();
  mRectMouseVis = r;
}

void MouseComponent::update() {}

void MouseComponent::mouseMove(const juce::MouseEvent& e) {
  if (mMouse != nullptr) {
    mMouseSigs.updatePosition(e.getScreenPosition().x, e.getScreenPosition().y);
    mMousePosition = e.getEventRelativeTo(this).getPosition().toFloat();
    juce::Desktop::setMousePosition(getScreenBounds().getCentre());
    // mMouse->setScreenPosition(getScreenBounds().getCentre().toFloat());
  }
}

void MouseComponent::mouseDrag(const juce::MouseEvent& e) {
  if (mMouse != nullptr) {
    mMouseSigs.updatePosition(e.getScreenPosition().x, e.getScreenPosition().y);
    if (e.source.isPressureValid()) mMouseSigs.updatePressure(e.pressure);
    // mMouseVisuals.
    mMouse->setScreenPosition(getScreenBounds().getCentre().toFloat());
  }
}

void MouseComponent::mouseUp(const juce::MouseEvent& e) {
  if (e.eventComponent == this) {
    // Save the mouse source that triggered this event
    mMouse = juce::Desktop::getInstance().getMouseSource(e.source.getIndex());
    mMouse->showMouseCursor(juce::MouseCursor::NoCursor);
    mIsActive = true;
  }
}

void MouseComponent::mouseExit(const juce::MouseEvent& e) {
  if (mMouse != nullptr) {
    mMouse->setScreenPosition(getScreenBounds().getCentre().toFloat());
  }
}

bool MouseComponent::keyPressed(const juce::KeyPress& key, juce::Component* originatingComponent) {
  if (key.isKeyCode(juce::KeyPress::escapeKey) && mMouse != nullptr) {
    mMouse->showMouseCursor(juce::MouseCursor::NormalCursor);
    mMouse = nullptr;
    mIsActive = false;
    return true;
  }

  return false;
}