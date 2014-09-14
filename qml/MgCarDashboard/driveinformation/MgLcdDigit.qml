import QtQuick 2.0


Canvas {
    id : canvas

    property int digit : 10
    property color paintColor : "blue"

    property bool empty : false

    //private:
    property int margin : Math.min(width,height) * 0.1

    property bool drawS1 : false
    property bool drawS2 : false
    property bool drawS3 : false
    property bool drawS4 : false
    property bool drawS5 : false
    property bool drawS6 : false
    property bool drawS7 : false


    property int segmentHeigth : height *0.5 - margin*2.5
    property int segmentWidth : width - 4* margin

    onPaint: {

        var ctx = getContext("2d");


        ctx.clearRect (0, 0, width, height);
        if(empty)
            return;

        ctx.fillStyle = paintColor;
        if(drawS1)drawSegment1(ctx);
        if(drawS2)drawSegment2(ctx);
        if(drawS3)drawSegment3(ctx);
        if(drawS4)drawSegment4(ctx);
        if(drawS5)drawSegment5(ctx);
        if(drawS6)drawSegment6(ctx);
        if(drawS7)drawSegment7(ctx);
    }


    function drawSegment1(ctx) //top : 1
    {
        drawSegment(ctx,2*margin,margin,segmentWidth,margin);
    }


    function drawSegment2(ctx)//left top : 2
    {
        drawSegment(ctx,margin,2*margin,margin, segmentHeigth);
    }

    function drawSegment3(ctx)// left bottom : 3
    {
        drawSegment(ctx,margin,(height+margin)/2  ,margin,segmentHeigth);
    }

    function drawSegment4(ctx) //bottom : 4
    {
        drawSegment(ctx,2*margin,height- 2 *margin,segmentWidth,margin);
    }

    function drawSegment5(ctx)//right bottom : 5
    {
        drawSegment(ctx,width-2*margin,(height+margin)/2 ,margin,segmentHeigth);
    }


    function drawSegment6(ctx)//rigth top : 6
    {
        drawSegment(ctx,width-2*margin,2*margin,margin, segmentHeigth);
    }

    function drawSegment7(ctx) //middle : 7
    {
        drawSegment(ctx,2*margin,(height-margin)/2,segmentWidth,margin);
    }


    function drawSegment(ctx,x,y,w,h)
    {
        ctx.beginPath();
        ctx.roundedRect(x,y,w,h,margin/4,margin/4);
        ctx.closePath();
        ctx.fill();
    }

    onDigitChanged : {

        switch(digit)
        {
            case 0:
                drawS1 = true;
                drawS2 = true;
                drawS3 = true;
                drawS4 = true;
                drawS5 = true;
                drawS6 = true;
                drawS7 = false;
                break;

            case 1:
                drawS1 = false;
                drawS2 = false;
                drawS3 = false;
                drawS4 = false;
                drawS5 = true;
                drawS6 = true;
                drawS7 = false;
                break;

            case 2:
                drawS1 = true;
                drawS2 = false;
                drawS3 = true;
                drawS4 = true;
                drawS5 = false;
                drawS6 = true;
                drawS7 = true;
                break;

            case 3:
                drawS1 = true;
                drawS2 = false;
                drawS3 = false;
                drawS4 = true;
                drawS5 = true;
                drawS6 = true;
                drawS7 = true;
                break;

            case 4:
                drawS1 = false;
                drawS2 = true;
                drawS3 = false;
                drawS4 = false;
                drawS5 = true;
                drawS6 = true;
                drawS7 = true;
                break;

            case 5:
                drawS1 = true;
                drawS2 = true;
                drawS3 = false;
                drawS4 = true;
                drawS5 = true;
                drawS6 = false;
                drawS7 = true;
                break;

            case 6:
                drawS1 = true;
                drawS2 = true;
                drawS3 = true;
                drawS4 = true;
                drawS5 = true;
                drawS6 = false;
                drawS7 = true;
                break;

            case 7:
                drawS1 = true;
                drawS2 = false;
                drawS3 = false;
                drawS4 = false;
                drawS5 = true;
                drawS6 = true;
                drawS7 = false;
                break;

            case 8:
                drawS1 = true;
                drawS2 = true;
                drawS3 = true;
                drawS4 = true;
                drawS5 = true;
                drawS6 = true;
                drawS7 = true;
                break;

            case 9:
                drawS1 = true;
                drawS2 = true;
                drawS3 = false;
                drawS4 = true;
                drawS5 = true;
                drawS6 = true;
                drawS7 = true;
                break;

            default:
                break;

        }

        requestPaint();
    }


}
