#include "App.h"
#include<stdlib.h>//provides random function
#include <deque>
using namespace std;
static deque<Grid> gBoard;
static deque<Rect> rects;
static deque<Figure> fig(9);

int counter;
bool AI = false;

//Board Grid
Grid myTopGrid(-1.0,1.0,2,0.03);
Grid myLeftGrid(-1.0,1.0,0.03,2);
Grid myBottomGrid(-1.0,-0.97,2,0.03);
Grid myRightGrid(0.97,1,0.03,2);
Grid myTopHorizontalGrid(-1,0.333,2,0.03);
Grid myBottomHorizontalGrid(-1,-0.333,2,0.03);
Grid myRightVerticalGrid(0.333,1,0.03,2);
Grid myLeftVerticalGrid(-0.333,1,0.03,2);

//BOXES WITH CLICKABLE AREAS
Rect TopLeft(-0.97,0.97,0.637,0.637);
Rect TopMiddle(-0.303,0.97,0.637,0.637);
Rect TopRight(0.363,0.97,0.607,0.637);
Rect MiddleLeft(-0.97,0.303,0.637,0.637);
Rect MiddleMid(-0.303,0.303,0.637,0.637);
Rect MiddleRight(0.363,0.303, 0.607, 0.637);
Rect LowerLeft(-0.97,-0.363,0.637,0.607);
Rect LowerMiddle(-0.303,-0.363,0.637,0.607);
Rect LowerRight(0.363,-0.363,0.607,0.607);

App::App(const char* label, int x, int y, int w, int h): GlutApp(label, x, y, w, h){
    // Initialize state variables
    mx = 0.0;
    my = 0.0;
    counter = 0;

    rects.push_back(TopLeft);//squares are pushed in order from left to right 0-8 to keep track of location
    rects.push_back(TopMiddle);
    rects.push_back(TopRight);
    rects.push_back(MiddleLeft);
    rects.push_back(MiddleMid);
    rects.push_back(MiddleRight);
    rects.push_back(LowerLeft);
    rects.push_back(LowerMiddle);
    rects.push_back(LowerRight);

}

int AIgo()
{
    return rand()%9;//picks cell
}

void resetGame()
{
    for(int i=0;i<fig.size();i++)
    {
        rects.at(i).setCor(false);
        rects.at(i).setU(false);
        rects.at(i).setUF(0);
        fig.at(i).setOcc(false);
        fig.at(i).setUF(false);
        fig.at(i).setPlot(0,0);
        counter = 0;
    }
}

int checkWin()
{
    //Horizontal Win
    if(rects.at(0).getUF()!=0 && rects.at(0).getUF()==rects.at(1).getUF() && rects.at(0).getUF()==rects.at(2).getUF())
    {
        return rects.at(0).getUF();
    }
    else if(rects.at(3).getUF()!=0 && rects.at(3).getUF()==rects.at(4).getUF() && rects.at(3).getUF()==rects.at(5).getUF())
    {
        return rects.at(3).getUF();
    }
    else if(rects.at(6).getUF()!=0 && rects.at(6).getUF()==rects.at(7).getUF() && rects.at(6).getUF()==rects.at(8).getUF())
    {
        return rects.at(6).getUF();
    }
    //Vertical Win
    else if(rects.at(0).getUF()!=0 && rects.at(0).getUF()==rects.at(3).getUF() && rects.at(0).getUF()==rects.at(6).getUF())
    {
        return rects.at(0).getUF();
    }
    else if(rects.at(1).getUF()!=0 && rects.at(1).getUF()==rects.at(4).getUF() && rects.at(1).getUF()==rects.at(7).getUF())
    {
        return rects.at(1).getUF();
    }
    else if(rects.at(2).getUF()!=0 && rects.at(2).getUF()==rects.at(5).getUF() && rects.at(2).getUF()==rects.at(8).getUF())
    {
        return rects.at(2).getUF();
    }
    //Diagonal Win
    else if(rects.at(0).getUF()!=0 && rects.at(0).getUF()==rects.at(4).getUF() && rects.at(0).getUF()==rects.at(8).getUF())
    {
        return rects.at(0).getUF();
    }
    else if(rects.at(6).getUF()!=0 && rects.at(6).getUF()==rects.at(4).getUF() && rects.at(6).getUF()==rects.at(2).getUF())
    {
        return rects.at(6).getUF();
    }
    else{return 0;}
}

void App::draw() {

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Set background color to black
    glClearColor(0.1, 0.0, 0.0, 1.0);
    
    // Set up the transformations stack
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); 

    for(int i=0;i<fig.size();i++)
    {
        fig.at(i).draw();
    }

    int outcome = checkWin();
    if(outcome==1){cout<<"Player 1 has won!"<<endl;cout<<"Press 'tab' to switch modes."<<endl;}
    else if(outcome==2){cout<<"Player 2 has won!"<<endl;cout<<"Press 'tab' to switch modes."<<endl;}
    else if(outcome!=(1||2))
    {
        cout << "Draw" << endl;
        cout << "Press 'tab' to switch modes" << endl;
    }
     
    //Draws the Board
    drawBoard();

    //Drawboxes
    TopLeft.draw();
    TopMiddle.draw();
    TopRight.draw();
    MiddleLeft.draw();
    MiddleMid.draw();
    MiddleRight.draw();
    LowerLeft.draw();
    LowerMiddle.draw();
    LowerRight.draw();

    myTopGrid.draw();
    myLeftGrid.draw(); 
    myBottomGrid.draw();
    myRightGrid.draw();
    myTopHorizontalGrid.draw();
    myBottomHorizontalGrid.draw();
    myLeftVerticalGrid.draw();
    myRightVerticalGrid.draw();


    // We have been drawing everything to the back buffer
    // Swap the buffers to see the result of what we drew
    glFlush();
    glutSwapBuffers();
}



void App::drawBoard()
{
    glLineWidth(5.0);
    glColor3f(1.0,1.0,0.0);
    glBegin(GL_LINES); 
        glVertex2f(-0.9,0.33);
        glVertex2f(0.9,0.33);
    glEnd();

    glBegin(GL_LINES);
        glVertex2f(-0.9,-0.33);
        glVertex2f(0.9,-0.33);
    glEnd();

    glBegin(GL_LINES); 
        glVertex2f(-0.33,0.9);
        glVertex2f(-0.33,-0.9);
    glEnd();

    glBegin(GL_LINES); 
        glVertex2f(0.33,0.9);
        glVertex2f(0.33,-0.9);
    glEnd();
}

void App::mouseDown(float x, float y){
    // Update app state
    mx = x;
    my = y;

    for(int i=0;i<rects.size();i++)
    {
        rects.at(i).contains(mx,my);
        if(AI==true && counter%2==1)
        {
            for(int j=0;counter%2==1;j++)
            {
                int go = AIgo();
                if(rects.at(go).getU()==false && counter%2==1)
                {
                    rects.at(go).setCor(true);
                    i=go;

                    break;
                }
            }
        }
        if(rects.at(i).getCor()==true && rects.at(i).getU()==false)
        {
            for(int k=0;k<fig.size();k++)
            {
                if(fig.at(k).isOccupied()==false)
                {
                    fig.at(k).setPlot(rects.at(i).getX(),rects.at(i).getY());
                    if(counter%2==0)
                    {
                        fig.at(k).setUF(1);
                        rects.at(i).setUF(1);
                        if(AI==true){cout<<"Click for AI turn!"<<endl;}
                    }
                    else{
                        fig.at(k).setUF(2);
                        rects.at(i).setUF(2);
                    }
                    rects.at(i).setU(true);
                    counter++;

                    break;
                }
            }
        break;
        }
    }
    
    // Redraw the scene
    redraw();
}

void App::mouseDrag(float x, float y){
    // Update app state
    mx = x;
    my = y;
    
    // Redraw the scene
    redraw();
}

void App::keyPress(unsigned char key) {
    if (key == 27){
        // Exit the app when Esc key is pressed
        exit(0);
    }
    if(key == 9){
        if(AI==false)
        {
            AI=true;
            cout<<"Playing AI!"<<endl;
            resetGame();
        }
        else if(AI==true)
        {
            AI=false;
            cout<<"Playing 2 player!"<<endl;
            resetGame();
        }
    }
    redraw();
}
