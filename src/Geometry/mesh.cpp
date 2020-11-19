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

#include "mesh.h"
#include "../Helper/objLoader.h"
#include <QOpenGLContext>
#include <QOpenGLFunctions>

/******************************************************
 * Constructors
 *****************************************************/

Mesh::Mesh()
        : Geometry(0, GeometryType::MESH)
        , m_positionsBuffer(new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer))
        , m_normalsBuffer(new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer))
        , m_indicesBuffer(new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer))
        , m_transform()
        , m_externalTransform()
        , m_fileChangeLoaded(true)
        , m_ambient(QVector3D(0.1, 0.1, 0.1))
        , m_diffuse(QVector3D(1.0, 0.1, 0.1))
        , m_specular(QVector3D(1.0, 1.0, 1.0))
        , m_shininess(32.0f)
        , m_opacity(1.0f)
        , m_lightPos(QVector4D(0.0, 0.0, 0.0, 1.0))
        , m_lightIntensity(QVector3D(1.0, 1.0, 1.0))
{}

/******************************************************
 * Public Functions
 *****************************************************/

void Mesh::render(const QVector3D &eye, const QMatrix4x4 &modelMatrix, const QMatrix4x4 &viewMatrix, const QMatrix4x4 &projectionMatrix) {
    QOpenGLFunctions *functions = QOpenGLContext::currentContext()->functions();

    const QMatrix4x4 modelViewMatrix = viewMatrix * modelMatrix;

    const QMatrix4x4 meshModelViewMatrix = modelViewMatrix * m_externalTransform * m_transform.getModel();
    const QMatrix4x4 meshModelProjectionMatrix = projectionMatrix * meshModelViewMatrix;

    m_shader->bind();

    m_shader->setUniformValue("modelViewMatrix", meshModelViewMatrix);
    m_shader->setUniformValue("normalMatrix", meshModelViewMatrix.normalMatrix());
    m_shader->setUniformValue("projectionMatrix", projectionMatrix);
    m_shader->setUniformValue("mvp", meshModelProjectionMatrix);

    m_shader->setUniformValue("light.position", m_lightPos);
    m_shader->setUniformValue("light.intensity", m_lightIntensity);

    m_shader->setUniformValue("material.ka", m_ambient);
    m_shader->setUniformValue("material.kd", m_diffuse);
    m_shader->setUniformValue("material.ks", m_specular);
    m_shader->setUniformValue("material.shininess", m_shininess);

    m_shader->setUniformValue("opacity", m_opacity);

    m_vao->bind();
    functions->glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, Q_NULLPTR);
    m_vao->release();
}

void Mesh::invalidate() {
    m_positionsBuffer->destroy();
    m_normalsBuffer->destroy();
    m_indicesBuffer->destroy();
    m_shader.reset();
    m_vao->destroy();
}

void Mesh::changeMesh(const QString &file) {
    m_meshFile = file;
    m_fileChangeLoaded = false;
}

void Mesh::flush() {
    m_vao->bind();

    const QVector<QVector3D> vertices;

    m_positionsBuffer->bind();
    m_positionsBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_positionsBuffer->allocate(vertices.constData(), vertices.size() * sizeof(QVector3D));

    const QVector<QVector3D> normals;

    m_normalsBuffer->bind();
    m_normalsBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_normalsBuffer->allocate(normals.constData(), normals.size() * sizeof(QVector3D));

    const QVector<unsigned int> indices;
    m_drawCount = indices.size();

    m_indicesBuffer->bind();
    m_indicesBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_indicesBuffer->allocate(indices.constData(), indices.size() * sizeof(unsigned int));

    m_shader->bind();

    m_positionsBuffer->bind();
    m_shader->enableAttributeArray("vertexPosition");
    m_shader->setAttributeBuffer("vertexPosition", GL_FLOAT, 0, 3);

    m_normalsBuffer->bind();
    m_shader->enableAttributeArray("vertexNormal");
    m_shader->setAttributeBuffer("vertexNormal", GL_FLOAT, 0, 3);

    m_vao->release();
}

void Mesh::setTransform(Transform transform) {
    m_transform = transform;
}

void Mesh::updateExternalTransform(const QMatrix4x4 &transform) {
    m_externalTransform = transform;
}

void Mesh::updateExternalTransform(const float *transform) {
    QMatrix4x4 transformation;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            transformation(i, j) = transform[4 * j + i];
        }
    }
    updateExternalTransform(transformation);
}

void Mesh::setMaterial(const QVector3D &diffuse, const QVector3D &ambient, const QVector3D &specular, const float &shininess) {
    m_ambient = ambient;
    m_diffuse = diffuse;
    m_specular = specular;
    m_shininess = shininess;
}

void Mesh::setOpacity(const float &opacity) {
    m_opacity = opacity;
}

void Mesh::setLight(const QVector3D &pos, const QVector3D &intensities) {
    m_lightPos = QVector4D(pos, 1.0);
    m_lightIntensity = intensities;
}


/******************************************************
 * Private Functions
 *****************************************************/

void Mesh::initializeBuffers() {
    if (!m_positionsBuffer->create())
        qFatal("Unable to create position buffer");
    if (!m_normalsBuffer->create())
        qFatal("Unable to create vertex buffer");
    if (!m_indicesBuffer->create())
        qFatal("Unable to create index buffer");
}

void Mesh::additionalChanges() {
    if (!m_fileChangeLoaded)
        changeMesh();
}

void Mesh::changeMesh() {
    ObjLoader loader;
    if (m_meshFile.length() == 0) {
        flush();
        return;
    }

    if (!loader.load(m_meshFile))
        qFatal("Could not load mesh");
    m_vao->bind();

    const QVector<QVector3D> vertices = loader.vertices();

    m_positionsBuffer->bind();
    m_positionsBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_positionsBuffer->allocate(vertices.constData(), vertices.size() * sizeof(QVector3D));

    const QVector<QVector3D> normals = loader.normals();

    m_normalsBuffer->bind();
    m_normalsBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_normalsBuffer->allocate(normals.constData(), normals.size() * sizeof(QVector3D));

    const QVector<unsigned int> indices = loader.indices();
    m_drawCount = indices.size();

    m_indicesBuffer->bind();
    m_indicesBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_indicesBuffer->allocate(indices.constData(), indices.size() * sizeof(unsigned int));

    m_shader->bind();

    m_positionsBuffer->bind();
    m_shader->enableAttributeArray("vertexPosition");
    m_shader->setAttributeBuffer("vertexPosition", GL_FLOAT, 0, 3);

    m_normalsBuffer->bind();
    m_shader->enableAttributeArray("vertexNormal");
    m_shader->setAttributeBuffer("vertexNormal", GL_FLOAT, 0, 3);

    m_vao->release();

    m_fileChangeLoaded = true;
}