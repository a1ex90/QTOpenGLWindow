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
 *       @date:   05.02.20
 *****************************************************/

// Icons from open source feathericons.com

import QtQuick 2.7
import QtQuick.Controls 1.0

import QtQuick.Dialogs 1.2

import "qrc"
import opengl.qt.viewer 1.0

ApplicationWindow
{
    id: applicationWindow
    visible: true
    width: 660
    height: 500
    title: qsTr("OpenGL Viewer")

    /******************************************************
     * Viewer (OpenGL)
     *****************************************************/

    Item {
        id: openGLViewer
        height: parent.height - 20
        width: parent.width - 20
        x: parent.width - width - 10
        y: 10
        z: 0
        visible: true
        focus: true

        Keys.onPressed: {
            if(event.key == Qt.Key_P) {
                console.log("P");
            }

            if(event.key == Qt.Key_S) {
                console.log("Screenshot");
                openGLViewer.grabToImage(function(result){result.saveToFile("screenshot.png");});
            }
        }

        QTOpenGLWindow { id:openGLWindow}
    }

    /******************************************************
     * Functions
     *****************************************************/
}
