#ifndef __UX_SCROLLABLE_
#define __UX_SCROLLABLE_

namespace ux
{
	class Scrollable
	{
	protected:
		struct
		{
			int startx, endx ;
			int starty, endy ;

			int lowx, highx ;
			int lowy, highy ;

			int incrx, incry ;
		} view ;

		int total_height ;
		int total_width ;

		Scrollable() {};
		Scrollable(const Scrollable&) = delete ;
		Scrollable(Scrollable&&) = default ;

		void setXLimits(int lx, int hx) { view.highx = hx; view.lowx = lx; }
		void setYLimits(int ly, int hy) { view.highy = hy; view.lowy = ly; }
		void incrementX(int x) { view.incrx = x; view.endx = view.startx + x; }
		void incrementY(int y) { view.incry = y; view.endy = view.starty + y; }

		void moveX(int);
		void moveY(int);

		void setY(int sy) { view.starty = view.lowy; moveY(sy); }
		void setX(int sx) { view.startx = view.lowx; moveX(sx); }

		virtual void generateTexture() = 0 ;

	public:
		virtual void smoothMove(int) = 0 ;
		virtual void coarseMove(int) = 0 ;

		int getStartY() const { return view.starty; }
		int getStartX() const { return view.startx; }
		int getEndX() const { return view.endx; }
		int getEndY() const { return view.endy; }
		int getTotalHeight() const { return total_height; }
		int getTotalWidth() const { return total_width; }
		int getVisibleHeight() const { return view.endy - view.starty; }
		int getVisibleWidth() const { return view.endx - view.startx; }
	};

	void Scrollable::moveX(int amount)
	{
		view.startx += amount ;
		view.endx = view.startx + view.incrx ;
		if(view.endx > view.highx)
		{
			view.endx = view.highx ;
			view.startx = view.endx - view.incrx ;
		}
		else
		if(view.startx < view.lowx)
		{
			view.startx = view.lowx ;
			view.endx = view.lowx + view.incrx ;
		}
	}

	void Scrollable::moveY(int amount)
	{
		view.starty += amount ;
		view.endy = view.starty + view.incry ;
		if(view.endy > view.highy)
		{
			view.endy = view.highy ;
			view.starty = view.endy - view.incry ;
		}
		else
		if(view.starty < view.lowy)
		{
			view.starty = view.lowy ;
			view.endy = view.lowy + view.incry ;
		}
	}
}

#endif
