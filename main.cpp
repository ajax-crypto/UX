#include "sux.hpp"
#include <string>
#include <cstdlib>
#include <sstream>

int main()
{
	using namespace sux ;

	std::vector<std::string> names = { "one", "two", "three", "four", "five", "six", "seven", "eight" };

	const int APP_WIDTH = 600, APP_HEIGHT = 400 ;
	SUXApp app("Addition demo", APP_WIDTH, APP_HEIGHT);
	SWindow w(APP_WIDTH, APP_HEIGHT);
	SButton b("Add", 100, 150, 100, 30);
	STextbox t1(100, 100, 100, 30), t2(250, 100, 100, 30);
	SLabel l("Result", 250, 150, 100, 30);
	SList list(100, 190, 100);
	SCheckbox c(50, 50, 35, 20);
	SRadio r(250, 190, 10);
	SSlider slide(150, 50, 70, 10, 0, 100);
	for(auto& item : names)
		list.addItem(item);

	// The event attached adds the two numbers from textbox and displays in label
	b.addEventListener(UXEvents::MouseButtonReleased,
	[&](const Event& event) {
		int a = std::atoi(t1.getString().c_str());
		int b = std::atoi(t2.getString().c_str());
		std::stringstream ss ;
		ss << (a + b);
		l.setString(ss.str());
	});

	list.setDropDown(true);

	// Adding event listener to get item selected from list
	list.addEventListener(UXEvents::ListItemSelected,
	[&](const Event& event) {
		std::stringstream ss ;
		ss << list.getSelectedItemIndex() ;
		l.setString("Selected item : " + ss.str()) ;
	});

	auto eid = c.addEventListener(UXEvents::CheckedStateChange,
	[&](const Event& event) {
		std::stringstream ss ;
		ss << std::boolalpha << c.isChecked() ;
		l.setString("Checkbox is checked? " + ss.str()) ;
	});

	slide.addEventListener(UXEvents::SliderValueChanged,
	[&](const Event& event) {
		std::stringstream ss ;
		ss << slide.getValue() ;
		l.setString("Slider value : " + ss.str()) ;
		if(slide.getValue() > 50)
            c.removeEventListener(eid);
	});

	// Change button style to color filled button
	b.makeButtonFilled(ColorProperty(Color(39, 165, 39), Color(39, 150, 39), Color(39, 134, 39)),
	                   ColorProperty(Color(240, 240, 240), Color(255, 255, 255), Color(255, 255, 255)));

	// Add components to window and add window to app
	w.add(&b);
	w.add(&t1);
	w.add(&t2);
	w.add(&l);
	w.add(&list);
	w.add(&c);
	w.add(&r);
	w.add(&slide);

	app.add(&w);
	app.draw();
	return app.run();
}
