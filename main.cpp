#define UX_DEBUG 1
#define FUNC_INFO 1
#define UX_LAYOUT_DEBUG 1
#define ELEMENT_PROPERTIES 1
#define RT 1

#include "include/sux.hpp"
#include "include/log.hpp"
#include <string>
#include <array>
#include <cstdlib>
#include <sstream>

enum Operation { ADD, SUB, MUL, DIV };

template <typename T>
class Calculator
{
    T val1, val2 ;
    Operation op ;
    bool first ;
    bool extracted ;

public:
    Calculator() : first{false}, extracted{false} {} ;

    void setVal(const std::string&);
    void setOperation(Operation o) { op = o; }
    void reset() { first = false; extracted = false; }
    std::string getResult() ;
    bool resultExtracted() const { return extracted; }
};

template <typename T>
void Calculator<T>::setVal(const std::string& str)
{
    std::string v1, v2 ;
    bool ops = false ;
    for(auto i = 0u; i < str.size(); ++i)
    {
        if(isdigit(str.at(i)) || str.at(i) == '.')
        {
            if(!ops)
                v1 += str.at(i);
            else
                v2 += str.at(i);
        }
        else
        {
            ops = true ;
            switch(str.at(i))
            {
                case '+': op = ADD; break ;
                case '-': op = SUB; break ;
                case '*': op = MUL; break ;
                case '/': op = DIV; break ;
            }
        }
    }

    std::istringstream in1{v1}, in2{v2};
    in1 >> val1 ;
    in2 >> val2 ;
}

template <typename T>
std::string Calculator<T>::getResult()
{
    T result ;
    extracted = true ;

    switch(op)
    {
    case ADD:
        result = val1 + val2 ;
        break;

    case SUB:
        result = val1 - val2 ;
        break;

    case MUL:
        result = val1 * val2 ;
        break;

    case DIV:
        if(val2 == 0)
            return "Cannot divide by 0";
        result = val1 / val2 ;
        break;
    }

    std::ostringstream out ;
    out << result ;

    return out.str();
}

enum ButtonType { NUMERIC, OPERATION, RESULT };

struct CalcButton
{
    sux::SButton button ;
    ButtonType type ;
    Operation op ;
};

int main()
{
    using namespace sux ;

    Calculator<float> calc ;

    ux::logger::logging = true ;

    const std::array<std::string, 16> names = {
        "1", "2", "3", "+",
        "4", "5", "6", "-",
        "7", "8", "9", "*",
        "0", "=", ".", "/" };

    Color colors[16] = {
        Color{69, 69, 69}, Color{69, 69, 69}, Color{69, 69, 69}, Color{0, 128, 128},
        Color{69, 69, 69}, Color{69, 69, 69}, Color{69, 69, 69}, Color{0, 128, 128},
        Color{69, 69, 69}, Color{69, 69, 69}, Color{69, 69, 69}, Color{0, 128, 128},
        Color{69, 69, 69}, Color{0, 128, 128}, Color{0, 128, 128}, Color{0, 128, 128} };

    Color fcolors[16] = {
        Color{128, 128, 128}, Color{128, 128, 128}, Color{128, 128, 128}, Color{128, 128, 0},
        Color{128, 128, 128}, Color{128, 128, 128}, Color{128, 128, 128}, Color{128, 128, 0},
        Color{128, 128, 128}, Color{128, 128, 128}, Color{128, 128, 128}, Color{128, 128, 0},
        Color{128, 128, 128}, Color{128, 128, 0}, Color{128, 128, 0}, Color{128, 128, 0} };

    const int APP_WIDTH = 300, APP_HEIGHT = 500 ;
    SUXApp app{"Grid Layout Demo", APP_WIDTH, APP_HEIGHT};
    SWindow w{APP_WIDTH, APP_HEIGHT};
    SBox layout{5, 4, 0, 0, APP_WIDTH, APP_HEIGHT};
    layout.merge(SBox::COLS, 0);

    ux::StyleData ob ;
    std::cout << "Size of class : " << sizeof(ob);

    ux::logger::logging = false;

    std::array<CalcButton, 16> buttons ;
    buttons[0].type = buttons[1].type = buttons[2].type = NUMERIC;
    buttons[4].type = buttons[5].type = buttons[6].type = NUMERIC;
    buttons[8].type = buttons[9].type = buttons[10].type = NUMERIC;
    buttons[12].type = buttons[14].type = NUMERIC;
    buttons[3].type = buttons[7].type = buttons[11].type = buttons[15].type = OPERATION ;
    buttons[3].op = ADD ;
    buttons[7].op = SUB ;
    buttons[11].op = MUL ;
    buttons[15].op = DIV ;
    buttons[13].type = RESULT;

    SLabel display{"", 0, 0, APP_WIDTH, 100};
    display.background(ux::RGB[ux::WHITE])
           .text("", ux::RGB[ux::BLACK], 40)
           .align(ux::RIGHT);

    for(unsigned int i = 0u; i < 16; ++i)
    {

        buttons[i].button.background(colors[i])
                         .text(names[i], ux::RGB[ux::BLACK])
                         .imbue_properties();
        //ux::log("Styling complete...\tAdding Callbacks");

        buttons[i].button.on(UXEvents::GainedFocus)
                  .animate(ux::SHAPE_COLOR)
                  .to(fcolors[i])
                  .speed(20)
                  .pack();

        buttons[i].button.on(UXEvents::LostFocus)
                  .animate(ux::SHAPE_COLOR)
                  .to(colors[i])
                  .speed(20)
                  .pack();

        buttons[i].button.on(UXEvents::MouseButtonPressed)
                  .animate(ux::TEXT_COLOR)
                  .to(ux::RGB[ux::WHITE])
                  .speed(2)
                  .pack();

        buttons[i].button.on(UXEvents::MouseButtonReleased)
                  .animate(ux::TEXT_COLOR)
                  .to(ux::RGB[ux::BLACK])
                  .speed(2)
                  .pack();

        buttons[i].button.addEventListener(UXEvents::MouseButtonReleased,
            [&](unsigned index) mutable {
                return [index, &display, &names, &buttons, &calc](Event const&) mutable {
                    switch(buttons[index].type)
                    {
                    case NUMERIC:
                        if(calc.resultExtracted())
                            calc.reset();
                        display.m_style.m_content.m_text += names[index];
                    break;

                    case OPERATION:
                        calc.setOperation(buttons[index].op);
                        display.m_style.m_content.m_text += names[index];
                    break;

                    case RESULT:
                        calc.setVal(display.m_style.m_content.m_text);
                        std::string res = calc.getResult();
                        if(res == "Cannot divide by 0")
                            display.m_style.m_content.m_font_size = 30;
                        else
                            display.m_style.m_content.m_font_size = 40;
                        display.m_style.m_content.m_text = res;
                    break ;
                    }
                    display.imbue_properties();
                };
            }(i)
        );
       layout.add(i + 1, &buttons[i].button);
    }

    layout.add(0, &display);
    layout.pack();
    //ux::log("Layout packed !!!");
    w.add(&layout);
    app.add(&w);
    //ux::log("Added to window");
    app.draw();
    return app.run();
}
