#ifndef MGAPPLICATIONSETTINGS_H
#define MGAPPLICATIONSETTINGS_H

#include <QObject>
#include <QColor>
#include <QString>

#include "mgcolorsettings.h"
#include "mgfontsettings.h"

class MgApplicationSettings : public QObject
{
    Q_OBJECT

    Q_PROPERTY(MgColorSettings* colorSettings READ colorSettings WRITE setColorSettings NOTIFY colorSettingsChanged)
    Q_PROPERTY(MgFontSettings* fontSettings READ fontSettings WRITE setFontSettings NOTIFY fontSettingsChanged)



public:
    MgApplicationSettings(QObject * parent = 0);

    MgColorSettings* colorSettings() const;
    MgFontSettings* fontSettings() const;

public Q_SLOTS:

    void save();
    void load();

    void setColorSettings(MgColorSettings* arg);
    void setFontSettings(MgFontSettings* arg);

Q_SIGNALS:

    void colorSettingsChanged();
    void fontSettingsChanged();

private:
    MgColorSettings* m_colorSettings;
    MgFontSettings* m_fontSettings;
};

#endif // MGAPPLICATIONSETTINGS_H
