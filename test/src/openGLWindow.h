/******************************************************
 *
 *   #, #,         CCCCCC  VV    VV MM      MM RRRRRRR
 *  %  %(  #%%#   CC    CC VV    VV MMM    MMM RR    RR
 *  %    %## #    CC        V    V  MM M  M MM RR    RR
 *   ,%      %    CC        VV  VV  MM  MM  MM RRRRRR
 *   (%      %,   CC    CC   VVVV   MM      MM RR   RR
 *     #%    %*    CCCCCC     VV    MM      MM RR    RR
 *    .%    %/
 *       (%.      Computer Vision & Mixed Reality Group
 *
 *****************************************************/
/** @copyright:   Hochschule RheinMain,
 *                University of Applied Sciences
 *     @author:   Alex Sommer
 *    @version:   1.0
 *       @date:   12.02.20
 *****************************************************/

#ifndef QTSIMVIEW_OPENGLWINDOW_H
#define QTSIMVIEW_OPENGLWINDOW_H

#include "fbo.h"

#include "transform.h"

class MyFrameBufferObject : public FrameBufferObject
{
Q_OBJECT

public:
    explicit MyFrameBufferObject(QQuickItem *parent = 0);
    Renderer *createRenderer() const Q_DECL_OVERRIDE;
};

#endif //QTSIMVIEW_OPENGLWINDOW_H
