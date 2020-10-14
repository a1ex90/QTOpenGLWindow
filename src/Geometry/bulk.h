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


class BulkCloud : public PointCloud {
public:
    /**
     * Constructor
     */
    BulkCloud();

    /**
     * Override this with the render function for the geometry
     * @param eye Eye Position
     * @param mm Model Matrix
     * @param vm View Matrix
     * @param pm Projection Matrix
     */
    virtual void render(const QVector3D &eye, const QMatrix4x4 &mm, const QMatrix4x4 &vm, const QMatrix4x4 &pm) override;

    /**
     * Function to destroy buffers and shader
     */
    virtual void invalidate() override;

    /**
     * Changes points to given array
     * @param dataHead data head of the array data
     * @param length number of elements to draw (1/3 of array length)
     */
    void changePoints(float *dataHead, int length);
private:
    virtual void initializeBuffers() override;
    virtual void additionalChanges() override;

protected:
    void updateColors();
    void generateColors();

protected:
    // Color buffer
    QScopedPointer<QOpenGLBuffer> m_colorBuffer;
    // Recolor (if vertex count changed)
    bool m_recolor;
    // Colors
    float *m_colors;
};


#endif //QTOPENGLWINDOW_SAND_H
