#include "mgfontsettings.h"

MgFontSettings::MgFontSettings(QObject * parent):QObject(parent)
{

    setTextPointSize(15);
    setTextFontFamily("Goudy Bookletter12");

    setSpeedGraduationsPointSize(20);
    setSpeedGaugeFontFamily("Goudy Bookletter12");


    setSpeedGaugePointSize(40);
    setSpeedGaugeFontFamily("Goudy Bookletter12");

}

QString MgFontSettings::textFontFamily() const
{
    return m_textFontFamily;
}

int MgFontSettings::textPointSize() const
{
    return m_textPointSize;
}

QString MgFontSettings::speedGaugeFontFamily() const
{
    return m_speedGaugeFontFamily;
}

int MgFontSettings::speedGaugePointSize() const
{
    return m_speedGaugePointSize;
}

QString MgFontSettings::speedGraduationsFontFamily() const
{
    return m_speedGraduationsFontFamily;
}

int MgFontSettings::speedGraduationsPointSize() const
{
    return m_speedGraduationsPointSize;
}

void MgFontSettings::setTextFontFamily(const QString &arg)
{
    if (m_textFontFamily != arg) {
        m_textFontFamily = arg;
        Q_EMIT textFontFamilyChanged();
    }
}

void MgFontSettings::setTextPointSize(int arg)
{
    if (m_textPointSize != arg) {
        m_textPointSize = arg;
        Q_EMIT textPointSizeChanged();
    }
}

void MgFontSettings::setSpeedGaugeFontFamily(const QString &arg)
{
    if (m_speedGaugeFontFamily != arg) {
        m_speedGaugeFontFamily = arg;
        Q_EMIT speedGaugeFontFamilyChanged();
    }
}

void MgFontSettings::setSpeedGaugePointSize(int arg)
{
    if (m_speedGaugePointSize != arg) {
        m_speedGaugePointSize = arg;
        Q_EMIT speedGaugePointSizeChanged();
    }
}

void MgFontSettings::setSpeedGraduationsFontFamily(const QString &arg)
{
    if (m_speedGraduationsFontFamily != arg) {
        m_speedGraduationsFontFamily = arg;
        Q_EMIT speedGraduationsFontFamilyChanged();
    }
}

void MgFontSettings::setSpeedGraduationsPointSize(int arg)
{
    if (m_speedGraduationsPointSize != arg) {
        m_speedGraduationsPointSize = arg;
        Q_EMIT speedGraduationsPointSizeChanged();
    }
}
