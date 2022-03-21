#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<math.h>

void *font;
void *currentfont;
float i,j,x,y,angle,angle_radians;
float r1=80,r2=5.0,r3=27.5,r4=6,r5=6,r6=23,r8=3,r10=18,r11=10,r12=26,r13=14;

void delay(int x)		//Delay function
{
    int i,j;
    for(i=0; i<x; i++)
    {
        for(j=0; j<i*1000; j++);
    }
}

void fan1() //Fans of the Turbine
{
    glBegin(GL_POINTS);
    glVertex2f(255,138);
    glEnd();

    glBegin(GL_POLYGON);	//Triangle coordinates
    glVertex2f(255,138);
    glVertex2f(265,158);
    glVertex2f(245,158);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(255,138);
    glVertex2f(277,135);
    glVertex2f(263,118);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(255,138);
    glVertex2f(231,133);
    glVertex2f(247,118);
    glEnd();
}

void fan2() //Fans of the Turbine
{
    glBegin(GL_POINTS);
    glVertex2f(255,138);
    glEnd();

    glBegin(GL_POLYGON);	//Triangle coordinates
    glVertex2f(255,138);
    glVertex2f(275,150);
    glVertex2f(275,126);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(255,138);
    glVertex2f(250,115);
    glVertex2f(234,130);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(255,138);
    glVertex2f(253,160);
    glVertex2f(236,149);
    glEnd();
}

void fan3()	//Fans of the Turbine
{

    glBegin(GL_POINTS);
    glVertex2f(255,138);
    glEnd();

    glBegin(GL_POLYGON);	//Triangle coordinates
    glVertex2f(255,138);
    glVertex2f(266,117);
    glVertex2f(244,117);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(255,138);
    glVertex2f(277,144);
    glVertex2f(261,160);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(255,138);
    glVertex2f(249,159);
    glVertex2f(233,144);
    glEnd();
}

void fan4()	//Fans of the Turbine
{
    glBegin(GL_POINTS);
    glVertex2f(255,138);
    glEnd();

    glBegin(GL_POLYGON);	//Triangle coordinates
    glVertex2f(255,138);
    glVertex2f(235,128);
    glVertex2f(235,148);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(255,138);
    glVertex2f(276,144);
    glVertex2f(257,161);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(255,138);
    glVertex2f(257,115);
    glVertex2f(275,127);
    glEnd();
}

void rotateFan()	//Rotation of fans of the turbine
{
    glDisable(GL_DEPTH_TEST);
    glColor3f(0.3,0.1,0.1);		//Display the triangle
    fan1();
    glFlush();
    delay(200);
    glColor3f(0.0,0.0,0.0);		//Hide the triangle to avoid overlapping by setting the color to the background color(black)
    fan1();
    glFlush();
    delay(200);
    glColor3f(0.3,0.1,0.1);
    fan2();
    glFlush();
    delay(200);
    glColor3f(0.0,0.0,0.0);
    fan2();
    glFlush();
    delay(200);
    glColor3f(0.3,0.1,0.1);
    fan3();
    glFlush();
    glColor3f(0.0,0.0,0.0);
    fan3();
    glFlush();
    delay(200);
    glColor3f(0.3,0.1,0.1);
    fan4();
    glFlush();
    delay(200);
}

void turbine()	//Circular loop of the turbine
{
    glLineWidth(6.0);
    glBegin(GL_LINE_LOOP);	//Inner loop
    for(angle=0; angle<=360; angle=angle+5)
    {
        angle_radians = angle * (float)3.14159 / (float)180;
        x = 255 + r6* (float)cos(angle_radians);
        y = 138 + r6* (float)sin(angle_radians);
        glColor3f(0.3,0.1,0.1);
        glVertex2f(x,y);
    }
    glEnd();

    glLineWidth(6.0);
    glBegin(GL_LINE_STRIP);	//Outer loop
    for(angle=0; angle<=360; angle=angle+5)
    {
        angle_radians = angle * (float)3.14159 / (float)180;
        x = 255 + r12* (float)cos(angle_radians);
        y = 138 + r12* (float)sin(angle_radians);
        glColor3f(0.3,0.1,0.1);

        glVertex2f(x,y);
    }
    glEnd();

    glPointSize(6);
    glBegin(GL_POINTS);		
    glVertex2f(255,138);	//Center of the turbine
    glEnd();
    fan4();		//Initial position of the fans
}

void generator()	//Generator
{
    glColor3f(0.5,0.5,0.9);	//Vertical part of power station
    glBegin(GL_POLYGON);
    glVertex3i(338,120,0);
    glColor3f(0.2,0.2,0.6);
    glVertex3i(338,150,0);
    glVertex3i(343,150,0);
    glVertex3i(343,120,0);
    glEnd();

    glColor3f(0.5,0.5,0.9);	//Vertical part of power station		
    glBegin(GL_POLYGON);
    glVertex3i(351,120,0);
    glColor3f(0.2,0.2,0.6);
    glVertex3i(351,150,0);
    glVertex3i(356,150,0);
    glVertex3i(356,120,0);
    glEnd();

    glColor3f(0.5,0.5,0.9);	//Vertical part of power station
    glBegin(GL_POLYGON);
    glVertex3i(364,120,0);
    glColor3f(0.2,0.2,0.6);
    glVertex3i(364,150,0);
    glVertex3i(369,150,0);
    glVertex3i(369,120,0);
    glEnd();

    glColor3f(0.3,0.1,0.1);	//Connection between turbine and power station
    glBegin(GL_POLYGON);
    glVertex3i(375,144,0);
    glVertex3i(277,144,0);
    glVertex3i(277,137,0);
    glVertex3i(375,137,0);
    glEnd();

    glLineWidth(6.0);
    glBegin(GL_LINE_STRIP);	//Enclosing case of the power station
    glColor3f(0.6,0.6,0.6);
    glVertex2f(330,170);
    glVertex2f(385,170);
    glVertex2f(385,111);
    glVertex2f(330,111);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.2,0.2,0.6);	//Base of vertical lines in power station
    glVertex3i(330,111,0);
    glVertex3i(330,120,0);
    glColor3f(0.5,0.5,0.9);
    glVertex3i(375,120,0);
    glVertex3i(375,111,0);
    glEnd();
}

void connecting_pipe()	//Connecting pipes of the pump between generator and steam generator
{
    glLineWidth(3.0);
    glColor3f(0.6,0.3,0.2);
    glBegin(GL_LINES);
    glVertex2i(150,104);
    glVertex2i(180,104);
    glVertex2i(150,108);
    glVertex2i(180,108);
    glEnd();

    glBegin(GL_LINES);
    glVertex2i(185,100);
    glVertex2i(185,50);
    glVertex2i(185,50);
    glVertex2i(224,50);
    glVertex2i(189,100);
    glVertex2i(189,54);
    glVertex2i(189,54);
    glVertex2i(224,54);
    glEnd();
}

void turbinePoints()	//Scattered points near the turbine
{
    glPointSize(4);
    glColor3f(0.7,0.7,0.7);
    glBegin(GL_POINTS);
    glVertex2f(243,134);
    glVertex2f(249,128);
    glVertex2f(246,122);
    glVertex2f(256,115);
    glVertex2f(251,110);
    glVertex2f(264,108);
    glVertex2f(272,104);
    glVertex2f(242,110);
    glVertex2f(247,100);
    glVertex2f(256,104);
    glVertex2f(230,100);
    glVertex2f(235,105);
    glVertex2f(239,110);
    glVertex2f(264,104);
    glVertex2f(249,123);
    glVertex2f(269,130);
    glVertex2f(264,128);
    glVertex2f(270,100);
    glVertex2f(274,104);
    glVertex2f(272,90);
    glVertex2f(275,130);
    glVertex2f(265,127);
    glVertex2f(255,133);
    glEnd();
}

void steam()
{
    for(i=0; i<21; i=i+1)	//Filling of steam in the steam line(vertically up)
    {
        glColor4f(0.4,0.4,0.4,1.0);
        glBegin(GL_QUADS);
        glVertex2f(120,185.5+i);
        glVertex2f(120,189.5+i);
	glColor4f(1.0,1.0,1.0,1.0);
        glVertex2f(124,189.5+i);
        glVertex2f(124,185.5+i);
        glEnd();
        glFlush();
        delay(200);
    }
    for(i=0; i<117; i=i+1)	//Filling of steam in the steam line(horizontal)
    {
        glBegin(GL_QUADS);
        glColor4f(1.0,1.0,1.0,1.0);
        glVertex2f(124+i,210);
        glVertex2f(128+i,210);
        glColor4f(0.4,0.4,0.4,1.0);
        glVertex2f(128+i,206);
        glVertex2f(124+i,206);
        glEnd();
        glFlush();
        delay(200);
    }
    for(i=0; i<33; i=i+1)	//Filling of steam in the steam line(vertically down)
    {
        glBegin(GL_QUADS);
        glColor4f(1.0,1.0,1.0,1.0);
        glVertex2f(240,206-i);
        glColor4f(0.4,0.4,0.4,1.0);
        glVertex2f(244,206-i);
        glVertex2f(244,202-i);
        glColor4f(1.0,1.0,1.0,1.0);
        glVertex2f(240,202-i );
        glEnd();
        glFlush();
        delay(200);
    }
    glColor3f(0.4,0.4,0.4);
    glBegin(GL_QUADS);		//End of the steam line near turbine(cone shape)
    glVertex2f(240,170);
    glVertex2f(244,170);
    glVertex2f(252,159);
    glVertex2f(232,159);
    glEnd();
    glFlush();
}

void coolant_pipe()	//Flowing of liquid in coolant pipes(between generator and steam generator)
{
    for(i=0; i<31; i=i+1)
    {
        glBegin(GL_QUADS);
        glColor3f(1.0,1.0,1.0);
        glVertex2f(215-i,54);
        glColor3f(0.0,0.6,0.8);
        glVertex2f(215-i,50);
        glVertex2f(225-i,50);
        glColor3f(1.0,1.0,1.0);
        glVertex2f(225-i,54);
        glEnd();
        glFlush();
        delay(200);
    }
    for(i=0; i<43; i=i+1)
    {
        glBegin(GL_QUADS);
        glColor3f(0.0,0.6,0.8);
        glVertex2f(185,54+i);
        glColor3f(1.0,1.0,1.0);
        glVertex2f(189,54+i);
        glVertex2f(189,58+i);
        glColor3f(0.0,0.6,0.8);
        glVertex2f(185,58+i);
        glEnd();
        glFlush();
        delay(200);
    }
    delay(500);
    for(i=0; i<28; i=i+1)
    {
        glBegin(GL_QUADS);
        glColor3f(1.0,1.0,1.0);
        glVertex2f(180-i,108);
        glColor3f(0.0,0.6,0.8);
        glVertex2f(180-i,104);
        glVertex2f(176-i,104);
        glColor3f(1.0,1.0,1.0);
        glVertex2f(176-i,108);
        glEnd();
        glFlush();
        delay(200);
    }
}

void reactorPoints()		//Scattered points in the reactor vessel
{
    glPointSize(5.0);
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_POINTS);
    glVertex2f(46,124);
    glVertex2f(44,130);
    glVertex2f(48,135);
    glVertex2f(49,126);
    glVertex2f(42,140);
    glVertex2f(46,139);
    glVertex2f(54,128);
    glVertex2f(38,148);
    glVertex2f(32,143);
    glVertex2f(57,124);
    glVertex2f(61,138);
    glVertex2f(51,134);
    glEnd();
}

void generatorPoints()		//Scattered points in the steam generator
{
    glPointSize(3.0);
    glColor3f(0.7,0.7,0.7);
    glBegin(GL_POINTS);
    glVertex2f(107,117);
    glVertex2f(109,120);
    glVertex2f(110,123);
    glVertex2f(106,125);
    glVertex2f(113,120);
    glVertex2f(113,131);
    glVertex2f(108,141);
    glVertex2f(111,130);
    glVertex2f(107,127);
    glVertex2f(111,131);
    glVertex2f(123,145);
    glVertex2f(131,145);
    glVertex2f(142,151);
    glVertex2f(133,148);
    glVertex2f(137,133);
    glVertex2f(139,157);
    glVertex2f(128,160);
    glVertex2f(146,163);
    glVertex2f(149,170);
    glVertex2f(150,124);
    glVertex2f(153,119);
    glVertex2f(148,136);
    glVertex2f(137,115);
    glVertex2f(149,127);
    glVertex2f(108,170);
    glVertex2f(104,145);
    glVertex2f(109,175);
    glVertex2f(111,156);
    glVertex2f(118,164);
    glVertex2f(127,166);
    glVertex2f(129,169);
    glVertex2f(126,132);
    glVertex2f(123,128);
    glVertex2f(126,140);
    glVertex2f(119,141);
    glVertex2f(127,151);
    glVertex2f(126,155);
    glVertex2f(121,171);
    glVertex2f(126,180);
    glVertex2f(133,185);
    glVertex2f(141,190);
    glVertex2f(138,176);
    glEnd();
}

void working()
{
    glClearColor(0,0,0,0);
    for(i=0,j=0; i<40,j<40; i=i+1,j=i+1)	//Horizontal flowing of liquid in condensor and pump
    {
        glBegin(GL_QUADS);
        glColor3f(0.0,0.6,0.8);
        glVertex2f(70+i,117);	
        glVertex2f(74+i,117);
        glColor3f(1.0,1.0,1.0);
        glVertex2f(74+i,121);
        glVertex2f(70+i,121);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.0,0.6,0.8);
        glVertex2f(350-j,89);
        glVertex2f(280-j,89);
        glColor3f(1.0,1.0,1.0);
        glVertex2f(280-j,85);
        glVertex2f(350-j,85);
        glEnd();
        glFlush();
        delay(200);
    }
    for(i=0,j=0; i<32,j<25; i=i+1,j=j+1)	//Vertical flow of liquid in steam generator pipes
    {
        glBegin(GL_QUADS);
        glColor3f(1.0,1.0,1.0);
        glVertex2f(111,117+i);
        glColor3f(0.0,0.6,0.8);
        glVertex2f(114,117+i);
        glVertex2f(114,136+i);
        glColor3f(1.0,1.0,1.0);
        glVertex2f(111,136+i);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.0,0.6,0.8);
        glVertex2f(240,89-j);
        glColor3f(1.0,1.0,1.0);
        glVertex2f(244,89-j);
        glVertex2f(244,85-j);
        glColor3f(0.0,0.6,0.8);
        glVertex2f(240,85-j);
        glEnd();
        glFlush();
        delay(200);
    }
    for(i=0,j=0; i<25,j<25; i=i+1,j=j+1)	//Horizontal flowing of liquid in condensor and steam generator
    {
        glBegin(GL_QUADS);
        glColor3f(1.0,1.0,1.0);
        glVertex2f(111+i,160);
        glVertex2f(115+i,160);
        glColor3f(0.0,0.6,0.8);
        glVertex2f(115+i,163.5);
        glVertex2f(111+i,163.5);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(1.0,1.0,1.0);
        glVertex2f(244+j,65);
        glVertex2f(326+j,65);
        glColor3f(0.0,0.6,0.8);
        glVertex2f(326+j,61);
        glVertex2f(244+j,61);
        glEnd();
        glFlush();
        delay(200);
    }
    for(i=0; i<112; i=i+1)	//Vertical flow of liquid in steam generator
    {
        glBegin(GL_QUADS);
        glColor3f(1.0,1.0,1.0);
        glVertex2f(135.2,160-i);
        glColor3f(0.0,0.6,0.8);
        glVertex2f(138.9,160-i);
        glVertex2f(138.9,156-i);

        glColor3f(1.0,1.0,1.0);
        glVertex2f(135.2,156-i);
        glEnd();
        glFlush();
        delay(200);
    }
    for(i=0; i<40; i=i+1)	//flow of liquid from steam generator to pump(Horizontal)
    {
        glBegin(GL_QUADS);
        glColor3f(1.0,1.0,1.0);
        glVertex2f(131-i,47.5);
        glVertex2f(135.3-i,47.5);
        glColor3f(0.0,0.6,0.8);
        glVertex2f(135.3-i,44.5);
        glVertex2f(131-i,44.5);
        glEnd();
        glFlush();
        delay(200);
    }
    delay(500);
    for(i=0; i<58; i=i+1)	//flow of liquid from pump to reactor vessel(Horizontal)
    {
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_QUADS);
        glVertex2f(80-i,47.5);
        glColor3f(0.0,0.6,0.8);
        glVertex2f(80-i,44.5);
        glVertex2f(76-i,44.5);
        glColor3f(1.0,1.0,1.0);
        glVertex2f(76-i,47.5);
        glEnd();
        glFlush();
        delay(200);
    }

    for(i=0; i<92; i=i+1)	//flow of liquid from pump to reactor vessel(Vertical)
    {
        glBegin(GL_QUADS);
        glColor3f(0.0,0.6,0.8);
        glVertex2f(16.5,47.5+i);
        glColor3f(1.0,1.0,1.0);
        glVertex2f(19.5,47.5+i);
        glVertex2f(19.5,44.5+i);
        glColor3f(0.0,0.6,0.8);
        glVertex2f(16.5,44.5+i);
        glEnd();
        glFlush();
        delay(200);
    }

    for(i=0; i<8; i=i+1)	//flow of liquid from pump to reactor vessel(Horizontal)
    {
        glColor3f(0.0,0.6,0.8);
        glBegin(GL_QUADS);
        glVertex2f(19.5+i,138.5);
        glVertex2f(23+i,138.5);
        glColor3f(1.0,1.0,1.0);
        glVertex2f(23+i,135.5);
        glVertex2f(19.5+i,135.5);
        glEnd();
        glFlush();
        delay(200);
    }
    generatorPoints();		//Steam in the steam generator
    steam();		//Filling of steam in the steam line
    rotateFan();		//Rotation of the turbine
    glEnable(GL_DEPTH_TEST);
    turbinePoints();		//Scattered points near turbine
    coolant_pipe();	//Flowing of coolant liquid
    glutIdleFunc(rotateFan);		//Enable the rotation of the fan (Disabled in display_about())
}

void drawstring(float x,float y,float z,char *string)		//To write something on the screen
{
    char *c;
    glRasterPos3f(x,y,z);
    for(c=string; *c!='\0'; c++)
    {
	   glColor3f(0.0,1.0,1.0);
           glutBitmapCharacter(currentfont,*c);
    }
}

void setFont(void *font)		//To set the font of the string
{
    currentfont=font;
}

void display_nuclear_power_plant()
{
    glutIdleFunc(NULL);			//Disable the rotation of the turbine fan
    glLineWidth(6.0);
    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glBegin(GL_LINE_STRIP);		//Constraint structure
    glColor3f(0.7,0.7,0.7);
    glVertex2i(10,200);
    glVertex2i(10,30);
    glVertex2i(170,30);
    glVertex2i(170,200);
    glEnd();

    glColor3f(0.6,0.6,0.6);		//Curved part of the constraint structure
    glBegin(GL_LINE_STRIP);
    for(angle=0; angle<=180; angle=angle+5)
    {
        angle_radians = angle * (float)3.14159 / (float)180;
        x = 90 + r1* (float)cos(angle_radians);
        y = 200 + r1* (float)sin(angle_radians);
        glLineWidth(6.0);
        glVertex2f(x,y);
    }
    glEnd();

    glBegin(GL_POLYGON);	//Fluid inside reactor vessel
    glColor3f(0.0,0.0,1.0);
    glVertex2f(26,122);
    glColor3f(0.0,0.6,0.8);
    glVertex2f(26,76);
    glVertex2f(74,76);
    glColor3f(0.0,0.0,0.5);
    glVertex2f(74,122);
    glEnd();

    glColor3f(0.0,0.6,0.8);	//Liquid inside steam generator(Dark color)
    glBegin(GL_POLYGON);
    glVertex2i(100,100);
    glVertex2i(155,100);
    glColor3f(0.0,0.0,1.0);
    glVertex2i(155,113);
    glVertex2i(100,113);
    glEnd();

    glColor3f(0.0,0.6,0.8);	//Liquid inside steam generator
    glBegin(GL_POLYGON);
    for(angle=180; angle<=360; angle=angle+5)
    {
        angle_radians = angle * (float)3.14159 / (float)180;
        x = 127.5 + r3* (float)cos(angle_radians);
        y = 100 + r3* (float)sin(angle_radians);
        glLineWidth(6.0);
        glVertex2f(x,y);
    }
    glEnd();

    glColor3f(0.7,0.7,0.7);		//Reactor Vessel
    glBegin(GL_LINE_LOOP);
    glVertex2i(25,150);
    glVertex2i(25,75);
    glVertex2i(75,75);
    glVertex2i(75,150);
    glEnd();

    glColor3f(0.7,0.7,0.7);		//Steam generator
    glBegin(GL_LINES);
    glVertex2i(100,100);
    glVertex2i(100,170);
    glVertex2i(155,100);
    glVertex2i(155,170);
    glEnd();
    glBegin(GL_LINE_STRIP);
    for(angle=0; angle<=180; angle=angle+5)
    {
        angle_radians = angle * (float)3.14159 / (float)180;
        x = 127.5 + r3* (float)cos(angle_radians);
        y = 170 + r3* (float)sin(angle_radians);
        glLineWidth(6.0);
        glVertex2f(x,y);
    }
    glEnd();

    glBegin(GL_LINE_STRIP);
    for(angle=180; angle<=360; angle=angle+5)
    {
        angle_radians = angle * (float)3.14159 / (float)180;
        x = 127.5 + r3* (float)cos(angle_radians);
        y = 100 + r3* (float)sin(angle_radians);
        glLineWidth(6.0);
        glVertex2f(x,y);
    }
    glEnd();

    glLineWidth(5.0);		//Core container
    glColor3f(0.7,0.7,0.7);
    glBegin(GL_LINE_LOOP);
    glVertex2i(42,105);
    glVertex2i(57,105);
    glVertex2i(57,120);
    glVertex2i(42,120);
    glEnd();

    glBegin(GL_POLYGON);	//Core
    for(angle=0; angle<=360; angle=angle+5)
    {
        angle_radians = angle * (float)3.14159 / (float)180;
        x = 49 + r2* (float)cos(angle_radians);
        y = 112.5 + r2* (float)sin(angle_radians);
        glColor3f(1.0,0.4,0.2);
        glLineWidth(6.0);
        glVertex2f(x,y);
    }
    glEnd();

    glLineWidth(6.0);		//Case enclosing the generator
    glColor3f(0.7,0.7,0.7);
    glBegin(GL_LINE_LOOP);
    glVertex2i(220,170);
    glVertex2i(220,30);
    glVertex2i(330,30);
    glVertex2i(330,220);
    glEnd();

    glLineWidth(3.0);		//Pipe from pump to reactor vessel
    glColor3f(0.6,0.3,0.2);
    glBegin(GL_LINE_STRIP);
    glVertex2i(30,135);
    glVertex2i(20,135);
    glVertex2i(20,48);
    glVertex2i(80,48);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2i(80,44);
    glVertex2i(16,44);
    glVertex2i(16,139);
    glVertex2i(30,139);
    glEnd();

    glColor3f(0.6,0.3,0.2);		//Pipe from reactor vessel to pump through steam generator
    glBegin(GL_LINE_STRIP);
    glVertex2i(70,117);
    glVertex2i(115,117);
    glVertex2i(115,160);
    glVertex2i(135,160);
    glVertex2i(135,48);
    glVertex2i(92,48);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2i(92,44);
    glVertex2i(139,44);
    glVertex2i(139,164);
    glVertex2i(111,164);
    glVertex2i(111,121);
    glVertex2i(70,121);
    glEnd();

    glColor3f(0.6,0.3,0.2);		//Pump(Between reactor vessel and steam generator		
    glBegin(GL_POLYGON);
    for(angle=0; angle<=360; angle=angle+5)
    {
        angle_radians = angle * (float)3.14159 / (float)180;
        x = 86 + r4* (float)cos(angle_radians);
        y = 46 + r4* (float)sin(angle_radians);

        glVertex2f(x,y);
    }
    glEnd();

    glLineWidth(3.0);		//Steam line pipe
    glColor3f(0.6,0.3,0.2);
    glBegin(GL_LINES);
    glVertex2i(240,170);
    glVertex2f(240,178);
    glVertex2f(240,180);
    glVertex2i(240,206);
    glVertex2i(240,206);
    glVertex2i(124,206);
    glVertex2i(124,206);
    glVertex2f(124,198);
    glVertex2f(124,196);
    glVertex2i(124,185);
    glEnd();

    glBegin(GL_LINES);
    glVertex2i(120,185);
    glVertex2i(120,195);
    glVertex2i(120,197);
    glVertex2i(120,210);
    glVertex2i(120,210);
    glVertex2i(244,210);
    glVertex2i(244,210);
    glVertex2i(244,182);
    glVertex2i(244,180);
    glVertex2i(244,170);
    glEnd();

    glBegin(GL_LINES);		//Condensor pipes
    glVertex2i(350,85);
    glVertex2f(331,85);
    glVertex2f(329,85);
    glVertex2i(244,85);
    glVertex2i(244,85);
    glVertex2i(244,65);
    glVertex2i(244,65);
    glVertex2i(329,65);
    glVertex2i(331,65);
    glVertex2i(350,65);
    glEnd();

    glBegin(GL_LINES);
    glVertex2i(350,89);
    glVertex2i(331,89);
    glVertex2i(329,89);
    glVertex2i(240,89);
    glVertex2i(240,89);
    glVertex2i(240,61);
    glVertex2i(240,61);
    glVertex2i(329,61);
    glVertex2i(331,61);
    glVertex2i(350,61);
    glEnd();

    glBegin(GL_LINE_LOOP);		//condensor outline
    glVertex2i(350,95);
    glVertex2i(350,55);
    glVertex2i(375,55);
    glVertex2i(375,95);
    glEnd();

    glColor3f(0.0,0.6,0.8);		//condensor water
    glBegin(GL_POLYGON);
    glVertex2i(351,94);
    glVertex2i(351,56);
    glVertex2i(374,56);
    glVertex2i(374,94);
    glEnd();
    

    glColor3f(0.6,0.6,0.4);		//Control Rods
    glBegin(GL_LINES);
    glVertex2i(45,120);
    glVertex2i(45,180);
    glVertex2i(50,120);
    glVertex2i(50,180);
    glVertex2i(55,120);
    glVertex2i(55,180);
    glEnd();

    glColor3f(1.0,1.0,1.0);
    setFont(GLUT_BITMAP_HELVETICA_18);
    drawstring(42.0,98.0,0.0,"Core");

    turbine();
    generator();
    connecting_pipe();

    glColor3f(0.6,0.3,0.2);	//Pump(Between generator and steam generator)
    glBegin(GL_POLYGON);
    for(angle=0; angle<=360; angle=angle+5)
    {
        angle_radians = angle * (float)3.14159 / (float)180;
        x = 186 + r5* (float)cos(angle_radians);
        y = 106 + r5* (float)sin(angle_radians);
        glLineWidth(6.0);
        glVertex2f(x,y);
    }
    glEnd();

    glColor3f(1.0,1.0,1.0);
    setFont(GLUT_BITMAP_HELVETICA_18);
    drawstring(60.0,250.0,0.0,"Constraint Structure");

    glColor3f(1.0,1.0,1.0);
    setFont(GLUT_BITMAP_HELVETICA_18);
    drawstring(54.0,160.0,0.0,"Control Rods");

    glColor3f(1.0,1.0,1.0);
    setFont(GLUT_BITMAP_HELVETICA_18);
    drawstring(30.0,60.0,0.0,"Reactor Vessel");

    glColor3f(1.0,1.0,1.0);
    setFont(GLUT_BITMAP_HELVETICA_18);
    drawstring(250.0,105.0,0.0,"Turbine");

    glColor3f(1.0,1.0,1.0);
    setFont(GLUT_BITMAP_HELVETICA_18);
    drawstring(180.0,120.0,0.0,"Pump");

    glColor3f(1.0,1.0,1.0);
    setFont(GLUT_BITMAP_HELVETICA_18);
    drawstring(180.0,215.0,0.0,"Steam Line");

    glColor3f(1.0,1.0,1.0);
    setFont(GLUT_BITMAP_HELVETICA_18);
    drawstring(102.0,170.0,0.0,"Steam Generator");

    glColor3f(1.0,1.0,1.0);
    setFont(GLUT_BITMAP_HELVETICA_18);
    drawstring(80.0,55.0,0.0,"Pump");

    glColor3f(1.0,1.0,1.0);
    setFont(GLUT_BITMAP_HELVETICA_18);
    drawstring(290.0,150.0,0.0,"Generator");

    glColor3f(1.0,1.0,1.0);
    setFont(GLUT_BITMAP_HELVETICA_18);
    drawstring(248.0,70.0,0.0,"Condensor Cooling Water");

    glBegin(GL_POLYGON);	//Water inside generator compartment
    glColor3f(0.0,0.6,0.8);
    glVertex2f(221,31);
    glVertex2f(329,31);
    glColor3f(0.0,0.0,1.0);
    glVertex2f(329,57);
    glVertex2f(221,57);
    glEnd();

    glFlush();

    glFlush();
}

void structure(void) {
    glutIdleFunc(NULL);			//Disable the rotation of the turbine fan
    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glColor3f(1.0,1.0,1.0);
    setFont(GLUT_BITMAP_HELVETICA_18);
    drawstring(180.0,120.0,0.0,"Pump");

    glColor3f(1.0,1.0,1.0);
    setFont(GLUT_BITMAP_HELVETICA_18);
    drawstring(180.0,215.0,0.0,"Steam Line");

    glColor3f(1.0,1.0,1.0);
    setFont(GLUT_BITMAP_HELVETICA_18);
    drawstring(60.0,20.0,0.0,"Constraint Structure");

    glColor3f(1.0,1.0,1.0);
    setFont(GLUT_BITMAP_HELVETICA_18);
    drawstring(260.0,20.0,0.0,"Generator");

    glColor3f(1.0,1.0,1.0);
    setFont(GLUT_BITMAP_HELVETICA_18);
    drawstring(340.0,40.0,0.0,"Condensor Water");

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    GLfloat mat_ambient[] = {0.0f,1.0f,1.0f,1.0f};
    GLfloat mat_diffuse[] = {1.0f,0.5f,1.0f,1.0f};
    GLfloat mat_specular[] = {0.5f,0.5f,1.0f,1.0f};
    GLfloat mat_shininess[] = {25.0f};
	
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_ambient);	 	 
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mat_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,mat_shininess);
	
    GLfloat lightIntensity[] = {1.0f,1.0f,1.0f,1.0f};
    GLfloat light_position[] = {25.0f,50.0f,50.0f,1.0f};
    glLightfv(GL_LIGHT0,GL_POSITION,light_position);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,lightIntensity);

    glLineWidth(3.0);

    glBegin(GL_LINES);		//Condensor pipes
    glVertex2i(350,85);
    glVertex2f(331,85);
    glVertex2f(329,85);
    glVertex2i(244,85);
    glVertex2i(244,85);
    glVertex2i(244,65);
    glVertex2i(244,65);
    glVertex2i(329,65);
    glVertex2i(331,65);
    glVertex2i(350,65);
    glEnd();

    glBegin(GL_LINES);
    glVertex2i(350,89);
    glVertex2i(331,89);
    glVertex2i(329,89);
    glVertex2i(240,89);
    glVertex2i(240,89);
    glVertex2i(240,61);
    glVertex2i(240,61);
    glVertex2i(329,61);
    glVertex2i(331,61);
    glVertex2i(350,61);
    glEnd();

    glBegin(GL_LINE_LOOP);		//condensor outline
    glVertex2i(350,95);
    glVertex2i(350,55);
    glVertex2i(375,55);
    glVertex2i(375,95);
    glEnd();

    glColor3f(0.0,0.6,0.8);		//condensor water
    glBegin(GL_POLYGON);
    glVertex2i(351,94);
    glVertex2i(351,56);
    glVertex2i(374,56);
    glVertex2i(374,94);
    glEnd();

    glLineWidth(3.0);
    glColor3f(0.6,0.3,0.2);
    glBegin(GL_LINES);
    glVertex2i(150,104);
    glVertex2i(180,104);
    glVertex2i(150,108);
    glVertex2i(180,108);
    glEnd();

    glBegin(GL_LINES);
    glVertex2i(185,100);
    glVertex2i(185,50);
    glVertex2i(185,50);
    glVertex2i(224,50);
    glVertex2i(189,100);
    glVertex2i(189,54);
    glVertex2i(189,54);
    glVertex2i(224,54);
    glEnd();
    
    glLineWidth(3.0);		//Steam line pipe
    glColor3f(0.6,0.3,0.2);
    glBegin(GL_LINES);
    glVertex2i(240,170);
    glVertex2f(240,178);
    glVertex2f(240,180);
    glVertex2i(240,206);
    glVertex2i(240,206);
    glVertex2i(124,206);
    glVertex2i(124,206);
    glVertex2f(124,198);
    glVertex2f(124,196);
    glVertex2i(124,185);
    glEnd();

    glBegin(GL_LINES);
    glVertex2i(120,185);
    glVertex2i(120,195);
    glVertex2i(120,197);
    glVertex2i(120,210);
    glVertex2i(120,210);
    glVertex2i(244,210);
    glVertex2i(244,210);
    glVertex2i(244,182);
    glVertex2i(244,180);
    glVertex2i(244,170);
    glEnd();

    glColor3f(0.6,0.3,0.2);	//Pump(Between generator and steam generator)
    glBegin(GL_POLYGON);
    for(angle=0; angle<=360; angle=angle+5)
    {
        angle_radians = angle * (float)3.14159 / (float)180;
        x = 186 + r5* (float)cos(angle_radians);
        y = 106 + r5* (float)sin(angle_radians);
        glLineWidth(6.0);
        glVertex2f(x,y);
    }
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.4,0.4,0.4);		//Constraint structure
    glVertex2i(10,200);
    glVertex2i(10,30);
    glVertex2i(170,30);
    glVertex2i(170,200);
    glEnd();

    glColor3f(0.4,0.4,0.4);		//Curved part of the constraint structure
    glBegin(GL_POLYGON);
    for(int angle=0; angle<=180; angle=angle+5)
    {
        float angle_radians = angle * (float)3.14159 / (float)180;
        float x = 90 + r1* (float)cos(angle_radians);
        float y = 200 + r1* (float)sin(angle_radians);
        glLineWidth(6.0);
        glVertex2f(x,y);
    }
    glEnd();

    glBegin(GL_POLYGON);		//Case enclosing the generator
    glColor3f(0.752941,0.752941,0.752941);
    glVertex2i(220,170);
    glVertex2i(220,30);
    glVertex2i(330,30);
    glVertex2i(330,220);
    glEnd();

    glBegin(GL_POLYGON);		//Enclosing case of the power station
    glColor3f(0.6,0.6,0.6);
    glVertex2f(331,170);
    glVertex2f(385,170);
    glVertex2f(385,111);
    glVertex2f(331,111);
    glEnd();

    glFlush();
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_NORMALIZE);

}

void display_about(void)		//Displaying the first page
{
    glutIdleFunc(NULL);			//Disable the rotation of the turbine fan

    glClearColor(0.0,0.0,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    setFont(GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(0.0,1.0,1.0);
    drawstring(165.0,275.0,0.0,"CG MINI PROJECT ON");

    setFont(GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(0.0,1.0,1.0);
    drawstring(130,260,0.0,"WORKING OF NUCLEAR POWER PLANT");

    setFont(GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(0.0,1.0,1.0);
    drawstring(200,200,0,"BY:");

    setFont(GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(0.0,1.0,1.0);
    drawstring(130,185,0,"MELWIN LOBO");

    setFont(GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(0.0,1.0,1.0);
    drawstring(230,185,0,"4SF16CS091");

    setFont(GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(0.0,1.0,1.0);
    drawstring(230,170,0,"4SF16CS148");

    setFont(GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(0.0,1.0,1.0);
    drawstring(130,170,0,"SHREYAS BALIGA");

    setFont(GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(0.0,1.0,1.0);
    drawstring(95,120,0,"SAHYADRI COLLEGE OF ENGINEERING AND MANAGEMENT");

    setFont(GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(0.0,1.0,1.0);
    drawstring(175,80,0,"PROJECT GUIDE:");

    setFont(GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(0.0,1.0,1.0);
    drawstring(160,65,0,"Ms. CHAITRA ACHARYA");

    setFont(GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(0.0,1.0,1.0);
    drawstring(170,50,0,"ASST. PROFESSOR");

    setFont(GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(1.0,1.0,1.0);
    drawstring(300,15,0.0,"Right Click for Menu");

    glFlush();
}

void reactions(void)
{
    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPointSize(10.0);
    glFlush();

    glBegin(GL_POLYGON);		//Neutron1
    for(angle=0; angle<=360; angle=angle+5)
    {
        angle_radians = angle * (float)3.14159 / (float)180;
        x = 200 + r8* (float)cos(angle_radians);
        y = 270 + r8* (float)sin(angle_radians);
        glColor3f(0.8,0.3,0.2);
        glVertex2f(x,y);
    }
    glEnd();

    glBegin(GL_POLYGON);		//Neutron2
    for(angle=0; angle<=360; angle=angle+5)
    {
        angle_radians = angle * (float)3.14159 / (float)180;
        x = 200 + r8* (float)cos(angle_radians);
        y = 92 + r8* (float)sin(angle_radians);
        glColor3f(0.8,0.3,0.2);
        glVertex2f(x,y);
    }
    glEnd();

    glBegin(GL_POLYGON);		//Neutron3
    for(angle=0; angle<=360; angle=angle+5)
    {
        angle_radians = angle * (float)3.14159 / (float)180;
        x = 178 + r8* (float)cos(angle_radians);
        y = 114 + r8* (float)sin(angle_radians);
        glColor3f(0.8,0.3,0.2);
        glVertex2f(x,y);
    }
    glEnd();

    glBegin(GL_POLYGON);		//Neutron4
    for(angle=0; angle<=360; angle=angle+5)
    {
        angle_radians = angle * (float)3.14159 / (float)180;
        x = 222  + r8* (float)cos(angle_radians);
        y = 114 + r8* (float)sin(angle_radians);
        glColor3f(0.8,0.3,0.2);
        glVertex2f(x,y);
    }
    glEnd();

    glColor3f(0.0,1.0,0.6);		//Line between neutron and U235 with arrow head
    glLineWidth(6.0);
    glBegin(GL_LINES);
    glVertex2f(200.0,267.0);
    glVertex2f(200.0,201.0);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(198.0,204.0);
    glVertex2f(200.0,198.0);
    glVertex2f(202.0,204.0);
    glEnd();

    glBegin(GL_LINES);			//Line between U235 and light nucleus with arrow head
    glVertex2f(91.0,180.0);
    glVertex2f(182.0,180.0);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(94.0,183.0);
    glVertex2f(91.0,180.0);
    glVertex2f(94.0,177.0);
    glEnd();

    glBegin(GL_LINES);			//Line between U235 and heavy nucleus with arrow head
    glVertex2f(218.0,180.0);
    glVertex2f(306.0,180.0);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(302.0,183.0);
    glVertex2f(306.0,180.0);
    glVertex2f(302.0,177.0);
    glEnd();

    glBegin(GL_LINES);			//Line between U235 and neutros with arrow heads
    glVertex2f(200.0,162.0);
    glVertex2f(200.0,97.0);
    glVertex2f(200.0,162.0);
    glVertex2f(220.0,117.0);
    glVertex2f(200.0,162.0);
    glVertex2f(180.0,117.0);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(197.0,101.0);
    glVertex2f(200.0,96.0);
    glVertex2f(203.0,101.0);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(177.0,119.0);
    glVertex2f(180.0,117.0);
    glVertex2f(183.0,117.0);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(217.0,117.0);
    glVertex2f(220.0,117.0);
    glVertex2f(223.0,119.0);
    glEnd();

    glBegin(GL_POLYGON);		//U235
    for(angle=0; angle<=360; angle=angle+5)
    {
        angle_radians = angle * (float)3.14159 / (float)180;
        x = 200 + r10* (float)cos(angle_radians);
        y = 180 + r10* (float)sin(angle_radians);
        glColor3f(0.6,0.1,0.9);
        glVertex2f(x,y);
    }
    glEnd();

    glBegin(GL_POLYGON);		//Heavy nucleus
    for(angle=0; angle<=360; angle=angle+5)
    {
        angle_radians = angle * (float)3.14159 / (float)180;
        x = 320 + r13* (float)cos(angle_radians);
        y = 180 + r13* (float)sin(angle_radians);
        glColor4f(1.0,0.0,0.0,0.6);
        glVertex2f(x,y);
    }
    glEnd();

    glBegin(GL_POLYGON);		//Light Nucleus
    for(angle=0; angle<=360; angle=angle+5)
    {
        angle_radians = angle * (float)3.14159 / (float)180;
        x = 80 + r11* (float)cos(angle_radians);
        y = 180 + r11* (float)sin(angle_radians);
        glColor4f(0.0,1.0,0.0,0.5);
        glVertex2f(x,y);
    }
    glEnd();

    setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(1.0,1.0,1.0);
    drawstring(210,160,0.0,"U235");

    setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(1.0,1.0,1.0);
    drawstring(190,290,0.0,"Neutron");

    setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(1.0,1.0,1.0);
    drawstring(190,280,0.0,"(thermal)");

    setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(1.0,1.0,1.0);
    drawstring(70,155,0.0,"Fission Product");

    setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(1.0,1.0,1.0);
    drawstring(70,145,0.0,"Light Nucleus");

    setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(1.0,1.0,1.0);
    drawstring(306,155,0.0,"Fission Product");

    setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(1.0,1.0,1.0);
    drawstring(306,145,0.0,"Heavy Nucleus");

    setFont(GLUT_BITMAP_HELVETICA_18);
    glColor3f(1.0,1.0,1.0);
    drawstring(165,80,0.0,"About 3 neutrons per fission");

    glColor3f(1.0,1.0,1.0);
    glPointSize(10.0);
    glBegin(GL_POINTS);
    glVertex2f(10,52);
    glEnd();

    setFont(GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(1.0,1.0,1.0);
    drawstring(20,50,0.0,"Neutrons produced can initiate further fission of U235, making the reaction to be self sustainable");

    setFont(GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(1.0,1.0,1.0);
    drawstring(20,40,0,"chain reaction");

    setFont(GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(0.0,1.0,1.0);
    drawstring(150,20,0,"NUCLEAR FISSION REACTION");

    glFlush();
}

void display_operations(void)
{
    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    setFont(GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(1.0,0.0,1.0);
    drawstring(150.0,275.0,0.0,"About Nuclear Power Plant");

    setFont(GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POLYGON);
    glVertex2i(80,230);
    glVertex2i(82,230);
    glVertex2i(82,232);
    glVertex2i(80,232);
    glEnd();
    glColor3f(1.0,0.0,1.0);
    drawstring(90.0,230.0,0.0,"Nuclear powerplant is a power generating unit in which nuclear energy\n");
    glColor3f(1.0,0.0,1.0);
    drawstring(90.0,220.0,0.0,"is converted to electrical energy.");

    setFont(GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POLYGON);
    glVertex2i(80,200);
    glVertex2i(82,200);
    glVertex2i(82,202);
    glVertex2i(80,202);
    glEnd();
    setFont(GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(1.0,0.0,1.0);
    drawstring(90.0,200.0,0.0,"Turbo Generator made to rotate from heat generated by nuclear fission ");
    glColor3f(1.0,0.0,1.0);
    drawstring(90,190,0.0,"reactions of radio active elements such as Uranium-235,plutonium");

    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POLYGON);
    glVertex2i(80,170);
    glVertex2i(82,170);
    glVertex2i(82,172);
    glVertex2i(80,172);
    glEnd();
    setFont(GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(1.0,0.0,1.0);
    drawstring(90,170,0.0,"Radioactive elements splits when bombarded by neutron.Reactions become");
    glColor3f(1.0,0.0,1.0);
    drawstring(90,160,0.0,"self sustaining chain reaction under controlled conditions.");

    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POLYGON);
    glVertex2i(80,140);
    glVertex2i(82,140);
    glVertex2i(82,142);
    glVertex2i(80,142);
    glEnd();
    setFont(GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(1.0,0.0,1.0);
    drawstring(90,140,0.0,"Heat Energy generated is transfered to ordinary water and carried away");
    glColor3f(1.0,0.0,1.0);
    drawstring(90,130,0.0,"from reactor as steam.");

    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POLYGON);
    glVertex2i(80,110);
    glVertex2i(82,110);
    glVertex2i(82,112);
    glVertex2i(80,112);
    glEnd();
    setFont(GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(1.0,0.0,1.0);
    drawstring(90,110,0.0,"Steem feeds the Turbo Generator thus making it to rotate and");
    glColor3f(1.0,0.0,1.0);
    drawstring(90,100,0.0,"power is generated.");

    delay(1000);
    glFlush();
}

void options(int id)					//Menu
{
    switch(id)
    {
	    case 1:
		display_about();			//Intro page
		break;
	    case 2:
		display_nuclear_power_plant();		//Internal structure
		break;
	    case 3:
		display_operations();			//About nuclear power plant
		break;
	    case 4:
		reactions();				//Info about the reactions in nuclear power plant
		break;
	    case 5:
                display_nuclear_power_plant();		
		delay(1000);
    		reactorPoints();				//Points inside reactor vessel(At the beginning of working of the plant)
    		delay(1000);	
    		working();				//Working of the plant
    		glFlush();	
                break;
	    case 6:
		exit(0);
    }
}

void keyInput(unsigned char key, int x, int y){
	
	if (key == 'c')			//Displays the closed structure when 'c' is pressed
	{
		structure();
	}
	if (key == 's')			//Displays the internal structure when 's' is pressed
	{
		display_nuclear_power_plant();
		
	}
}

void disp(void)
{
    display_about();		//Displays the intro page in the beginning
    glFlush();
}

void init(void)
{
    gluOrtho2D(0.0,400.0,0.0,300.0);
}

int main(int argc,char** argv)
{
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
    glutInit(&argc,argv);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(1366,768);
    glutCreateWindow("Nuclear Power Plant");

    init();

    glutKeyboardFunc(keyInput);

    int submenu_2 = glutCreateMenu(options);
    glutAddMenuEntry("About nuclear power plant",3);
    glutAddMenuEntry("Internal reactions",4);

    glutCreateMenu(options);
    glutAddMenuEntry("Title of the Project",1);
    glutAddMenuEntry("Internal Structure",2);
    glutAddMenuEntry("Working",5);
    glutAddSubMenu("Info",submenu_2);
    glutAddMenuEntry("Quit",6);
    
    glutAttachMenu(GLUT_LEFT_BUTTON | GLUT_RIGHT_BUTTON);
    glutDisplayFunc(disp);
    glutMainLoop();
}

