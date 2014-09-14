#include "mgcolorsettings.h"

MgColorSettings::MgColorSettings(QObject *parent) :
    QObject(parent)
{
    setColor1("#1AC2DB");
    setColor2("#DB310B");
    setColor3("#1C4DED");
    setColor4("#F21619");
    setDarkColor("#0A0A0A");
    setIntermediaryColor("#5C5A5A");
    setLightColor("#ADADAD");
}

QColor MgColorSettings::color1() const
{
    return m_color1;
}

QColor MgColorSettings::color2() const
{
    return m_color2;
}

QColor MgColorSettings::color3() const
{
    return m_color3;
}

QColor MgColorSettings::color4() const
{
    return m_color4;
}

QColor MgColorSettings::darkColor() const
{
    return m_darkColor;
}

QColor MgColorSettings::intermediaryColor() const
{
    return m_intermediaryColor;
}

QColor MgColorSettings::lightColor() const
{
    return m_lightColor;
}

void MgColorSettings::setColor1(const QColor &arg)
{
    if (m_color1 != arg) {
        m_color1 = arg;
        Q_EMIT color1Changed();
    }
}

void MgColorSettings::setColor2(const QColor &arg)
{
    if (m_color2 != arg) {
        m_color2 = arg;
        Q_EMIT color2Changed();
    }
}

void MgColorSettings::setColor3(const QColor &arg)
{
    if (m_color3 != arg) {
        m_color3 = arg;
        Q_EMIT color3Changed();
    }
}

void MgColorSettings::setColor4(const QColor &arg)
{
    if (m_color4 != arg) {
        m_color4 = arg;
        Q_EMIT color4Changed();
    }
}

void MgColorSettings::setDarkColor(const QColor &arg)
{
    if (m_darkColor != arg) {
        m_darkColor = arg;
        Q_EMIT darkColorChanged();
    }
}

void MgColorSettings::setIntermediaryColor(const QColor &arg)
{
    if (m_intermediaryColor != arg) {
        m_intermediaryColor = arg;
        Q_EMIT intermediaryColorChanged();
    }
}

void MgColorSettings::setLightColor(const QColor &arg)
{
    if (m_lightColor != arg) {
        m_lightColor = arg;
        Q_EMIT lightColorChanged();
    }
}
