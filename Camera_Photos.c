#include "Camera_Photos.h"

// GLCD
#include "Board_GLCD.h"
#include "GLCD_Config.h"

// Touch
#include "Touch_Handler.h"

// SDCard
#include "SDCard_Module.h"

// Camera application
#include "Camera_Defines.h"
#include "Camera_Globals.h"
#include "Data_Types.h"
#include "Icons/Icon_Camera.c"
#include "Error_Message.h"


#define PHOTO_DIRECTORY "/Media/Images"
#define PHOTO_ICONDIRECTORY "/Media/Icons"

#define PHOTO_PREVIEWSIZE 48
#define PHOTO_PREVIEW_HEIGHT_PADDING 40
#define PHOTO_PREVIEW_WIDTH_PADDING 20

#define PHOTO_PREVIEW_MAX_COLUMN 10
#define PHOTO_PREVIEW_MAX_ROW 4

#define MAX_PHOTOFILENAME 12


extern GLCD_FONT     GLCD_Font_16x24;
extern int Camera_Global_DrawToScreen;

Entity Camera_PhotosEntities[1];
unsigned int num_PhotosEntities;

char* rowPreviewFiles[PHOTO_PREVIEW_MAX_COLUMN];

unsigned int Camera_Photos_Page;

void Camera_Photos_Initalise(void)
{
	Camera_PhotosEntities[0] = Entity_Make(
																				Point_2D_Make(
																											GLCD_CAMERA_WIDTH-Icon_Camera.width - GLCD_CAMERA_EDGE_PADDING, 
																											GLCD_CAMERA_HEIGHT-Icon_Camera.height - GLCD_CAMERA_EDGE_PADDING), 
																				&Icon_Camera);
	num_PhotosEntities = 1;
	
	// Reserve memory to store directories of row of image previews  
	int i;
	for(i = 0; i < PHOTO_PREVIEW_MAX_COLUMN; i++)
	{
		rowPreviewFiles[i] = malloc(MAX_PHOTOFILENAME);
		if(rowPreviewFiles[i] == NULL)
		{
			Error_DisplayMessage("Not enough memory");
		}
	}
}

enum CAMERA_STATE Camera_Photos_Run(void)
{
	
	if(Camera_Global_DrawToScreen)
	{
		Camera_Global_DrawToScreen = 0;
		
		// Draw the state string to the screen
		GLCD_SetForegroundColor(GLCD_COLOR_BLACK);
		GLCD_SetFont (&GLCD_Font_16x24);
		GLCD_DrawString(GLCD_CAMERA_EDGE_PADDING, GLCD_CAMERA_EDGE_PADDING, "Photos State");
		
		// Draw the photos icon to the screen
		GLCD_DrawBitmap( 
										Camera_PhotosEntities[0].position.x, 
										Camera_PhotosEntities[0].position.y, 
										Camera_PhotosEntities[0].image->width,
										Camera_PhotosEntities[0].image->height, 
										Camera_PhotosEntities[0].image->pixel_data);
		
		// Draw the preview photos
		if(!Camera_Photos_DrawPreviewPhotos(Camera_Photos_Page))
		{
			Error_DisplayMessage("Failed to draw previews");
		}
	}
	
	
	// Check if the photos icon has been pressed
	Point_2D point;
	if(Screen_Touched(&point))
	{
		if(Point_Entity_Collision(&point, Camera_PhotosEntities, num_PhotosEntities) != 0)
		{
			GLCD_ClearScreen();
			
			// Release the draw to screen flag, enabling items to be drawn again
			Camera_Global_DrawToScreen = 1;
			
			return CAMERA_VIEW;
		}
	}

	return CAMERA_PHOTOS;
}

int Camera_Photos_DrawPreviewPhotos(const unsigned int page)
{

	// Loop over all rows and columns
	int i, j;
	for(i = 0; i < PHOTO_PREVIEW_MAX_ROW; i++)
	{
		// Get the y coord for the row of image previews
		unsigned int y = 48 * i + PHOTO_PREVIEW_HEIGHT_PADDING;
			
		// Load image preview directories for this row
		unsigned int startIndex = PHOTO_PREVIEW_MAX_COLUMN*i;
		unsigned int numPreviewsInRow;
		numPreviewsInRow = SDCard_GetBMPFileName(PHOTO_ICONDIRECTORY, rowPreviewFiles, PHOTO_PREVIEW_MAX_COLUMN, MAX_PHOTOFILENAME, startIndex);
		
		// Loop over all elements in row
		for(j = 0; j < numPreviewsInRow; j++)
		{
			uint8_t str[30];
			uint32_t uwBmplen = 0;
			sprintf ((char*)str, "Media/Icons/%-11.11s", rowPreviewFiles[j]);
					
			// Load the bmp buffer into memory from SDCard
			unsigned char *buffer = (unsigned char*)0xC0260000;
			if(!SDCard_loadBMP(buffer, (const char*)str))
			{
				return 0;
			}
				
			// Get the x coord for the image in the row
			unsigned int x = 48 * j;
					
			// Draw the buffer to screen
			GLCD_DrawBitmap(x, 
											y, 
											PHOTO_PREVIEWSIZE, 
											PHOTO_PREVIEWSIZE, 
											buffer);
		}
	}

	return 1;
}
