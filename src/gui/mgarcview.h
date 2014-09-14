#ifndef MGARCVIEW_H
#define MGARCVIEW_H


#include <QQuickItem>
class QSGGeometry;

class MgArcView : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(float innerRadius READ innerRadius WRITE setInnerRadius NOTIFY innerRadiusChanged)
    Q_PROPERTY(float outerRadius READ outerRadius WRITE setOuterRadius NOTIFY outerRadiusChanged)
    Q_PROPERTY(float startAngle READ startAngle WRITE setStartAngle NOTIFY startAngleChanged)
    Q_PROPERTY(float endAngle READ endAngle WRITE setEndAngle NOTIFY endAngleChanged)
    Q_PROPERTY(int pointsSize READ pointsSize WRITE setPointsSize NOTIFY pointsSizeChanged)
    Q_PROPERTY(float diameter READ diameter WRITE setDiameter NOTIFY diameterChanged)
    Q_PROPERTY(bool fullDisk READ fullDisk WRITE setFullDisk NOTIFY fullDiskChanged)
    Q_PROPERTY(QColor color1 READ color1 WRITE setColor1 NOTIFY color1Changed)
    Q_PROPERTY(QColor color2 READ color2 WRITE setColor2 NOTIFY color2Changed)
    Q_PROPERTY(bool roundStartAngle READ roundStartAngle WRITE setRoundStartAngle NOTIFY roundStartAngleChanged)
    Q_PROPERTY(bool roundEndAngle READ roundEndAngle WRITE setRoundEndAngle NOTIFY roundEndAngleChanged)


    Q_PROPERTY(ShadingMode shadingMode READ shadingMode WRITE setShadingMode NOTIFY shadingModeChanged)

    Q_ENUMS(ShadingMode)

public:
    enum ShadingMode {
        Flat,
        InnerRadiusToOuterRadiusLinearGradient,
        InnerRadiusToOuterRadiusExponentialGradient,
        Glow,
        ThinGlow
    };

    explicit MgArcView(QQuickItem *parent = 0);


    float innerRadius() const;
    float outerRadius() const;
    float startAngle() const;
    float endAngle() const;
    int pointsSize() const;
    float diameter() const;
    bool fullDisk() const;
    QColor color1() const;
    QColor color2() const;
    bool roundStartAngle() const;
    bool roundEndAngle() const;

    ShadingMode shadingMode() const;


    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *);



Q_SIGNALS:

    void innerRadiusChanged(float arg);
    void outerRadiusChanged(float arg);
    void startAngleChanged(float arg);
    void endAngleChanged(float arg);
    void pointsSizeChanged(int arg);
    void diameterChanged(float arg);
    void colorChanged(QColor arg);
    void fullDiskChanged(bool arg);
    void color1Changed(QColor arg);
    void color2Changed(QColor arg);
    void shadingModeChanged(ShadingMode arg);
    void roundStartAngleChanged(bool arg);
    void roundEndAngleChanged(bool arg);

public Q_SLOTS:

    void setInnerRadius(float arg);
    void setOuterRadius(float arg);
    void setStartAngle(float arg);
    void setEndAngle(float arg);
    void setPointsSize(int arg);
    void setDiameter(float arg);
    void setFullDisk(bool arg);
    void setColor1(const QColor& arg);
    void setColor2(const QColor& arg);
    void setShadingMode(ShadingMode arg);
    void setRoundStartAngle(bool arg);
    void setRoundEndAngle(bool arg);

protected Q_SLOTS:
    void handleSizeChanged();



private:
    float m_innerRadius;
    float m_outerRadius;
    float m_startAngle;
    float m_endAngle;
    int m_pointsSize;
    float m_diameter;
    bool m_geometryChanged,m_materialChanged,m_shadingModeChanged;
    QColor m_color1;
    QColor m_color2;
    bool m_fullDisk;
    bool m_roundStartAngle;
    bool m_roundEndAngle;
    ShadingMode m_shadingMode;
    friend class ArcNode;


};


#endif // MGARCVIEW_H
