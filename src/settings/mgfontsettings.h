#ifndef MGFONTSETTINGS_H
#define MGFONTSETTINGS_H
#include <QObject>
class MgFontSettings : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString textFontFamily READ textFontFamily WRITE setTextFontFamily NOTIFY textFontFamilyChanged)
    Q_PROPERTY(int textPointSize READ textPointSize WRITE setTextPointSize NOTIFY textPointSizeChanged)

    Q_PROPERTY(QString speedGaugeFontFamily READ speedGaugeFontFamily WRITE setSpeedGaugeFontFamily NOTIFY speedGaugeFontFamilyChanged)
    Q_PROPERTY(int speedGaugePointSize READ speedGaugePointSize WRITE setSpeedGaugePointSize NOTIFY speedGaugePointSizeChanged)

    Q_PROPERTY(QString speedGraduationsFontFamily READ speedGraduationsFontFamily WRITE setSpeedGraduationsFontFamily NOTIFY speedGraduationsFontFamilyChanged)
    Q_PROPERTY(int speedGraduationsPointSize READ speedGraduationsPointSize WRITE setSpeedGraduationsPointSize NOTIFY speedGraduationsPointSizeChanged)

public:
    MgFontSettings(QObject * parent = 0);

    QString textFontFamily() const;
    int textPointSize() const;

    QString speedGaugeFontFamily() const;
    int speedGaugePointSize() const;

    QString speedGraduationsFontFamily() const;
    int speedGraduationsPointSize() const;

public Q_SLOTS:


    void setTextFontFamily(const QString & arg);
    void setTextPointSize(int arg);
    void setSpeedGaugeFontFamily(const QString & arg);
    void setSpeedGaugePointSize(int arg);
    void setSpeedGraduationsFontFamily(const QString & arg);
    void setSpeedGraduationsPointSize(int arg);

Q_SIGNALS:
    void textFontFamilyChanged();
    void textPointSizeChanged();
    void speedGaugeFontFamilyChanged();
    void speedGaugePointSizeChanged();
    void speedGraduationsFontFamilyChanged();
    void speedGraduationsPointSizeChanged();

private:
    QString m_textFontFamily;
    int m_textPointSize;
    QString m_speedGaugeFontFamily;
    int m_speedGaugePointSize;
    QString m_speedGraduationsFontFamily;
    int m_speedGraduationsPointSize;
};

#endif // MGFONTSETTINGS_H
