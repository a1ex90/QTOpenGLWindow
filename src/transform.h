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
 *       @date:   18.02.20
 *****************************************************/
#ifndef QTSIMVIEW_TRANSFORM_H
#define QTSIMVIEW_TRANSFORM_H

#include <QtGui/QVector3D>
#include <QtGui/QMatrix4x4>

/**
 * \class Transform
 *
 * \brief Transformation class for position, rotation and scaling transformations
 *        done directly by the shader
 */
class Transform
{
public:
    /**
     * Creates a transformation object
     * @param pos position transformation default 0,0,0
     * @param rot rotation transformation default 0,0,0
     * @param scale scaling transformation default 1,1,1
     */
    Transform(const QVector3D& pos = QVector3D(), const QMatrix4x4& rot = QMatrix4x4(), const QVector3D& scale = QVector3D(1.0f, 1.0f, 1.0f)) :
            m_pos(pos),
            m_rot(rot),
            m_scale(scale) {}

    /**
     * Returns the model matrix resulting from the present transformation
     * @return model matrix
     */
    inline QMatrix4x4 getModel() const {
        QMatrix4x4 posMatrix;
        posMatrix.translate(m_pos);
        QMatrix4x4 scaleMatrix;
        scaleMatrix.scale(m_scale);

        return posMatrix * m_rot * scaleMatrix;
    }

    /**
     * Returns the position part of the transformation
     * @return position transformation
     */
    inline QVector3D& getPos() { return m_pos; }

    /**
     * Returns the rotation part of the transformation
     * @return rotation transformation as quaternion
     */
    inline QMatrix4x4& getRot() { return m_rot; }

    /**
     * Returns the scaling part of the transformation
     * @return scaling transformation
     */
    inline QVector3D& getScale() { return m_scale; }

    /**
     * Set the position part of the transformation
     * @param pos position transformation
     */
    inline void setPos(const QVector3D& pos) { m_pos = pos; }

    /**
     * Set the rotation part of the transformation
     * @param rot rotation transformation
     */
    inline void setRot(const QMatrix4x4& rot) { m_rot = rot; }

    /**
     * Set the scaling part of the transformation
     * @param scale position transformation
     */
    inline void setScale(const QVector3D& scale) { m_scale = scale; }

    /**
     * Set the scaling part of the transformation
     * @param scale position transformation
     */
    inline void setScale(const float& scale) { m_scale = QVector3D(scale, scale, scale);}
private:
    // position transformation
    QVector3D m_pos;

    // rotation transformation
    QMatrix4x4 m_rot;

    // scaling transformation
    QVector3D m_scale;
};

#endif //QTSIMVIEW_TRANSFORM_H
