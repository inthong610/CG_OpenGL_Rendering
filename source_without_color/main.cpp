//
//  main.cpp
//  CG_HW5
//  without color
//  Created by Jungsoo on 2018. 11. 25..
//  Copyright © 2018년 Jungsoo. All rights reserved.

// 1415088 Jungsoo Hong
#include <stdio.h>

#include <stdlib.h>
#include <iostream>

#include <OpenGL/OpenGL.h>
//#include <OpenGL/gl3.h> // for mac
#include <OpenGL/glu.h>
#define __gl_h_ // for mac

#ifdef __APPLE__ // in Mac os, <GLUT/glut.h>, in Window os, <GL/glut.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h> /* glut.h includes gl.h and glu.h*/
#endif
#include <math.h>

using namespace std;

double con_rot = 0.0;

struct ModelTri
{
    double p0[3], p1[3], p2[3];
    int    pi[3];
    double n[3];
    double n0[3], n1[3], n2[3];
    double ver[3];
};

/*
struct ModelTri
{
	double p0[3], p1[3], p2[3];
	double normal[3];
    int vnum[3];
};

struct ModelVert
{
	double ver[3];
	double normal[3];
	int trinum[100] = { 0 };
	int index = 0;

};
*/


ModelTri *triangle;
ModelTri *vertex;
int ntris,nvertics;

inline void VmV(double Vr[3], const double V1[3], const double V2[3])
{ // v0에서의벡타/
    Vr[0] = V1[0] - V2[0];
    Vr[1] = V1[1] - V2[1];
    Vr[2] = V1[2] - V2[2];
}

inline void VcrossV(double Vr[3], const double V1[3], const double V2[3])
{
    Vr[0] = V1[1]*V2[2] - V1[2]*V2[1];
    Vr[1] = V1[2]*V2[0] - V1[0]*V2[2];
    Vr[2] = V1[0]*V2[1] - V1[1]*V2[0];
}

inline void Vnormalize(double V[3])
{
    double d1=sqrt(V[0]*V[0] + V[1]*V[1] + V[2]*V[2]);
    double d;
    if (d1==0)
    {
        d=0;
    }
    else
    {
        d = (double)1.0 / sqrt(V[0]*V[0] + V[1]*V[1] + V[2]*V[2]);
    }

    V[0] *= d;
    V[1] *= d;
    V[2] *= d;
}

void ReadTriFile(const char *tris_file)
{
    FILE *fp = fopen(tris_file, "r");
    if (fp == NULL)
    {
        fprintf(stderr,"Model Constructor: Couldn't open %s\n",tris_file);
        exit(-1);
    }

    int i1,i2,i3;
    double am, bm, cm;
    char str[10];

    fscanf(fp,"%s",str);
    fscanf(fp,"%d",&nvertics);
    fscanf(fp,"%d",&ntris);

    triangle = new ModelTri[ntris]; //.총 삼각형의 갯수.
    vertex = new ModelTri[nvertics];

    for (int i = 0; i < nvertics; i++)
    {
        fscanf(fp,"%lf %lf %lf",&am,&bm,&cm);
        vertex[i].ver[0]=am;
        vertex[i].ver[1]=bm;
        vertex[i].ver[2]=cm;
    }
    for (int i = 0; i < ntris; i++)
    {
        //int temp;
        fscanf(fp,"%d %d %d", &i1,&i2,&i3);
        triangle[i].p0[0] = vertex[i1].ver[0];
        triangle[i].p0[1] = vertex[i1].ver[1];
        triangle[i].p0[2] = vertex[i1].ver[2];

        triangle[i].p1[0] = vertex[i2].ver[0];
        triangle[i].p1[1] = vertex[i2].ver[1];
        triangle[i].p1[2] = vertex[i2].ver[2];

        triangle[i].p2[0] = vertex[i3].ver[0];
        triangle[i].p2[1] = vertex[i3].ver[1];
        triangle[i].p2[2] = vertex[i3].ver[2];

        double a[3],b[3];
        VmV(a,triangle[i].p1,triangle[i].p0); ///.VmV(double Vr[3], const double V1[3], const double V2[3])

        VmV(b,triangle[i].p2,triangle[i].p0);
        VcrossV(triangle[i].n,a,b);///.VcrossV(double Vr[3], const double V1[3], const double V2[3])
        Vnormalize(triangle[i].n);
    }
    fclose(fp);

}

void ReadOffFile(const char *offs_file)
{
    FILE *fp =fopen(offs_file, "r");
    if (fp == NULL)
    {
        fprintf(stderr,"Model Constructor: Couldn't open %s\n",offs_file);
        exit(-1);
    }

    int a,i1,i2,i3;
    double am, bm, cm;
    char str[10];

    fscanf(fp,"%s",str);
    fscanf(fp,"%d",&nvertics);
    fscanf(fp,"%d",&ntris);
    fscanf(fp,"%d",&a);
    triangle = new ModelTri[ntris];
    vertex = new ModelTri[nvertics];

    for (int i = 0; i < nvertics; i++)
    {
        fscanf(fp,"%lf %lf %lf",&am,&bm,&cm);
        vertex[i].ver[0]=am;
        vertex[i].ver[1]=bm;
        vertex[i].ver[2]=cm;
    }
    for (int i = 0; i < ntris; i++)
    {

        int temp;
        fscanf(fp,"%d %d %d %d",&temp, &i1,&i2,&i3);
        triangle[i].p0[0] = vertex[i1].ver[0];
        triangle[i].p0[1] = vertex[i1].ver[1];
        triangle[i].p0[2] = vertex[i1].ver[2];
        triangle[i].pi[0] = i1;

        triangle[i].p1[0] = vertex[i2].ver[0];
        triangle[i].p1[1] = vertex[i2].ver[1];
        triangle[i].p1[2] = vertex[i2].ver[2];
        triangle[i].pi[1] = i2;

        triangle[i].p2[0] = vertex[i3].ver[0];
        triangle[i].p2[1] = vertex[i3].ver[1];
        triangle[i].p2[2] = vertex[i3].ver[2];
        triangle[i].pi[2] = i3;

        double a[3],b[3];
        VmV(a,triangle[i].p1,triangle[i].p0);
        VmV(b,triangle[i].p2,triangle[i].p0);
        VcrossV(triangle[i].n,a,b);
        Vnormalize(triangle[i].n);

        triangle[i].n0[0] = triangle[i].n[0]; //copy the normal to each vertex normal
        triangle[i].n0[1] = triangle[i].n[1];
        triangle[i].n0[2] = triangle[i].n[2];

        triangle[i].n1[0] = triangle[i].n[0];
        triangle[i].n1[1] = triangle[i].n[1];
        triangle[i].n1[2] = triangle[i].n[2];

        triangle[i].n2[0] = triangle[i].n[0];
        triangle[i].n2[1] = triangle[i].n[1];
        triangle[i].n2[2] = triangle[i].n[2];
    }


    for (int i = 0; i < ntris; i++) //average adjacent triangle normals
    {
        int currIndex0 = triangle[i].pi[0];
        int currIndex1 = triangle[i].pi[1];
        int currIndex2 = triangle[i].pi[2];
        for(int k = 0; k < ntris; k++) //brute force search
        {
            if(triangle[k].pi[0] == currIndex0)
            {
                triangle[i].n0[0] += triangle[k].n[0];
                triangle[i].n0[1] += triangle[k].n[1];
                triangle[i].n0[2] += triangle[k].n[2];
                return; // 수정. for HW5. 파일 빠르게.
            }
            if(triangle[k].pi[1] == currIndex1)
            {
                triangle[i].n1[0] += triangle[k].n[0];
                triangle[i].n1[1] += triangle[k].n[1];
                triangle[i].n1[2] += triangle[k].n[2];
                return; // 수정. for HW5. 파일 빠르게.

            }
            if(triangle[k].pi[0] == currIndex2)
            {
                triangle[i].n2[0] += triangle[k].n[0];
                triangle[i].n2[1] += triangle[k].n[1];
                triangle[i].n2[2] += triangle[k].n[2];
                return;// 수정. for HW5. 파일 빠르게.

            }
        }
        Vnormalize(triangle[i].n0);
        Vnormalize(triangle[i].n1);
        Vnormalize(triangle[i].n2);
    }
    fclose(fp);

}

void drawCatchModel()
{
    glClearColor(0.1,0.1,0.1,1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
  //  glTranslatef(0,0,0); // 수정. for HW5. 위치 재선정.
	glTranslatef(0,-3,0);


    glRotatef(90,-1,0,0);
    glRotatef(con_rot,0,0,1);


    glBegin(GL_TRIANGLES);
    for (int i = 0; i < ntris; i++)
    {
        glNormal3dv(triangle[i].n0);
        glVertex3dv(triangle[i].p0);
        glNormal3dv(triangle[i].n1);
        glVertex3dv(triangle[i].p1);
        glNormal3dv(triangle[i].n2);
        glVertex3dv(triangle[i].p2);
    }
    glEnd();
    glPopMatrix();
    glFlush();
}

static void Timer(int value)
{
    con_rot += 3.0; // 수정. for HW5. 회전 속도 늦추기 위하여 10->3
    if(con_rot > 360.0)
        con_rot /= 360.0;
    glutPostRedisplay();
    glutTimerFunc(100, Timer, 0);
}



void myReshape(GLsizei w,GLsizei h)
{
    float ratio = 1.0* w / h;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100,(float)w/h,0.1,5000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 15.0, 0.0, 0.0, -5.0, 0.0f,1.0f,0.0f);
}

void init()
{
    char filename[256];

	glEnable(GL_COLOR_MATERIAL); // 수정. for HW5. 이게 있어야 컬러 나옴. in 튜토리얼.


	   /////// from teapots.c
	   ///////
	   GLfloat ambient[] = {0.0, 0.0, 0.0, 1.0};
	    GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0};
	    GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
	    GLfloat position[] = {0.0, 3.0, 3.0, 0.0};

	    GLfloat lmodel_ambient[] = {0.2, 0.2, 0.2, 1.0};
	    GLfloat local_view[] = {0.0};

	    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	    glLightfv(GL_LIGHT0, GL_POSITION, position);
	    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);//

	    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	    glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

	    glFrontFace(GL_CW);
	    glEnable(GL_LIGHTING);
	    glEnable(GL_LIGHT0);
	    glEnable(GL_AUTO_NORMAL);
	    glEnable(GL_NORMALIZE);
	    glEnable(GL_DEPTH_TEST);
	   ///////
	   ///////

    glShadeModel(GL_SMOOTH);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    printf("Enter the file name :  ");

    scanf( "%s", filename );

    ReadOffFile(filename);

 //   ReadOffFile("generated.off");
}


int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH |GLUT_SINGLE);

    glutInitWindowSize(800,600);
    glutInitWindowPosition(10,10);
    glutCreateWindow("123DCatchGLRendering");

    init();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(drawCatchModel);
    Timer(100); // to rotate model
    glutMainLoop();

}

