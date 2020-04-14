#include "cube.h"
#include "display.h"

//define some colour values
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF


#define NUM_OF_INDICES 12

// Feel free to change these rotation speeds
float rotationXspeed = 0.09;
float rotationYspeed = 0.16;
float rotationZspeed = 0.3;

float cubeX = 0;
float cubeY = 0;
float cubeZ = 2;

int cubeOffset_x = CONFIG_WIDTH / 2;
int cubeOffset_y = CONFIG_HEIGHT / 2;
float cubeSize = 100;
float cameraDistance = 2;
float rotationX = 0;
float rotationY = 0;
float rotationZ = 0;


float vertices[][3] = { {-1, -1, -1}, {1, -1, -1}, {1, 1, -1}, {-1, 1, -1},
                      {-1, -1, 1}, {1, -1, 1}, {1, 1, 1}, {-1, 1, 1} };

int indices[][2] = { {0, 1}, {1, 2}, {2, 3}, {3, 0}, {4, 5}, {5, 6}, {6, 7}, {7, 4}, {0, 4}, {1, 5}, {2, 6}, {3, 7} };

float result_num[2] = {0,0};

float* rotate(float x, float y, float angle)
{
  float s = sin(angle);
  float c = cos(angle);
  float* result = result_num;
  result[0] = x * c - y * s;
  result[1] = y * c + x * s;
  return result;
}
void draw_cube(void)
{
	while(1)
	{
		vTaskDelay(10);
		lcdFillScreen(&dev,WHITE);
		for (int n = 0; n < 2; n++)
		{
		    int lineColor = n ? BLACK : GREEN;
		    for (int i = 0; i < NUM_OF_INDICES; i++)
		    {
		      int* index = indices[i];
		      int a = index[0];
		      int b = index[1];
		  
		      float* vertex1 = vertices[a];
		      float* vertex2 = vertices[b];
		  
		      float x1, y1, z1, x2, y2, z2;
		      x1 = vertex1[0];
		      y1 = vertex1[1];        
		      z1 = vertex1[2];
		  
		      float* temp_Rotation = rotate(x1, z1, rotationY);
		      x1 = temp_Rotation[0];
		      z1 = temp_Rotation[1];
		      // delete temp_Rotation;
		  
		      temp_Rotation = rotate(y1, z1, rotationX);
		      y1 = temp_Rotation[0];
		      z1 = temp_Rotation[1];
		      // delete temp_Rotation;
		  
		      x1 = (float)(x1 * cubeSize);
		      y1 = (float)(y1 * cubeSize);
		      
		      x2 = (float)vertex2[0];
		      y2 = (float)vertex2[1];
		      z2 = (float)vertex2[2];
		  
		      temp_Rotation = rotate(x2, z2, rotationY);
		      x2 = temp_Rotation[0];
		      z2 = temp_Rotation[1];
		      // delete temp_Rotation;
		  
		      temp_Rotation = rotate(y2, z2, rotationX);
		      y2 = temp_Rotation[0];
		      z2 = temp_Rotation[1];
		      // delete temp_Rotation;    
		      
		      x2 = (float)(x2 * cubeSize);
		      y2 = (float)(y2 * cubeSize);            
		  
		      x1 += cubeX;
		      x2 += cubeX;
		      y1 += cubeY;
		      y2 += cubeY;
		      z1 += cubeZ;
		      z2 += cubeZ;
		  
		      x1 /= z1 * cameraDistance;
		      x2 /= z2 * cameraDistance;
		      y1 /= z1 * cameraDistance;
		      y2 /= z2 * cameraDistance;
		  
		      x1 += cubeOffset_x;
		      x2 += cubeOffset_x;
		      y1 += cubeOffset_y;
		      y2 += cubeOffset_y;
		              
		      lcdDrawLine(&dev, x1, y1, x2, y2, lineColor);
		    }
		}
		rotationX += rotationXspeed;
		rotationY += rotationYspeed;
		rotationZ += rotationZspeed;
	}


}