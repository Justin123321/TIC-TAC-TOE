 #include <iostream>
#include "Vec.h"

using namespace std; 

class Rect
{
public:
	Vec v1, v2 ,v3 ,v4;
	float width, length;
	
	Rect()
	{
	}

	Rect(float x1,float y1, float width, float length)
	{
		v1.x = x1;
		v1.y = y1;
	
		v2.x = x1 + width;
		v2.y = y1;
	
		v3.x = x1;
		v3.y = y1 - length;
	
		v4.x = x1 + width;
		v4.y = y1 - length; 
	}
	
	bool contains(Vec a)
	{
		if ((this -> v1.x <= a.x && a.x <= this -> v2.x) && (this->v1.y >= a.y && this -> v3.y <= a.y))
		{
			return true;
		}
		else
		{
			return false; 
		}
	}
};

