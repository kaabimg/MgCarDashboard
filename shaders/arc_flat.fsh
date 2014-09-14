varying highp vec2 qt_TexCoord;
uniform lowp float qt_Opacity ;
uniform highp vec4 color1;
uniform highp vec4 color2;
uniform highp vec2 center;
uniform highp float innerRadius;
uniform highp float outerRadius;

uniform lowp bool roundStartAngle;
uniform lowp bool roundEndAngle;


float roundCoef() {

    if(roundStartAngle) {

        if(qt_TexCoord.x<0.05) {
            if(!roundStartAngle)
                return 1.;
            vec2 p = qt_TexCoord;
            p.x *= 20;
            float d = distance(p,vec2(1,0.5));
            if(d<0.5)
                return 1.0;
            return 0 ;
        }
    }

    if(roundEndAngle) {
        if(qt_TexCoord.x>0.95) {
            if(!roundEndAngle)
                return 1.;
            vec2 p = qt_TexCoord;
            p.x -= 0.95;
            p.x *= 20;
            float d = distance(p,vec2(0,0.5));
            if(d<0.5)
                return 1.0;
            return 0;
        }
    }
    return 1.;
}


float antiAliasingCoef() {
    const float offset = 1.5;

    float d = distance(gl_FragCoord.xy,center);
    if(d<outerRadius && d>innerRadius) {
        if(d>=(outerRadius-offset)) {
            return (outerRadius-d)/offset;
        }
        else if(d<=(innerRadius + offset)){
            return (d - innerRadius) /offset;
        }
        return 1.0;
    }
    return 0.0;
}

//////////////////////////////////////////////////////////


void main(void)
{
    gl_FragColor = color1 * antiAliasingCoef() * roundCoef() * qt_Opacity;
}
