import QtQuick 2.7
import QtQuick.Controls 1.0

import opengl.qt.viewer 1.0

Item {
    id: parWindow
    width: parent.width
    height: parent.height

    property RenderUnit renderer: RenderUnit{parent: parWindow; width: parWindow.width; height: parWindow.height}

    Slider {
        id: sl_distanceControll
        x: 8
        y: parent.height - height - 8
        z: 1
        value: 40
        height: parent.height / 3
        minimumValue: 1
        maximumValue: 100
        orientation: Qt.Vertical
        onValueChanged: {
            var MINZOOM = 0.1;
            var MAXZOOM = 10;
            var logMinZoom = Math.log(MINZOOM);
            var logMaxZoom = Math.log(MAXZOOM);
            var logZoom = logMinZoom + (logMaxZoom - logMinZoom)*this.value / (this.maximumValue - this.minimumValue);
            renderer.distance = Math.exp(logZoom);
        }
    }

    Slider {
        id: sl_azimuthControl
        x: 36
        y: parent.height - height - 8
        z: 1
        maximumValue: 359
        value: 0
        height: parent.height / 3
        orientation: Qt.Vertical
        onValueChanged: renderer.azimuth = this.value;
    }

    Slider {
        id: sl_elevationControl
        x: 64
        y: parent.height - height - 8
        z: 1
        minimumValue: -89
        maximumValue: 90
        value: -20
        height: parent.height / 3
        orientation: Qt.Vertical
        onValueChanged: renderer.elevation = this.value;
    }
}
