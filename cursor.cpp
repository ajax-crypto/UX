#include "cursor.hpp"

#ifdef _WIN32

ux::Cursor::Cursor(int t)
{
    switch(t)
    {
        case ux::Cursor::WAIT :
            cursor = LoadCursor(NULL, IDC_WAIT);
        break;
        case ux::Cursor::HAND :
            cursor = LoadCursor(NULL, IDC_HAND);
        break;
        case ux::Cursor::NORMAL :
            cursor = LoadCursor(NULL, IDC_ARROW);
        break;
        case ux::Cursor::TEXT :
            cursor = LoadCursor(NULL, IDC_IBEAM);
        break;
        //For more cursor options on Windows go here: http://msdn.microsoft.com/en-us/library/ms648391%28v=vs.85%29.aspx
    }
}

void ux::Cursor::set(const ux::WindowHandle& aWindowHandle) const
{
	SetClassLongPtr(aWindowHandle, GCLP_HCURSOR, reinterpret_cast<LONG_PTR>(cursor));
}

ux::Cursor::~Cursor()
{
	// Nothing to do for destructor : no memory has been allocated (shared ressource principle)
}

#elif __linux

ux::Cursor::Cursor(const ux::Cursor::TYPE t)
{
    display = XOpenDisplay(NULL);
    
    switch(t)
    {
        case ux::Cursor::WAIT:
            cursor = XCreateFontCursor(display, XC_watch);
        break;
        case ux::Cursor::HAND:
            cursor = XCreateFontCursor(display, XC_hand1);
        break;
        case ux::Cursor::NORMAL:
            cursor = XCreateFontCursor(display, XC_left_ptr);
        break;
        case ux::Cursor::TEXT:
            cursor = XCreateFontCursor(display, XC_xterm);
        break;
        // For more cursor options on Linux go here: http://www.tronche.com/gui/x/xlib/appendix/b/
    }
}

void ux::Cursor::set(const ux::WindowHandle& aWindowHandle) const
{
    XDefineCursor(display, aWindowHandle, cursor);
    XFlush(display);
}

ux::Cursor::~Cursor()
{
    XFreeCursor(display, cursor);
    delete display;
    display = NULL;
}

#else
    #error This OS is not yet supported by the cursor library.
#endif