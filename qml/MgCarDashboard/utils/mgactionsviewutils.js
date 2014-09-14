



function createCirclePath(ctx,x,y,radius)
{
    ctx.beginPath();
    ctx.arc(
                x,
                y,
                radius,0,Math.PI*2,true);
    ctx.closePath();
}

function createArcPath(ctx,x,y,radius,angle)
{
    ctx.save()
    ctx.beginPath();
    ctx.arc(
                x,
                y,
                radius,0,angle,true);
    ctx.closePath();

}



function strokeAndFillCircle(ctx,x,y,radius)
{
    createCirclePath(ctx,x,y,radius);
    ctx.fill();
    ctx.stroke();
}



function fillCircle(ctx,x,y,radius)
{
    createCirclePath(ctx,x,y,radius)
    ctx.fill();
}


function strokeCircle(ctx,x,y,radius)
{
    createCirclePath(ctx,x,y,radius)
    ctx.stroke();
}

function strokeArk(ctx,x,y,radius,angle)
{
    createArcPath(ctx,x,y,radius,angle)
    ctx.stroke();
}


function drawActionsCircle(ctx)
{
    ctx.globalAlpha = 0.4;

    var dAngle  = Math.PI / 40;

    var angle  = 0,x,y;
    while(angle<= Math.PI * 2)
    {
        x = root.xCenter_ + drawRadius_ * Math.cos(angle);
        y = root.yCenter_ - drawRadius_ * Math.sin(angle);
        if(!isPointInActionsCircle(x,y))
            fillCircle(ctx,x,y,lineCircleRadius);
        angle += dAngle
    }



}


function drawCurrentPosition(ctx)
{
    ctx.globalAlpha = 1 - actionsOpacity;
    ctx.fillStyle = root.actionFillColor;
    fillCircle(ctx,cX_,cY_,currentPositionRadius_);
}


function drawActions(ctx)
{
    if(root.actions.length == 0)
        return;

    ctx.globalAlpha = 1 - actionsOpacity;

    var x_,y_;
    for(var i=0;i<root.actionsRelativePositions_.length;i++)
    {
        x_ = root.xCenter_ + drawRadius_ * root.actionsRelativePositions_[i].x ;
        y_ = root.yCenter_ - drawRadius_ * root.actionsRelativePositions_[i].y;
        drawAction(ctx,actions[i],x_,y_);
    }
}


function drawAction(ctx,action,x,y)
{
    ctx.fillStyle = root.actionFillColor;
    ctx.strokeStyle = root.actionBorderColor;
    strokeAndFillCircle(ctx,x,y,actionRadius_);;
}


function highlightCurrentAction(ctx)
{
    ctx.globalAlpha = 1 - actionsOpacity;
    var dAngle = Math.PI*2/actions.length;
    var x,y;
    x = root.xCenter_ + drawRadius_ * Math.cos(Math.PI/2 + selectedActionIndex_ * dAngle);
    y = root.yCenter_ - drawRadius_ * Math.sin(Math.PI/2 + selectedActionIndex_ * dAngle);
    drawAction(ctx,actions[selectedActionIndex_],x,y);

    ctx.strokeStyle = root.actionHighlightColor;
    ctx.lineWidth = highlightLineWidth;
    strokeCircle(ctx,x,y,actionRadius_*1.4);

}


function currentPositionAction()
{
    if(root.actions.length == 0)
        return -1;
    var x_,y_;
    for(var i=0;i<root.actionsRelativePositions_.length;i++)
    {
        x_ = root.xCenter_ + drawRadius_ * root.actionsRelativePositions_[i].x - root.cX_;
        y_ = root.yCenter_ - drawRadius_ * root.actionsRelativePositions_[i].y - root.cY_;

        if (Math.sqrt( x_*x_ + y_*y_)<=root.actionRadius_)
            return i;
    }

    return -1;
}


function calculateActionsPositions()
{
    root.actionsRelativePositions_ = new Array ();
    var dAngle = Math.PI*2/actions.length;
    var x,y;

    for(var i=0;i<root.actions.length;i++)
    {
        x = Math.cos(Math.PI/2 + i * dAngle);
        y = Math.sin(Math.PI/2 + i * dAngle);
        root.actionsRelativePositions_[i] = Qt.point(x,y);
    }
}


function isPointInActionsCircle(x,y)
{
    var x_,y_;
    for(var i=0;i<root.actionsRelativePositions_.length;i++)
    {
        x_ = root.xCenter_ + drawRadius_ * root.actionsRelativePositions_[i].x - x;
        y_ = root.yCenter_ - drawRadius_ * root.actionsRelativePositions_[i].y - y;

        if (Math.sqrt( x_*x_ + y_*y_)<root.actionRadius_+root.lineCircleRadius)
            return true;
    }


    return false;
}

