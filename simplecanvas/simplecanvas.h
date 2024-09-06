/**
 * @brief A simple library for 2D drawing in C++, by Chris Tralie
 */
#ifndef SIMPLECANVAS_H
#define SIMPLECANVAS_H

#include <string>

class SimpleCanvas {
    private:
        // Helper method for Bresenham's line algorithm
        void drawLineLow(int x0, int y0, int x1, int y1, uint8_t R, uint8_t G, uint8_t B);

        // Helper method for Bresenham's line algorithm
        void drawLineHigh(int x0, int y0, int x1, int y1, uint8_t R, uint8_t G, uint8_t B);

        /**
         * @brief Draw a character at a particular position by loading its bitmap
         * image and copying it over pixel by pixel to a chosen position
         * @param c The character to draw
         * @param x x location of lower left corner of character
         * @param y y location of lower left corner of character
         * @param dx Change in x to move cursor after this character
         * @param dy Change in y to move cursor after this character
         * @param relpath Relative path to directory containing the fonts
         * @return Width of character
         */
        void drawChar(char c, int x0, int y0, int* dx, int* dy, std::string relpath);

        /**
         * @brief Create a 3D array wrapper around the flattened image format
         * 
         */
        void createWrapper();

        void deallocate();

        uint8_t* dataInternal;

    public:
        int width, height;
        uint8_t*** data;

        /**
         * @brief Construct a new image object from a file.  
         * 
         * @param fname Path to file
         */
        SimpleCanvas(std::string fname);

        /**
         * @brief Instantiate an image object of a particular dimension
         * 
         * @param width Width of image
         * @param height Height of image
         */
        SimpleCanvas(int32_t width, int32_t height);

        /**
         * @brief Destroy the Simple Image object by de-allocating the pixel data
         */
        ~SimpleCanvas();

        /**
         * @brief Read in a ppm file.  Use ffmpeg to convert the file to a 
         * temporary .ppm file if it has a non ppm extension
         * 
         * @param fname Path to file
         */
        void read(std::string fname);

        /**
         * Write the image to a file
         * If the filename ends with an extension other than ppm, write it to a
         * temporary ppm file, and use ffmpeg to convert it to the desired name
         * 
         * @param fname Name of the file
         * 
         */
        void write(std::string fname);

        /**
         * @brief Set the color of a particular pixel
         * 
         * @param x X coordinate of pixel
         * @param y Y coordinate of pixel
         * @param R Red channel
         * @param G Green channel
         * @param B Blue channel
         */
        void setPixel(int x, int y, uint8_t R, uint8_t G, uint8_t B);

        /**
         * @brief Fill a solid rectangle with a color
         * 
         * @param x0 Left of rectangle
         * @param y0 Top of rectangle
         * @param w Width of rectangle
         * @param h Height of rectangle
         * @param R Red channel
         * @param G Green channel
         * @param B Blue channel
         */
        void fillRect(int x0, int y0, int w, int h, uint8_t R, uint8_t G, uint8_t B);

        /**
         * @brief Clear the entire canvas to be one color
         * 
         * @param R Red channel
         * @param G Green channel
         * @param B Blue channel
         */
        void clearRect(uint8_t R, uint8_t G, uint8_t B);

        /**
         * @brief Draw the outline of a rectangle with a particular color
         * 
         * @param x0 Left of rectangle
         * @param y0 Top of rectangle
         * @param w Width of rectangle
         * @param h Height of rectangle
         * @param R Red channel
         * @param G Green channel
         * @param B Blue channel
         * @param line_w Width of rectangle
         */
        void drawRect(int x0, int y0, int w, int h,
                            uint8_t R, uint8_t G, uint8_t B, uint8_t line_w);

        /**
         * @brief Draw a thin line from one point to another
         * 
         * @param x0 X coordinate of first point
         * @param y0 Y coordinate of first point
         * @param x1 X coordinate of second point
         * @param y1 Y coordinate of second point
         * @param R Red channel
         * @param G Green channel
         * @param B Blue channel
         */
        void drawLine(int x0, int y0, int x1, int y1, uint8_t R, uint8_t G, uint8_t B);

        
        /**
         * @brief Draw a thick line from one point to another
         * 
         * @param x0 X coordinate of first point
         * @param y0 Y coordinate of first point
         * @param x1 X coordinate of second point
         * @param y1 Y coordinate of second point
         * @param thickness Thickness of line
         * @param R Red channel
         * @param G Green channel
         * @param B Blue channel
         */
        void drawLine(int x0, int y0, int x1, int y1, int thickness, uint8_t R, uint8_t G, uint8_t B);

        /**
         * @brief Fill in a solid disc of a particular color
         * 
         * @param cx X coordinate of center of disc
         * @param cy Y coordinate of center of disc
         * @param r Radius of disc
         * @param R Red channel
         * @param G Green channel
         * @param B Blue channel
         */
        void fillCircle(int cx, int cy, double r, uint8_t R, uint8_t G, uint8_t B);

        /**
         * @brief Draw a character at a string at a position
         * @param s The string to draw
         * @param x x location of lower left corner of the string
         * @param y y location of lower left corner of the string
         * @param relpath Relative path to directory containing the fonts
         */
        void drawString(std::string s, int x0, int y0, std::string relpath);
};

#endif