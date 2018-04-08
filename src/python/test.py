import sys
import array
import math
from OpenGL.GL import *
# from OpenGL.GLU import *
from OpenGL.GLUT import *

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

tireCenterPoints = [
        0.30, 0.15, 0.0,
        0.60, 0.15, 0.0,
        0.30, 0.15, -0.70,
        0.60, 0.15, -0.70
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

tireIndices=[
        0,1,2, 0,2,3, 0,3,4, 0,4,5, 0,5,6, 0,6,7, 0,7,8, 0,8,9, 0,9,10, 0,10,11, 0,11,12, 0,12,13, 0,13,14, 0,14,15, 0,15,16, 0,16,17, 0,17,18, 0,18,19, 0,19,20, 0,20,21,
        22,23,24, 22,24,25, 22,25,26, 22,26,27, 22,27,28, 22,28,29, 22,29,30, 22,30,31, 22,31,32, 22,32,33, 22,33,34, 22,34,35, 22,35,36, 22,36,37, 22,37,38, 22,38,39, 22,39,40, 22,40,41,
        1,2,23, 23,24,2, 2,3,24 
    ]

triangleAmount = 20
tireVertices = [
    array.array('i',(0 for i in range(0,(triangleAmount + 1) * 2 * 3 + 1))),
    array.array('i',(0 for i in range(0,(triangleAmount + 1) * 2 * 3 + 1))),
    array.array('i',(0 for i in range(0,(triangleAmount + 1) * 2 * 3 + 1))),
    array.array('i',(0 for i in range(0,(triangleAmount + 1) * 2 * 3 + 1)))
    ]

radius = 150.0
twicePI = 2.0 * 3.14
def GenerateTireArray():
    currentTire = 0
    tireCount = 0
    while (currentTire < 4):
        tireCount = currentTire * 3
        tireVertices[currentTire][0] = tireCenterPoints[tireCount]
        tireVertices[currentTire][1] = tireCenterPoints[tireCount + 1]
        tireVertices[currentTire][2] = tireCenterPoints[tireCount + 2]
        currentVertex = 1
        valueCount = 0
        while (currentVertex - 1 <= triangleAmount) :
            valueCount = currentVertex * 3
            tireVertices[currentTire][valueCount] = tireCenterPoints[tireCount] + (radius * math.cos(currentVertex * twicePI / triangleAmount))
            tireVertices[currentTire][valueCount + 1] = tireCenterPoints[tireCount + 1] + (radius * math.sin(currentVertex * twicePI /triangleAmount))
            tireVertices[currentTire][valueCount + 2] = tireCenterPoints[tireCount + 2]
            currentVertex = currentVertex + 1

        valueCount = currentVertex * 3
        tireVertices[currentTire][valueCount] = tireCenterPoints[tireCount]
        tireVertices[currentTire][valueCount + 1] = tireCenterPoints[tireCount + 1]
        tireVertices[currentTire][valueCount + 2] = tireCenterPoints[tireCount + 2] + 0.2
        currentVertex = currentVertex + 1
        while (currentVertex - 1 <= triangleAmount * 2) :
            valueCount = currentVertex * 3
            tireVertices[currentTire][valueCount] = tireCenterPoints[tireCount] + (radius * math.cos(currentVertex * twicePI / triangleAmount))
            tireVertices[currentTire][valueCount + 1] = tireCenterPoints[tireCount + 1] + (radius * math.sin(currentVertex * twicePI /triangleAmount))
            tireVertices[currentTire][valueCount + 2] = tireCenterPoints[tireCount + 2] + 0.2
            currentVertex = currentVertex + 1
        currentTire = currentTire + 1
    tireIndices[0] = 0

carBuffers=None
def createCarVBO():
    carBuffers = glGenBuffers(3)
    glBindBuffer(GL_ARRAY_BUFFER, carBuffers[0])
    glBufferData(GL_ARRAY_BUFFER, 
            len(carVertices)*4,  # byte size
            (ctypes.c_float*len(carVertices))(*carVertices), 
            GL_STATIC_DRAW)
    glBindBuffer(GL_ARRAY_BUFFER, carBuffers[1])
    glBufferData(GL_ARRAY_BUFFER, 
            len(carColors)*4, # byte size 
            (ctypes.c_float*len(carColors))(*carColors), 
            GL_STATIC_DRAW)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, carBuffers[2])
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
            len(carIndices)*4, # byte size
            (ctypes.c_uint*len(carIndices))(*carIndices), 
            GL_STATIC_DRAW)
    return carBuffers

def drawCarVBO():
    glEnableClientState(GL_VERTEX_ARRAY)
    glEnableClientState(GL_COLOR_ARRAY)
    glBindBuffer(GL_ARRAY_BUFFER, carBuffers[0])
    glVertexPointer(3, GL_FLOAT, 0, None)
    glBindBuffer(GL_ARRAY_BUFFER, carBuffers[1])
    glColorPointer(3, GL_FLOAT, 0, None)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, carBuffers[2])
    glDrawElements(GL_TRIANGLE_FAN, len(carIndices), GL_UNSIGNED_INT, None)
    glDisableClientState(GL_COLOR_ARRAY)
    glDisableClientState(GL_VERTEX_ARRAY)

def drawCar():
    global carBuffers
    if carBuffers==None:
        carBuffers=createCarVBO()
    drawCarVBO()


# The display() method does all the work; it has to call the appropriate
# OpenGL functions to actually display something.
def display():
    # Clear the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

    # ... render stuff in here ...
    # It will go to an off-screen frame buffer.
    drawCar()

    # Copy the off-screen buffer to the screen.
    glutSwapBuffers()

glutInit(sys.argv)

# Create a double-buffer RGBA window. (Single-buffering is possible.
# So is creating an index-mode window.)
glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH)

# Create a window, setting its title
glutCreateWindow(b'3D car')
# glutCreateWindow('interactive')

# Set the display callback. You can set other callbacks for keyboard and
# mouse events.
glutDisplayFunc(display)

# Run the GLUT main loop until the user closes the window.
glutMainLoop()