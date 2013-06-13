#ifdef __APPLE__
#include <QtGui>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glew.h>
#include <QtGui/QApplication>
#include <QtGui/QMouseEvent>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "glInfo.h"
#include <QtGlobal>
#include <QtGui/QMouseEvent>
#include <QTimer>

#include <iostream>
#include <fstream>
#include <math.h>
#include <exception>
#include <math.h>
#include <string>
#include "GLWidget.h"

using namespace std;

#define PI	3.141592

GLWidget::GLWidget(QWidget *parent) :QGLWidget(/*QGLFormat( QGL::AlphaChannel |
                                                          QGL::DoubleBuffer |
                                                          QGL::DepthBuffer |
                                                          QGL::Rgba |
                                                          QGL::SampleBuffers |
                                                          QGL::StereoBuffers),*/parent)
{

    timef = 0.0;
    myqtimer = new QTimer(this);
    connect(myqtimer,SIGNAL(timeout()),this,SLOT(idle()));
    myqtimer->start(20);

    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
    setAutoBufferSwap(false);
    format().setDoubleBuffer(true);
    mouseLeftDown = mouseRightDown = mouseMiddleDown = false;
    mouseX = mouseY = 0;
    cameraAngleX = cameraAngleY = 0.0f;
    cameraDistance = 25.0f;
    cameraSpeed = 2.0;

}


GLWidget::~GLWidget()
{
    makeCurrent();
    clearMemory();

}

void GLWidget::initializeGL()
{

	cameraTranslateX = 0.0f;
	cameraTranslateX = 8.0f;
	cameraTranslateZ = 0.0f;
	cameraAngle = 0.0f;

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {

        cout << "Error: " << glewGetErrorString(err) << endl;
    }

    cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << endl;
    glInfo  gl;
    gl.getInfo();
    // gl.printSelf();

    glShadeModel(GL_SMOOTH);                    // shading mathod: GL_SMOOTH or GL_FLAT
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);      // 4-byte pixel alignment

    // enable /disable features
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

    glEnable(GL_LIGHTING);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glClearColor(0.0, 0.0, 0.0, 0.0);                   // background color
    glClearStencil(0);                          // clear stencil buffer
    glClearDepth(1.0f);                         // 0 is near, 1 is far
    glDepthFunc(GL_LEQUAL);
    museum = new Museo();
    initLights();
    loadShaders();
    
}

void GLWidget::initLights()
{

    glEnable(GL_LIGHT0);
    static const GLfloat lightPos[4] = { 0.0f, 9.95f, 0.0f, 1.0f };
    GLfloat ambient_light[] = { 0.1, 0.1, 0.1, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT,ambient_light);


    glEnable(GL_LIGHT1);
    static const GLfloat lightPos1[4] = { 52.37f, 10.0, -30.44f, 1.0f };
    static const GLfloat light1[4] = {1.0, 1.0, 0.5, 1.0};
    static const GLfloat lightDirection1[3] = {0.0, -1.0, 0.0};
    glLightfv(GL_LIGHT1, GL_POSITION, light1);
    glLightfv(GL_LIGHT1, GL_AMBIENT,light1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,light1);
    glLightfv(GL_LIGHT1, GL_SPECULAR,light1);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lightDirection1);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 75.0);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 50.0);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.8);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.6);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.4);

    GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glEnable(GL_NORMALIZE);
}

void GLWidget::loadShaders()
{

    //model1 = new xcModel("../resources/dragon.ply","../Shaders/program.vert","../Shaders/program.frag");

    //model2 = new xcModel("../resources/bunny.ply","../Shaders/default.vert","../Shaders/default.frag"); //para shaders menores
    // model2 = new xcModel("../resources/bunny.ply","../Shaders/default.vert","../Shaders/default.frag");
    // model3 = new LoadOBJ("../resources/dragon.obj",1);
    // model3->initVBO();
    // model3->initShader("../Shaders/noise.vert","../Shaders/noise1.frag");


}

void GLWidget::paintGL()
{
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);

    //GLuint tloc;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearDepth(1.0f);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers

    glPushMatrix();

    glRotatef(cameraAngle, 0.0f, 1.0f, 0.0f);
    glTranslatef(cameraTranslateX, cameraTranslateY, cameraTranslateZ);

    glPushMatrix();

    glTranslatef(0, 0, -cameraDistance);
    glRotatef(cameraAngleX, 1, 0, 0);
    glRotatef(cameraAngleY, 0, 1, 0);


    glPushMatrix();

    glTranslated(-36.0,0.0,-32.0);
    glScaled(2.0,2.0,2.0);
    glGetFloatv(GL_PROJECTION_MATRIX, projMatrix);
    glGetFloatv(GL_MODELVIEW_MATRIX, viewMatrix);



    museum->drawMuseum();
    //model2->activeShader();
    //model2->setMVPM(projMatrix,viewMatrix);
    //model2->setTime(timef);
    // model2->paintModelVBO();
   // model2->paintDisplayList();
   // model2->disactiveShader();

    glPopMatrix();

    glPushMatrix();
     glScaled(0.5,0.5,0.5);
    glGetFloatv(GL_PROJECTION_MATRIX, projMatrix);
    glGetFloatv(GL_MODELVIEW_MATRIX, viewMatrix);


   /* model3->activeShader();
    model3->setMVPM(projMatrix,viewMatrix);
    model3->setTime(timef);*/
   //model3->RenderOBJModel();
    //model3->disactiveShader();



    glPopMatrix();
    glPopMatrix();

    glPopMatrix();

    this->swapBuffers();


}

void GLWidget::resizeGL(int w, int h)
{

    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    gluPerspective(45,w/h,0.01,1000);
    gluLookAt(0.0,8.0,10.0,
              0.0,8.0,0.0,
              0.0,1.0,0.0);
    // glFrustum(-10.0, +10.0, -10.0, 10.0, 5.0, 60.0);

    // glTranslated(0.0, 0.0, -1.0);
}

void GLWidget::normalizeAngle(int *angle)

{
    while (*angle < 0)
        *angle += 360;
    while (*angle > 360)
        *angle -= 360;
}

void GLWidget ::idle()
{
    timef += 0.1;
    updateGL();
}

void GLWidget::clearMemory()
{
//     delete model1;
//     delete model2;
//     model3->FreeModel();
//     delete model3;
//     delete shader;
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{

  if(mouseLeftDown)
    {
      cameraAngleY += (event->x() - mouseX);
      cameraAngleX += (event->y() - mouseY);
      mouseX = event->x();
      mouseY = event->y();
    }
  if(mouseRightDown)
    {
      cameraDistance -= (event->y() - mouseY) * 0.2f;
      mouseY = event->y();
    }

  updateGL();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{

  mouseX = event->x();
  mouseY = event->y();

  if(event->buttons() & Qt::LeftButton)
    {
      mouseLeftDown = true;
    }
  else if(event->buttons() & Qt::RightButton )
    {
      mouseRightDown = true;
    }
  else if(event->buttons() & Qt::MidButton)
    {
      mouseMiddleDown = true;
    }

  updateGL();

}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{

  mouseX = event->x();
  mouseY = event->y();

  if(event->button() == Qt::LeftButton)
    {
      mouseLeftDown = false;
    }
  else if(event->button() == Qt::RightButton )
    {
      mouseRightDown = false;
    }
  else if(event->button() == Qt::MidButton)
    {
      mouseMiddleDown = false;
    }

  updateGL();
}

void GLWidget::keyPressEvent(QKeyEvent* event)
{
  switch(event->key()){
  case Qt::Key_Escape:
    emit exit();
    break;
  case Qt::Key_A:
    cout << mouseLeftDown << mouseRightDown << mouseMiddleDown <<endl;
    break;
  case Qt::Key_L:
    glEnable(GL_LIGHTING);
    break;
  case Qt::Key_K:
    glDisable(GL_LIGHTING);
    break;
  case Qt::Key_Up:
	  cameraTranslateZ += cameraSpeed*sin((cameraAngle + 90) *PI/180.0f);
	  cameraTranslateX += cameraSpeed*cos((cameraAngle + 90)*PI/180.0f);
	  updateGL();
	  break;
  case Qt::Key_Down:
	  cameraTranslateZ -= cameraSpeed*sin((cameraAngle + 90)*PI/180.0f);
	  cameraTranslateX -= cameraSpeed*cos((cameraAngle + 90)*PI/180.0f);
	  updateGL();
  	  break;
  case Qt::Key_Right:
	  cameraAngle += 5;
	  normalizeAngle(&cameraAngle);
	  break;
  case Qt::Key_Left:
	  cameraAngle -= 5;
	  normalizeAngle(&cameraAngle);
  	  break;
  case Qt::Key_W:
	  cameraTranslateY -= cameraSpeed;
	  break;
  case Qt::Key_S:
  	  cameraTranslateY += cameraSpeed;
  	  break;
  case Qt::Key_P:
	  cout << "(" << -cameraTranslateX << ", " << -cameraTranslateZ << ")" << endl;
	  break;
  default:
	  event->ignore();
    break;
  }

  updateGL();
}

