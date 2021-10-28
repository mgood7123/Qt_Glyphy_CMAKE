#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QOpenGLWindow>

class GLWindow : public QOpenGLWindow
{
    Q_OBJECT
public:
    GLWindow(UpdateBehavior updateBehavior = NoPartialUpdate);
    ~GLWindow();
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
};

#endif // GLWINDOW_H
