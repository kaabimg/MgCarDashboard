#include "mggraphview.h"
#include <QSGGeometryNode>
#include <QSGGeometry>
#include <QSGFlatColorMaterial>



#include "../core/mgpointsprovider.h"
#include <QDebug>






class LineNode : public QSGGeometryNode
{
public:
    LineNode(MgGraphView* graphView_)
        :graphView(graphView_)
    {
        QSGGeometry  * geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), graphView->graphPointsSize());
        geometry->setDrawingMode(GL_LINE_STRIP);
        geometry->setLineWidth(graphView->graphLineWidth());
        setGeometry(geometry);
        setFlag(QSGNode::OwnsGeometry);
        QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
        material->setColor(graphView->graphColor());
        setMaterial(material);
        setFlag(QSGNode::OwnsMaterial);
    }

    void updateGeometry()
    {

        geometry()->setLineWidth(graphView->graphLineWidth());
        static_cast<QSGFlatColorMaterial*>(material())->setColor(graphView->graphColor());
        QSGGeometry::Point2D *vertices = geometry()->vertexDataAsPoint2D();
        for (int i = 0; i < graphView->m_points.size(); ++i) {

            vertices[i].set(graphView->xToRelativePosition(graphView->m_points[i].x),
                            graphView->yToRelativePosition(graphView->m_points[i].y));
        }
        if(graphView->m_points.size()<graphView->m_graphPointsSize)
        {
            float x,y;
            if(graphView->m_points.empty())
            {
                x = graphView->xToRelativePosition(0);
                y = graphView->yToRelativePosition(graphView->minY()) ;

            }
            else
            {
                x = graphView->xToRelativePosition(graphView->m_points.last().x);
                y = graphView->yToRelativePosition(graphView->m_points.last().y);
            }


            for (int i = graphView->m_points.size();i<graphView->graphPointsSize(); ++i) {
                vertices[i].set(x, y);
            }
        }
        markDirty(QSGNode::DirtyGeometry );
    }

    MgGraphView* graphView;
};





class FillNode : public QSGGeometryNode
{
public:
    FillNode(MgGraphView* graphView_):
        graphView(graphView_)
    {
        QSGGeometry  * geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), graphView->graphPointsSize()*2);

        geometry->setDrawingMode(GL_TRIANGLE_STRIP);
        setGeometry(geometry);
        setFlag(QSGNode::OwnsGeometry);
        QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
        material->setColor(graphView->fillColor());
        setMaterial(material);
        setFlag(QSGNode::OwnsMaterial);
    }

    void updateGeometry()
    {
        static_cast<QSGFlatColorMaterial*>(material())->setColor(graphView->fillColor());
        QSGGeometry::Point2D *vertices = geometry()->vertexDataAsPoint2D();

        for (int i = 0; i < graphView->m_points.size(); ++i) {
            vertices[i*2].set(graphView->xToRelativePosition(graphView->m_points[i].x),
                              graphView->yToRelativePosition(graphView->m_points[i].y));
            vertices[i*2+1].set(graphView->xToRelativePosition(graphView->m_points[i].x),
                                graphView->yToRelativePosition(graphView->m_minY));
        }
        if(graphView->m_points.size()<graphView->m_graphPointsSize)
        {
            float x,y;
            if(graphView->m_points.empty())
            {
                x = graphView->xToRelativePosition(0);
                y = graphView->yToRelativePosition(graphView->height() );

            }
            else
            {
                x = graphView->xToRelativePosition(graphView->m_points.last().x);
                y = graphView->yToRelativePosition(graphView->m_points.last().y);
            }


            for (int i = graphView->m_points.size();i<graphView->graphPointsSize(); ++i) {
                vertices[i*2].set(x, y);
                vertices[i*2+1].set(x, y);
            }
        }
        markDirty(QSGNode::DirtyGeometry );
    }

    MgGraphView* graphView;
};



class GraphNode : public QSGNode
{
public:

    LineNode *line;
    FillNode *fill;
};

//////////////////////////////////////////////////////////////////

MgGraphView::MgGraphView(QQuickItem *parent) :
    QQuickItem(parent),
    m_minY(0),
    m_maxY(10),
    m_timeWindow(1000),
    m_graphPointsSize(0),
    m_pointsProvider(NULL),
    m_graphColor(0,255,0),
    m_fillColor(100,0,0),
    m_lastTime(0),
    m_lastValue(0),
    m_graphLineWidth(1.5),
    m_synchroniszed(false)

{

    setFlag(ItemHasContents, true);
    setAntialiasing(true);
    setSmooth(true);
}

float MgGraphView::minY() const
{
    return m_minY;
}

float MgGraphView::maxY() const
{
    return m_maxY;
}

MgPointsProvider *MgGraphView::pointsProvider() const
{
    return m_pointsProvider;
}


int MgGraphView::graphPointsSize() const
{
    return m_graphPointsSize;
}



void MgGraphView::setMinY(double arg)
{
    if (m_minY != arg) {
        m_minY = arg;
        m_yWindow = m_maxY-m_minY;
        m_synchroniszed= false;
        Q_EMIT minYChanged(arg);
        update();
    }

}

void MgGraphView::setMaxY(double arg)
{
    if (m_maxY != arg) {
        m_maxY = arg;
        m_yWindow = m_maxY-m_minY;
        m_synchroniszed= false;
        Q_EMIT maxYChanged(arg);
        update();
    }

}

void MgGraphView::setPointsProvider(MgPointsProvider *arg)
{
    if (m_pointsProvider != arg) {

        if(m_pointsProvider)
            disconnect(m_pointsProvider,SIGNAL(newPoint(float,float)),this,SLOT(addPoint(float,float)));
        m_pointsProvider = arg;
        connect(m_pointsProvider,SIGNAL(newPoint(float,float)),SLOT(addPoint(float,float)));
        Q_EMIT pointsProviderChanged(arg);
    }

}


void MgGraphView::setGraphPointsSize(int arg)
{
    if (m_graphPointsSize != arg && !m_graphPointsSize) {
        m_graphPointsSize = arg;
        m_synchroniszed= false;
        Q_EMIT graphPointsSizeChanged(arg);
    }
}

void MgGraphView::setGraphColor(const QColor & arg)
{
    if (m_graphColor != arg) {
        m_graphColor = arg;
        Q_EMIT graphColorChanged(arg);
    }
}

void MgGraphView::setFillColor(QColor arg)
{
    if (m_fillColor != arg) {
        m_fillColor = arg;
        m_synchroniszed= false;
        Q_EMIT fillColorChanged(arg);
    }
}

void MgGraphView::setTimeWindow(float arg)
{
    if (m_timeWindow != arg) {
        m_timeWindow = arg;
        m_synchroniszed= false;
        Q_EMIT timeWindowChanged(arg);
    }
}

QColor MgGraphView::graphColor() const
{
    return m_graphColor;
}

QColor MgGraphView::fillColor() const
{
    return m_fillColor;
}


float MgGraphView::timeWindow() const
{
    return m_timeWindow;
}


float MgGraphView::graphLineWidth() const
{
    return m_graphLineWidth;
}

QSGNode * MgGraphView::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    GraphNode *node= static_cast<GraphNode *>(oldNode);


    if (!node) {
        node = new GraphNode;
        node->line = new LineNode(this);
        node->fill = new FillNode(this);

        node->appendChildNode(node->line);
        node->appendChildNode(node->fill);
    }
    if(!m_synchroniszed)
    {
        node->line->updateGeometry();
        node->fill->updateGeometry();

        m_synchroniszed= true;
    }
    return node;
}



void MgGraphView::addPoint(float time, float value)
{
    m_points<<Point(time,value);
    while(m_points.size()>m_graphPointsSize)
        m_points.removeFirst();


    while (m_points.size()>2 && m_points.last().x- m_points.first().x > m_timeWindow) {
        m_points.removeFirst();
    }


    m_synchroniszed= false;

    setLastTime(time);
    setLastValue(value);
    update();
}



int MgGraphView::xToRelativePosition(float x)
{
    if(!m_points.size() || m_points.size()==1) {
        return 0;
    }

    if(x<m_points.first().x)
        return xToRelativePosition(m_points.first().x);

    if(x>m_points.last().x)
        return xToRelativePosition(m_points.last().x);

    return width() * 0.7 * (x-m_points.first().x) /m_timeWindow;
}

int  MgGraphView::yToRelativePosition(float y)
{
    if(y < m_minY)
        return yToRelativePosition(m_minY);

    if(y>m_maxY)
        return yToRelativePosition(m_maxY);
    return  height() * (1- (y-m_minY)/m_yWindow);
}


void MgGraphView::setLastTime(float arg)
{
    if(m_lastTime != arg)
    {
        m_lastTime = arg;
        Q_EMIT lastTimeChanged(arg);
    }
}

void MgGraphView::setLastValue(float arg)
{
    if(m_lastValue != arg)
    {
        m_lastValue = arg;
        Q_EMIT lastValueChanged(arg);
    }
}



float MgGraphView::lastTime() const
{
    return m_lastTime;
}

float MgGraphView::lastValue() const
{
    return m_lastValue;
}


void MgGraphView::clear()
{
    m_points.clear();
}



void MgGraphView::setGraphLineWidth(float arg)
{
    if (m_graphLineWidth != arg) {
        m_graphLineWidth = arg;
        m_synchroniszed= false;
        Q_EMIT graphLineWidthChanged(arg);
        update();
    }
}


