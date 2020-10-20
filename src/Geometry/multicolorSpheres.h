/******************************************************
 *
 *   #, #,         CCCCCC  VV    VV MM      MM RRRRRRR
 *  %  %(  #%%#   CC    CC VV    VV MMM    MMM RR    RR
 *  %    %#  #    CC        V    V  MM M  M MM RR    RR
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
 *       @date:   13.10.20
 *****************************************************/

#ifndef QTOPENGLWINDOW_SAND_H
#define QTOPENGLWINDOW_SAND_H

#include "points.h"

/**
 * \class MCSphereCloud
 *
 * \brief Renderable geometry for point cloud/particle data. Draws
 * given vertices as different colored spheres
 */
class MCSphereCloud : public PointCloud {
public:
    /**
     * Constructor
     */
    MCSphereCloud();

    /**
     * Override this with the render function for the geometry
     * @param eye Eye Position
     * @param mm Model Matrix
     * @param vm View Matrix
     * @param pm Projection Matrix
     */
    void render(const QVector3D &eye, const QMatrix4x4 &mm, const QMatrix4x4 &vm, const QMatrix4x4 &pm) override;

    /**
     * Function to destroy buffers and shader
     */
    void invalidate() override;

    /**
     * Changes points to given array
     * @param dataHead data head of the array data
     * @param length number of elements to draw (1/3 of array length)
     */
    void changePoints(float *dataHead, int length) override;

    /**
     * Sets the list of all possible colors
     * @param colors possible colors
     */
    void setColors(const QList<QVector3D> &colors);
private:
    void initializeBuffers() override;
    void additionalChanges() override;

protected:
    void updateColors();
    void generateColorBuffer();

protected:
    // Color buffer
    QScopedPointer<QOpenGLBuffer> m_colorBuffer;
    // Recolor (if vertex count changed)
    bool m_recolor;
    // Color buffer
    float *m_colors;
    // Possible colors
    QList<QVector3D> m_possibleColors;
};


#endif //QTOPENGLWINDOW_SAND_H
