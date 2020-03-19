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

#include "DistrhoUI.hpp"
#include "ImageWidgets.hpp"

#include "Artwork.hpp"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------------------------------------------

class TemplateFxUI : public UI, public ImageSlider::Callback
{
public:
    TemplateFxUI()
        : UI(400, 400)
    {
        fSliderGain = new ImageSlider(this, Image(Artwork::slider_handleData, Artwork::slider_handleWidth, Artwork::slider_handleHeight, GL_BGRA));
        fSliderGain->setId(0);
        fSliderGain->setDefault(1.0f);
        fSliderGain->setRange(0.0f, 1.0f);
        fSliderGain->setHeight(Artwork::slider_backHeight);
        fSliderGain->setWidth(Artwork::slider_backWidth);
        fSliderGain->setStartPos(Point<int>(12, 12));
        fSliderGain->setEndPos(Point<int>(12, 98));
        fSliderGain->setValue(1.0f);
        fSliderGain->setInverted(true);
        fSliderGain->setCallback(this);
    }

protected:
    /* --------------------------------------------------------------------------------------------------------
    * DSP/Plugin Callbacks */

    /**
      A parameter has changed on the plugin side.
      This is called by the host to inform the UI about parameter changes.
    */
    void parameterChanged(uint32_t index, float value) override
    {
        switch (index)
        {
        case 0:
            fSliderGain->setValue(value);
            break;
        default:
            break;
        }
    }

    /* --------------------------------------------------------------------------------------------------------
    * Widget Callbacks */
    void imageSliderValueChanged(ImageSlider *slider, float value)
    {
        int id = slider->getId();
        setParameterValue(id, value);
    }
    void imageSliderDragStarted(ImageSlider *slider)
    {
        int id = slider->getId();
        editParameter(id, true);
    }
    void imageSliderDragFinished(ImageSlider *slider)
    {
       int id = slider->getId();
        editParameter(id, false);
    }

    void onDisplay() override
    {
        background.drawAt(0, 0);
        sliderBack.drawAt(10, 10);
        // draw stuff
    }

    // -------------------------------------------------------------------------------------------------------

private:
    float fGain;
    ScopedPointer<ImageSlider> fSliderGain;
    Image sliderBack = Image(Artwork::slider_backData, Artwork::slider_backWidth, Artwork::slider_backHeight, GL_BGRA);
    Image background = Image(Artwork::TheAudioProgrammerData, Artwork::TheAudioProgrammerWidth, Artwork::TheAudioProgrammerHeight, GL_BGRA);

    /**
      Set our UI class as non-copyable and add a leak detector just in case.
    */
    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TemplateFxUI)
};

/* ------------------------------------------------------------------------------------------------------------
 * UI entry point, called by DPF to create a new UI instance. */

UI *createUI()
{
    return new TemplateFxUI();
}

// -----------------------------------------------------------------------------------------------------------

END_NAMESPACE_DISTRHO
