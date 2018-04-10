#ifndef App_hpp
#define App_hpp
#include "GlutApp.h"
#include<cmath>
//#include <deque>

class App: public GlutApp {
    // Maintain app state here
    float mx;
    float my;

public:
    // Constructor, to initialize state
    App(const char* label, int x, int y, int w, int h);
    
    // These are the events we want to handle
    void draw();
    void drawBoard();
    void keyPress(unsigned char key);
    void mouseDown(float x, float y);
    void mouseDrag(float x, float y);
};

struct Rect
{
    public:
        float x, y, width, height;
        //bool selected;
        bool AA, BB;
        int CC;

    public:
    
        Rect(){
            x=0.0;
            y=0.0;
            width=0.0;
            height=0.0;
            AA = false;
            BB = false;
            //selected = false;
            CC = 0;
        }
        
        Rect(float xx, float yy, float w, float h){
            x=xx;
            y=yy;
            width=w;
            height=h;
        }

        float getX()const{return x;}
        float getY()const{return y;}
        float getW()const{return width;}
        float getH()const{return height;}
        int getUF()const{return CC;}
        bool getCor()const{return AA;}
        bool getU(){return BB;}

        void setX(float xx){x=xx;}
        void setY(float yy){y=yy;}
        void setUF(int uFig){CC=uFig;}
        void setCor(bool coorde){AA=coorde;}
        void setU(bool Justin){BB=Justin;}
        
        //void select(){selected=true;}
        //void deselect(){selected=false;}
        //bool is_selected(){return selected;}

        bool contains(float x, float y){
            if(x >= this->x && this->x + this->width >= x)
            {
                if(y <= this->y && y >= this->y - this->height)
                {
                    AA=true;
                }
            }
        }

        void draw()
        {
            glColor3f(1.0,0.0,1.0);
            
            glBegin(GL_POINTS);
                glVertex2f(getX(),getY());
                glVertex2f(getX() + getW(),getY());
                glVertex2f(getX() + getW(),getY() - getH());
                glVertex2f(getX(),getY() - getH());
            glEnd();    
        }

};

class Grid
{
public:
    float x, y, width, height;
    public:

    Grid(){
        x = 0.0;
        y = 0.0;
        width = 0.0;
        height = 0.0;
    }

    Grid(float xx, float yy, float w, float h){
        x=xx;
        y=yy;
        width=w;
        height=h;
    }
    
    float getY()const{return y;}
    float getX()const{return x;}
    float getW()const{return width;}
    float getH()const{return height;}

    void draw(){ //draws grid outline
        
        glColor3d(1.0, 0.5, 0.0);
        glBegin(GL_POLYGON);
            glVertex2f(getX(), getY());
            glVertex2f(getX() + getW(), getY());
            glVertex2f(getX() + getW(), getY() - getH());
            glVertex2f(getX(), getY() - getH());    
        glEnd();
    }
};

class Figure
{
    float x, y, rad;
    int res, CC;
    bool occ;

    public:

        Figure(){
            x = 0.0;
            y = 0.0;
            occ = false;
        }

        Figure(float xx, float yy){
            x=xx;
            y=yy;
        }

        void setPlot(float xx, float yy){
            x=xx;
            y=yy;
            res = 300;
            rad = .20;
            CC = 0;
            if(xx != 0 && yy != 0)
            {
                occ = true;
            }
        }

        float getX()const{return x;}
        float getY()const{return y;}
        float getRad()const{return rad;}
        float getCenX()const{
            if(x < -0.31){return (-0.66);}
            else if(x > 0.31){return (0.66);}
            else{return 0;}
        }
        float getCenY()const{
            if(y < -0.31){return (-0.66);}
            else if(y > 0.31){return (0.66);}
            else{return 0;}
        }
        int getUF()const{return CC;}
        bool isOccupied()const{return occ;}

        void setUF(int uFig){CC=uFig;}
        void setOcc(bool occu){occ=occu;}

        void draw()
        {
            if(CC == 1)
            {
                glColor3d(0.0,1.0,1.0);
                glPointSize(6.0);
                glBegin(GL_POINTS);
                for (int i= -res; i<res;i++)
                {
                    float ang = i*(360/res);
                    float deg = (ang*M_PI/180);
                    float circX = getCenX()+getRad()*cos(deg);
                    float circY = getCenY()+getRad()*sin(deg);

                    glVertex2f(circX,circY);

                }
                occ = true;
                glEnd();
            }
            else if(CC == 2)//FIX THE X
            {
                glColor3d(0.0,0.0,1.0);
                float yy=y-0.1;
                float xx=x+0.1;

                glLineWidth(9.0);
                glBegin(GL_LINES);
                    glVertex2f(xx,yy);   
                    glVertex2f(xx+0.40,yy-0.40);
                glEnd();

                glBegin(GL_LINES);
                    glVertex2f(xx,yy-0.40);  
                    glVertex2f(xx+0.40,yy);               
                glEnd();
            }
        }
};

#endif
