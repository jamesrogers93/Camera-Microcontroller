
#ifndef _CAMERA_PHOTOS_H
#define _CAMERA_PHOTOS_H

void Camera_Photos_Initalise(void);

enum CAMERA_STATE Camera_Photos_Run(void);

int Camera_Photos_DrawPreviewPhotos(const unsigned int page);
int Camera_Photos_DrawPhoto(const unsigned int index);

#endif /* _CAMERA_PHOTOS_H */
