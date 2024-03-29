/*********************************************************************
 *
 * $Id: pic24config.php 8610 2012-11-07 08:54:50Z mvuilleu $
 *
 * Declares yFindDisplay(), the high-level API for Display functions
 *
 * - - - - - - - - - License information: - - - - - - - - - 
 *
 * Copyright (C) 2011 and beyond by Yoctopuce Sarl, Switzerland.
 *
 * 1) If you have obtained this file from www.yoctopuce.com,
 *    Yoctopuce Sarl licenses to you (hereafter Licensee) the
 *    right to use, modify, copy, and integrate this source file
 *    into your own solution for the sole purpose of interfacing
 *    a Yoctopuce product with Licensee's solution.
 *
 *    The use of this file and all relationship between Yoctopuce 
 *    and Licensee are governed by Yoctopuce General Terms and 
 *    Conditions.
 *
 *    THE SOFTWARE AND DOCUMENTATION ARE PROVIDED 'AS IS' WITHOUT
 *    WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING 
 *    WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS 
 *    FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO
 *    EVENT SHALL LICENSOR BE LIABLE FOR ANY INCIDENTAL, SPECIAL,
 *    INDIRECT OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, 
 *    COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR 
 *    SERVICES, ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT 
 *    LIMITED TO ANY DEFENSE THEREOF), ANY CLAIMS FOR INDEMNITY OR
 *    CONTRIBUTION, OR OTHER SIMILAR COSTS, WHETHER ASSERTED ON THE
 *    BASIS OF CONTRACT, TORT (INCLUDING NEGLIGENCE), BREACH OF
 *    WARRANTY, OR OTHERWISE.
 *
 * 2) If your intent is not to interface with Yoctopuce products,
 *    you are not entitled to use, read or create any derived
 *    material from this source file.
 *
 *********************************************************************/


#ifndef YOCTO_DISPLAY_H
#define YOCTO_DISPLAY_H

#include "yocto_api.h"
#include <cfloat>
#include <cmath>
#include <map>

//--- (generated code: return codes)
//--- (end of generated code: return codes)

//--- (generated code: YDisplay definitions)
class YDisplay; //forward declaration

typedef void (*YDisplayUpdateCallback)(YDisplay *func, const string& functionValue);
typedef enum {
    Y_POWERSTATE_OFF = 0,
    Y_POWERSTATE_ON = 1,
    Y_POWERSTATE_INVALID = -1,
} Y_POWERSTATE_enum;

typedef enum {
    Y_ORIENTATION_LEFT = 0,
    Y_ORIENTATION_UP = 1,
    Y_ORIENTATION_RIGHT = 2,
    Y_ORIENTATION_DOWN = 3,
    Y_ORIENTATION_INVALID = -1,
} Y_ORIENTATION_enum;

typedef enum {
    Y_DISPLAYTYPE_MONO = 0,
    Y_DISPLAYTYPE_GRAY = 1,
    Y_DISPLAYTYPE_RGB = 2,
    Y_DISPLAYTYPE_INVALID = -1,
} Y_DISPLAYTYPE_enum;

#define Y_LOGICALNAME_INVALID           (YAPI::INVALID_STRING)
#define Y_ADVERTISEDVALUE_INVALID       (YAPI::INVALID_STRING)
#define Y_STARTUPSEQ_INVALID            (YAPI::INVALID_STRING)
#define Y_BRIGHTNESS_INVALID            (-1)
#define Y_DISPLAYWIDTH_INVALID          (0xffffffff)
#define Y_DISPLAYHEIGHT_INVALID         (0xffffffff)
#define Y_LAYERWIDTH_INVALID            (0xffffffff)
#define Y_LAYERHEIGHT_INVALID           (0xffffffff)
#define Y_LAYERCOUNT_INVALID            (0xffffffff)
#define Y_COMMAND_INVALID               (YAPI::INVALID_STRING)
//--- (end of generated code: YDisplay definitions)

//--- (generated code: YDisplayLayer definitions)
    typedef enum {
        Y_ALIGN_TOP_LEFT = 0 ,
        Y_ALIGN_CENTER_LEFT = 1 ,
        Y_ALIGN_BASELINE_LEFT = 2 ,
        Y_ALIGN_BOTTOM_LEFT = 3 ,
        Y_ALIGN_TOP_CENTER = 4 ,
        Y_ALIGN_CENTER = 5 ,
        Y_ALIGN_BASELINE_CENTER = 6 ,
        Y_ALIGN_BOTTOM_CENTER = 7 ,
        Y_ALIGN_TOP_DECIMAL = 8 ,
        Y_ALIGN_CENTER_DECIMAL = 9 ,
        Y_ALIGN_BASELINE_DECIMAL = 10 ,
        Y_ALIGN_BOTTOM_DECIMAL = 11 ,
        Y_ALIGN_TOP_RIGHT = 12 ,
        Y_ALIGN_CENTER_RIGHT = 13 ,
        Y_ALIGN_BASELINE_RIGHT = 14 ,
        Y_ALIGN_BOTTOM_RIGHT = 15 
    } Y_ALIGN;
    
//--- (end of generated code: YDisplayLayer definitions)

class YDisplay;

//--- (generated code: YDisplayLayer declaration)
/**
 * YDisplayLayer Class: DisplayLayer object interface
 * 
 * A DisplayLayer is an image layer containing objects to display
 * (bitmaps, text, etc.). The content is displayed only when
 * the layer is active on the screen (and not masked by other
 * overlapping layers).
 */
class YDisplayLayer {
protected:
    // Attributes (function value cache)
    //--- (end of generated code: YDisplayLayer declaration)
    YDisplay *_display;
    int    _id;
    string _cmdbuff;
    bool   _hidden;
    
    // internal function to send a command for this layer
    int command_push(string cmd);
    int command_flush(string cmd);
    
public:
    int flush_now();
    YDisplayLayer(YDisplay *parent, int id):
    _display(parent),_id(id),_cmdbuff(""),_hidden(false){};
    //--- (generated code: YDisplayLayer accessors declaration)

    static const Y_ALIGN ALIGN_TOP_LEFT = Y_ALIGN_TOP_LEFT;
    static const Y_ALIGN ALIGN_CENTER_LEFT = Y_ALIGN_CENTER_LEFT;
    static const Y_ALIGN ALIGN_BASELINE_LEFT = Y_ALIGN_BASELINE_LEFT;
    static const Y_ALIGN ALIGN_BOTTOM_LEFT = Y_ALIGN_BOTTOM_LEFT;
    static const Y_ALIGN ALIGN_TOP_CENTER = Y_ALIGN_TOP_CENTER;
    static const Y_ALIGN ALIGN_CENTER = Y_ALIGN_CENTER;
    static const Y_ALIGN ALIGN_BASELINE_CENTER = Y_ALIGN_BASELINE_CENTER;
    static const Y_ALIGN ALIGN_BOTTOM_CENTER = Y_ALIGN_BOTTOM_CENTER;
    static const Y_ALIGN ALIGN_TOP_DECIMAL = Y_ALIGN_TOP_DECIMAL;
    static const Y_ALIGN ALIGN_CENTER_DECIMAL = Y_ALIGN_CENTER_DECIMAL;
    static const Y_ALIGN ALIGN_BASELINE_DECIMAL = Y_ALIGN_BASELINE_DECIMAL;
    static const Y_ALIGN ALIGN_BOTTOM_DECIMAL = Y_ALIGN_BOTTOM_DECIMAL;
    static const Y_ALIGN ALIGN_TOP_RIGHT = Y_ALIGN_TOP_RIGHT;
    static const Y_ALIGN ALIGN_CENTER_RIGHT = Y_ALIGN_CENTER_RIGHT;
    static const Y_ALIGN ALIGN_BASELINE_RIGHT = Y_ALIGN_BASELINE_RIGHT;
    static const Y_ALIGN ALIGN_BOTTOM_RIGHT = Y_ALIGN_BOTTOM_RIGHT;

    /**
     * Reverts the layer to its initial state (fully transparent, default settings).
     * Reinitializes the drawing pointer to the upper left position,
     * and selects the most visible pen color. If you only want to erase the layer
     * content, use the method clear() instead.
     * 
     * @return YAPI_SUCCESS if the call succeeds.
     * 
     * On failure, throws an exception or returns a negative error code.
     */
    int             reset();

    /**
     * Erases the whole content of the layer (makes it fully transparent).
     * This method does not change any other attribute of the layer.
     * To reinitialize the layer attributes to defaults settings, use the method
     * reset() instead.
     * 
     * @return YAPI_SUCCESS if the call succeeds.
     * 
     * On failure, throws an exception or returns a negative error code.
     */
    int             clear();

    /**
     * Selects the pen color for all subsequent drawing functions,
     * including text drawing. The pen color is provided as an RGB value.
     * For grayscale or monochrome displays, the value is
     * automatically converted to the proper range.
     * 
     * @param color: the desired pen color, as a 24-bit RGB value
     * 
     * @return YAPI_SUCCESS if the call succeeds.
     * 
     * On failure, throws an exception or returns a negative error code.
     */
    int             selectColorPen(int color);

    /**
     * Selects the pen gray level for all subsequent drawing functions,
     * including text drawing. The gray level is provided as a number between
     * 0 (black) and 255 (white, or whichever the lighest color is).
     * For monochrome displays (without gray levels), any value
     * lower than 128 is rendered as black, and any value equal
     * or above to 128 is non-black.
     * 
     * @param graylevel: the desired gray level, from 0 to 255
     * 
     * @return YAPI_SUCCESS if the call succeeds.
     * 
     * On failure, throws an exception or returns a negative error code.
     */
    int             selectGrayPen(int graylevel);

    /**
     * Selects an eraser instead of a pen for all subsequent drawing functions,
     * except for text drawing and bitmap copy functions. Any point drawn
     * using the eraser becomes transparent (as when the layer is empty),
     * showing the other layers beneath it.
     * 
     * @return YAPI_SUCCESS if the call succeeds.
     * 
     * On failure, throws an exception or returns a negative error code.
     */
    int             selectEraser();

    /**
     * Enables or disables anti-aliasing for drawing oblique lines and circles.
     * Anti-aliasing provides a smoother aspect when looked from far enough,
     * but it can add fuzzyness when the display is looked from very close.
     * At the end of the day, it is your personal choice.
     * Anti-aliasing is enabled by default on grayscale and color displays,
     * but you can disable it if you prefer. This setting has no effect
     * on monochrome displays.
     * 
     * @param mode: <t>true</t> to enable antialiasing, <t>false</t> to
     *         disable it.
     * 
     * @return YAPI_SUCCESS if the call succeeds.
     * 
     * On failure, throws an exception or returns a negative error code.
     */
    int             setAntialiasingMode(bool mode);

    /**
     * Draws a single pixel at the specified position.
     * 
     * @param x: the distance from left of layer, in pixels
     * @param y: the distance from top of layer, in pixels
     * 
     * @return YAPI_SUCCESS if the call succeeds.
     * 
     * On failure, throws an exception or returns a negative error code.
     */
    int             drawPixel(int x,int y);

    /**
     * Draws an empty rectangle at a specified position.
     * 
     * @param x1: the distance from left of layer to the left border of the rectangle, in pixels
     * @param y1: the distance from top of layer to the top border of the rectangle, in pixels
     * @param x2: the distance from left of layer to the right border of the rectangle, in pixels
     * @param y2: the distance from top of layer to the bottom border of the rectangle, in pixels
     * 
     * @return YAPI_SUCCESS if the call succeeds.
     * 
     * On failure, throws an exception or returns a negative error code.
     */
    int             drawRect(int x1,int y1,int x2,int y2);

    /**
     * Draws a filled rectangular bar at a specified position.
     * 
     * @param x1: the distance from left of layer to the left border of the rectangle, in pixels
     * @param y1: the distance from top of layer to the top border of the rectangle, in pixels
     * @param x2: the distance from left of layer to the right border of the rectangle, in pixels
     * @param y2: the distance from top of layer to the bottom border of the rectangle, in pixels
     * 
     * @return YAPI_SUCCESS if the call succeeds.
     * 
     * On failure, throws an exception or returns a negative error code.
     */
    int             drawBar(int x1,int y1,int x2,int y2);

    /**
     * Draws an empty circle at a specified position.
     * 
     * @param x: the distance from left of layer to the center of the circle, in pixels
     * @param y: the distance from top of layer to the center of the circle, in pixels
     * @param r: the radius of the circle, in pixels
     * 
     * @return YAPI_SUCCESS if the call succeeds.
     * 
     * On failure, throws an exception or returns a negative error code.
     */
    int             drawCircle(int x,int y,int r);

    /**
     * Draws a filled disc at a given position.
     * 
     * @param x: the distance from left of layer to the center of the disc, in pixels
     * @param y: the distance from top of layer to the center of the disc, in pixels
     * @param r: the radius of the disc, in pixels
     * 
     * @return YAPI_SUCCESS if the call succeeds.
     * 
     * On failure, throws an exception or returns a negative error code.
     */
    int             drawDisc(int x,int y,int r);

    /**
     * Selects a font to use for the next text drawing functions, by providing the name of the
     * font file. You can use a built-in font as well as a font file that you have previously
     * uploaded to the device built-in memory. If you experience problems selecting a font
     * file, check the device logs for any error message such as missing font file or bad font
     * file format.
     * 
     * @param fontname: the font file name
     * 
     * @return YAPI_SUCCESS if the call succeeds.
     * 
     * On failure, throws an exception or returns a negative error code.
     */
    int             selectFont(string fontname);

    /**
     * Draws a text string at the specified position. The point of the text that is aligned
     * to the specified pixel position is called the anchor point, and can be chosen among
     * several options. Text is rendered from left to right, without implicit wrapping.
     * 
     * @param x: the distance from left of layer to the text ancor point, in pixels
     * @param y: the distance from top of layer to the text ancor point, in pixels
     * @param anchor: the text anchor point, chosen among the Y_ALIGN enumeration:
     *         Y_ALIGN_TOP_LEFT,    Y_ALIGN_CENTER_LEFT,    Y_ALIGN_BASELINE_LEFT,    Y_ALIGN_BOTTOM_LEFT,
     *         Y_ALIGN_TOP_CENTER,  Y_ALIGN_CENTER,         Y_ALIGN_BASELINE_CENTER,  Y_ALIGN_BOTTOM_CENTER,
     *         Y_ALIGN_TOP_DECIMAL, Y_ALIGN_CENTER_DECIMAL, Y_ALIGN_BASELINE_DECIMAL, Y_ALIGN_BOTTOM_DECIMAL,
     *         Y_ALIGN_TOP_RIGHT,   Y_ALIGN_CENTER_RIGHT,   Y_ALIGN_BASELINE_RIGHT,   Y_ALIGN_BOTTOM_RIGHT.
     * @param text: the text string to draw
     * 
     * @return YAPI_SUCCESS if the call succeeds.
     * 
     * On failure, throws an exception or returns a negative error code.
     */
    int             drawText(int x,int y,Y_ALIGN anchor,string text);

    /**
     * Draws a GIF image at the specified position. The GIF image must have been previously
     * uploaded to the device built-in memory. If you experience problems using an image
     * file, check the device logs for any error message such as missing image file or bad
     * image file format.
     * 
     * @param x: the distance from left of layer to the left of the image, in pixels
     * @param y: the distance from top of layer to the top of the image, in pixels
     * @param imagename: the GIF file name
     * 
     * @return YAPI_SUCCESS if the call succeeds.
     * 
     * On failure, throws an exception or returns a negative error code.
     */
    int             drawImage(int x,int y,string imagename);

    /**
     * Draws a bitmap at the specified position. The bitmap is provided as a binary object,
     * where each pixel maps to a bit, from left to right and from top to bottom.
     * The most significant bit of each byte maps to the leftmost pixel, and the least
     * significant bit maps to the rightmost pixel. Bits set to 1 are drawn using the
     * layer selected pen color. Bits set to 0 are drawn using the specified background
     * gray level, unless -1 is specified, in which case they are not drawn at all
     * (as if transparent).
     * 
     * @param x: the distance from left of layer to the left of the bitmap, in pixels
     * @param y: the distance from top of layer to the top of the bitmap, in pixels
     * @param w: the width of the bitmap, in pixels
     * @param bitmap: a binary object
     * @param bgcol: the background gray level to use for zero bits (0 = black,
     *         255 = white), or -1 to leave the pixels unchanged
     * 
     * @return YAPI_SUCCESS if the call succeeds.
     * 
     * On failure, throws an exception or returns a negative error code.
     */
    int             drawBitmap(int x,int y,int w,string bitmap,int bgcol);

    /**
     * Moves the drawing pointer of this layer to the specified position.
     * 
     * @param x: the distance from left of layer, in pixels
     * @param y: the distance from top of layer, in pixels
     * 
     * @return YAPI_SUCCESS if the call succeeds.
     * 
     * On failure, throws an exception or returns a negative error code.
     */
    int             moveTo(int x,int y);

    /**
     * Draws a line from current drawing pointer position to the specified position.
     * The specified destination pixel is included in the line. The pointer position
     * is then moved to the end point of the line.
     * 
     * @param x: the distance from left of layer to the end point of the line, in pixels
     * @param y: the distance from top of layer to the end point of the line, in pixels
     * 
     * @return YAPI_SUCCESS if the call succeeds.
     * 
     * On failure, throws an exception or returns a negative error code.
     */
    int             lineTo(int x,int y);

    /**
     * Outputs a message in the console area, and advances the console pointer accordingly.
     * The console pointer position is automatically moved to the beginning
     * of the next line when a newline character is met, or when the right margin
     * is hit. When the new text to display extends below the lower margin, the
     * console area is automatically scrolled up.
     * 
     * @param text: the message to display
     * 
     * @return YAPI_SUCCESS if the call succeeds.
     * 
     * On failure, throws an exception or returns a negative error code.
     */
    int             consoleOut(string text);

    /**
     * Sets up display margins for the consoleOut function.
     * 
     * @param x1: the distance from left of layer to the left margin, in pixels
     * @param y1: the distance from top of layer to the top margin, in pixels
     * @param x2: the distance from left of layer to the right margin, in pixels
     * @param y2: the distance from top of layer to the bottom margin, in pixels
     * 
     * @return YAPI_SUCCESS if the call succeeds.
     * 
     * On failure, throws an exception or returns a negative error code.
     */
    int             setConsoleMargins(int x1,int y1,int x2,int y2);

    /**
     * Sets up the background color used by the clearConsole function and by
     * the console scrolling feature.
     * 
     * @param bgcol: the background gray level to use when scrolling (0 = black,
     *         255 = white), or -1 for transparent
     * 
     * @return YAPI_SUCCESS if the call succeeds.
     * 
     * On failure, throws an exception or returns a negative error code.
     */
    int             setConsoleBackground(int bgcol);

    /**
     * Sets up the wrapping behaviour used by the consoleOut function.
     * 
     * @param wordwrap: true to wrap only between words,
     *         false to wrap on the last column anyway.
     * 
     * @return YAPI_SUCCESS if the call succeeds.
     * 
     * On failure, throws an exception or returns a negative error code.
     */
    int             setConsoleWordWrap(bool wordwrap);

    /**
     * Blanks the console area within console margins, and resets the console pointer
     * to the upper left corner of the console.
     * 
     * @return YAPI_SUCCESS if the call succeeds.
     * 
     * On failure, throws an exception or returns a negative error code.
     */
    int             clearConsole();

    /**
     * Sets the position of the layer relative to the display upper left corner.
     * When smooth scrolling is used, the display offset of the layer is
     * automatically updated during the next milliseconds to animate the move of the layer.
     * 
     * @param x: the distance from left of display to the upper left corner of the layer
     * @param y: the distance from top of display to the upper left corner of the layer
     * @param scrollTime: number of milliseconds to use for smooth scrolling, or
     *         0 if the scrolling should be immediate.
     * 
     * @return YAPI_SUCCESS if the call succeeds.
     * 
     * On failure, throws an exception or returns a negative error code.
     */
    int             setLayerPosition(int x,int y,int scrollTime);

    /**
     * Hides the layer. The state of the layer is perserved but the layer is not displayed
     * on the screen until the next call to unhide(). Hiding the layer can positively
     * affect the drawing speed, since it postpones the rendering until all operations are
     * completed (double-buffering).
     * 
     * @return YAPI_SUCCESS if the call succeeds.
     * 
     * On failure, throws an exception or returns a negative error code.
     */
    int             hide();

    /**
     * Shows the layer. Shows the layer again after a hide command.
     * 
     * @return YAPI_SUCCESS if the call succeeds.
     * 
     * On failure, throws an exception or returns a negative error code.
     */
    int             unhide();

    /**
     * Gets parent YDisplay. Returns the parent YDisplay object of the current YDisplayLayer.
     * 
     * @return an YDisplay object
     */
    YDisplay*             get_display();

    /**
     * Returns the display width, in pixels.
     * 
     * @return an integer corresponding to the display width, in pixels
     * 
     * On failure, throws an exception or returns Y_DISPLAYWIDTH_INVALID.
     */
    int             get_displayWidth();

    /**
     * Returns the display height, in pixels.
     * 
     * @return an integer corresponding to the display height, in pixels
     * 
     * On failure, throws an exception or returns Y_DISPLAYHEIGHT_INVALID.
     */
    int             get_displayHeight();

    /**
     * Returns the width of the layers to draw on, in pixels.
     * 
     * @return an integer corresponding to the width of the layers to draw on, in pixels
     * 
     * On failure, throws an exception or returns Y_LAYERWIDTH_INVALID.
     */
    int             get_layerWidth();

    /**
     * Returns the height of the layers to draw on, in pixels.
     * 
     * @return an integer corresponding to the height of the layers to draw on, in pixels
     * 
     * On failure, throws an exception or returns Y_LAYERHEIGHT_INVALID.
     */
    int             get_layerHeight();

    int             resetHiddenFlag();

    //--- (end of generated code: YDisplayLayer accessors declaration)
    int drawBitmap(int x,int y,int w,const std::vector<unsigned char>& data,int bgcol);
};


//--- (generated code: YDisplay declaration)
/**
 * YDisplay Class: Display function interface
 * 
 * Yoctopuce display interface has been designed to easily
 * show information and images. The device provides built-in
 * multi-layer rendering. Layers can be drawn offline, individually,
 * and freely moved on the display. It can also replay recorded
 * sequences (animations).
 */
class YDisplay: public YFunction {
protected:
    // Attributes (function value cache)
    YDisplayUpdateCallback _callback;
    string          _logicalName;
    string          _advertisedValue;
    Y_POWERSTATE_enum _powerState;
    string          _startupSeq;
    int             _brightness;
    Y_ORIENTATION_enum _orientation;
    unsigned        _displayWidth;
    unsigned        _displayHeight;
    Y_DISPLAYTYPE_enum _displayType;
    unsigned        _layerWidth;
    unsigned        _layerHeight;
    unsigned        _layerCount;
    string          _command;
    // Static function object cache
    static std::map<string,YDisplay*> _DisplayCache;

    friend YDisplay *yFindDisplay(const string& func);
    friend YDisplay *yFirstDisplay(void);

    // Function-specific method for parsing of JSON output and caching result
    int             _parse(yJsonStateMachine& j);
    //--- (end of generated code: YDisplay declaration)
    vector<YDisplayLayer*>  _allDisplayLayers;
    bool                    _recording;
    string                  _sequence;

    
    

    //--- (generated code: YDisplay constructor)
    // Constructor is protected, use yFindDisplay factory function to instantiate
    YDisplay(const string& func): YFunction("Display", func)
    //--- (end of generated code: YDisplay constructor)
    //--- (generated code: Display initialization)
            ,_callback(NULL)
            ,_logicalName(Y_LOGICALNAME_INVALID)
            ,_advertisedValue(Y_ADVERTISEDVALUE_INVALID)
            ,_powerState(Y_POWERSTATE_INVALID)
            ,_startupSeq(Y_STARTUPSEQ_INVALID)
            ,_brightness(Y_BRIGHTNESS_INVALID)
            ,_orientation(Y_ORIENTATION_INVALID)
            ,_displayWidth(Y_DISPLAYWIDTH_INVALID)
            ,_displayHeight(Y_DISPLAYHEIGHT_INVALID)
            ,_displayType(Y_DISPLAYTYPE_INVALID)
            ,_layerWidth(Y_LAYERWIDTH_INVALID)
            ,_layerHeight(Y_LAYERHEIGHT_INVALID)
            ,_layerCount(Y_LAYERCOUNT_INVALID)
            ,_command(Y_COMMAND_INVALID)
    //--- (end of generated code: Display initialization)
            ,_allDisplayLayers(0)
            ,_recording(false)
            ,_sequence("")
    {};
public:
    //--- (generated code: YDisplay accessors declaration)

    static const string LOGICALNAME_INVALID;
    static const string ADVERTISEDVALUE_INVALID;
    static const Y_POWERSTATE_enum POWERSTATE_OFF = Y_POWERSTATE_OFF;
    static const Y_POWERSTATE_enum POWERSTATE_ON = Y_POWERSTATE_ON;
    static const Y_POWERSTATE_enum POWERSTATE_INVALID = Y_POWERSTATE_INVALID;
    static const string STARTUPSEQ_INVALID;
    static const int      BRIGHTNESS_INVALID = -1;
    static const Y_ORIENTATION_enum ORIENTATION_LEFT = Y_ORIENTATION_LEFT;
    static const Y_ORIENTATION_enum ORIENTATION_UP = Y_ORIENTATION_UP;
    static const Y_ORIENTATION_enum ORIENTATION_RIGHT = Y_ORIENTATION_RIGHT;
    static const Y_ORIENTATION_enum ORIENTATION_DOWN = Y_ORIENTATION_DOWN;
    static const Y_ORIENTATION_enum ORIENTATION_INVALID = Y_ORIENTATION_INVALID;
    static const unsigned DISPLAYWIDTH_INVALID = 0xffffffff;
    static const unsigned DISPLAYHEIGHT_INVALID = 0xffffffff;
    static const Y_DISPLAYTYPE_enum DISPLAYTYPE_MONO = Y_DISPLAYTYPE_MONO;
    static const Y_DISPLAYTYPE_enum DISPLAYTYPE_GRAY = Y_DISPLAYTYPE_GRAY;
    static const Y_DISPLAYTYPE_enum DISPLAYTYPE_RGB = Y_DISPLAYTYPE_RGB;
    static const Y_DISPLAYTYPE_enum DISPLAYTYPE_INVALID = Y_DISPLAYTYPE_INVALID;
    static const unsigned LAYERWIDTH_INVALID = 0xffffffff;
    static const unsigned LAYERHEIGHT_INVALID = 0xffffffff;
    static const unsigned LAYERCOUNT_INVALID = 0xffffffff;
    static const string COMMAND_INVALID;

    /**
     * Returns the logical name of the display.
     * 
     * @return a string corresponding to the logical name of the display
     * 
     * On failure, throws an exception or returns Y_LOGICALNAME_INVALID.
     */
           string          get_logicalName(void);
    inline string          logicalName(void)
    { return this->get_logicalName(); }

    /**
     * Changes the logical name of the display. You can use yCheckLogicalName()
     * prior to this call to make sure that your parameter is valid.
     * Remember to call the saveToFlash() method of the module if the
     * modification must be kept.
     * 
     * @param newval : a string corresponding to the logical name of the display
     * 
     * @return YAPI_SUCCESS if the call succeeds.
     * 
     * On failure, throws an exception or returns a negative error code.
     */
    int             set_logicalName(const string& newval);
    inline int      setLogicalName(const string& newval)
    { return this->set_logicalName(newval); }

    /**
     * Returns the current value of the display (no more than 6 characters).
     * 
     * @return a string corresponding to the current value of the display (no more than 6 characters)
     * 
     * On failure, throws an exception or returns Y_ADVERTISEDVALUE_INVALID.
     */
           string          get_advertisedValue(void);
    inline string          advertisedValue(void)
    { return this->get_advertisedValue(); }

    /**
     * Returns the power state of the display.
     * 
     * @return either Y_POWERSTATE_OFF or Y_POWERSTATE_ON, according to the power state of the display
     * 
     * On failure, throws an exception or returns Y_POWERSTATE_INVALID.
     */
           Y_POWERSTATE_enum get_powerState(void);
    inline Y_POWERSTATE_enum powerState(void)
    { return this->get_powerState(); }

    /**
     * Changes the power state of the display.
     * 
     * @param newval : either Y_POWERSTATE_OFF or Y_POWERSTATE_ON, according to the power state of the display
     * 
     * @return YAPI_SUCCESS if the call succeeds.
     * 
     * On failure, throws an exception or returns a negative error code.
     */
    int             set_powerState(Y_POWERSTATE_enum newval);
    inline int      setPowerState(Y_POWERSTATE_enum newval)
    { return this->set_powerState(newval); }

    /**
     * Returns the name of the sequence to play when the displayed is powered on.
     * 
     * @return a string corresponding to the name of the sequence to play when the displayed is powered on
     * 
     * On failure, throws an exception or returns Y_STARTUPSEQ_INVALID.
     */
           string          get_startupSeq(void);
    inline string          startupSeq(void)
    { return this->get_startupSeq(); }

    /**
     * Changes the name of the sequence to play when the displayed is powered on.
     * Remember to call the saveToFlash() method of the module if the
     * modification must be kept.
     * 
     * @param newval : a string corresponding to the name of the sequence to play when the displayed is powered on
     * 
     * @return YAPI_SUCCESS if the call succeeds.
     * 
     * On failure, throws an exception or returns a negative error code.
     */
    int             set_startupSeq(const string& newval);
    inline int      setStartupSeq(const string& newval)
    { return this->set_startupSeq(newval); }

    /**
     * Returns the luminosity of the  module informative leds (from 0 to 100).
     * 
     * @return an integer corresponding to the luminosity of the  module informative leds (from 0 to 100)
     * 
     * On failure, throws an exception or returns Y_BRIGHTNESS_INVALID.
     */
           int             get_brightness(void);
    inline int             brightness(void)
    { return this->get_brightness(); }

    /**
     * Changes the brightness of the display. The parameter is a value between 0 and
     * 100. Remember to call the saveToFlash() method of the module if the
     * modification must be kept.
     * 
     * @param newval : an integer corresponding to the brightness of the display
     * 
     * @return YAPI_SUCCESS if the call succeeds.
     * 
     * On failure, throws an exception or returns a negative error code.
     */
    int             set_brightness(int newval);
    inline int      setBrightness(int newval)
    { return this->set_brightness(newval); }

    /**
     * Returns the currently selected display orientation.
     * 
     * @return a value among Y_ORIENTATION_LEFT, Y_ORIENTATION_UP, Y_ORIENTATION_RIGHT and
     * Y_ORIENTATION_DOWN corresponding to the currently selected display orientation
     * 
     * On failure, throws an exception or returns Y_ORIENTATION_INVALID.
     */
           Y_ORIENTATION_enum get_orientation(void);
    inline Y_ORIENTATION_enum orientation(void)
    { return this->get_orientation(); }

    /**
     * Changes the display orientation. Remember to call the saveToFlash()
     * method of the module if the modification must be kept.
     * 
     * @param newval : a value among Y_ORIENTATION_LEFT, Y_ORIENTATION_UP, Y_ORIENTATION_RIGHT and
     * Y_ORIENTATION_DOWN corresponding to the display orientation
     * 
     * @return YAPI_SUCCESS if the call succeeds.
     * 
     * On failure, throws an exception or returns a negative error code.
     */
    int             set_orientation(Y_ORIENTATION_enum newval);
    inline int      setOrientation(Y_ORIENTATION_enum newval)
    { return this->set_orientation(newval); }

    /**
     * Returns the display width, in pixels.
     * 
     * @return an integer corresponding to the display width, in pixels
     * 
     * On failure, throws an exception or returns Y_DISPLAYWIDTH_INVALID.
     */
           unsigned        get_displayWidth(void);
    inline unsigned        displayWidth(void)
    { return this->get_displayWidth(); }

    /**
     * Returns the display height, in pixels.
     * 
     * @return an integer corresponding to the display height, in pixels
     * 
     * On failure, throws an exception or returns Y_DISPLAYHEIGHT_INVALID.
     */
           unsigned        get_displayHeight(void);
    inline unsigned        displayHeight(void)
    { return this->get_displayHeight(); }

    /**
     * Returns the display type: monochrome, gray levels or full color.
     * 
     * @return a value among Y_DISPLAYTYPE_MONO, Y_DISPLAYTYPE_GRAY and Y_DISPLAYTYPE_RGB corresponding to
     * the display type: monochrome, gray levels or full color
     * 
     * On failure, throws an exception or returns Y_DISPLAYTYPE_INVALID.
     */
           Y_DISPLAYTYPE_enum get_displayType(void);
    inline Y_DISPLAYTYPE_enum displayType(void)
    { return this->get_displayType(); }

    /**
     * Returns the width of the layers to draw on, in pixels.
     * 
     * @return an integer corresponding to the width of the layers to draw on, in pixels
     * 
     * On failure, throws an exception or returns Y_LAYERWIDTH_INVALID.
     */
           unsigned        get_layerWidth(void);
    inline unsigned        layerWidth(void)
    { return this->get_layerWidth(); }

    /**
     * Returns the height of the layers to draw on, in pixels.
     * 
     * @return an integer corresponding to the height of the layers to draw on, in pixels
     * 
     * On failure, throws an exception or returns Y_LAYERHEIGHT_INVALID.
     */
           unsigned        get_layerHeight(void);
    inline unsigned        layerHeight(void)
    { return this->get_layerHeight(); }

    /**
     * Returns the number of available layers to draw on.
     * 
     * @return an integer corresponding to the number of available layers to draw on
     * 
     * On failure, throws an exception or returns Y_LAYERCOUNT_INVALID.
     */
           unsigned        get_layerCount(void);
    inline unsigned        layerCount(void)
    { return this->get_layerCount(); }

           string          get_command(void);
    inline string          command(void)
    { return this->get_command(); }

    int             set_command(const string& newval);
    inline int      setCommand(const string& newval)
    { return this->set_command(newval); }

    /**
     * Clears the display screen and resets all display layers to their default state.
     * 
     * @return YAPI_SUCCESS if the call succeeds.
     * 
     * On failure, throws an exception or returns a negative error code.
     */
    int             resetAll();

    /**
     * Smoothly changes the brightness of the screen to produce a fade-in or fade-out
     * effect.
     * 
     * @param brightness: the new screen brightness
     * @param duration: duration of the brightness transition, in milliseconds.
     * 
     * @return YAPI_SUCCESS if the call succeeds.
     * 
     * On failure, throws an exception or returns a negative error code.
     */
    int             fade(int brightness,int duration);

    /**
     * Starts to record all display commands into a sequence, for later replay.
     * The name used to store the sequence is specified when calling
     * saveSequence(), once the recording is complete.
     * 
     * @return YAPI_SUCCESS if the call succeeds.
     * 
     * On failure, throws an exception or returns a negative error code.
     */
    int             newSequence();

    /**
     * Stops recording display commands and saves the sequence into the specified
     * file on the display internal memory. The sequence can be later replayed
     * using playSequence().
     * 
     * @param sequenceName : the name of the newly created sequence
     * 
     * @return YAPI_SUCCESS if the call succeeds.
     * 
     * On failure, throws an exception or returns a negative error code.
     */
    int             saveSequence(string sequenceName);

    /**
     * Replays a display sequence previously recorded using
     * newSequence() and saveSequence().
     * 
     * @param sequenceName : the name of the newly created sequence
     * 
     * @return YAPI_SUCCESS if the call succeeds.
     * 
     * On failure, throws an exception or returns a negative error code.
     */
    int             playSequence(string sequenceName);

    /**
     * Waits for a specified delay (in milliseconds) before playing next
     * commands in current sequence. This method can be used while
     * recording a display sequence, to insert a timed wait in the sequence
     * (without any immediate effect). It can also be used dynamically while
     * playing a pre-recorded sequence, to suspend or resume the execution of
     * the sequence. To cancel a delay, call the same method with a zero delay.
     * 
     * @param delay_ms : the duration to wait, in milliseconds
     * 
     * @return YAPI_SUCCESS if the call succeeds.
     * 
     * On failure, throws an exception or returns a negative error code.
     */
    int             pauseSequence(int delay_ms);

    /**
     * Stops immediately any ongoing sequence replay.
     * The display is left as is.
     * 
     * @return YAPI_SUCCESS if the call succeeds.
     * 
     * On failure, throws an exception or returns a negative error code.
     */
    int             stopSequence();

    /**
     * Uploads an arbitrary file (for instance a GIF file) to the display, to the
     * specified full path name. If a file already exists with the same path name,
     * its content is overwritten.
     * 
     * @param pathname : path and name of the new file to create
     * @param content : binary buffer with the content to set
     * 
     * @return YAPI_SUCCESS if the call succeeds.
     * 
     * On failure, throws an exception or returns a negative error code.
     */
    int             upload(string pathname,string content);

    /**
     * Copies the whole content of a layer to another layer. The color and transparency
     * of all the pixels from the destination layer are set to match the source pixels.
     * This method only affects the displayed content, but does not change any
     * property of the layer object.
     * Note that layer 0 has no transparency support (it is always completely opaque).
     * 
     * @param srcLayerId : the identifier of the source layer (a number in range 0..layerCount-1)
     * @param dstLayerId : the identifier of the destination layer (a number in range 0..layerCount-1)
     * 
     * @return YAPI_SUCCESS if the call succeeds.
     * 
     * On failure, throws an exception or returns a negative error code.
     */
    int             copyLayerContent(int srcLayerId,int dstLayerId);

    /**
     * Swaps the whole content of two layers. The color and transparency of all the pixels from
     * the two layers are swapped. This method only affects the displayed content, but does
     * not change any property of the layer objects. In particular, the visibility of each
     * layer stays unchanged. When used between onae hidden layer and a visible layer,
     * this method makes it possible to easily implement double-buffering.
     * Note that layer 0 has no transparency support (it is always completely opaque).
     * 
     * @param layerIdA : the first layer (a number in range 0..layerCount-1)
     * @param layerIdB : the second layer (a number in range 0..layerCount-1)
     * 
     * @return YAPI_SUCCESS if the call succeeds.
     * 
     * On failure, throws an exception or returns a negative error code.
     */
    int             swapLayerContent(int layerIdA,int layerIdB);


    /**
     * Registers the callback function that is invoked on every change of advertised value.
     * The callback is invoked only during the execution of ySleep or yHandleEvents.
     * This provides control over the time when the callback is triggered. For good responsiveness, remember to call
     * one of these two functions periodically. To unregister a callback, pass a null pointer as argument.
     * 
     * @param callback : the callback function to call, or a null pointer. The callback function should take two
     *         arguments: the function object of which the value has changed, and the character string describing
     *         the new advertised value.
     * @noreturn
     */
    void registerValueCallback(YDisplayUpdateCallback callback);

    void advertiseValue(const string& value);

    /**
     * Continues the enumeration of displays started using yFirstDisplay().
     * 
     * @return a pointer to a YDisplay object, corresponding to
     *         a display currently online, or a null pointer
     *         if there are no more displays to enumerate.
     */
           YDisplay        *nextDisplay(void);
    inline YDisplay        *next(void)
    { return this->nextDisplay();}

    /**
     * Retrieves a display for a given identifier.
     * The identifier can be specified using several formats:
     * <ul>
     * <li>FunctionLogicalName</li>
     * <li>ModuleSerialNumber.FunctionIdentifier</li>
     * <li>ModuleSerialNumber.FunctionLogicalName</li>
     * <li>ModuleLogicalName.FunctionIdentifier</li>
     * <li>ModuleLogicalName.FunctionLogicalName</li>
     * </ul>
     * 
     * This function does not require that the display is online at the time
     * it is invoked. The returned object is nevertheless valid.
     * Use the method YDisplay.isOnline() to test if the display is
     * indeed online at a given time. In case of ambiguity when looking for
     * a display by logical name, no error is notified: the first instance
     * found is returned. The search is performed first by hardware name,
     * then by logical name.
     * 
     * @param func : a string that uniquely characterizes the display
     * 
     * @return a YDisplay object allowing you to drive the display.
     */
           static YDisplay* FindDisplay(const string& func);
    inline static YDisplay* Find(const string& func)
    { return YDisplay::FindDisplay(func);}
    /**
     * Starts the enumeration of displays currently accessible.
     * Use the method YDisplay.nextDisplay() to iterate on
     * next displays.
     * 
     * @return a pointer to a YDisplay object, corresponding to
     *         the first display currently online, or a null pointer
     *         if there are none.
     */
           static YDisplay* FirstDisplay(void);
    inline static YDisplay* First(void)
    { return YDisplay::FirstDisplay();}
    //--- (end of generated code: YDisplay accessors declaration)

    
    
    
    
    /**
     * Returns a YDisplayLayer object that can be used to draw on the specified
     * layer. The content is displayed only when the layer is active on the
     * screen (and not masked by other overlapping layers).
     * 
     * @param layerId : the identifier of the layer (a number in range 0..layerCount-1)
     * 
     * @return an YDisplayLayer object
     * 
     * On failure, throws an exception or returns null.
     */
    YDisplayLayer* get_displayLayer(unsigned layerId);
    
      
    /**
     * Force a flush of all commands buffered by all layers.
     *
     * @return YAPI_SUCCESS if the call succeeds.
     *
     * On failure, throws an exception or returns a negative error code.
     */
    int flushLayers(void);
    
    /**
     * Add a given command string to the currently recorded display sequence
     *
     * @return YAPI_SUCCESS if the call succeeds.
     *
     * On failure, throws an exception or returns a negative error code.
     */
    int sendCommand(string cmd);
    
    // internal function to clear hidden flag during resetAll
    void resetHiddenLayerFlags(void);
};

//--- (generated code: Display functions declaration)

/**
 * Retrieves a display for a given identifier.
 * The identifier can be specified using several formats:
 * <ul>
 * <li>FunctionLogicalName</li>
 * <li>ModuleSerialNumber.FunctionIdentifier</li>
 * <li>ModuleSerialNumber.FunctionLogicalName</li>
 * <li>ModuleLogicalName.FunctionIdentifier</li>
 * <li>ModuleLogicalName.FunctionLogicalName</li>
 * </ul>
 * 
 * This function does not require that the display is online at the time
 * it is invoked. The returned object is nevertheless valid.
 * Use the method YDisplay.isOnline() to test if the display is
 * indeed online at a given time. In case of ambiguity when looking for
 * a display by logical name, no error is notified: the first instance
 * found is returned. The search is performed first by hardware name,
 * then by logical name.
 * 
 * @param func : a string that uniquely characterizes the display
 * 
 * @return a YDisplay object allowing you to drive the display.
 */
inline YDisplay* yFindDisplay(const string& func)
{ return YDisplay::FindDisplay(func);}
/**
 * Starts the enumeration of displays currently accessible.
 * Use the method YDisplay.nextDisplay() to iterate on
 * next displays.
 * 
 * @return a pointer to a YDisplay object, corresponding to
 *         the first display currently online, or a null pointer
 *         if there are none.
 */
inline YDisplay* yFirstDisplay(void)
{ return YDisplay::FirstDisplay();}

//--- (end of generated code: Display functions declaration)

#endif
