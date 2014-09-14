#ifndef MGCOLORSETTINGS_H
#define MGCOLORSETTINGS_H

#include <QObject>
#include <QColor>
class MgColorSettings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor color1 READ color1 WRITE setColor1 NOTIFY color1Changed)
    Q_PROPERTY(QColor color2 READ color2 WRITE setColor2 NOTIFY color2Changed)
    Q_PROPERTY(QColor color3 READ color3 WRITE setColor3 NOTIFY color3Changed)
    Q_PROPERTY(QColor color4 READ color4 WRITE setColor4 NOTIFY color4Changed)
    Q_PROPERTY(QColor darkColor READ darkColor WRITE setDarkColor NOTIFY darkColorChanged)
    Q_PROPERTY(QColor intermediaryColor READ intermediaryColor WRITE setIntermediaryColor NOTIFY intermediaryColorChanged)
    Q_PROPERTY(QColor lightColor READ lightColor WRITE setLightColor NOTIFY lightColorChanged)
public:
    explicit MgColorSettings(QObject *parent = 0);

    QColor color1() const;
    QColor color2() const;
    QColor color3() const;
    QColor color4() const;
    QColor darkColor() const;
    QColor intermediaryColor() const;
    QColor lightColor() const;

Q_SIGNALS:

    void color1Changed();
    void color2Changed();
    void color3Changed();
    void color4Changed();
    void darkColorChanged();
    void intermediaryColorChanged();
    void lightColorChanged();

public Q_SLOTS:

    void setColor1(const QColor & arg);
    void setColor2(const QColor & arg);
    void setColor3(const QColor & arg);
    void setColor4(const QColor & arg);
    void setDarkColor(const QColor & arg);
    void setIntermediaryColor(const QColor & arg);
    void setLightColor(const QColor & arg);

private:

    QColor m_color1;
    QColor m_color2;
    QColor m_color3;
    QColor m_color4;
    QColor m_darkColor;
    QColor m_intermediaryColor;
    QColor m_lightColor;
};

#endif // MGCOLORSETTINGS_H
