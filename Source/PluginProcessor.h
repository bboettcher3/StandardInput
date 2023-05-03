#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

#if (MSVC)
#include "ipps.h"
#endif

#include "Parameters.h"

class AudioPluginAudioProcessor : public juce::AudioProcessor {
 public:
  AudioPluginAudioProcessor();
  ~AudioPluginAudioProcessor() override;

  void prepareToPlay(double sampleRate, int samplesPerBlock) override;
  void releaseResources() override;

  bool isBusesLayoutSupported(const BusesLayout& layouts) const override;

  void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

  double getSampleRate() { return mSampleRate; }
  std::atomic<int>& getSampleCount() { return mTotalSamps; }
  juce::Optional<juce::AudioPlayHead::PositionInfo> getPositionInfo() { return mPositionInfo; }
  void setIsPlaying(bool isPlaying) { 
    mIsPlaying = isPlaying;
  }
  void setIsRecording(bool isRecording) { 
    mIsRecording = isRecording;
  }

  juce::AudioProcessorEditor* createEditor() override;
  bool hasEditor() const override;

  const juce::String getName() const override;

  bool acceptsMidi() const override;
  bool producesMidi() const override;
  bool isMidiEffect() const override;
  double getTailLengthSeconds() const override;

  int getNumPrograms() override;
  int getCurrentProgram() override;
  void setCurrentProgram(int index) override;
  const juce::String getProgramName(int index) override;
  void changeProgramName(int index, const juce::String& newName) override;

  void getStateInformation(juce::MemoryBlock& destData) override;
  void setStateInformation(const void* data, int sizeInBytes) override;
  
  Parameters params;

 private:
   // Bookkeeping
  double mSampleRate;
  std::atomic<int> mTotalSamps{0};
  juce::Optional<juce::AudioPlayHead::PositionInfo> mPositionInfo;
  bool mIsPlaying = false;
  bool mIsRecording = false;
  
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginAudioProcessor)
};
