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

#include "plyLoader.h"

#include <QDebug>
#include <QFile>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QTextStream>

PlyLoader::PlyLoader() {}

bool PlyLoader::load(const QString &fileName) {
    QFile file( fileName );
    if ( !file.open( ::QIODevice::ReadOnly | ::QIODevice::Text ) )
    {
        qDebug() << "Could not open file" << fileName << "for reading";
        return false;
    }

    return load( &file );
}

bool PlyLoader::load(QIODevice *ioDev) {
    Q_CHECK_PTR(ioDev);
    if (!ioDev->isOpen()) {
        qWarning() << "iodevice" << ioDev << "not open for reading";
        return false;
    }

    m_points.clear();
    QTextStream stream(ioDev);
    bool endHeader = false;
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        line = line.simplified();

        if (line.length() > 0 && line.at(0) != QChar::fromLatin1('#')) {
            QTextStream lineStream(&line, QIODevice::ReadOnly);
            if(endHeader) {
                float x, y, z;
                lineStream >> x >> y >> z;
                m_points.append(QVector3D( x, y, z ));
            } else {
                QString token;
                lineStream >> token;
                if(token == QStringLiteral("end_header"))
                    endHeader = true;
            }
        }
    }
    m_centroid = centroid(m_points);
    return true;
}

QVector3D PlyLoader::centroid(QVector<QVector3D> positions) {
    QVector3D centroid(0,0,0);
    double x = 0;
    double y = 0;
    double z = 0;
    for(int i = 0; i < positions.length(); i++) {
        x += positions[i][0];
        y += positions[i][1];
        z += positions[i][2];
    }
    centroid.setX(x / positions.length());
    centroid.setY(y / positions.length());
    centroid.setZ(z / positions.length());
    return centroid;
}