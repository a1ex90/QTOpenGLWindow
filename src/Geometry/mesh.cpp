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
{}

/******************************************************
 * Public Functions
 *****************************************************/

void Mesh::render(QMatrix4x4 modelMatrix, QMatrix4x4 viewMatrix, QMatrix4x4 projectionMatrix) {
    QOpenGLFunctions *functions = QOpenGLContext::currentContext()->functions();

    const QMatrix4x4 modelViewMatrix = viewMatrix * modelMatrix;

    const QMatrix4x4 meshModelViewMatrix = modelViewMatrix * m_transform.getModel();
    const QMatrix4x4 meshModelProjectionMatrix = projectionMatrix * meshModelViewMatrix;

    m_shader->bind();

    m_shader->setUniformValue("modelViewMatrix", meshModelViewMatrix);
    m_shader->setUniformValue("normalMatrix", meshModelViewMatrix.normalMatrix());
    m_shader->setUniformValue("projectionMatrix", projectionMatrix);
    m_shader->setUniformValue("mvp", meshModelProjectionMatrix);

    m_shader->setUniformValue("light.position", QVector4D(0.0, 0.0, 0.0, 1.0));
    m_shader->setUniformValue("light.intensity", QVector3D(1.0, 1.0, 1.0));

    m_shader->setUniformValue("material.ka", QVector3D(0.1, 0.1, 0.1));
    m_shader->setUniformValue("material.kd", QVector3D(1.0, 0.1, 0.1));
    m_shader->setUniformValue("material.ks", QVector3D(1.0, 1.0, 1.0));
    m_shader->setUniformValue("material.shininess", 32.0f);

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

void Mesh::changeMesh(QString file) {
    ObjLoader loader;
    if(file.length() == 0) {
        flush();
        return;
    }

    if (!loader.load(file))
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