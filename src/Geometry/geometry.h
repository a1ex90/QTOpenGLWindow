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
    POINTCLOUD,
    SPHERECLOUD,
    BULKCLOUD
};

/**
 * \class Geometry
 *
 * \brief Interface for all renderable geometry.
 */
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
            , m_isInitialized(false)
    {}

    /**
     * Initialization of buffers and shader
     * @param fragmentShader Fragment Shader File
     * @param vertexShader Vertex Shader File
     */
    void initialize(QString fragmentShader, QString vertexShader) {
        m_isInitialized = false;
        m_fragmentShader = fragmentShader;
        m_vertexShader = vertexShader;
    }

    /**
     * changes that need happen during synchronization
     * to prevent false context errors
     */
    void performChanges() {
        if (!m_isInitialized)
            initialize();
        additionalChanges();
    }

    /**
     * Override this with the render function for the geometry
     * @param eye Eye Position
     * @param mm Model Matrix
     * @param vm View Matrix
     * @param pm Projection Matrix
     */
    virtual void render(const QVector3D &eye, const QMatrix4x4 &mm, const QMatrix4x4 &vm, const QMatrix4x4 &pm) = 0;

    /**
     * Override this with a function to destroy buffers and shader
     */
    virtual void invalidate() = 0;

    /**
     * Returns geometry type
     * @return geometry type
     */
    GeometryType getType() {
        return m_type;
    }
private:
    /**
     * Initialization of buffers and shader
     */
    void initialize() {
        if (m_vao->isCreated())
            return; // already initialized
        if (!m_vao->create())
            qFatal("Unable to create VAO");
        initializeBuffers();
        m_shader.reset(new QOpenGLShaderProgram);
        if (!m_shader->create())
            qFatal("Unable to create shader program");
        if (!m_shader->addShaderFromSourceFile(QOpenGLShader::Vertex, m_vertexShader))
            qFatal("Vertex shader compilation failed");
        if (!m_shader->addShaderFromSourceFile(QOpenGLShader::Fragment, m_fragmentShader))
            qFatal("Fragment shader compilation failed");
        if (!m_shader->link())
            qFatal("Shader program not linked");
        m_isInitialized = true;
    }

    /**
     * Override this with additional changes that need happen during
     * synchronization to prevent false context errors
     */
    virtual void additionalChanges() = 0;
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
    // Fragment Shader File;
    QString m_fragmentShader;
    // Vertex Shader File
    QString m_vertexShader;
    // Weather the Shader has been initialized
    bool m_isInitialized;
};

#endif //QTSIMVIEW_GEOMETRY_H
