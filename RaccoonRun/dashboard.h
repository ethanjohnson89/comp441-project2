// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// dashboard.h v1.0

#ifndef _DASHBOARD_H            // Prevent multiple definitions if this 
#define _DASHBOARD_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <string>
#include <sstream>
#include "image.h"
#include "constants.h"
#include "textureManager.h"
#include "input.h"

namespace dashboardNS
{
    const int   IMAGE_SIZE = 64;        // each texture size
    const int   TEXTURE_COLS = 4;       // texture has 4 columns
    const int   BAR_FRAME = 0;          // the frame number of each texture
    const int   DIAL360_FRAME = 1;      // "
    const int   DIAL270_FRAME = 2;      // ...
    const int   DIAL180_FRAME = 3;
    const int   LIGHT_FRAME = 4;
    const int   POINTER_FRAME = 5;
    const int   SEGMENT_FRAME = 6;
    const int   DECIMAL_FRAME = 7;
    const int   SWITCH_OFF_FRAME = 8;
    const int   SWITCH_ON_FRAME = 9;
    const int   BUTTON_UP_FRAME = 10;
    const int   BUTTON_DOWN_FRAME = 11;
    const int   BAR_GRAPH_FRAME = 12;
    const int   SWITCH_WIDTH = 44;      // width of toggle switch 
    const int   BAR_GRAPH_WIDTH = 8;    // width of bar + gap
    enum DialType{DIAL360, DIAL270, DIAL180};
}

class SevenSegment : public Image
{
    private:
    Image   decimal;
    UINT    digits;
    double  number;
    public:
    SevenSegment();
    // Initialize Seven Segment
    // Pre: *graphics = pointer to Graphics object
    //      *textureM = pointer to TextureManager object
    //      left, top = screen location
    //      scale = scaling (zoom) amount
    //      digits = number of digits
    //      color = color of digits
    bool initialize(Graphics *graphics, TextureManager *textureM, int left, int top,
                    float scale, UINT digits, COLOR_ARGB color);
    // Set Number in 7-Segment
    void set(double value);
    // Override update
    virtual void update(float frameTime)    {}
    // Draw 1 digit (internal use)
    void drawDigit(char n, COLOR_ARGB color);
    // Draw decimal point (internal use)
    void drawDecimal(COLOR_ARGB color);
    // Draw Image using color as filter. Default color is WHITE.
    virtual void draw(COLOR_ARGB color = graphicsNS::WHITE);
};

class Bar : public Image
{
    public:
    // Initialize the Bar 
    // Pre: *graphics = pointer to Graphics object
    //      *textureM = pointer to TextureManager object
    //      left, top = screen location
    //      scale = scaling (zoom) amount
    //      color = color of bar
    bool initialize(Graphics *graphics, TextureManager *textureM, int left, int top,
                    float scale, COLOR_ARGB color);
    // Set Bar Size
    void set(float percentOn);
    // Override update so setRect() is not called.
    virtual void update(float frameTime)    {}
};

class DialGauge : public Image
{
    private:
    Image   pointer;
    dashboardNS::DialType dialType;
    public:
    // Initialize Dial Gauge
    // Pre: *graphics = pointer to Graphics object
    //      *textureM = pointer to TextureManager object
    //      left, top = screen location
    //      scale = scaling (zoom) amount
    //      type = dial type
    //      zeroAngle = where zero is on dial
    //      dialColor = color of dial
    //      pointerColor = color of pointer
    bool initialize(Graphics *graphics, TextureManager *textureM, int left, int top,
                    float scale, dashboardNS::DialType type, float zeroAngle,
                    COLOR_ARGB dialColor, COLOR_ARGB pointerColor);
    // Set Dial as percentage 0 to 100
    void set(float percentOn);
    // Override update so setRect() is not called.
    virtual void update(float frameTime)    {}
    // Draw the image without creating a sprite Begin/End pair.
    // Pre : Image::spriteBegin() is called.
    // Post: Image::spriteEnd() is called.
    virtual void draw(COLOR_ARGB color = graphicsNS::WHITE); // draw using color as filter
};

class Light : public Image
{
    private:
    float   flashTimer;
    float   flashDelay;
    COLOR_ARGB  onColor;
    COLOR_ARGB  offColor;
    public:
    Light();    // constructor
    // Initialize the Light
    // Pre: *graphics = pointer to Graphics object
    //      *textureM = pointer to TextureManager object
    //      left, top = screen location
    //      scale = scaling (zoom) amount
    //      flashRate = on/off/flash delay, <0 On, =0 Off, >0 flashes per second
    //      colorOn = the color of the light when on
    //      colorOff = the color of the light when off
    bool initialize(Graphics *graphics, TextureManager *textureM, int left, int top,
                float scale,float flashRate, COLOR_ARGB colorOn, COLOR_ARGB colorOff);
    // Set flashRate: <0 On, =0 Off, >0 flash delay in seconds
    void set(float rate);
    // Override update
    virtual void update(float frameTime);
};

class ToggleSwitch : public Image
{
    private:
    Input   *input;
    HWND    hwnd;
    RECT    switchRect;         // mouse click region
    bool    switchOn;           // switch state
    bool    mouseClick;         // track mouse clicks
    public:
    // Toggle switch constructor
    ToggleSwitch();
    // Initialize the Toggle Switch
    // Pre: *graphics = pointer to Graphics object
    //      *textureM = pointer to TextureManager object
    //      *in = pointer to Input object
    //      hwnd = handle to window
    //      left, top = screen location
    //      scale = scaling (zoom) amount
    bool initialize(Graphics *graphics, TextureManager *textureM, Input *in, HWND hwnd,
                    int left, int top, float scale);
    // Override update
    virtual void update(float frameTime);
    // Get switch state
    bool getSwitchOn()   {return switchOn;}
    // Set switch state
    void setSwitch(bool on) {switchOn = on;}
};

class PushButton : public Image
{
    private:
    private:
    Input   *input;
    HWND    hwnd;
    RECT    switchRect;         // mouse click region
    bool    switchOn;           // switch state
    bool    mouseClick;         // track mouse clicks
    bool    momentary;          // true for momentary, false for toggle
    public:
    // Pushbutton switch constructor
    PushButton();
    // Initialize the Pushbutton
    // Pre: *graphics = pointer to Graphics object
    //      *textureM = pointer to TextureManager object
    //      *in = pointer to Input object
    //      hwnd = handle to window
    //      left, top = screen location
    //      scale = scaling (zoom) amount
    //      momentary = true for momentary, false for toggle
    bool initialize(Graphics *graphics, TextureManager *textureM, Input *in, HWND hwnd,
                    int left, int top, float scale, bool momentary);
    // Override update
    virtual void update(float frameTime);
    // Get switch state
    bool getSwitchOn()  {return switchOn;}
    // Set switch state
    void setSwitch(bool on) {switchOn = on;}
};

//
class BarGraph : public Image
{
    private:
    int     maxBars;    // max bars
    int   barsOn;       // bars currently on
    public:
    // BarGraph constructor
    BarGraph();
    // Initialize the Bar Graph
    // Pre: *graphics = pointer to Graphics object
    //      *textureM = pointer to TextureManager object
    //      *in = pointer to Input object
    //      hwnd = handle to window
    //      left, top = screen location
    //      scale = scaling (zoom) amount
    //      bars = number of bars in meter
    //      color = color of bars
    bool initialize(Graphics *graphics, TextureManager *textureM, int left, int top,
                    float scale, UINT bars, COLOR_ARGB color);
    // Set display 0 to 100 percent
    void set(float percentOn);
    // Override update so setRect() is not called.
    virtual void update(float frameTime)    {}
    // Draw the image without creating a sprite Begin/End pair.
    // Pre : Image::spriteBegin() is called.
    // Post: Image::spriteEnd() is called.
    virtual void draw(COLOR_ARGB color = graphicsNS::WHITE); // draw using color as filter
};

#endif

