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
 *       @date:   12.02.2020
 *****************************************************/

#ifndef QTSIMVIEW_RENDERUNIT_H
#define QTSIMVIEW_RENDERUNIT_H

#include <QObject>

#include <QScopedPointer>
#include <QtGui/QVector3D>
#include <memory>

#include "transform.h"
#include "Geometry/mesh.h"
#include "Geometry/grid.h"
#include "Geometry/points.h"

class QOpenGLBuffer;
class QOpenGLShaderProgram;
class QOpenGLVertexArrayObject;

class RenderUnit : public QObject
{
Q_OBJECT
public:
    explicit RenderUnit(QObject *parent = 0);
    ~RenderUnit();

    enum CoordinateMirroring {
        DoNotMirrorCoordinates,
        MirrorYCoordinate
    };

    // All assume that the GL context is current.
    void render();
    void invalidate();

    void setAzimuth(float azimuth);
    void setElevation(float elevation);
    void setDistance(float distance);
    void setCenter(QVector3D center);

    void addGeometry(const std::shared_ptr<Geometry> &geometry);
    std::shared_ptr<Geometry> &getGeometry(const unsigned int& id);

private:
    // all drawable geometry
    std::vector<std::shared_ptr<Geometry>> m_geometries;

    CoordinateMirroring m_coordinateMirroring;

    float m_azimuth;
    float m_elevation;
    float m_distance;
    QVector3D m_center;
};


#endif //QTSIMVIEW_RENDERUNIT_H
