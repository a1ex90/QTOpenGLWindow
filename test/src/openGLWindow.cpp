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
//        std::shared_ptr<Mesh> ms = std::make_shared<Mesh>();
//        ms->initialize("../../test/assets/shaders/gl3/phong.frag", "../../test/assets/shaders/gl3/phong.vert");
//        ms->changeMesh("../../test/assets/obj/Squirrel.obj");
//        Transform t1;
//        float scaling = 0.3;
//        t1.setPos(scaling * QVector3D(0.05,0.43,4.272));
//        t1.setScale(scaling);
//        ms->setTransform(t1);
//        m_render.addGeometry(ms);

        std::shared_ptr<BulkCloud> ps = std::make_shared<BulkCloud>();
        ps->initialize("../../test/assets/shaders/gl3/bulk.frag", "../../test/assets/shaders/gl3/bulk.vert");
        m_points = new float[9];
        m_points[0] = 0.0f;
        m_points[1] = 0.2f;
        m_points[2] = 0.0f;
        m_points[3] = 0.2f;
        m_points[4] = 0.2f;
        m_points[5] = 0.0f;
        m_points[6] = -0.2f;
        m_points[7] = 0.2f;
        m_points[8] = 0.0f;
        ps->changePoints(m_points, 3);
        ps->setColor(QVector3D(1.0,0,0));
        ps->setPointSize(0.02);
        m_render.addGeometry(ps);

        std::shared_ptr<Mesh> ms = std::make_shared<Mesh>();
        ms->initialize("../../test/assets/shaders/gl3/phong.frag", "../../test/assets/shaders/gl3/phong.vert");
        ms->changeMesh("../../test/assets/obj/cube.obj");
        Transform t1;
        float scaling = 0.04;
        t1.setPos(QVector3D(-0.02f,0.18f,-0.02f));
        t1.setScale(scaling);
        ms->setTransform(t1);
        m_render.addGeometry(ms);

//        std::shared_ptr<PointCloud> ps2 = std::make_shared<PointCloud>();
//        ps2->initialize("../../test/assets/shaders/gl3/part.frag", "../../test/assets/shaders/gl3/part.vert");
//        m_points2 = new float[3];
//        m_points2[0] = 0.0f;
//        m_points2[1] = 0.4f;
//        m_points2[2] = 0.0f;
//        ps2->changePoints(m_points2, 1);
//        ps2->setColor(QVector3D(1.0,0,0));
//        ps2->setPointSize(3);
//        m_render.addGeometry(ps2);

        std::shared_ptr<Grid> gd = std::make_shared<Grid>();
        gd->initialize("../../test/assets/shaders/gl3/checkerboard.frag", "../../test/assets/shaders/gl3/checkerboard.vert");
        gd->initGrid(QVector3D(0,0,0));
        m_render.addGeometry(gd);
    }

    void addSync(QQuickFramebufferObject *item) Q_DECL_OVERRIDE
    {
        for (int j = 0; j < m_render.geometryCount(); j++) {
            m_render.getGeometry(j)->performChanges();
        }
    }

protected:
    float *m_points;
    float *m_points2;
};

// MyFrameBufferObject implementation

MyFrameBufferObject::MyFrameBufferObject(QQuickItem *parent)
        : FrameBufferObject(parent)
{}

QQuickFramebufferObject::Renderer *MyFrameBufferObject::createRenderer() const
{
    return new MyFrameBufferObjectRenderer;
}