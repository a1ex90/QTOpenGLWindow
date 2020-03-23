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
 *       @date:   05.02.2020
 *****************************************************/

// Icons from open source feathericons.com

import QtQuick 2.7
import QtQuick.Controls 1.0

import QtQuick.Dialogs 1.2

import QtQuick.Scene3D 2.0

import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Input 2.0
import Qt3D.Extras 2.0

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
        x: 10
        y: 10
        width: 640
        height: 480
        visible: true

        QTOpenGLWindow { id:openGLWindow}
    }

    /******************************************************
     * Functions
     *****************************************************/
}