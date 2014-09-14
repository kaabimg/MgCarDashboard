#ifndef MGGRAPHVIEW_H
#define MGGRAPHVIEW_H

#include <QQuickItem>

class QSGGeometry;
class MgPointsProvider;
class MgGraphView : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(float minY READ minY WRITE setMinY NOTIFY minYChanged)
    Q_PROPERTY(float maxY READ maxY WRITE setMaxY NOTIFY maxYChanged)
    Q_PROPERTY(int graphPointsSize READ graphPointsSize WRITE setGraphPointsSize NOTIFY graphPointsSizeChanged)
    Q_PROPERTY(float timeWindow READ timeWindow WRITE setTimeWindow NOTIFY timeWindowChanged)
    Q_PROPERTY(QColor graphColor READ graphColor WRITE setGraphColor NOTIFY graphColorChanged)
    Q_PROPERTY(QColor fillColor READ fillColor WRITE setFillColor NOTIFY fillColorChanged)
    Q_PROPERTY(float graphLineWidth READ graphLineWidth WRITE setGraphLineWidth NOTIFY graphLineWidthChanged)
    Q_PROPERTY(MgPointsProvider* pointsProvider READ pointsProvider WRITE setPointsProvider NOTIFY pointsProviderChanged)

    Q_PROPERTY(float lastTime READ lastTime NOTIFY lastTimeChanged)
    Q_PROPERTY(float lastValue READ lastValue NOTIFY lastValueChanged)

public:
    explicit MgGraphView(QQuickItem *parent = 0);

    float minY() const;
    float maxY() const;
    MgPointsProvider *pointsProvider() const;
    int graphPointsSize() const;
    QColor graphColor() const;
    QColor fillColor() const;
    float timeWindow() const;
    float graphLineWidth() const;
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *);



Q_SIGNALS:


    void minYChanged(float arg);
    void maxYChanged(float arg);
    void pointsProviderChanged(MgPointsProvider* arg);
    void graphPointsSizeChanged(int arg);
    void graphColorChanged(QColor arg);
    void fillColorChanged(QColor arg);
    void timeWindowChanged(float arg);
    void lastTimeChanged(float arg);
    void lastValueChanged(float arg);
    void graphLineWidthChanged(float arg);



public Q_SLOTS:

    void setMinY(double arg);
    void setMaxY(double arg);
    void setPointsProvider(MgPointsProvider* arg);
    void setGraphPointsSize(int arg);
    void setGraphColor(const QColor  & arg);
     void setFillColor(QColor arg);
    void setGraphLineWidth(float arg);

    void setTimeWindow(float arg);

    int xToRelativePosition(float);
    int yToRelativePosition(float);

    float lastTime() const;
    float lastValue() const;

    void clear();




protected Q_SLOTS:
    void addPoint(float time,float value);


private:

    void setLastTime(float arg);
    void setLastValue(float arg);

private:
    friend class LineNode;
    friend class FillNode;
private:
    float m_minY;
    float m_maxY;
    float m_timeWindow,m_yWindow;
    int m_graphPointsSize;

    MgPointsProvider* m_pointsProvider;

    struct Point {
        float x,y;
        Point(float _x,float _y):x(_x),y(_y){}
    };
    QList<Point> m_points;
    QColor m_graphColor;
    QColor m_fillColor;
    float m_lastTime,m_lastValue;
    float m_graphLineWidth;
    bool m_synchroniszed;


};

#endif // MGGRAPHVIEW_H
