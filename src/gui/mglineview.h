#ifndef MGLINEVIEW_H
#define MGLINEVIEW_H

#include <QQuickItem>

class MgLineView : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(bool roundExtremities READ roundExtremities WRITE setRoundExtremities NOTIFY roundExtremitiesChanged)
    Q_PROPERTY(QPointF startPoint READ startPoint WRITE setStartPoint NOTIFY startPointChanged)
    Q_PROPERTY(QPointF endPoint READ endPoint WRITE setEndPoint NOTIFY endPointChanged)
    Q_PROPERTY(float size READ size WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(ShadingMode shadingMode READ shadingMode WRITE setShadingMode NOTIFY shadingModeChanged)
    Q_PROPERTY(QColor color1 READ color1 WRITE setColor1 NOTIFY color1Changed)
    Q_PROPERTY(QColor color2 READ color2 WRITE setColor2 NOTIFY color2Changed)
    Q_ENUMS(ShadingMode)

public:
    enum ShadingMode {Flat,Glow};
    explicit MgLineView(QQuickItem *parent = 0);

    bool roundExtremities() const;
    QPointF startPoint() const;
    QPointF endPoint() const;
    float size() const;
    ShadingMode shadingMode() const;
    QColor color1() const;
    QColor color2() const;

    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *);


Q_SIGNALS:

    void roundExtremitiesChanged();
    void startPointChanged();
    void endPointChanged();
    void sizeChanged();

    void shadingModeChanged();
    void color1Changed();
    void color2Changed();

public Q_SLOTS:

    void setRoundExtremities(bool arg);
    void setStartPoint(QPointF arg);
    void setEndPoint(QPointF arg);
    void setSize(float arg);
    void setShadingMode(ShadingMode arg);
    void setColor1(const QColor & arg);
    void setColor2(const QColor & arg);

private:
    friend class LineViewNode;
    bool m_roundExtremities;
    QPointF m_startPoint;
    QPointF m_endPoint;
    float m_size;
    ShadingMode m_shadingMode;
    QColor m_color1;
    QColor m_color2;
    bool m_geometryChanged,m_materialChanged;
};

#endif // MGLINEVIEW_H
