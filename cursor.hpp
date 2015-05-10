#ifndef STANDARCURSOR_HPP
#define STANDARCURSOR_HPP

#ifdef _WIN32
    #include <windows.h>
#elif __linux
    #include <X11/cursorfont.h>
    #include <X11/Xlib.h>
#else
    #error This OS is not yet supported by the cursor library.
#endif

namespace ux
{
	#ifdef _WIN32
		typedef HWND__* WindowHandle;
	#elif __linux
		typedef unsigned long WindowHandle;
	#endif

	class Cursor
    {
    private:
		#ifdef _WIN32 
			HCURSOR cursor; /*Type of the Cursor with Windows*/
		#else
			XID cursor;
			Display* display;
		#endif
    public:
        enum TYPE{ WAIT, TEXT, NORMAL, HAND /*,...*/ };
        Cursor(int t);
        void set(const WindowHandle& aWindowHandle) const;
        ~Cursor();
    };
}


#endif // STANDARCURSOR_HPP