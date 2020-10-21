/******************************************************
 *
 *   #, #,         CCCCCC  VV    VV MM      MM RRRRRRR
 *  %  %(  #%%#   CC    CC VV    VV MMM    MMM RR    RR
 *  %    %#  #    CC        V    V  MM M  M MM RR    RR
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
 *       @date:   19.10.20
 *****************************************************/

#ifndef QTOPENGLWINDOW_QDUALQUATERNION_H
#define QTOPENGLWINDOW_QDUALQUATERNION_H

#include <QQuaternion>
#include <QMatrix4x4>
#include <cmath>

class QDualQuaternion {
public:
    QDualQuaternion() {
        m_real = QQuaternion(1.0f, 0.0f, 0.0f, 0.0f);
        m_dual = QQuaternion(0.0f, 0.0f, 0.0f, 0.0f);
    }

    QDualQuaternion(const QQuaternion &r, const QQuaternion &d = QQuaternion(0.0f, {})) {
        m_real = r.normalized();
        m_dual = d;
    }

    QDualQuaternion(const QQuaternion &r, const QVector3D &t) {
        m_real = r.normalized();
        m_dual = 0.5f * (QQuaternion(0.0f, t) * m_real);
    }

    static QDualQuaternion translation(const QVector3D &t) {
        return {QQuaternion(1.0f,{}), 0.5f * QQuaternion(0, t)};
    }

    static QDualQuaternion axisAngle(const QVector3D &axis, const float &angle) {
        return { {cosf(0.5f * angle), axis.x() * sinf(0.5f * angle), axis.y() * sinf(0.5f * angle), axis.z() * sinf(0.5f * angle) }, QQuaternion(0.0f, 0.0f, 0.0f, 0.0f) };
    }

    QDualQuaternion operator* (const float &scale) {
        QDualQuaternion tmp;
        tmp.m_real = this->m_real * scale;
        tmp.m_dual = this->m_dual * scale;
        return tmp;
    }

    QDualQuaternion operator+ (const QDualQuaternion &rhs) {
        QDualQuaternion tmp;
        tmp.m_real = this->m_real + rhs.m_real;
        tmp.m_dual = this->m_dual + rhs.m_dual;
        return tmp;
    }

    QDualQuaternion operator* (const QDualQuaternion &rhs) {
        QDualQuaternion tmp;
        tmp.m_real = rhs.m_real * this->m_real;
        tmp.m_dual = rhs.m_dual * this->m_real + rhs.m_real * this->m_dual;
        return tmp;
    }

    static float dot(const QDualQuaternion &a, const QDualQuaternion &b) {
        return QQuaternion::dotProduct(a.m_real, b.m_real);
    }

    static QDualQuaternion normalize(QDualQuaternion q) {
        float mag = QQuaternion::dotProduct(q.m_real, q.m_dual);
        if(mag > 0.0000001f) {
            q.m_real *= 1.0f / mag;
            q.m_dual *= 1.0f / mag;
        } else {
            qDebug() << "Can't normalize!";
        }
        return q;
    }

    QDualQuaternion normalized() {
        QDualQuaternion tmp = QDualQuaternion{m_real, m_dual};
        return QDualQuaternion::normalize(tmp);
    }

    void normalize() {
        float mag = QQuaternion::dotProduct(m_real, m_dual);
        if(mag > 0.0000001f) {
            m_real *= 1.0f / mag;
            m_dual *= 1.0f / mag;
        } else {
            qDebug() << "Can't normalize!";
        }
    }

    static QDualQuaternion conjugate(const QDualQuaternion &q) {
        return {q.m_real.conjugated(), q.m_dual.conjugated()};
    }

    QDualQuaternion conjugated() {
        QDualQuaternion tmp = QDualQuaternion{m_real, m_dual};
        return QDualQuaternion::conjugate(tmp);
    }

    void conjugate() {
        m_real = m_real.conjugated();
        m_dual = m_dual.conjugated();
    }

    static QDualQuaternion invert(QDualQuaternion q) {
        q.normalize();
        q.conjugate();
        return q;
    }

    QDualQuaternion inverted() {
        QDualQuaternion tmp = QDualQuaternion{m_real, m_dual};
        return QDualQuaternion::invert(tmp);
    }

    void invert() {
        normalize();
        conjugate();
    }

    QQuaternion getRotation() {
        return m_real;
    }

    QVector3D getTranslation() {
        QQuaternion t = (m_dual * 2.0f) * m_real.conjugated();
        return t.vector();
    }

    QMatrix4x4 toMatrix() {
//        QDualQuaternion q = this->normalized();

        QMatrix4x4 M;
        M.setToIdentity();

        // Translation
        QQuaternion t = (m_dual * 2.0f) * m_real.conjugated();
        M.translate(t.vector());

        const float w = m_real.scalar();
        const float x = m_real.x();
        const float y = m_real.y();
        const float z = m_real.z();

        // Rotation
        M(0,0) = w*w + x*x - y*y - z*z;
        M(1,0) = 2*x*y + 2*w*z;
        M(2,0) = 2*x*z - 2*w*y;
        M(0,1) = 2*x*y - 2*w*z;
        M(1,1) = w*w + y*y - x*x - z*z;
        M(2,1) = 2*y*z + 2*w*x;
        M(0,2) = 2*x*z + 2*w*y;
        M(1,2) = 2*y*z - 2*w*x;
        M(2,2) = w*w + z*z - x*x - y*y;

        return M;
    }

protected:
    QQuaternion m_real;
    QQuaternion m_dual;
};

#endif //QTOPENGLWINDOW_QDUALQUATERNION_H
