#include <iostream>
#include <SDL.h>
#include <cstdlib>
#include <GL/glu.h>
#include <GL/gl.h>

void drawTriangle();
void drawCube();

int main()
{
    if(SDL_Init(SDL_INIT_VIDEO))
    {
        std::cerr<<"Error init SDL\n";
        exit(EXIT_FAILURE);
    }

    SDL_Rect screenSize; //create screenSize variable
    SDL_GetDisplayBounds(0,&screenSize);

    SDL_Window *window = SDL_CreateWindow(
                "OpenGL Demo",
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                screenSize.w/2,
                screenSize.h/2,
                SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE

                );

    SDL_GLContext glContext;
    //set openGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    glContext = SDL_GL_CreateContext(window);
    //now make this the active context
    SDL_GL_MakeCurrent(window, glContext);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0f, (float)screenSize.w/screenSize.h,
                   0.5, 100
                   );

    glMatrixMode(GL_MODELVIEW);
    gluLookAt(2, 2, 2, 0, 0, 0, 0, 1, 0);

    bool quit = false;
    SDL_Event event;
    while(!quit)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT : quit = true; break;
                case SDL_KEYDOWN :
                    switch(event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE : quit = true; break;
                    case SDLK_w : glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
                    case SDLK_s : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
                    }
            }
        }
    glClear(GL_COLOR_BUFFER_BIT);
    //drawTriangle();
    drawCube();
    SDL_GL_SwapWindow(window);
    }
}

void drawTriangle()
{
    static int rot = 0;
    glPushMatrix();
        glRotated(++rot, 0, 1, 0);
        glBegin(GL_TRIANGLES);
            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(0.0f, 1.0f, 0.0f);
            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex3f(1.0f, -1.0f, 0.0f);
            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3f(0.0f, 0.0f, 1.0f);
        glEnd();
    glPopMatrix();
}


void drawCube()
{
    static int rot = 0;
    glPushMatrix();
        glRotated(++rot, 0, 1, 0);
        glBegin(GL_QUADS);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(-1.0, -1.0, 1.0);
        glVertex3f(-1.0, 1.0, 1.0);
        glVertex3f(1.0, 1.0, 1.0);
        glVertex3f(1.0, -1.0, 1.0);
        glEnd();
    glPopMatrix();
}
