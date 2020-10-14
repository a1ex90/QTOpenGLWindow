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

#ifndef QTSIMVIEW_MESH_H
#define QTSIMVIEW_MESH_H

#include "geometry.h"
#include "../transform.h"
#include <QOpenGLBuffer>

/**
 * \class Mesh
 *
 * \brief Renderable geometry for triangular meshes. Draws
 * given vertices as a shaded mesh.
 */
class Mesh : public Geometry {
public:
    /**
     * Constructor
     */
    Mesh();

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

    /**
     * Sets external transformation that's applied to the internal
     * @param transform External transformation 4x4 Matrix data (column major)
     */
    void updateExternalTransform(float* transform);

    /**
     * Sets the material colors
     * @param diffuse Diffuse (Base color)
     * @param ambient Ambient (Shadow color)
     * @param specular Specular (Highlight color)
     * @param shininess Shininess
     */
    void setMaterial(QVector3D diffuse, QVector3D ambient = QVector3D(0,0,0), QVector3D specular = QVector3D(0,0,0), float shininess = 32.0f);

    /**
     * Sets the lighting
     * @param pos Positon of the point light
     * @param intensities Intensity (color of the light)
     */
    void setLight(QVector3D pos, QVector3D intensities = QVector3D(1,1,1));
private:
    virtual void initializeBuffers() override;
    virtual void additionalChanges() override;
    void changeMesh();
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
    // Mesh file
    QString m_meshFile;
    // Weather the mesh has been loaded to buffers
    bool m_fileChangeLoaded;
    // Ambient color
    QVector3D m_ambient;
    // Diffuse color
    QVector3D m_diffuse;
    // Specular color
    QVector3D m_specular;
    // Shininess
    float m_shininess;
    // Light position
    QVector4D m_lightPos;
    // Light intensity
    QVector3D m_lightIntensity;
};

#endif //QTSIMVIEW_MESH_H