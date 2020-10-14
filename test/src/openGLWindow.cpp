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

#include "Helper/plyLoader.h"

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

        std::shared_ptr<MCSphereCloud> ps = std::make_shared<MCSphereCloud>();
        ps->initialize("../../test/assets/shaders/gl3/mcspheres.frag", "../../test/assets/shaders/gl3/mcspheres.vert");

        PlyLoader ply;
        ply.load("/home/alex/Documents/Atrium/Code/AtriumSIM/assets/obj/squirrel2k.ply");
        auto pos = ply.positions();
        m_points = new float[3*pos.count()];
        for(int i = 0; i < pos.count(); i++) {
            m_points[3*i] = pos[i].x();
            m_points[3*i + 1] = pos[i].y();
            m_points[3*i + 2] = pos[i].z();
        }

        QList<QVector3D> possibleColors;
        possibleColors.push_back(QVector3D(0.835, 0.827, 0.525));
        possibleColors.push_back(QVector3D(0.647, 0.639, 0.435));
        possibleColors.push_back(QVector3D(0.337, 0.333, 0.243));
        possibleColors.push_back(QVector3D(0.713, 0.705, 0.345));
        possibleColors.push_back(QVector3D(0.882, 0.882, 0.815));
        possibleColors.push_back(QVector3D(0.870, 0.796, 0.290));
        possibleColors.push_back(QVector3D(0.670, 0.611, 0.211));

        ps->changePoints(m_points, pos.count());
        ps->setColors(possibleColors);
        ps->setPointSize(0.02);
        m_render.addGeometry(ps);

//        std::shared_ptr<Mesh> ms = std::make_shared<Mesh>();
//        ms->initialize("../../test/assets/shaders/gl3/phong.frag", "../../test/assets/shaders/gl3/phong.vert");
//        ms->changeMesh("../../test/assets/obj/cube.obj");
//        Transform t1;
//        float scaling = 0.04;
//        ms->setMaterial(QVector3D(0,1,0));
//        t1.setPos(QVector3D(-0.02f,0.18f,-0.02f));
//        t1.setScale(scaling);
//        ms->setTransform(t1);
//        m_render.addGeometry(ms);

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