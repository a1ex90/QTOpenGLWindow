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

#include "openGLWindow.h"

#include "renderUnit.h"
#include "fboRenderer.h"

#include <QQuickWindow>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFramebufferObjectFormat>

class MyFrameBufferObjectRenderer : public FrameBufferObjectRenderer
{
public:
    MyFrameBufferObjectRenderer()
    {
        std::shared_ptr<Mesh> ms = std::make_shared<Mesh>();
        ms->initialize("../../test/assets/shaders/gl3/phong.frag", "../../test/assets/shaders/gl3/phong.vert");
        ms->changeMesh("../../test/assets/obj/Squirrel.obj");
        Transform t1;
        float scaling = 0.3;
        t1.setPos(scaling * QVector3D(0.05,0.43,4.272));
        t1.setScale(scaling);
        ms->setTransform(t1);
        m_render.addGeometry(ms);

        std::shared_ptr<Grid> gd = std::make_shared<Grid>();
        gd->initialize("../../test/assets/shaders/gl3/checkerboard.frag", "../../test/assets/shaders/gl3/checkerboard.vert");
        gd->initGrid(QVector3D(0,0,0));
        m_render.addGeometry(gd);
    }
};

// MyFrameBufferObject implementation

MyFrameBufferObject::MyFrameBufferObject(QQuickItem *parent)
        : FrameBufferObject(parent)
{}

QQuickFramebufferObject::Renderer *MyFrameBufferObject::createRenderer() const
{
    return new MyFrameBufferObjectRenderer;
}