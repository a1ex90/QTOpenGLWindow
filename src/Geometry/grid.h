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
 *       @date:   11.03.2020
 *****************************************************/

#ifndef QTSIMVIEW_GRID_H
#define QTSIMVIEW_GRID_H

#include "geometry.h"
#include <QOpenGLBuffer>

class Grid : public Geometry {
public:
    Grid();

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
     * Initializes the grid with center at given position
     * @param offset center of the grid
     */
    void initGrid(QVector3D offset);

private:
    virtual void initializeBuffers() override;
protected:
    // Grid Vertex position buffer
    QScopedPointer<QOpenGLBuffer> m_positionsBuffer;
    // Grid Texture Coordinates buffer
    QScopedPointer<QOpenGLBuffer> m_texCoordBuffer;
    // Triangle indices buffer
    QScopedPointer<QOpenGLBuffer> m_indicesBuffer;
};


#endif //QTSIMVIEW_GRID_H
