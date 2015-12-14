#ifndef DATABINDING_H
#define DATABINDING_H

#include <QObject>
#include <QVariant>
#include <QSlider>
#include <QLineEdit>
#include <QCheckBox>
#include <QButtonGroup>
#include <QRadioButton>
#include <QDockWidget>
#include <QTabWidget>
#include <QDial>

//#include <CS123Common.h>

/**
 * @class DataBinding
 *
 * This class binds a slider and a textbox to an int, so when either the slider or the textbox
 * is changed, the other is also changed and the int is updated with the new value.  This does
 * not update either the slider or the textbox when the int is set to a new value.
 */
class DataBinding : public QObject
{
    Q_OBJECT

public:
    DataBinding(QObject *parent = 0) : QObject(parent) {}
    virtual ~DataBinding() {}

signals:
    void dataChanged();

};

/**
 *
 * @class FloatBinding
 *
 * This class binds a slider and a textbox to a REAL, so when either the slider or the textbox
 * is changed, the other is also changed and the REAL is updated with the new value.  This does
 * not update either the slider or the textbox when the REAL is set to a new value.
 */
class FloatBinding : public DataBinding
{
    Q_OBJECT
public:
    virtual ~FloatBinding() {}

    static FloatBinding* bindSlider(
         QSlider *slider, float &value, float minValue, float maxValue);

private slots:
    void intChanged(int newValue);

signals:
    void updateInt(int newValue);

private:
    FloatBinding(float &value) :
        DataBinding(),
        m_value(value),
        m_maxValue(0),
        m_minValue(0),
        m_offset(0),
        m_wrappingExtendsRange(false) {}

    float &m_value, m_maxValue, m_minValue, m_offset;
    bool m_wrappingExtendsRange;
};

/**
 * @class BoolBinding
 *
 * This class binds a checkbox to a bool, so when the checkbox is changed the bool is updated
 * with the new value.  This does not update the checkbox when the bool is set to a new value.
 */
class BoolBinding : public DataBinding
{
    Q_OBJECT
public:
    virtual ~BoolBinding() {}

    static BoolBinding* bindCheckbox(QCheckBox *checkbox, bool &value);
//    static BoolBinding* bindDock(QDockWidget *dock, bool &value);

private slots:
    void boolChanged(bool newValue);

private:
    BoolBinding(bool &value) : DataBinding(), m_value(value) {}

    bool &m_value;
};

#endif // DATABINDING_H
