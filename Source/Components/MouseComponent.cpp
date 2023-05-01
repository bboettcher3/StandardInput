#include "MouseComponent.h"
#include "../Utils.h"

//==============================================================================
MouseComponent::MouseComponent() {
  juce::Desktop::getInstance().addGlobalMouseListener(this);
  setFramesPerSecond(30);
}

MouseComponent::~MouseComponent() {}

//==============================================================================
void MouseComponent::paint(juce::Graphics& g) {
  g.fillAll(juce::Colour(Utils::BG_COLOUR));
  g.setColour(juce::Colours::black);
  g.fillRoundedRectangle(mRectMouseVis.toFloat(), Utils::ROUNDED_AMOUNT);
  g.setColour(mIsActive ? juce::Colours::lawngreen : juce::Colours::red);
  g.drawLine(mRectMouseVis.getCentreX(), mRectMouseVis.getCentreY(), mMousePosition.x, mMousePosition.y, 2);
  g.drawRect(mRectMouseVis, 2);  // draw an outline around the component

  if (mIsActive) {
    juce::Rectangle<int> escRect = mRectMouseVis.withSize(80, 15);
    g.setColour(juce::Colours::white);
    g.fillRoundedRectangle(escRect.toFloat(), Utils::ROUNDED_AMOUNT);
    g.setColour(juce::Colours::black);
    g.drawFittedText("ESC to cancel", escRect, juce::Justification::centred, 1);
  }

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
  juce::Rectangle<int> r = getLocalBounds().reduced(Utils::PADDING);
  mRectMouseVis = r.removeFromLeft(r.getHeight());
  mMousePosition = mRectMouseVis.getCentre().toFloat();
}

void MouseComponent::update() {}

void MouseComponent::mouseMove(const juce::MouseEvent& e) {
  if (mMouse != nullptr) {
    mMouseSigs.updatePosition(e.getScreenPosition().x, e.getScreenPosition().y);
    mMousePosition = e.getEventRelativeTo(this).getPosition().toFloat();
    //juce::Desktop::setMousePosition(mRectMouseVis.getCentre());
    mMouse->setScreenPosition(getScreenPosition().toFloat() + mRectMouseVis.getCentre().toFloat());
  }
}

void MouseComponent::mouseDrag(const juce::MouseEvent& e) {
  if (mMouse != nullptr) {
    mMouseSigs.updatePosition(e.getScreenPosition().x, e.getScreenPosition().y);
    if (e.source.isPressureValid()) mMouseSigs.updatePressure(e.pressure);
    mMouse->setScreenPosition(getScreenPosition().toFloat() + mRectMouseVis.getCentre().toFloat());
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
    mMouse->setScreenPosition(getScreenPosition().toFloat() + mRectMouseVis.getCentre().toFloat());
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