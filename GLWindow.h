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



    // QWindow interface
protected:
    virtual void keyPressEvent(QKeyEvent *) override;
    virtual void keyReleaseEvent(QKeyEvent *) override;
    virtual void mousePressEvent(QMouseEvent *) override;
    virtual void mouseReleaseEvent(QMouseEvent *) override;
    virtual void mouseMoveEvent(QMouseEvent *) override;
};

#endif // GLWINDOW_H
