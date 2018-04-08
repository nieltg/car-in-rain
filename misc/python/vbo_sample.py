# coding: utf-8
import pygame
from OpenGL.GL import (glClearColor,glClearDepth, glDepthFunc, glEnable, GL_LESS, GL_DEPTH_TEST, glViewport,
    glMatrixMode,glLoadIdentity,GL_PROJECTION,glClear,GL_COLOR_BUFFER_BIT,GL_DEPTH_BUFFER_BIT, GL_MODELVIEW,
    glTranslatef, glRotatef,glFlush,glGetError,GL_NO_ERROR,glCreateProgram,glCreateShader,GL_VERTEX_SHADER,
    glShaderSource,glCompileShader,glAttachShader,glCreateShader, GL_FRAGMENT_SHADER, glShaderSource, glLinkProgram,
    glUseProgram,glBegin, GL_TRIANGLES, glColor3f, glVertex3f, glEnd, glEnableClientState,GL_VERTEX_ARRAY,GL_COLOR_ARRAY,
    glVertexPointer,GL_FLOAT, glColorPointer, glDrawElements, GL_UNSIGNED_INT, glDisableClientState, glGenBuffers, glBindBuffer,
    GL_ARRAY_BUFFER, glBufferData, GL_STATIC_DRAW, GL_ELEMENT_ARRAY_BUFFER, ctypes, GL_TRIANGLE_FAN, glDrawArrays)
from OpenGL.GLU import (gluPerspective, gluErrorString)
from OpenGL.GLUT import (glutSwapBuffers, glutInit, glutInitDisplayMode, GLUT_RGBA, GLUT_DOUBLE, GLUT_DEPTH, glutInitWindowSize,
glutDisplayFunc, glutIdleFunc, glutReshapeFunc, glutMainLoop, glutCreateWindow)
from pygame.locals import *
import sys

##############################################################################
# OpenGL funcs
##############################################################################
def initialize():
    glClearColor(0.0, 0.0, 0.0, 0.0)
    glClearDepth(1.0)
    glDepthFunc(GL_LESS)
    glEnable(GL_DEPTH_TEST)

def resize(Width, Height):
    # viewport
    if Height == 0:
        Height = 1
    glViewport(0, 0, Width, Height)
    # projection
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(45.0, float(Width)/float(Height), 0.1, 100.0)

yaw=0
pitch=0
def draw():
    global yaw, pitch
    # clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

    # view
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    yaw+=0.01
    pitch+=0.27
    glTranslatef(0.0, 0.0, -2.0)
    glRotatef(yaw, 1, 1, 1)
    # glRotatef(pitch, 0, 0, 1)

    # cube
    #draw_cube0()
    #draw_cube1()
    #draw_cube2()
    # draw_cube3()
    drawCar()
    drawTire()

    glFlush()

##############################################################################
# Shader
##############################################################################
# Checks for GL posted errors after appropriate calls
def printOpenGLError():
    err = glGetError()
    if (err != GL_NO_ERROR):
        print('GLERROR: ', gluErrorString(err))
        #sys.exit()

class Shader(object):

    def initShader(self, vertex_shader_source, fragment_shader_source):
        # create program
        self.program=glCreateProgram()
        print('create program')
        printOpenGLError()

        # vertex shader
        print('compile vertex shader...')
        self.vs = glCreateShader(GL_VERTEX_SHADER)
        glShaderSource(self.vs, [vertex_shader_source])
        glCompileShader(self.vs)
        glAttachShader(self.program, self.vs)
        printOpenGLError()

        # fragment shader
        print('compile fragment shader...')
        self.fs = glCreateShader(GL_FRAGMENT_SHADER)
        glShaderSource(self.fs, [fragment_shader_source])
        glCompileShader(self.fs)
        glAttachShader(self.program, self.fs)
        printOpenGLError()

        print('link...')
        glLinkProgram(self.program)
        printOpenGLError()

    def begin(self):
        if glUseProgram(self.program):
            printOpenGLError()

    def end(self):
        glUseProgram(0)


##############################################################################
# vertices
##############################################################################
s=0.5
vertices=[
        -s, -s, -s,
         s, -s, -s,
         s,  s, -s,
        -s,  s, -s,
        -s, -s,  s,
         s, -s,  s,
         s,  s,  s,
        -s,  s,  s,
        ]

carVertices= [
        0.10, 0.15, 0.10,
        0.10, 0.50, 0.10,
        0.30, 0.50, 0.10,
        0.30, 0.70, 0.10,
        0.60, 0.70, 0.10,
        0.60, 0.50, 0.10,
        0.90, 0.50, 0.10,
        0.90, 0.15, 0.10,
        0.10, 0.15, -0.60,
        0.10, 0.50, -0.60,
        0.30, 0.50, -0.60,
        0.30, 0.70, -0.60,
        0.60, 0.70, -0.60,
        0.60, 0.50, -0.60,
        0.90, 0.50, -0.60,
        0.90, 0.15, -0.60
    ]

tireVertices = [
        0.30, 0.15, 0.05,
        0.60, 0.15, 0.05,
        0.30, 0.15, 0.70,
        0.60, 0.15, 0.70
    ]

carColors=[
        1, 0, 1,
        0, 1, 1,
        1, 0, 1,
        0, 1, 1,
        1, 0, 1,
        0, 1, 1,
        1, 0, 1,
        0, 1, 1,
        1, 0, 1,
        0, 1, 1,
        1, 0, 1,
        0, 1, 1,
        1, 0, 1,
        0, 1, 1,
        1, 0, 1,
        0, 1, 1,
        ]

tireColors=[
        1, 0, 1,
        1, 0, 1,
        1, 0, 1,
        1, 0, 1,
        1, 0, 1,
        1, 0, 1,
        1, 0, 1,
        1, 0, 1,
        ]

colors=[
        0, 0, 0,
        1, 0, 0,
        0, 1, 0,
        0, 0, 1,
        0, 1, 1,
        1, 0, 1,
        1, 1, 1,
        1, 1, 0,
        ]

carIndices=[
         0, 1, 6,  2, 3, 4,  4, 5, 2,  6, 7, 0,
         8, 9,14, 14,15, 8, 10,11,12, 12,13,10, 
         0, 1, 9,  9, 8, 0,
         7, 6,14, 14,15, 7,
         0, 8,15, 15, 7, 0,
         1, 2,10, 10, 9, 1,
         5, 6,14, 14,13, 5,
         2, 3,11, 11,10, 2,
         5, 4,12, 12,13, 5,
         3, 4,12, 12,11, 3
    ]
    
indices=[
        0, 1, 2, 2, 3, 0,
        0, 4, 5, 5, 1, 0,
        1, 5, 6, 6, 2, 1,
        2, 6, 7, 7, 3, 2,
        3, 7, 4, 4, 0, 3,
        4, 7, 6, 6, 5, 4,
        ]


buffers=None
def createCarVBO():
    buffers = glGenBuffers(3)
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0])
    glBufferData(GL_ARRAY_BUFFER, 
            len(carVertices)*4,  # byte size
            (ctypes.c_float*len(carVertices))(*carVertices), 
            GL_STATIC_DRAW)
    glBindBuffer(GL_ARRAY_BUFFER, buffers[1])
    glBufferData(GL_ARRAY_BUFFER, 
            len(carColors)*4, # byte size 
            (ctypes.c_float*len(carColors))(*carColors), 
            GL_STATIC_DRAW)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[2])
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
            len(carIndices)*4, # byte size
            (ctypes.c_uint*len(carIndices))(*carIndices), 
            GL_STATIC_DRAW)
    return buffers

def drawCarVBO():
    glEnableClientState(GL_VERTEX_ARRAY)
    glEnableClientState(GL_COLOR_ARRAY)
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0])
    glVertexPointer(3, GL_FLOAT, 0, None)
    glBindBuffer(GL_ARRAY_BUFFER, buffers[1])
    glColorPointer(3, GL_FLOAT, 0, None)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[2])
    #glDrawArrays(GL_TRIANGLE_FAN, 0,200)
    glDrawElements(GL_TRIANGLE_FAN, len(carIndices), GL_UNSIGNED_INT, None)
    glDisableClientState(GL_COLOR_ARRAY)
    glDisableClientState(GL_VERTEX_ARRAY)

shader=None
def drawCar():
    global shader, buffers
    # drawTire()
    if shader==None:
        shader=Shader()
        shader.initShader('''
            void main()
            {
                gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
                gl_FrontColor = gl_Color;
            }
                    ''',
                    '''
            void main()
            {
                gl_FragColor = gl_Color;
            }
        ''')
        
        buffers=createCarVBO()

    shader.begin()
    drawCarVBO()
    shader.end() 

buffers=None
def createTireVBO():
    buffers = glGenBuffers(3)
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0])
    glBufferData(GL_ARRAY_BUFFER, 
            len(tireVertices)*4,  # byte size
            (ctypes.c_float*len(tireVertices))(*tireVertices), 
            GL_STATIC_DRAW)
    glBindBuffer(GL_ARRAY_BUFFER, buffers[1])
    glBufferData(GL_ARRAY_BUFFER, 
            len(tireColors)*4, # byte size 
            (ctypes.c_float*len(tireColors))(*tireColors), 
            GL_STATIC_DRAW)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[2])
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
            len(indices)*4, # byte size
            (ctypes.c_uint*len(indices))(*indices), 
            GL_STATIC_DRAW)
    return buffers

def drawTireVBO():
    glEnableClientState(GL_VERTEX_ARRAY)
    glEnableClientState(GL_COLOR_ARRAY)
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0])
    glVertexPointer(3, GL_FLOAT, 0, None)
    glBindBuffer(GL_ARRAY_BUFFER, buffers[1])
    glColorPointer(3, GL_FLOAT, 0, None)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[2])
    glDrawElements(GL_TRIANGLE_FAN, len(indices), GL_UNSIGNED_INT, None)
    glDisableClientState(GL_COLOR_ARRAY)
    glDisableClientState(GL_VERTEX_ARRAY)

shader=None
def drawTire():
    global shader, buffers
    if shader==None:
        shader=Shader()
        shader.initShader('''
            void main()
            {
                gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
                gl_FrontColor = gl_Color;
            }
                    ''',
                    '''
            void main()
            {
                gl_FragColor = gl_Color;
            }
        ''')
        buffers=createTireVBO()

    shader.begin()
    drawTireVBO()
    shader.end() 

def draw_cube0():
    glBegin(GL_TRIANGLES)
    for i in range(0, len(indices), 3):
        index=indices[i]*3
        glColor3f(*colors[index:index+3])
        glVertex3f(*vertices[index:index+3])

        index=indices[i+1]*3
        glColor3f(*colors[index:index+3])
        glVertex3f(*vertices[index:index+3])

        index=indices[i+2]*3
        glColor3f(*colors[index:index+3])
        glVertex3f(*vertices[index:index+3])
    glEnd()

def draw_cube1():
    glEnableClientState(GL_VERTEX_ARRAY)
    glEnableClientState(GL_COLOR_ARRAY)
    glVertexPointer(3, GL_FLOAT, 0, vertices)
    glColorPointer(3, GL_FLOAT, 0, colors)
    glDrawElements(GL_TRIANGLES, len(indices), GL_UNSIGNED_INT, indices)
    glDisableClientState(GL_COLOR_ARRAY)
    glDisableClientState(GL_VERTEX_ARRAY)

buffers=None
def create_vbo():
    buffers = glGenBuffers(3)
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0])
    glBufferData(GL_ARRAY_BUFFER, 
            len(vertices)*4,  # byte size
            (ctypes.c_float*len(vertices))(*vertices), 
            GL_STATIC_DRAW)
    glBindBuffer(GL_ARRAY_BUFFER, buffers[1])
    glBufferData(GL_ARRAY_BUFFER, 
            len(colors)*4, # byte size 
            (ctypes.c_float*len(colors))(*colors), 
            GL_STATIC_DRAW)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[2])
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
            len(indices)*4, # byte size
            (ctypes.c_uint*len(indices))(*indices), 
            GL_STATIC_DRAW)
    return buffers

def draw_vbo():
    glEnableClientState(GL_VERTEX_ARRAY)
    glEnableClientState(GL_COLOR_ARRAY)
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0])
    glVertexPointer(3, GL_FLOAT, 0, None)
    glBindBuffer(GL_ARRAY_BUFFER, buffers[1])
    glColorPointer(3, GL_FLOAT, 0, None)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[2])
    glDrawElements(GL_TRIANGLES, len(indices), GL_UNSIGNED_INT, None)
    glDisableClientState(GL_COLOR_ARRAY)
    glDisableClientState(GL_VERTEX_ARRAY)

def draw_cube2():
    global buffers
    if buffers==None:
        buffers=create_vbo()
    draw_vbo()

shader=None
def draw_cube3():
    global shader, buffers
    if shader==None:
        shader=Shader()
        shader.initShader('''
void main()
{
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_FrontColor = gl_Color;
}
        ''',
        '''
void main()
{
    gl_FragColor = gl_Color;
}
        ''')
        buffers=create_vbo()

    shader.begin()
    draw_vbo()
    shader.end()

##############################################################################
def reshape_func(w, h):
    resize(w, h == 0 and 1 or h)

def disp_func():
    draw()
    glutSwapBuffers()

# __main__ :
if __name__=="__main__":
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH)
    glutInitWindowSize(256, 256)
    glutCreateWindow(b"vbo")
    glutDisplayFunc(disp_func)
    glutIdleFunc(disp_func)
    glutReshapeFunc(reshape_func)

    initialize()

    glutMainLoop()
