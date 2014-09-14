#include "mgarcview.h"

#include <QSGGeometry>
#include <QSGGeometryNode>
#include <QSGSimpleMaterialShader>
#include <QResource>
#include <math.h>
#include <QQuickWindow>
#include <QtQuick/QSGSimpleMaterial>
#include <QSGTexture>

namespace ArcConstants {
static const float PI_2 = 2 * M_PI;
}


struct ArcMaterial
{
    QColor color1;
    QColor color2;
    QPointF center;
    float innerRadius,outerRadius;
    bool roundStartAngle,roundEndAngle;
    QSGTexture *texture;
};

#define ARC_MATERIAL(Name) \
    struct Name : ArcMaterial{};



class ArcShader : public QSGSimpleMaterialShader<ArcMaterial>
{
public:
    ArcShader(const QByteArray & fsh_)
        : vsh(readResource(":/shaders/arc.vsh")),fsh(fsh_){}
    const char *vertexShader() const {
        return vsh.constData();
    }

    const char *fragmentShader() const {
        return fsh.constData();

    }
    QList<QByteArray> attributes() const {  return QList<QByteArray>() << "qt_VertexPosition"<<"qt_VertexTexCoord"; }

    void updateState(const ArcMaterial *m, const ArcMaterial *) {
        if(id_color1>-1) QSGMaterialShader::program()->setUniformValue(id_color1, m->color1);
        if(id_color2>-1) QSGMaterialShader::program()->setUniformValue(id_color2, m->color2);
        if(id_center>-1) QSGMaterialShader::program()->setUniformValue(id_center,m->center);
        if(id_innerRadius>-1) QSGMaterialShader::program()->setUniformValue(id_innerRadius,m->innerRadius);
        if(id_outerRadius>-1) QSGMaterialShader::program()->setUniformValue(id_outerRadius,m->outerRadius);
        if(id_roundStartAngle>-1) QSGMaterialShader::program()->setUniformValue(id_roundStartAngle,m->roundStartAngle);
        if(id_roundEndAngle>-1) QSGMaterialShader::program()->setUniformValue(id_roundEndAngle,m->roundEndAngle);
        if(id_texture>-1){
            QSGMaterialShader::program()->setUniformValue(id_texture, 0);
            m->texture->bind();
        }


    }

    void resolveUniforms() {
        id_color1 = QSGMaterialShader::program()->uniformLocation("color1");
        id_color2 = QSGMaterialShader::program()->uniformLocation("color2");
        id_center = QSGMaterialShader::program()->uniformLocation("center");
        id_innerRadius = QSGMaterialShader::program()->uniformLocation("innerRadius");
        id_outerRadius = QSGMaterialShader::program()->uniformLocation("outerRadius");
        id_roundStartAngle = QSGMaterialShader::program()->uniformLocation("roundStartAngle");
        id_roundEndAngle = QSGMaterialShader::program()->uniformLocation("roundEndAngle");
        id_texture = QSGMaterialShader::program()->uniformLocation("texture");
    }

    static QByteArray readResource(const char *path) {
        QFile r(path);
        Q_ASSERT(r.open(QFile::ReadOnly));
        return r.readAll();
    }

    int id_color1,id_color2;
    int id_center;
    int id_innerRadius,id_outerRadius;
    int id_roundStartAngle,id_roundEndAngle;
    int id_texture;
    QByteArray vsh;
    QByteArray fsh;
};



#define ARC_SHADER(Name,file) \
    ARC_MATERIAL(Name##Material)\
    struct Name : ArcShader {\
    QSG_DECLARE_SIMPLE_SHADER(Name, Name##Material)\
    Name():ArcShader(readResource(file)){}\
    }\



ARC_SHADER(ArcShaderFlat,":/shaders/arc_flat.fsh");
ARC_SHADER(ArcShaderGlow,":/shaders/arc_glow.fsh");
ARC_SHADER(ArcShaderThinGlow,":/shaders/arc_glow_thin.fsh");
ARC_SHADER(ArcShaderInnerRadiusToOuterRadiusLinear,":/shaders/arc_inner_radius_to_outer_radius_linear_gradient.fsh");
ARC_SHADER(ArcShaderInnerRadiusToOuterRadiusExponential,":/shaders/arc_inner_radius_to_outer_radius_exponential_gradient.fsh");



class ArcNode : public QSGGeometryNode
{
public:
    ArcNode(MgArcView* arcView_)
        :arcView(arcView_)
    {
        QSGGeometry  * geometry = new QSGGeometry(
                    QSGGeometry::defaultAttributes_TexturedPoint2D(),
                    2 *arcView->m_pointsSize + 2
                    );
        geometry->setDrawingMode(GL_TRIANGLE_STRIP);
        setGeometry(geometry);
        setFlag(QSGNode::OwnsGeometry);
        setFlag(OwnsMaterial);
        QSGMaterial *material ;

        switch (arcView->shadingMode()) {
        case MgArcView::Flat:
            material = ArcShaderFlat::createMaterial();
            break;
        case MgArcView::InnerRadiusToOuterRadiusLinearGradient:
            material = ArcShaderInnerRadiusToOuterRadiusLinear::createMaterial();
            break;
        case MgArcView::InnerRadiusToOuterRadiusExponentialGradient:
            material = ArcShaderInnerRadiusToOuterRadiusExponential::createMaterial();
            break;
        case MgArcView::Glow:
            material = ArcShaderGlow::createMaterial();
            break;
        case MgArcView::ThinGlow:
            material = ArcShaderThinGlow::createMaterial();
            break;
        default:
            material = 0;
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
            updateMaterial(static_cast<QSGSimpleMaterial<ArcMaterial> *>(material()));
    }

    void updateMaterial(QSGSimpleMaterial<ArcMaterial> * material){
        material->state()->color1 = arcView->m_color1;
        material->state()->color2 = arcView->m_color2;

        float radius =  arcView->m_diameter/2;

        material->state()->center = arcView->mapToScene(QPointF(arcView->width()/2,0));
        material->state()->center.setY( arcView->height()/2);

        material->state()->innerRadius = arcView->m_innerRadius* radius;
        material->state()->outerRadius = arcView->m_outerRadius* radius;
        material->state()->roundStartAngle = arcView->m_roundStartAngle;
        material->state()->roundEndAngle = arcView->m_roundEndAngle;

        markDirty(QSGNode::DirtyMaterial);
    }
    void updateGeometry() {
        updateGeometry(geometry());
    }



    float roundRadius(float xIndex)const {



        float m = (arcView->m_outerRadius - arcView->m_innerRadius)/2;
        if(xIndex<.5){//begin arc
            return arcView->m_diameter * arcView->m_innerRadius + m * xIndex * xIndex*xIndex;
        }
        else {
            float i = (1-xIndex);
            return arcView->m_diameter * arcView->m_outerRadius - m * i * i * i;
        }

    }

    void updateGeometry(QSGGeometry  * geometry){
        int size = geometry->vertexCount();
        int newSize = 2 *arcView->m_pointsSize + 2;


        if(size != newSize)
            geometry->allocate(newSize);

        QSGGeometry::TexturedPoint2D * vertices = geometry->vertexDataAsTexturedPoint2D();


        float endAngle = arcView->m_endAngle;
        while(endAngle>arcView->m_startAngle)
            endAngle -= ArcConstants::PI_2;

        while(endAngle+ ArcConstants::PI_2<arcView->m_startAngle )
            endAngle += ArcConstants::PI_2;

        size = arcView->m_pointsSize+1;

        float dAngle = ( arcView->m_startAngle-endAngle) /(arcView->m_pointsSize);
        float angle,colorIndex;

        float xCenter,yCenter;
        xCenter = arcView->width()/2;
        yCenter = arcView->height()/2;

        for(int i = 0;i<size;++i) {
            colorIndex =  i;
            colorIndex /= arcView->m_pointsSize;
            angle = arcView->m_startAngle -dAngle*i;
            vertices[2*i].set(
                        xCenter + arcView->m_diameter * arcView->m_innerRadius * cos(angle)/2,
                        yCenter - arcView->m_diameter * arcView->m_innerRadius * sin(angle)/2,
                        colorIndex,
                        1
                        );
            vertices[2*i+1].set(
                        xCenter + arcView->m_diameter * arcView->m_outerRadius * cos(angle)/2,
                        yCenter - arcView->m_diameter * arcView->m_outerRadius * sin(angle)/2,
                        colorIndex,
                        0
                        );
        }

        if(arcView->m_fullDisk) {
            vertices[2*arcView->m_pointsSize].set
                    (vertices[0].x,
                    vertices[0].y,
                    1,
                    1
                    );
            vertices[2*arcView->m_pointsSize+1].set(vertices[1].x,vertices[1].y,
                    0,
                    1);
        }
        markDirty(QSGNode::DirtyGeometry);
    }

    MgArcView* arcView;
};





///////////////////////////////////////
///////////////////////////////////////
MgArcView::MgArcView(QQuickItem *parent) :
    QQuickItem(parent),
    m_innerRadius(0),
    m_outerRadius(1),
    m_startAngle(0),
    m_endAngle(1.99 * M_PI),
    m_pointsSize(100),
    m_geometryChanged(true),
    m_materialChanged(true),
    m_shadingModeChanged(true),
    m_fullDisk(false),
    m_shadingMode(Flat)
{
    setFlag(ItemHasContents, true);
    setAntialiasing(true);
    setSmooth(true);
    setDiameter(0);

    connect(this,SIGNAL(widthChanged()),this,SLOT(handleSizeChanged()));
    connect(this,SIGNAL(heightChanged()),this,SLOT(handleSizeChanged()));
}

void MgArcView::handleSizeChanged()
{
    m_geometryChanged = true;
    m_materialChanged = true;
    update();
}


float MgArcView::innerRadius() const
{
    return m_innerRadius;
}

float MgArcView::outerRadius() const
{
    return m_outerRadius;
}


QColor MgArcView::color1() const
{
    return m_color1;
}

QColor MgArcView::color2() const
{
    return m_color2;
}

bool MgArcView::roundStartAngle() const
{
    return m_roundStartAngle;
}

bool MgArcView::roundEndAngle() const
{
    return m_roundEndAngle;
}


MgArcView::ShadingMode MgArcView::shadingMode() const
{
    return m_shadingMode;
}




bool MgArcView::fullDisk() const
{
    return m_fullDisk;
}


float MgArcView::startAngle() const
{
    return m_startAngle;
}

float MgArcView::endAngle()const
{
    return m_endAngle;
}


int MgArcView::pointsSize() const
{
    return m_pointsSize;
}
float MgArcView::diameter() const
{
    return m_diameter;
}


void MgArcView::setInnerRadius(float arg)
{
    if (m_innerRadius != arg) {
        m_innerRadius = arg;
        Q_EMIT innerRadiusChanged(arg);
        m_geometryChanged = true;
        m_materialChanged = true;
        update();
    }
}

void MgArcView::setOuterRadius(float arg)
{
    if (m_outerRadius != arg) {
        m_outerRadius = arg;
        Q_EMIT outerRadiusChanged(arg);
        m_geometryChanged = true;
        m_materialChanged = true;
        update();
    }
}

void MgArcView::setStartAngle(float arg)
{
    if (m_startAngle != arg) {
        m_startAngle = arg;
        Q_EMIT startAngleChanged(arg);
        m_geometryChanged = true;
        update();
    }
}


void MgArcView::setEndAngle(float arg)
{
    if (m_endAngle != arg) {
        m_endAngle = arg;
        Q_EMIT endAngleChanged(arg);
        m_geometryChanged = true;
        update();
    }
}


void MgArcView::setPointsSize(int arg)
{
    if (m_pointsSize != arg && arg > 2) {
        m_pointsSize = arg;
        Q_EMIT pointsSizeChanged(arg);
        m_geometryChanged = true;
        update();
    }
}

void MgArcView::setDiameter(float arg)
{
    if (m_diameter != arg && arg >= 0) {
        m_diameter = arg;
        Q_EMIT diameterChanged(arg);
        m_geometryChanged = true;
        m_materialChanged = true;
        update();
    }
}


void MgArcView::setFullDisk(bool arg)
{
    if (m_fullDisk != arg) {
        m_fullDisk = arg;
        Q_EMIT fullDiskChanged(arg);
        m_geometryChanged = true;
        update();
    }
}



void MgArcView::setColor1(const QColor &arg)
{
    if (m_color1 != arg) {
        m_color1 = arg;
        Q_EMIT color1Changed(arg);
        m_materialChanged = true;
        update();
    }
}

void MgArcView::setColor2(const QColor &arg)
{
    if (m_color2 != arg) {
        m_color2 = arg;
        Q_EMIT color2Changed(arg);
        m_materialChanged = true;
        update();
    }
}



void MgArcView::setShadingMode(MgArcView::ShadingMode arg)
{
    if (m_shadingMode != arg) {
        m_shadingMode = arg;
        Q_EMIT shadingModeChanged(arg);
        m_shadingModeChanged = true;
        update();
    }
}

void MgArcView::setRoundStartAngle(bool arg)
{
    if (m_roundStartAngle != arg) {
        m_roundStartAngle = arg;
        Q_EMIT roundStartAngleChanged(arg);
        m_materialChanged = true;
        update();
    }
}

void MgArcView::setRoundEndAngle(bool arg)
{
    if (m_roundEndAngle != arg) {
        m_roundEndAngle = arg;
        Q_EMIT roundEndAngleChanged(arg);
        m_geometryChanged = true;
        update();
    }
}



///////////////////////////////////////////////:


QSGNode *MgArcView::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *)
{
    ArcNode *node= static_cast<ArcNode *>(oldNode);
    if (!node) {
        node = new ArcNode(this);
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



