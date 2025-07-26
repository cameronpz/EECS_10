#ifndef ADVANCED_H_INCLUDED_
#define ADVANCED_H_INCLUDED_

/* add noise to an image */
IMAGE *Noise(IMAGE *image, int n);

/* posterize the image */
IMAGE *Posterize(IMAGE *image, int rbits, int gbits, int bbits);

/* motion blur */
IMAGE *MotionBlur(IMAGE *image, int BlurAmount);

//crop image to a square
IMAGE *Square(IMAGE *image, int x_offset, int y_offset, int square_size);

//enlarge an image by the percentage specified
IMAGE *Enlarge(IMAGE *image, int percentage);

//adjusts brightness and contrast for an image
IMAGE *BrightnessandContrast(IMAGE *image, int brightness, int contrast);

#endif /* ADVANCED_H_INCLUDED_ */

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
