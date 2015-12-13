#include "Databinding.h"
#include <math.h>
#include <QVariant>

////////////////////////////////////////////////////////////////////////////////
// class FloatBinding
////////////////////////////////////////////////////////////////////////////////

// Sliders can only work in ints, so use 100 slider units for every value unit (two decimals of
// resolution)
inline float mapValue(int i) { return (float)i * 0.01f; }
inline int mapValue(float f) { return (int)ceilf(f * 100 - 0.5f); }

FloatBinding* FloatBinding::bindSlider(
        QSlider *slider, float &value, float minValue, float maxValue)
{
    // Bind the slider and the value together
    FloatBinding *binding = new FloatBinding(value);
    connect(slider, SIGNAL(sliderMoved(int)), binding, SLOT(intChanged(int)));
    connect(binding, SIGNAL(updateInt(int)), slider, SLOT(setValue(int)));

    // Set the range and initial value
    slider->setMinimum(mapValue(minValue));
    slider->setMaximum(mapValue(maxValue));
    slider->setValue(mapValue(value));

    return binding;
}

void FloatBinding::intChanged(int newValue)
{
    float floatValue = mapValue(newValue);

    if (m_wrappingExtendsRange)
    {
        float lowerBound = m_minValue * 0.75f + m_maxValue * 0.25f;
        float upperBound = m_minValue * 0.25f + m_maxValue * 0.75f;

        // This is a hack to get dials to wrap around infinitely
        //
        //        A           B           C           D
        //  |-----------|-----------|-----------|-----------|
        // min     lowerBound              upperBound      max
        //
        // Any jump from A -> D or D -> A is considered a wrap around

        if (m_value - m_offset < lowerBound && floatValue > upperBound)
            m_offset -= m_maxValue - m_minValue;
        else if (m_value - m_offset > upperBound && floatValue < lowerBound)
            m_offset += m_maxValue - m_minValue;
    }

    if (m_value - m_offset != floatValue)
    {
        m_value = floatValue + m_offset;
        emit dataChanged();
    }
}

////////////////////////////////////////////////////////////////////////////////
// class BoolBinding
////////////////////////////////////////////////////////////////////////////////

BoolBinding* BoolBinding::bindCheckbox(QCheckBox *checkbox, bool &value)
{
    // Bind the checkbox and the value together
    BoolBinding *binding = new BoolBinding(value);
    connect(checkbox, SIGNAL(toggled(bool)), binding, SLOT(boolChanged(bool)));

    // Set the initial value
    checkbox->setChecked(value);

    return binding;
}

//BoolBinding* BoolBinding::bindDock(QDockWidget *dock, bool &value)
//{
//    // Bind the checkbox and the value together
//    BoolBinding *binding = new BoolBinding(value);
//    connect(dock, SIGNAL(visibilityChanged(bool)), binding, SLOT(boolChanged(bool)));

//    // Set the initial value
//    dock->setVisible(value);

//    return binding;
//}

void BoolBinding::boolChanged(bool newValue)
{
    m_value = newValue;
    emit dataChanged();
}
