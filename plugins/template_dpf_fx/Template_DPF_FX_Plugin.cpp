/* 
Copyright (c) 2020, Rob van den Berg <rghvdberg@gmail.com>

Permission to use, copy, modify, and/or distribute this software for any
purpose with or without fee is hereby granted, provided that the above
copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "DistrhoPlugin.hpp"
#include "DistrhoPluginInfo.h"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------------------------------------------

/**
  Template plugin for audio in/out
 */
class Template_FX : public Plugin
{
public:
  Template_FX()
      : Plugin(kParameterCount, 0, 0), // 1 parameter, 0 programs, 0 states
        fGain(1.0f)
  {
  }

protected:
  /* --------------------------------------------------------------------------------------------------------
    * Information */

  /**
      Get the plugin label.
      A plugin label follows the same rules as Parameter::symbol, with the exception that it can start with numbers.
    */
  const char *getLabel() const override
  {
    return "Template FX";
  }

  /**
      Get an extensive comment/description about the plugin.
    */
  const char *getDescription() const override
  {
    return "Template Plugin for FX";
  }

  /**
      Get the plugin author/maker.
    */
  const char *getMaker() const override
  {
    return "BRAND NAME";
  }

  /**
      Get the plugin homepage.
    */
  const char *getHomePage() const override
  {
    return "https://example.org/PLUGIN_NAME";
  }

  /**
      Get the plugin license name (a single line of text).
      For commercial plugins this should return some short copyright information.
    */
  const char *getLicense() const override
  {
    return "ISC";
  }

  /**
      Get the plugin version, in hexadecimal.
    */
  uint32_t getVersion() const override
  {
    return d_version(1, 0, 0);
  }

  /**
      Get the plugin unique Id.
      This value is used by LADSPA, DSSI and VST plugin formats.
    */
  int64_t getUniqueId() const override
  {
    return d_cconst('t', 'M', 'F', 'x');
  }

  /* --------------------------------------------------------------------------------------------------------
    * Init */

  /**
      Initialize the parameter @a index.
      This function will be called once, shortly after the plugin is created.
    */
  void initParameter(uint32_t index, Parameter &parameter) override
  {
    /*
          Set parameter data.
        see https://distrho.github.io/DPF/structParameter.html
        */
    switch (index)
    {
    case kGain:
      parameter.hints = kParameterIsAutomable;
      parameter.name = "Gain";
      parameter.symbol = "gain";
      parameter.ranges.def = 1.0f;
      parameter.ranges.min = 0.0f;
      parameter.ranges.max = 1.0f;
      break;
    default:
      break;
    }
  }

  /* --------------------------------------------------------------------------------------------------------
    * Internal data */

  /**
      Get the current value of a parameter.
    */
  float getParameterValue(uint32_t index) const override
  {
    switch (index)
    {
    case kGain:
      return fGain;
      break;
    default:
      break;
    }

    return 0.0f;
  }

  /**
      Change a parameter value.
    */
  void setParameterValue(uint32_t index, float value) override
  {
    switch (index)
    {
    case kGain:
      fGain = value;
      break;
    default:
      break;
    }
  }

  /* --------------------------------------------------------------------------------------------------------
    * Process */

  /**
      Run/process function for plugins without MIDI input.
    */
  void run(const float **inputs, float **outputs, uint32_t frames) override
  {
    float *outLeft = outputs[0];
    float *outRight = outputs[1];
    const float *inLeft = inputs[0];
    const float *InRight = inputs[1];

    for (uint32_t i = 0; i < frames; ++i)
    {
      outLeft[i] = inLeft[i] * fGain;
      outRight[i] = InRight[i] * fGain;
    }
  }

  // -------------------------------------------------------------------------------------------------------

private:
  /**
      Parameters.
    */
  float fGain;

  DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Template_FX)
};

/* ------------------------------------------------------------------------------------------------------------
 * Plugin entry point, called by DPF to create a new plugin instance. */

Plugin *createPlugin()
{
  return new Template_FX();
}

// -----------------------------------------------------------------------------------------------------------

END_NAMESPACE_DISTRHO
