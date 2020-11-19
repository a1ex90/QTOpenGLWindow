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
#include "Transformation/transform.h"
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
    void render(const QVector3D &eye, const QMatrix4x4 &mm, const QMatrix4x4 &vm, const QMatrix4x4 &pm) override;

    /**
     * Function to destroy buffers and shader
     */
    void invalidate() override;

    /**
     * Changes mesh to given .obj file
     * @param file filepath to .obj file
     */
    void changeMesh(const QString &file);

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
    void updateExternalTransform(const QMatrix4x4 &transform);

    /**
     * Sets external transformation that's applied to the internal
     * @param transform External transformation 4x4 Matrix data (column major)
     */
    void updateExternalTransform(const float* transform);

    /**
     * Sets the material colors
     * @param diffuse Diffuse (Base color)
     * @param ambient Ambient (Shadow color)
     * @param specular Specular (Highlight color)
     * @param shininess Shininess
     */
    void setMaterial(const QVector3D &diffuse, const QVector3D &ambient = QVector3D(0,0,0), const QVector3D &specular = QVector3D(0,0,0), const float &shininess = 32.0f);

    /**
     * Sets the opacity (1 opaque / 0 transparent)
     * @param opacity
     */
    void setOpacity(const float &opacity);
    /**
     * Sets the lighting
     * @param pos Positon of the point light
     * @param intensities Intensity (color of the light)
     */
    void setLight(const QVector3D &pos, const QVector3D &intensities = QVector3D(1,1,1));
private:
    void initializeBuffers() override;
    void additionalChanges() override;
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
    // Object opacity
    float m_opacity;
    // Light position
    QVector4D m_lightPos;
    // Light intensity
    QVector3D m_lightIntensity;
};

#endif //QTSIMVIEW_MESH_H