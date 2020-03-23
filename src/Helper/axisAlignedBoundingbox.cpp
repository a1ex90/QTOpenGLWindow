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
 *       @date:   12.02.2020
 *****************************************************/

#include "axisAlignedBoundingbox.h"
#include <QDebug>

AxisAlignedBoundingBox::AxisAlignedBoundingBox()
        : m_center(),
          m_radii()
{
}

AxisAlignedBoundingBox::AxisAlignedBoundingBox( const QVector<QVector3D>& points )
{
    update( points );
}

void AxisAlignedBoundingBox::update( const QVector<QVector3D>& points )
{
    if (points.isEmpty()) {
        m_center = QVector3D();
        m_radii = QVector3D();
        return;
    }

    QVector3D minPoint = points.at( 0 );
    QVector3D maxPoint = points.at( 0 );

    for ( int i = 1; i < points.size(); ++i )
    {
        const QVector3D& point = points.at( i );
        if ( point.x() > maxPoint.x() )
            maxPoint.setX( point.x() );
        if ( point.y() > maxPoint.y() )
            maxPoint.setY( point.y() );
        if ( point.z() > maxPoint.z() )
            maxPoint.setZ( point.z() );
        if ( point.x() < minPoint.x() )
            minPoint.setX( point.x() );
        if ( point.y() < minPoint.y() )
            minPoint.setY( point.y() );
        if ( point.z() < minPoint.z() )
            minPoint.setZ( point.z() );
    }

    m_center = 0.5 * ( minPoint + maxPoint );
    m_radii = 0.5 * ( maxPoint - minPoint );
#if 0
    qDebug() << "AABB:";
    qDebug() << "    min =" << minPoint;
    qDebug() << "    max =" << maxPoint;
    qDebug() << " center =" << m_center;
    qDebug() << "  radii =" << m_radii;
#endif
}


QDebug &operator<<(QDebug &stream, const AxisAlignedBoundingBox &bbox)
{
    stream << "AABB: min=" << bbox.minPoint() << ", max=" << bbox.maxPoint();
    return stream;
}
