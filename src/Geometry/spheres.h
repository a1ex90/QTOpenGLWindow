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
 *       @date:   10.07.20
 *****************************************************/

#ifndef QTOPENGLWINDOW_SPHERES_H
#define QTOPENGLWINDOW_SPHERES_H

#include "points.h"


class SphereCloud : public PointCloud {
public:
    /**
     * Constructor
     */
    SphereCloud();

    /**
     * Override this with the render function for the geometry
     * @param eye Eye Position
     * @param mm Model Matrix
     * @param vm View Matrix
     * @param pm Projection Matrix
     */
    void render(const QVector3D &eye, const QMatrix4x4 &mm, const QMatrix4x4 &vm, const QMatrix4x4 &pm) override;

protected:

};


#endif //QTOPENGLWINDOW_SPHERES_H
