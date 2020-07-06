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
 *       @date:   11.03.20
 *****************************************************/

#ifndef QTSIMVIEW_POINTS_H
#define QTSIMVIEW_POINTS_H

#include "geometry.h"
#include <QOpenGLBuffer>

/**
 * \class PointCloud
 *
 * \brief Renderable geometry for point cloud/particle data. Draws
 * given vertices as points.
 */
class PointCloud : public Geometry {
public:
    /**
     * Constructor
     */
    PointCloud();

    /**
     * Render function for the geometry
     * @param mm Model Matrix
     * @param vm View Matrix
     * @param pm Projection Matrix
     */
    virtual void render(QMatrix4x4 mm, QMatrix4x4 vm, QMatrix4x4 pm) override;

    /**
     * Function to destroy buffers and shader
     */
    virtual void invalidate() override;

    /**
     * Changes points to given .ply file
     * @param file filepath to .ply file
     */
    void changePoints(QString file);

    /**
     * Changes points to given array
     * @param dataHead data head of the array data
     * @param length number of elements to draw (1/3 of array length)
     */
    void changePoints(float *dataHead, int length);

    /**
     * Sets the color in which the points should be drawn
     * @param color desired color
     */
    void setColor(QVector3D color);

    /**
     * Sets the rendered size of the points
     * @param ps desired point size
     */
    void setPointSize(const float &ps);

    /**
     * Function to clear buffers
     */
    void flush();

    /**
     * Returns the center of gravity of the point cloud
     * @return point cloud centroid
     */
    QVector3D centroid();

private:
    virtual void initializeBuffers() override;
protected:
    // Points position buffer
    QScopedPointer<QOpenGLBuffer> m_positionsBuffer;
    // Center of gravity of the point cloud
    QVector3D m_centroid;
    // Color of points
    QVector3D m_color;
    // Size of the points
    float m_pointSize;
};

#endif //QTSIMVIEW_POINTS_H
