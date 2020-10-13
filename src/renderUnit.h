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
#include "Geometry/spheres.h"
#include "Geometry/bulk.h"

class QOpenGLBuffer;
class QOpenGLShaderProgram;
class QOpenGLVertexArrayObject;

/**
 * \class RenderUnit
 *
 * \brief Hosts elements rendered by the FBO and specific render function for
 * the FBO. Has methods for panning, zooming and rotation. Actually moves and
 * scales all objects by a model transformation in front of a fixed camera
 * position.
 */
class RenderUnit : public QObject
{
Q_OBJECT
public:
    /**
     * Constructor
     */
    explicit RenderUnit(QObject *parent = 0);

    /**
     * Deconstructor
     */
    ~RenderUnit();

    enum CoordinateMirroring {
        DoNotMirrorCoordinates,
        MirrorYCoordinate
    };

    // All assume that the GL context is current.
    /**
     * Renders all geometries
     */
    void render();

    /**
     * Invalidates all geometries. Removes all shaders and buffers.
     */
    void invalidate();

    /**
     * Arcball rotation
     * @param move current mouse position
     * @param start previous mouse position
     * @param screen window resolution
     */
    void rotate(const QVector2D &move, const QVector2D &start, const QVector2D &screen);

    /**
     * Panning move
     * @param move current mouse position
     * @param start previous mouse position
     * @param screen window resolution
     */
    void pan(const QVector2D &move, const QVector2D &start, const QVector2D &screen);

    /**
     * Zooming
     * @param move current mouse position
     * @param start previous mouse position
     * @param screen window resolution
     */
    void zoom(const QVector2D &move, const QVector2D &start, const QVector2D &screen);

    /**
     * Set center of projection
     * @param center new center to projection
     */
    void setCenter(const QVector3D &center);

    /**
     * Set the background color
     * @param color
     */
    void setBgColor(const QVector4D &color);

    /**
     * Adds given geometry to renderable geometries
     * @param geometry reference to geometry that should be added
     */
    void addGeometry(const std::shared_ptr<Geometry> &geometry);

    /**
     * Returns a reference to the geometry with given id
     * @param id id of desired geometry
     * @return pointer to geometry object
     */
    std::shared_ptr<Geometry> &getGeometry(const unsigned int& id);

    /**
     * Clears all geometries
     */
    void clearGeometries();

    /**
     * Returns the number of renderable geometries
     * @return number of renderable gemeotries
     */
    int geometryCount();

    /**
     * Sets externally the camera transform
     * @return Reference to the camera transform
     */
    Transform& getCameraTransformReference();

private:
    QVector3D projectOnSphere(QVector2D point, const QVector2D &screen, const float &r);

protected:
    // all drawable geometry
    std::vector<std::shared_ptr<Geometry>> m_geometries;
    // Model Transformation
    Transform m_transform;
    // Weather Y-axis is mirrored
    CoordinateMirroring m_coordinateMirroring;
    // Center of projection
    QVector3D m_center;
    // Eye position;
    QVector3D m_eye;
    // Background color
    QVector4D m_bg_color;

};


#endif //QTSIMVIEW_RENDERUNIT_H
