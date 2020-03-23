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

#ifndef QTSIMVIEW_GEOMETRY_H
#define QTSIMVIEW_GEOMETRY_H

#include <QScopedPointer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

enum GeometryType {
    MESH,
    GRID,
    POINTCLOUD
};

class Geometry {
public:
    /**
     * Constructor
     * @param drawCount number of elements to be drawn
     * @param type geometry type
     */
    Geometry(const unsigned int& drawCount, GeometryType type)
        : m_type(type)
        , m_shader()
        , m_vao(new QOpenGLVertexArrayObject)
        , m_drawCount(drawCount)
    {}

    /**
     * Initialization of buffers and shader
     * @param fragmentShader Fragment Shader File
     * @param vertexShader Vertex Shader File
     */
    void initialize(QString fragmentShader, QString vertexShader) {
        if (m_vao->isCreated())
            return; // already initialized
        if (!m_vao->create())
            qFatal("Unable to create VAO");
        initializeBuffers();
        m_shader.reset(new QOpenGLShaderProgram);
        if (!m_shader->create())
            qFatal("Unable to create shader program");
        if (!m_shader->addShaderFromSourceFile(QOpenGLShader::Vertex, vertexShader))
            qFatal("Vertex shader compilation failed");
        if (!m_shader->addShaderFromSourceFile(QOpenGLShader::Fragment, fragmentShader))
            qFatal("Fragment shader compilation failed");
        if (!m_shader->link())
            qFatal("Shader program not linked");
    }

    /**
     * Override this with the render function for the geometry
     * @param mm Model Matrix
     * @param vm View Matrix
     * @param pm Projection Matrix
     */
    virtual void render(QMatrix4x4 mm, QMatrix4x4 vm, QMatrix4x4 pm) = 0;

    /**
     * Override this with a function to destroy buffers and shader
     */
    virtual void invalidate() = 0;
private:
    /**
     * Override this with initialization of position buffers, etc.
     */
    virtual void initializeBuffers() = 0;
protected:
    // Shader
    QScopedPointer<QOpenGLShaderProgram> m_shader;
    // VBO
    QScopedPointer<QOpenGLVertexArrayObject> m_vao;
    // Number of elements to be drawn
    unsigned int m_drawCount;
    // Geometry Type;
    GeometryType m_type;
};


#endif //QTSIMVIEW_GEOMETRY_H
