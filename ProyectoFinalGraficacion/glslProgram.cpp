
#include "glslProgram.h"

using namespace std;
#define printOpenGLError() printOglError(__FILE__, __LINE__)

GLSLProgram::GLSLProgram(char* vsFile, GLuint& vsId, char* fsFile, GLuint& fsId, GLuint& programId, bool link)
{
  if(link)
    {
      setVertexShader(vsFile,vsId);
      setFragmentShader(fsFile,fsId);
  
      programId = glCreateProgram();
      glAttachShader(programId,vsId);
      glAttachShader(programId,fsId);
      glLinkProgram(programId);
      printProgramInfoLog(programId);
      cout << "creando shader" << endl;
    }else
    {
      setVertexShader(vsFile,vsId);
      setFragmentShader(fsFile,fsId);
  
      programId = glCreateProgram();
      glAttachShader(programId,vsId);
      glAttachShader(programId,fsId);
      cout << "creando shader false" << endl;
    }
  lastFragmentShader = fragmentID = fsId;
  lastVertexShader = vertexID = vsId;
}

GLSLProgram::GLSLProgram(string vsFile, GLuint& vsId, string fsFile, GLuint& fsId, GLuint& programId, bool link)
{
  if(link)
    {
      setVertexShader(vsFile,vsId);
      setFragmentShader(fsFile,fsId);
  
      programId = glCreateProgram();
      glAttachShader(programId,vsId);
      glAttachShader(programId,fsId);
      glLinkProgram(programId);
      printProgramInfoLog(programId);
      cout << "creando shader" << endl;
    }else
    {
      setVertexShader(vsFile,vsId);
      setFragmentShader(fsFile,fsId);
  
      programId = glCreateProgram();
      glAttachShader(programId,vsId);
      glAttachShader(programId,fsId);
      cout << "creando shader false" << endl;
    }
  lastFragmentShader = fragmentID = fsId;
  lastVertexShader = vertexID = vsId;
}

GLSLProgram::GLSLProgram(string vsFile, string fsFile, GLuint& programId, bool link)
{
  if(link)
    {
      setVertexShader(vsFile,vertexID);
      setFragmentShader(fsFile,fragmentID);
  
      programId = glCreateProgram();
      glAttachShader(programId,vertexID);
      glAttachShader(programId,fragmentID);
      glLinkProgram(programId);
      printProgramInfoLog(programId);
      cout << "creando shader" << endl;
    }else
    {
      setVertexShader(vsFile,vertexID);
      setFragmentShader(fsFile,fragmentID);
  
      programId = glCreateProgram();
      glAttachShader(programId,vertexID);
      glAttachShader(programId,fragmentID);
      cout << "creando shader false" << endl;
    }
  lastFragmentShader = fragmentID;
  lastVertexShader = vertexID;
}

GLSLProgram::GLSLProgram(const char* vsFile,const char* fsFile, GLuint& programId, bool link)
{
	
	  if(link)
    {
      setVertexShader(vsFile,vertexID);
      setFragmentShader(fsFile,fragmentID);
  
      programId = glCreateProgram();
      glAttachShader(programId,vertexID);
      glAttachShader(programId,fragmentID);
      glLinkProgram(programId);
      printProgramInfoLog(programId);
      cout << "creando shader 0" << endl;
    }else
    {
      setVertexShader(vsFile,vertexID);
      setFragmentShader(fsFile,fragmentID);
  
      programId = glCreateProgram();
      glAttachShader(programId,vertexID);
      glAttachShader(programId,fragmentID);
      cout << "creando shader false 1" << endl;
    }
  lastFragmentShader = fragmentID;
  lastVertexShader = vertexID;


}

GLSLProgram::GLSLProgram(GLuint& programId)
{
  programId = glCreateProgram();
  glLinkProgram(programId);
  printProgramInfoLog(programId);
  lastVertexShader = -1;
  lastFragmentShader = -1;
}

GLSLProgram::~GLSLProgram()
{
  useShaders(0);
}

void GLSLProgram::linkProgram(GLuint& programId)
{
  glLinkProgram(programId);
  printProgramInfoLog(programId);
}

void GLSLProgram::setVertexShader(char* vsFile, GLuint& vsId)
{ 
  const char * vertexShader;
  char *vs = NULL;
  vsId = glCreateShader(GL_VERTEX_SHADER);
  vs = textFileRead(vsFile);
  vertexShader = vs;
  glShaderSource(vsId,1,&vertexShader,NULL);
  free(vs);
  glCompileShader(vsId);
  printShaderInfoLog(vsId);
 
}

void GLSLProgram::setFragmentShader(char* fsFile, GLuint& fsId)
{
  const char * fragmentShader;
  char *fs = NULL;
  fsId = glCreateShader(GL_FRAGMENT_SHADER);
  fs = textFileRead(fsFile);
  fragmentShader = fs;
  glShaderSource(fsId,1,&fragmentShader,NULL);
  free(fs);
  glCompileShader(fsId);
  printShaderInfoLog(fsId);
 
 
}


void GLSLProgram::setVertexShader(string vsFile, GLuint& vsId)
{ 
	
cout << "String " << endl;
  const char * vertexShader;
  char *vs = NULL;
  vsId = glCreateShader(GL_VERTEX_SHADER);
  vs = textFileRead(vsFile.c_str());
  vertexShader = vs;
  glShaderSource(vsId,1,&vertexShader,NULL);
  free(vs);
  glCompileShader(vsId);
  printShaderInfoLog(vsId);
 
}

void GLSLProgram::setFragmentShader(string fsFile, GLuint& fsId)
{
	cout << "String " << endl;
  const char * fragmentShader;
  char *fs = NULL;
  fsId = glCreateShader(GL_FRAGMENT_SHADER);
  fs = textFileRead(fsFile.c_str());
  fragmentShader = fs;
  glShaderSource(fsId,1,&fragmentShader,NULL);
  free(fs);
  glCompileShader(fsId);
  printShaderInfoLog(fsId);
 
 
}

void GLSLProgram::setVertexShader(string vsFile)
{ 
	
cout << "String " << endl;
  const char * vertexShader;
  char *vs = NULL;
  this->vertexID = glCreateShader(GL_VERTEX_SHADER);
  vs = textFileRead(vsFile.c_str());
  vertexShader = vs;
  glShaderSource(this->vertexID,1,&vertexShader,NULL);
  free(vs);
  glCompileShader(this->vertexID);
  printShaderInfoLog(this->vertexID);
 
}

void GLSLProgram::setFragmentShader(string fsFile)
{
	cout << "String " << endl;
  const char * fragmentShader;
  char *fs = NULL;
  this->fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
  fs = textFileRead(fsFile.c_str());
  fragmentShader = fs;
  glShaderSource(this->fragmentID,1,&fragmentShader,NULL);
  free(fs);
  glCompileShader(this->fragmentID);
  printShaderInfoLog(this->fragmentID);
 
 
}

void GLSLProgram::useShaders(const GLuint& use) //pasar programId para ejecutarShader 
{
  glUseProgram(use);
}// si es 0 se inhabilita el shader


int GLSLProgram::printOglError(char *file, int line)
{
  //
  // Returns 1 if an OpenGL error occurred, 0 otherwise.
  //
  GLenum glErr;
  int    retCode = 0;

  glErr = glGetError();
  while (glErr != GL_NO_ERROR)
    {
      //printf("glError in file %s @ line %d: %s\n", file, line, gluErrorString(glErr));
      cout << "glError in file " << file << " @ line " << line << ": " << gluErrorString(glErr) << endl; 
      retCode = 1;
      glErr = glGetError();
    }
  return retCode;
}


void GLSLProgram::printShaderInfoLog(GLuint obj)
{
  int infologLength = 0;
  int charsWritten  = 0;
  char *infoLog;

  glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

  if (infologLength > 0)
    {
      infoLog = (char *)malloc(infologLength);
      glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
      //intf("%s\n",infoLog);
      cout << infoLog << endl;
      free(infoLog);
    }else
    {
      cout << "problema al llamar el shader con id: " << obj << endl;
    }
}

void GLSLProgram::printProgramInfoLog(GLuint obj)
{
  int infologLength = 0;
  int charsWritten  = 0;
  char *infoLog;

  glGetProgramiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

  if (infologLength > 0)
    {
      infoLog = (char *)malloc(infologLength);
      glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
      //printf("%s\n",infoLog);
      cout << infoLog << endl;
      free(infoLog);
    }else
    {
      cout << "problema al llamar el programa con id: " << obj << endl;
    }
}

void GLSLProgram::setUniform1f(const GLuint& programa, GLuint loc ,const char* nameLocation,GLfloat value)
{
  loc = glGetUniformLocation(programa,nameLocation);
  glUniform1f(loc,value);
}

void GLSLProgram::setUniform2f(const GLuint& programa, GLuint loc, const char* nameLocation,GLfloat v0, GLfloat v1)
{
  loc = glGetUniformLocation(programa,nameLocation);
  glUniform2f(loc,v0,v1);
} 

void GLSLProgram::setUniform3f(const GLuint& programa, GLuint loc, const char* nameLocation,GLfloat v0, GLfloat v1, GLfloat v2)
{
  loc = glGetUniformLocation(programa,nameLocation);
  glUniform3f(loc,v0,v1,v2);
}

void GLSLProgram::setUniform4f(const GLuint& programa, GLuint loc, const char* nameLocation,GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
  loc = glGetUniformLocation(programa,nameLocation);
  glUniform4f(loc,v0,v1,v2,v3);
} 
  
void GLSLProgram::setUniform1fv(const GLuint& programa, GLuint loc, const char* nameLocation,GLfloat* value, int size)
{
  loc = glGetUniformLocation(programa,nameLocation);
  glUniform1fv(loc,size,value);
}

void GLSLProgram::setUniform2fv(const GLuint& programa, GLuint loc, const char* nameLocation,GLfloat* value, int size)
{
  loc = glGetUniformLocation(programa,nameLocation);
  glUniform2fv(loc,size,value);
}

void GLSLProgram::setUniform3fv(const GLuint& programa, GLuint loc, const char* nameLocation,GLfloat* value, int size)
{
  loc = glGetUniformLocation(programa,nameLocation);
  glUniform3fv(loc,size,value);
}

void GLSLProgram::setUniform4fv(const GLuint& programa, GLuint loc, const char* nameLocation,GLfloat* value, int size)
{
  loc = glGetUniformLocation(programa,nameLocation);
  glUniform3fv(loc,size,value);
}

void GLSLProgram::setUniformMatrix4(const GLuint& programa,GLfloat* matrix, const char* nameLocation, GLuint loc)
{
  /*  if(loc == 0)
      loc = glGetUniformLocation(programa,nameLocation);*/
  glUniformMatrix4fv(loc,1,false,matrix);
}

void GLSLProgram::bindAttributeLocation(const GLuint& programa, unsigned int nameId, char* name)
{
	glBindAttribLocation(programa, nameId, name);
	/*unsigned int err = glGetError();
	DWORD werr = GetLastError();*/
}

void GLSLProgram::bindFragDataLocation(const GLuint& programa){
    glBindFragDataLocationEXT(programa, 0, "outputF");
}
