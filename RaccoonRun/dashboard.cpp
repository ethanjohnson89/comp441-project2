// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// dashboard.cpp v1.0

#include "dashboard.h"

//=============================================================================
// Seven Segment constructor
//=============================================================================
SevenSegment::SevenSegment()
{
    digits = 1;
    number = 0;
}

//=============================================================================
// initialize the Seven Segment
// Pre: *graphics = pointer to Graphics object
//      *textureM = pointer to TextureManager object
//      left, top = screen location
//      scale = scaling (zoom) amount
//      digits = number of digits
//      color = color of digits
// Post: returns true on success, false on error
//=============================================================================
bool SevenSegment::initialize(Graphics *graphics, TextureManager *textureM,
                   int left, int top, float scale, UINT digs, COLOR_ARGB color)
{
    try {
        Image::initialize(graphics, dashboardNS::IMAGE_SIZE, dashboardNS::IMAGE_SIZE, 
                          dashboardNS::TEXTURE_COLS, textureM);
        setCurrentFrame(dashboardNS::SEGMENT_FRAME);
        spriteData.x = (float)left;
        spriteData.y = (float)top;
        spriteData.scale = scale;
        colorFilter = color;
        if(digs < 1)
            digs = 1;
        digits = digs;

        decimal.initialize(graphics, dashboardNS::IMAGE_SIZE, dashboardNS::IMAGE_SIZE,
                           dashboardNS::TEXTURE_COLS, textureM);
        decimal.setCurrentFrame(dashboardNS::DECIMAL_FRAME);
        decimal.setColorFilter(color);
    }
    catch(...)
    {
        return false;
    }
    //return okay
    return true;
}

//=============================================================================
// set the number on the Seven Segment display
//=============================================================================
void SevenSegment::set(double value)
{
    number = value;
}

//=============================================================================
// Display 7 segment digit 0-9, and -
//         A
//       -----
//     F|     |B
//      |  G  |
//       -----
//     E|     |C
//      |  D  |
//       -----  
//=============================================================================
void SevenSegment::drawDigit(char n, COLOR_ARGB color)
{
    float lowerY = spriteData.y + spriteData.height * spriteData.scale * 0.75f;
    float saveY = spriteData.y;

    // segment A
    if(n=='0' || n=='2' || n=='3' || n=='5' || n=='6' || n=='7' || n=='8' || n=='9')
    {
        setDegrees(0);
        Image::draw(color);
    }
    // segment B
    if(n=='0' || n=='1' || n=='2' || n=='3' || n=='4' || n=='7' || n=='8' || n=='9')
    {
        setDegrees(90);
        Image::draw(color);
    }
    // segment G
    if(n=='-' || n=='2' || n=='3' || n=='4' || n=='5' || n=='6' || n=='8' || n=='9')
    {
        setDegrees(180);
        Image::draw(color);
    }
    // if segment F
    if(n=='0' || n=='4' || n=='5' || n=='6' || n=='8' || n=='9')
    {
        setDegrees(270);
        Image::draw(color);
    }

    spriteData.y = lowerY;  // set Y for lower half of digit

    // if segment E
    if(n=='0' || n=='2' || n=='6' || n=='8')
    {
        setDegrees(270);
        Image::draw(color);
    }
    // if segment D
    if(n=='0' || n=='2' || n=='3' || n=='5' || n=='6' || n=='8' || n=='9')
    {
        setDegrees(180);
        Image::draw(color);
    }
    // if segment C
    if(n=='0' || n=='1' || n=='3' || n=='4' || n=='5' || n=='6' || n=='7' || n=='8' || n=='9')
    {
        setDegrees(90);
        Image::draw(color);
    }
    spriteData.y = saveY;
}

//=============================================================================
// Draw the Decimal point
//=============================================================================
void SevenSegment::drawDecimal(COLOR_ARGB color)
{
    float saveX = spriteData.x;
    float saveY = spriteData.y;

    setDegrees(0);
    spriteData.x -= spriteData.width * spriteData.scale * 0.25f;
    spriteData.y += spriteData.height * spriteData.scale * 0.80f;

    decimal.draw(spriteData, color);

    spriteData.x = saveX;
    spriteData.y = saveY;
}

//=============================================================================
// Draw the Seven Segment display
// The number variable contains float value to display
//=============================================================================
void SevenSegment::draw(COLOR_ARGB color)
{
    float saveX = spriteData.x;
    float saveY = spriteData.y;
    char ch;

    if(digits == 0)
        return;

    // convert number to string
    std::stringstream strstm;
    strstm.precision(digits);
    strstm.flags(std::ios_base::fixed);
    strstm << number;           // convert number to string
    std::string str = strstm.str();

    UINT digitN = str.length(); // get digits in string
    if (digitN > digits)        // if string has more digits than 7-seg display
        digitN = digits;

    // x location of left most digit
    spriteData.x += spriteData.width * spriteData.scale * 1.2f * (digits-digitN);

    UINT n=0;
    ch = str.at(n++);           // get first digit from number
    while(digitN > 0)           // while digits remain to be displayed
    {
        if(ch == '.')           // if decimal point
            drawDecimal(color);
        else
        {
            drawDigit(ch, color);   // display digit
            // next digit position on screen
            spriteData.x += spriteData.width * spriteData.scale * 1.2f;
        }
        if(n < str.length())
            ch = str.at(n++);   // get next digit
        else
            ch = '0';           // if string ends with '.' pad with 0 digit
        if(ch != '.')           // if not decimal point
            digitN--;           // decrement digit count
    }
    spriteData.x = saveX;
}

//=============================================================================
// Initialize the Bar 
// Pre: *graphics = pointer to Graphics object
//      *textureM = pointer to TextureManager object
//      left, top = screen location
//      scale = scaling (zoom) amount
//      color = color of bar
// Post: returns true on success, false on error
//=============================================================================
bool Bar::initialize(Graphics *graphics, TextureManager *textureM, int left,
                     int top, float scale, COLOR_ARGB color)
{
    try {
        Image::initialize(graphics, dashboardNS::IMAGE_SIZE, dashboardNS::IMAGE_SIZE, 
                          dashboardNS::TEXTURE_COLS, textureM);
        setCurrentFrame(dashboardNS::BAR_FRAME);
        spriteData.x = (float)left;
        spriteData.y = (float)top;
        spriteData.scale = scale;
        colorFilter = color;
    }
    catch(...)
    {
        return false;
    }
    //return okay
    return true;
}

//=============================================================================
// set the Bar size
//=============================================================================
void Bar::set(float p)
{
    if (p < 0)
        p = 0;
    else if(p > 100)
        p = 100;
    spriteData.rect.right = spriteData.rect.left + (LONG)(spriteData.width*p/100);
}

//=============================================================================
// Initialize Dial Gauge
// Pre: *graphics = pointer to Graphics object
//      *textureM = pointer to TextureManager object
//      left, top = screen location
//      scale = scaling (zoom) amount
//      type = dial type
//      zeroAngle = where zero is on dial
//      dialColor = color of dial
//      pointerColor = color of pointer
// Post: returns true on success, false on error
//=============================================================================
bool DialGauge::initialize(Graphics *graphics, TextureManager *textureM, int left,
                    int top, float scale, dashboardNS::DialType type,
                    float zeroAngle, COLOR_ARGB dialColor, COLOR_ARGB pointerColor)
{
    try {
        Image::initialize(graphics, dashboardNS::IMAGE_SIZE, dashboardNS::IMAGE_SIZE, 
                          dashboardNS::TEXTURE_COLS, textureM);
        dialType = type;
        switch(type)
        {
        case dashboardNS::DIAL360:
            setCurrentFrame(dashboardNS::DIAL360_FRAME); break;
        case dashboardNS::DIAL270:
            setCurrentFrame(dashboardNS::DIAL270_FRAME); break;
        case dashboardNS::DIAL180:
            setCurrentFrame(dashboardNS::DIAL180_FRAME); break;
        }
        spriteData.x = (float)left;
        spriteData.y = (float)top;
        spriteData.scale = scale;
        colorFilter = dialColor;
        setDegrees(zeroAngle);

        pointer.initialize(graphics, dashboardNS::IMAGE_SIZE,
                           dashboardNS::IMAGE_SIZE, dashboardNS::TEXTURE_COLS,
                           textureM);
        pointer.setCurrentFrame(dashboardNS::POINTER_FRAME);
        pointer.setColorFilter(pointerColor);
    }
    catch(...)
    {
        return false;
    }
    //return okay
    return true;
}

//=============================================================================
// set the DialGauge pointer
//=============================================================================
void DialGauge::set(float p)
{
    if (p < 0)
        p = 0;
    else if(p > 100)
        p = 100;
    switch(dialType)
    {
    case dashboardNS::DIAL360:
        pointer.setDegrees(p * 360/100.0f + getDegrees()); break;
    case dashboardNS::DIAL270:
        pointer.setDegrees(p * 270/100.0f + getDegrees() - 135); break;
    case dashboardNS::DIAL180:
        pointer.setDegrees(p * 180/100.0f + getDegrees() - 90); break;
    }
}

//=============================================================================
// Draw the DialGauge and pointer
//=============================================================================
void DialGauge::draw(COLOR_ARGB color)
{
    Image::draw(color);
    float dialAngle = spriteData.angle;
    spriteData.angle = pointer.getRadians();
    pointer.draw(spriteData, graphicsNS::FILTER);
    spriteData.angle = dialAngle;
}

//=============================================================================
// Light constructor
//=============================================================================
Light::Light()
{
    flashDelay = 0;
    flashTimer = 0;
    onColor = graphicsNS::RED;
    offColor = SETCOLOR_ARGB(255,32,0,0);   // dark RED
}

//=============================================================================
// Initialize the Light
// Pre: *graphics = pointer to Graphics object
//      *textureM = pointer to TextureManager object
//      left, top = screen location
//      scale = scaling (zoom) amount
//      flashRate = on/off/flash delay, <0 On, =0 Off, >0 flashes per second
//      colorOn = the color of the light when on
//      colorOff = the color of the light when off
// Post: returns true on success, false on error
//=============================================================================
bool Light::initialize(Graphics *graphics, TextureManager *textureM, int left, int top,
                float scale, float flashRate, COLOR_ARGB colorOn, COLOR_ARGB colorOff)
{
    try {
        Image::initialize(graphics, dashboardNS::IMAGE_SIZE, dashboardNS::IMAGE_SIZE, 
                          dashboardNS::TEXTURE_COLS, textureM);
        setCurrentFrame(dashboardNS::LIGHT_FRAME);
        spriteData.x = (float)left;
        spriteData.y = (float)top;
        spriteData.scale = scale;
        colorFilter = colorOff;
        offColor = colorOff;
        onColor = colorOn;
        if(flashRate > 0)
            flashDelay = flashRate/2.0f;    // 50 % duty cycle
        else
            flashDelay = flashRate;
    }
    catch(...)
    {
        return false;
    }
    //return okay
    return true;
}

//=============================================================================
// Set flashRate: <0 On, =0 Off, >0 cycle rate
//=============================================================================
void Light::set(float flashRate)
{
    if(flashRate > 0)
        flashDelay = flashRate/2.0f;    // 50 % duty cycle
    else
        flashDelay = flashRate;
}

//=============================================================================
// update the light
//=============================================================================
void Light::update(float frameTime)
{
    if(flashDelay > 0)  // >0 flashing light
    {
        flashTimer += frameTime;
        if(flashTimer >= flashDelay)
        {
            flashTimer -= flashDelay;
            if(colorFilter == onColor)
                colorFilter = offColor;
            else
                colorFilter = onColor;
        }
    }
}


//=============================================================================
//  ToggleSwitch Constructor
//=============================================================================
ToggleSwitch::ToggleSwitch()
{
    switchOn = false;
    mouseClick = true;
}

//=============================================================================
// Initialize the Toggle Switch
// Pre: *graphics = pointer to Graphics object
//      *textureM = pointer to TextureManager object
//      *in = pointer to Input object
//      hwnd = handle to window
//      left, top = screen location
//      scale = scaling (zoom) amount
// Post: returns true on success, false on error
//=============================================================================
bool ToggleSwitch::initialize(Graphics *graphics, TextureManager *textureM, Input *in, HWND h,
                    int left, int top, float scale)
{
    try {
        Image::initialize(graphics, dashboardNS::IMAGE_SIZE, dashboardNS::IMAGE_SIZE, 
                          dashboardNS::TEXTURE_COLS, textureM);
        setCurrentFrame(dashboardNS::SWITCH_OFF_FRAME);
        spriteData.x = (float)left;
        spriteData.y = (float)top;
        spriteData.scale = scale;
        hwnd = h;                       // handle to the window
        input = in;                     // the input object
        switchRect.left = left;
        switchRect.top  = top;
        switchRect.right = (long)(left + (dashboardNS::SWITCH_WIDTH * spriteData.scale));
        switchRect.bottom = (long)(top + (spriteData.height * spriteData.scale));
    }
    catch(...)
    {
        return false;
    }
    //return okay
    return true;
}

//=============================================================================
// Checks for mouse click on switch
//=============================================================================
void ToggleSwitch::update(float frameTime)
{
    if (!initialized || !visible)
        return;

    // calculate screen ratios incase window was resized
    RECT clientRect;
    GetClientRect(hwnd, &clientRect);
    float screenRatioX = (float)GAME_WIDTH / clientRect.right;
    float screenRatioY = (float)GAME_HEIGHT / clientRect.bottom;

    if (input->getMouseLButton())       // if mouse left button
    {
        // if mouse clicked inside switch
        if (input->getMouseX()*screenRatioX >= switchRect.left &&
            input->getMouseX()*screenRatioX <= switchRect.right &&
            input->getMouseY()*screenRatioY >= switchRect.top &&
            input->getMouseY()*screenRatioY <= switchRect.bottom)
        {
            if(mouseClick)
            {
                mouseClick = false;
                switchOn = !switchOn;       // toggle the switch
                if(switchOn)
                    setCurrentFrame(dashboardNS::SWITCH_ON_FRAME);
                else
                    setCurrentFrame(dashboardNS::SWITCH_OFF_FRAME);
            }
        }
    } else
        mouseClick = true;
}

//=============================================================================
// Constructor
//=============================================================================
PushButton::PushButton()
{
    switchOn = false;
    mouseClick = true;
    momentary = true;
}

//=============================================================================
// Initialize the Pushbutton
// Pre: *graphics = pointer to Graphics object
//      *textureM = pointer to TextureManager object
//      *in = pointer to Input object
//      hwnd = handle to window
//      left, top = screen location
//      scale = scaling (zoom) amount
//      type = true for momentary, false for toggle
// Post: returns true on success, false on error
//=============================================================================
bool PushButton::initialize(Graphics *graphics, TextureManager *textureM, Input *in, HWND h,
                    int left, int top, float scale, bool type)
{
    try {
        Image::initialize(graphics, dashboardNS::IMAGE_SIZE, dashboardNS::IMAGE_SIZE, 
                          dashboardNS::TEXTURE_COLS, textureM);
        setCurrentFrame(dashboardNS::BUTTON_UP_FRAME);
        spriteData.x = (float)left;
        spriteData.y = (float)top;
        spriteData.scale = scale;
        hwnd = h;                       // handle to the window
        input = in;                     // the input object
        switchRect.left = left;
        switchRect.top  = top;
        switchRect.right = (long)(left + spriteData.width * spriteData.scale);
        switchRect.bottom = (long)(top + spriteData.height * spriteData.scale);
        momentary = type;
    }
    catch(...)
    {
        return false;
    }
    //return okay
    return true;
}

//=============================================================================
// Checks for mouse click on pushbutton
//=============================================================================
void PushButton::update(float frameTime)
{
    if (!initialized || !visible)
        return;

    // calculate screen ratios incase window was resized
    RECT clientRect;
    GetClientRect(hwnd, &clientRect);
    float screenRatioX = (float)GAME_WIDTH / clientRect.right;
    float screenRatioY = (float)GAME_HEIGHT / clientRect.bottom;

    if (input->getMouseLButton())           // if mouse left button
    {
        // if mouse clicked inside switch
        if (input->getMouseX()*screenRatioX >= switchRect.left &&
            input->getMouseX()*screenRatioX <= switchRect.right &&
            input->getMouseY()*screenRatioY >= switchRect.top &&
            input->getMouseY()*screenRatioY <= switchRect.bottom)
        {
            if(mouseClick)
            {
                mouseClick = false;
                if(momentary)               // if momentary switch
                    switchOn = true;
                else
                    switchOn = !switchOn;   // toggle the switch
                if(switchOn)
                    setCurrentFrame(dashboardNS::BUTTON_DOWN_FRAME);
                else
                    setCurrentFrame(dashboardNS::BUTTON_UP_FRAME);
            }
        }
    } 
    else
    {
        mouseClick = true;
        if(momentary)
        {
            switchOn = false;
            setCurrentFrame(dashboardNS::BUTTON_UP_FRAME);
        }
    }
}

//=============================================================================
//  Constructor
//=============================================================================
BarGraph::BarGraph()
{
    maxBars = 1;
    barsOn = 0;
}

//=============================================================================
// Initialize the Bar Graph
// Pre: *graphics = pointer to Graphics object
//      *textureM = pointer to TextureManager object
//      left, top = screen location
//      scale = scaling (zoom) amount
//      bars = number of bars in meter
//      color = color of bars
// Post: returns true on success, false on error
//=============================================================================
bool BarGraph::initialize(Graphics *graphics, TextureManager *textureM, int left, int top,
                    float scale, UINT bars, COLOR_ARGB color)
{
    try {
        Image::initialize(graphics, dashboardNS::IMAGE_SIZE, dashboardNS::IMAGE_SIZE, 
                          dashboardNS::TEXTURE_COLS, textureM);
        setCurrentFrame(dashboardNS::BAR_GRAPH_FRAME);
        spriteData.x = (float)left;
        spriteData.y = (float)top;
        spriteData.scale = scale;
        colorFilter = color;
        if(maxBars > 0)
            maxBars = bars;
    }
    catch(...)
    {
        return false;
    }
    //return okay
    return true;
}

//=============================================================================
// Set barsOn count to the number of bars to display.
// The parameter p is a percent from 0 to 100.
//=============================================================================
void BarGraph::set(float p)
{
    if (p < 0)
        p = 0;
    else if(p > 100)
        p = 100;
    barsOn = (int)(p * 0.01f * maxBars + 0.5);
}

//=============================================================================
// Draw the Bar Graph
// barsOn contains the number of bars to display
//=============================================================================
void BarGraph::draw(COLOR_ARGB color)
{
    float saveX = spriteData.x;

    for (int i=barsOn; i > 0; i--)
    {
        // next bar position on screen
        spriteData.x += dashboardNS::BAR_GRAPH_WIDTH * spriteData.scale;
        Image::draw(color);
    }
    spriteData.x = saveX;
}

