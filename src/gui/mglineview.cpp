#include "mglineview.h"

#include <QSGGeometryNode>

#include <QSGSimpleMaterialShader>
#include <QSGGeometryNode>
#include <QDebug>

struct LineMaterial
{
    QColor color1;
    QColor color2;
    bool roundExtremities;
};

#define LINE_MATERIAL(Name) \
struct Name : LineMaterial{};



class LineShader : public QSGSimpleMaterialShader<LineMaterial>
{
    public:
        LineShader(const QByteArray & fsh_)
      : vsh(readResource(":/shaders/line.vsh")),fsh(fsh_){}
    const char *vertexShader() const {
        return vsh.constData();
    }

    const char *fragmentShader() const {
        return fsh.constData();

    }
    QList<QByteArray> attributes() const {  return QList<QByteArray>() << "qt_VertexPosition"<<"qt_VertexTexCoord"; }

    void updateState(const LineMaterial *m, const LineMaterial *) {
        if(id_color1>-1) QSGMaterialShader::program()->setUniformValue(id_color1, m->color1);
        if(id_color2>-1) QSGMaterialShader::program()->setUniformValue(id_color2, m->color2);


    }

    void resolveUniforms() {
        id_color1 = QSGMaterialShader::program()->uniformLocation("color1");
        id_color2 = QSGMaterialShader::program()->uniformLocation("color2");
    }

    static QByteArray readResource(const char *path) {
        QFile r(path);
        Q_ASSERT(r.open(QFile::ReadOnly));
        return r.readAll();
    }

    int id_color1,id_color2;

    QByteArray vsh;
    QByteArray fsh;
};



#define LINE_SHADER(Name,file) \
LINE_MATERIAL(Name##Material)\
struct Name : LineShader {\
    QSG_DECLARE_SIMPLE_SHADER(Name, Name##Material)\
    Name():LineShader(readResource(file)){}\
}\



LINE_SHADER(LineShaderFlat,":/shaders/line_flat.fsh");
LINE_SHADER(LineShaderGlow,":/shaders/line_glow.fsh");





class LineViewNode : public QSGGeometryNode
{
public:
    LineViewNode(MgLineView* lineView_)
        :lineView(lineView_)
    {
        QSGGeometry  * geometry = new QSGGeometry( QSGGeometry::defaultAttributes_TexturedPoint2D(),4);
        geometry->setDrawingMode(GL_TRIANGLE_STRIP);
        setGeometry(geometry);
        setFlag(QSGNode::OwnsGeometry);
        setFlag(OwnsMaterial);
        QSGMaterial *material =0;

        switch (lineView->shadingMode()) {
        case MgLineView::Flat:
            material = LineShaderFlat::createMaterial();
            break;
        case MgLineView::Glow:
            material = LineShaderGlow::createMaterial();
            break;
        default:
            break;
        }
        if(material) {
            material->setFlag(QSGMaterial::Blending,true);
            setMaterial(material);
            updateMaterial();
        }

    }

    void updateMaterial(){
        if(material())
            updateMaterial(static_cast<QSGSimpleMaterial<LineMaterial> *>(material()));

    }

    void updateMaterial(QSGSimpleMaterial<LineMaterial> * material){

        material->state()->color1 = lineView->m_color1;
        material->state()->color2 = lineView->m_color2;
        material->state()->roundExtremities = lineView->m_roundExtremities;
        markDirty(QSGNode::DirtyMaterial);

    }
    void updateGeometry() {
        updateGeometry(geometry());
    }


    void updateGeometry(QSGGeometry  * geometry){
        QVector3D v1(lineView->m_endPoint-lineView->m_startPoint);
        QVector3D v2 = QVector3D::crossProduct(v1*lineView->m_size * 0.5/v1.length(),QVector3D(0,0,1));

        QPointF perpendicularVector(v2.x(),v2.y());
        QPointF point;
        QSGGeometry::TexturedPoint2D * vertices =  geometry->vertexDataAsTexturedPoint2D();
        point = lineView->m_startPoint + perpendicularVector;
        vertices[0].set(point.x(),point.y(),0,0);

        point = lineView->m_startPoint - perpendicularVector;
        vertices[1].set(point.x(),point.y(),0,1);


        point = lineView->m_endPoint + perpendicularVector;
        vertices[2].set(point.x(),point.y(),1,0);

        point = lineView->m_endPoint - perpendicularVector;
        vertices[3].set(point.x(),point.y(),1,1);

        markDirty(QSGNode::DirtyGeometry);
    }

    MgLineView* lineView;
};







/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
MgLineView::MgLineView(QQuickItem *parent) :
    QQuickItem(parent),
    m_roundExtremities(false),
    m_startPoint(0,0),
    m_endPoint(0,0),
    m_size(0),
    m_shadingMode(Flat),
    m_color1(0,0,0,0),
    m_color2(0,0,0,0),
    m_geometryChanged(false),
    m_materialChanged(false)
{
    setFlag(ItemHasContents,true);
}

bool MgLineView::roundExtremities() const
{
    return m_roundExtremities;
}



QPointF MgLineView::startPoint() const
{
    return m_startPoint;
}

QPointF MgLineView::endPoint() const
{
    return m_endPoint;
}

float MgLineView::size() const
{
    return m_size;
}


MgLineView::ShadingMode MgLineView::shadingMode() const
{
    return m_shadingMode;
}

QColor MgLineView::color1() const
{
    return m_color1;
}

QColor MgLineView::color2() const
{
    return m_color2;
}

void MgLineView::setRoundExtremities(bool arg)
{
    if (m_roundExtremities != arg) {
        m_roundExtremities = arg;
        Q_EMIT roundExtremitiesChanged();
        m_materialChanged =  true;
        update();
    }
}



void MgLineView::setStartPoint(QPointF arg)
{
    if (m_startPoint != arg) {
        m_startPoint = arg;
        Q_EMIT startPointChanged();
        m_geometryChanged = true;
        update();
    }
}

void MgLineView::setEndPoint(QPointF arg)
{
    if (m_endPoint != arg) {
        m_endPoint = arg;
        Q_EMIT endPointChanged();
        m_geometryChanged = true;
        update();
    }
}

void MgLineView::setSize(float arg)
{
    if (m_size != arg) {
        m_size = arg;
        Q_EMIT sizeChanged();
        m_geometryChanged = true;
        update();
    }
}

void MgLineView::setShadingMode(MgLineView::ShadingMode arg)
{
    if (m_shadingMode != arg) {
        m_shadingMode = arg;
        Q_EMIT shadingModeChanged();
        update();
    }
}

void MgLineView::setColor1(const QColor &arg)
{
    if (m_color1 != arg) {
        m_color1 = arg;
        Q_EMIT color1Changed();
        m_materialChanged = true;
        update();
    }
}

void MgLineView::setColor2(const QColor &arg)
{
    if (m_color2 != arg) {
        m_color2 = arg;
        Q_EMIT color2Changed();
        m_materialChanged = true;
        update();
    }
}





QSGNode *MgLineView::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *)
{
    LineViewNode *node= static_cast<LineViewNode *>(oldNode);
    if (!node) {
        node = new LineViewNode(this);
    }

    if(m_geometryChanged) {
        node->updateGeometry();
        m_geometryChanged = false;
    }
    if(m_materialChanged) {
        node->updateMaterial();
        m_materialChanged = false;
    }
    return node;
}
