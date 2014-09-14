#include "mgapplicationsettings.h"

MgApplicationSettings::MgApplicationSettings(QObject * parent ):
    QObject(parent),
    m_colorSettings(NULL),
    m_fontSettings(NULL)
{
    setFontSettings(new MgFontSettings());
    setColorSettings(new MgColorSettings());
}



MgColorSettings *MgApplicationSettings::colorSettings() const
{
    return m_colorSettings;
}

MgFontSettings *MgApplicationSettings::fontSettings() const
{
    return m_fontSettings;
}

void MgApplicationSettings::setColorSettings(MgColorSettings *arg)
{
    if (m_colorSettings != arg) {
        if(m_colorSettings)
            delete m_colorSettings;
        m_colorSettings = arg;
        m_colorSettings->setParent(this);
        Q_EMIT colorSettingsChanged();
    }
}

void MgApplicationSettings::setFontSettings(MgFontSettings *arg)
{
    if (m_fontSettings != arg) {
        if(m_fontSettings)
            delete m_fontSettings;
        m_fontSettings = arg;
        m_fontSettings->setParent(this);
        Q_EMIT fontSettingsChanged();
    }
}


void MgApplicationSettings::save()
{

}

void MgApplicationSettings::load()
{

}
