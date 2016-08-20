#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QGLWidget>
#include <QGLShaderProgram>
#include <QMouseEvent>
#include <QKeyEvent>
#include "rubixcube.h"
#include "stopwatch.h"
#include "material.h"
#include "camera.h"
#include "light.h"

class OpenGLWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit OpenGLWidget(QStatusBar *parent);
    ~OpenGLWidget();

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    Light *light;
    Material *material;
    Camera *camera;

    RubixCube *rubix;
    StopWatch *stopWatch;
//    QMatrix4x4 pMatrix;
    QGLShaderProgram sProgram;
    QVector<QVector3D> vertices;
    QVector<QVector3D> color;
    double alpha;
    double beta;
    double gama;
    double distance;
    QPoint lastMousePosition;

protected slots:
    void cubeSolvedCallback();
    void shuffleEndCallback();
};

#endif // OPENGLWIDGET_H
