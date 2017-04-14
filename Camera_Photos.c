#include "Camera_Photos.h"

// GLCD
#include "Board_GLCD.h"
#include "GLCD_Config.h"

// Touch
#include "Touch_Handler.h"

// SDCard
#include "SDCard_Module.h"

// JPEG
#include "Jpeg_Decode.h"

// BMP
#include "Bmp_Load.h"

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
extern unsigned char *buffer;

Entity Camera_PhotosEntities[1];
unsigned int num_PhotosEntities;

char* rowPreviewFiles[PHOTO_PREVIEW_MAX_COLUMN];
unsigned int Camera_Photos_Page;

enum CAMERA_PHOTOS_STATE Camera_Photos_State = CAMERA_PHOTOS_PREVIEWS;
int numPreviewsOnScreen = 0;
int imageTouched = 0;

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
	// To store position of screen touch.
	Point_2D point;
	
	// Check what to display.
	// If Camera_Photos_State is CAMERA_PHOTOS_PREVIEWS, we want to display the image previews on the screen.
	// If Camera_Photos_State is CAMERA_PHOTOS_PHOTO, we want to display a large image to screen.
	switch(Camera_Photos_State)
	{
		case CAMERA_PHOTOS_PREVIEWS:
			// Display the image previews.
			
			// Check if we can draw to screen.
			// This prevents us from drawing the same thing to the screen every frame.
			if(Camera_Global_DrawToScreen == CAMERA_GLOBAL_DRAWON)
			{
				// Lock the draw to screen flag.
				Camera_Global_DrawToScreen = CAMERA_GLOBAL_DRAWOFF;
				
				// Draw the state string to the screen.
				GLCD_SetForegroundColor(GLCD_COLOR_BLACK);
				GLCD_SetFont (&GLCD_Font_16x24);
				GLCD_DrawString(GLCD_CAMERA_EDGE_PADDING, GLCD_CAMERA_EDGE_PADDING, "Photos State");
				
				// Draw the photos icon to the screen.
				GLCD_DrawBitmap( 
												Camera_PhotosEntities[0].position.x, 
												Camera_PhotosEntities[0].position.y, 
												Camera_PhotosEntities[0].image->width,
												Camera_PhotosEntities[0].image->height, 
												Camera_PhotosEntities[0].image->pixel_data);
				
				// Draw the preview photos.
				if(!Camera_Photos_DrawPreviewPhotos(Camera_Photos_Page))
				{
					Error_DisplayMessage("Failed to draw previews");
				}
			}
		
		
			// Check if screen is touched.
			if(Screen_Touched(&point))
			{
				// Check if entity is touched
				if(Point_Entity_Collision(&point, Camera_PhotosEntities, num_PhotosEntities) != 0)
				{
					GLCD_ClearScreen();
					
					// Release the draw to screen flag, enabling items to be drawn again.
					Camera_Global_DrawToScreen = CAMERA_GLOBAL_DRAWON;
					
					return CAMERA_VIEW;
				}
			
				// Check if picture is touched.
				int x = point.x / PHOTO_PREVIEWSIZE+1;
				if(point.y > PHOTO_PREVIEW_HEIGHT_PADDING)
				{
					int y = ((point.y - PHOTO_PREVIEW_HEIGHT_PADDING) / PHOTO_PREVIEWSIZE);
					if(y < PHOTO_PREVIEW_MAX_ROW)
					{
						// Touched in the preview zone.
						
						// Now check if touched a image.
						int imgTouched = PHOTO_PREVIEW_MAX_COLUMN * y + x;
						if(imgTouched <= numPreviewsOnScreen)
						{
							// Collision with image.
							
							// Store the image touched.
							imageTouched = imgTouched;
							
							// Release the draw to screen flag, enabling items to be drawn again.
							Camera_Global_DrawToScreen = CAMERA_GLOBAL_DRAWON;
							
							GLCD_ClearScreen();
							
							// Switch to displaying a full image.
							Camera_Photos_State = CAMERA_PHOTOS_PHOTO;
						}						
					}
				}
			}
			
			break;
			
		case CAMERA_PHOTOS_PHOTO:
			// Display the full image.
			
			// Check if we can draw to screen.
			// This prevents us from drawing the same thing to the screen every frame.
			if(Camera_Global_DrawToScreen == CAMERA_GLOBAL_DRAWON)
			{
				// Lock the draw to screen flag.
				Camera_Global_DrawToScreen = CAMERA_GLOBAL_DRAWOFF;
				
				// Draw the photo
				if(!Camera_Photos_DrawPhoto(imageTouched-1))
				{
					Error_DisplayMessage("Failed to draw photo");
				}
			}
			
			// Check if screen is touched.
			if(Screen_Touched(&point))
			{
				// Release the draw to screen flag, enabling items to be drawn again.
				Camera_Global_DrawToScreen = CAMERA_GLOBAL_DRAWON;
							
				GLCD_ClearScreen();
			
				// Switch back to displaying the previews.
				Camera_Photos_State = CAMERA_PHOTOS_PREVIEWS;
			}
			break;
	}

	return CAMERA_PHOTOS;
}

int Camera_Photos_DrawPreviewPhotos(const unsigned int page)
{
	// Set the number of preview images on screen to 0.
	// Ready to count the preview images on screen.
	numPreviewsOnScreen = 0;
	
	// Loop over all rows and columns
	int i, j;
	for(i = 0; i < PHOTO_PREVIEW_MAX_ROW; i++)
	{
		// Get the y coord for the row of image previews
		unsigned int y = PHOTO_PREVIEWSIZE * i + PHOTO_PREVIEW_HEIGHT_PADDING;
		
		// Load image preview directories for this row
		unsigned int startIndex = PHOTO_PREVIEW_MAX_COLUMN*i;
		unsigned int numPreviewsInRow;
		numPreviewsInRow = SDCard_GetBMPFileName(PHOTO_ICONDIRECTORY, rowPreviewFiles, PHOTO_PREVIEW_MAX_COLUMN, MAX_PHOTOFILENAME, startIndex);
		
		// Count the total number of previews loaded 
		numPreviewsOnScreen += numPreviewsInRow;
		
		// Loop over all elements in row
		for(j = 0; j < numPreviewsInRow; j++)
		{
			uint8_t str[30];
			sprintf ((char*)str, "Media/Icons/%-11.11s", rowPreviewFiles[j]);
					
			// Open file from SD Card
			FIL file;
			if(!SDCard_OpenFile(&file, (char*)str))
			{
				return 0;
			}
			
			// Load bmp from file
			uint16_t width, height;
			if(!bmp_process(&file, buffer, &width, &height))
			{
				return 0;
			}
			
			// Check if the image loaded is the size of a preview image specification
			if(width != PHOTO_PREVIEWSIZE || height != PHOTO_PREVIEWSIZE)
			{
				return 0;
			}
			
			// Close File
			if(!SDCard_CloseFile(&file))
			{
				return 0;
			}
	
			// Get the x coord for the image in the row
			unsigned int x = PHOTO_PREVIEWSIZE * j;
					
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

int Camera_Photos_DrawPhoto(const unsigned int index)
{
	// Load the bmp buffer into memory from SDCard
	
	// Get the file name of the imageTouched bmp
	unsigned int numPreviewsInRow;
	numPreviewsInRow = SDCard_GetBMPFileName(PHOTO_ICONDIRECTORY, rowPreviewFiles, 1, MAX_PHOTOFILENAME, index);
	
	if(numPreviewsInRow != 1)
		return 0;
	
	// Change file extension to jpg
	char *charPtr = rowPreviewFiles[0];
	while (*(charPtr) != 0x2E) // . 
  {
		charPtr++;
  }
  *(++charPtr) = 'j'; 
	*(++charPtr) = 'p';
	*(++charPtr) = 'g';
	
	// Format the string to point to the jpg file
	uint8_t str[30];
  sprintf ((char*)str, "Media/Photos/%-11.11s", rowPreviewFiles[0]);
	
	// Open File
	FIL file;
	if(!SDCard_OpenFile(&file, "Media/test.jpg"))
	{
		return 0;
	}
	
	// Decode jpeg image and store in buffer
	uint16_t width, height;
	jpeg_decode(&file, buffer, &width, &height);
	
	// Close File
	if(!SDCard_CloseFile(&file))
	{
		return 0;
	}
	
	// Draw Buffer
	GLCD_DrawBitmap(0, 
									0, 
									width, 
									height, 
									buffer);
	
	return 1;
}
