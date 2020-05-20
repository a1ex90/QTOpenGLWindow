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

#ifndef QTSIMVIEW_MESH_H
#define QTSIMVIEW_MESH_H

#include "geometry.h"
#include "../transform.h"
#include <QOpenGLBuffer>

class Mesh : public Geometry {
public:
    Mesh();

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
     * Changes mesh to given .obj file
     * @param file filepath to .obj file
     */
    void changeMesh(QString file);

    /**
     * Function to clear buffers
     */
    void flush();

    /**
     * Sets Position, Roation and Scaling of the mesh
     * @param transform
     */
    void setTransform(Transform transform);

    /**
     * Sets external transformation that's applied to the internal
     * @param transform External transformation 4x4 Matrix
     */
    void updateExternalTransform(QMatrix4x4 transform);
private:
    virtual void initializeBuffers() override;
protected:
    // Vertex position buffer
    QScopedPointer<QOpenGLBuffer> m_positionsBuffer;
    // Vertex normals buffer
    QScopedPointer<QOpenGLBuffer> m_normalsBuffer;
    // Triangle indices buffer
    QScopedPointer<QOpenGLBuffer> m_indicesBuffer;
    // Position, Rotation and Scaling transformation
    Transform m_transform;
    // External editable transformation
    QMatrix4x4 m_externalTransform;
};


#endif //QTSIMVIEW_MESH_H
