#ifndef MGTEXTURESPROVIDER_H
#define MGTEXTURESPROVIDER_H

#include <QImage>
#include <QDebug>
#include <math.h>
//InnerRadiusToOuterRadiusLinearGradient,
//InnerRadiusToOuterRadiusExponentialGradient,
//Glow,
//ThinGlow
namespace MgTexturesProvider {

struct ValueProvider {
    virtual uchar oparator()(int /*index*/,int /*total*/){
        return 0;
    }

};

struct GlowValue  : ValueProvider{
    uchar oparator()(int index,int total){
        double coeff = 0.5- index*1. / (total-1);
        coeff = exp(-coeff*coeff*50);
        qDebug()<<index<<(uchar)(coeff * 255);
        return coeff * 255;
    }
};


inline QImage genrateImage(int size,const ValueProvider & valueProvider) {
    QImage image  = QImage(size,1, QImage::Format_ARGB32);
    uint *data = (uint *) image.bits();
    for (int index=0; i<size; ++index) {
         data[i] = valueProvider(index,size);
    }
    //0xAARRGGBB
    return image;
}


inline QImage  glowTexture (){
    int size = 100;// 100 uchar == 25 uint
    static QImage image ;
    static bool firstPass = true;
    if(firstPass){
        image = genrateImage(size,GlowValue());
        firstPass = false;
    }
    return image;
}
}




#endif // MGTEXTURESPROVIDER_H
