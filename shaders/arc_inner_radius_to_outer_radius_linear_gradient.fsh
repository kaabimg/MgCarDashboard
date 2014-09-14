varying highp vec2 qt_TexCoord;
uniform lowp float qt_Opacity ;
uniform highp vec4 color1;
uniform highp vec4 color2;
uniform highp vec2 center;
uniform highp float innerRadius;
uniform highp float outerRadius;

float antiAliasingCoef(float d) {
    const float offset = 1.5;


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


float color1Coef(float d) {
    float c = (d-innerRadius)/(outerRadius-innerRadius);
    return 1-c;
}

float color2Coef(float d) {
    float c = (outerRadius-d)/(outerRadius-innerRadius);
    return 1-c;
}

void main(void)
{
    float d = distance(gl_FragCoord.xy,center);
    gl_FragColor = (color1 * color1Coef(d) + color2*color2Coef(d)) * antiAliasingCoef(d) * qt_Opacity;

}

