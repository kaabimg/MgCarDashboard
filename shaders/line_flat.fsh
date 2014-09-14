varying highp vec2 qt_TexCoord;
uniform lowp float qt_Opacity ;
uniform highp vec4 color1;
uniform highp vec4 color2;
uniform lowp bool roundExtremities;

const float offset = 0.005;

float xAntiAliasingCoef() {

    float d = abs(qt_TexCoord.x -0.5) * 2;
    if(d<1 ) {
        if(d> 1 - offset){
            return (1-d)/offset;
        }
        return 1.0;
    }
    return 0.0;
}


float yAntiAliasingCoef() {
    float d = abs(qt_TexCoord.y -0.5) * 2;
    if(d<1 ) {
        if(d> 1 - offset){
            return (1-d)/offset;
        }
        return 1.0;
    }
    return 0.0;
}

//////////////////////////////////////////////////////////


void main(void)
{
    gl_FragColor = color1 * xAntiAliasingCoef( )* yAntiAliasingCoef()*  qt_Opacity;
}
