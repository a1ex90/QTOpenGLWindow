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

/**
 * \class Grid
 *
 * \brief Renderable geometry for a checkboard grid.
 */
class Grid : public Geometry {
public:
    /**
     * Constructor
     */
    Grid();

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
     * Initializes the grid with center at given position
     * @param offset center of the grid
     */
    void initGrid(QVector3D offset);

private:
    void initializeBuffers() override;
    void additionalChanges() override;
    void initGrid();
protected:
    // Grid Vertex position buffer
    QScopedPointer<QOpenGLBuffer> m_positionsBuffer;
    // Grid Texture Coordinates buffer
    QScopedPointer<QOpenGLBuffer> m_texCoordBuffer;
    // Triangle indices buffer
    QScopedPointer<QOpenGLBuffer> m_indicesBuffer;
    // Grid offset from 0,0,0
    QVector3D m_offset;
    // Weather the grid has been initialized
    bool m_gridInitialized;
};

#endif //QTSIMVIEW_GRID_H
