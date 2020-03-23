# QTOpenGLWindow
This is an OpenGL Viewer Item for QT5, which can be added as a submodule and embedded in QT Quick 2 applications.

## Requirements
- QT 5.9.5
- QT Quick 2.7
- OpenGL 4.*
- CMake
- C++ 14

## Testing
CMake can be advised to build a test application by passing variable `BUILD_TESTS` to Cmake. (CMake option `-DBUILD_TESTS=1`)

## Setup 
The following steps need to be done to a this module to an existing project:
1. clone this module to a folder inside the project (e.g. `ext/QTOpenGLWindow`)
2. add this module to the project CMake file
```
add_subdirectory(ext/QTOpenGLWindow)
include_directories(ext/QTOpenGLWindow/src)
...
target_link_libraries(
        QTOpenGLWindow
        ...)
```
3. add this module to the project qrc file
```
<qresource>
    <file>../ext/QTOpenGLWindow/qrc/</file>
</qresource>
```
4. (optional) add this module as a submodule to the project git
```
git submodule add git@github.com:a1ex90/QTOpenGLWindow.git ext/QTOpenGLWindow
```

## Usage
For rendering some geometry the `FrameBufferObject` and `FrameBufferObjectRender` need to be extended. An easy example can be found in the `openGLWindow` class inside the `test` folder. The `FrameBufferObject` can also be extended to have new signals and slots to interact with the QT Quick application. The `addSync` function of the `FrameBufferObjectRender` class can be overwritten, to manipulate geometry objects safely during runtime. Further renderable geometry can be created by extending the geometry class.

The extended `FrameBufferObject` needs to be registered as a qml module inside the main.cpp, like e.g.:
```
qmlRegisterType<MyFrameBufferObject>("opengl.qt.viewer", 1, 0, "RenderUnit");
```

This so generated module plus the qml from the submodule need to be imported in the project's qml file, like e.g.:
```
import "ext/QTOpenGLWindow/qrc"
import opengl.qt.viewer 1.0
```

Finally a the `QTOpenGLWindow` can be defined with an id inside the qml `QTOpenGLWindow { id:openGLWindow }`. Its attributes (e.g. `azimuth`) can be read/set by accessing them like `openGLWindow.renderer.azimuth`. 


