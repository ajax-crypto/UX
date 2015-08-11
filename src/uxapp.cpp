#include "..\include\uxapp.hpp"

namespace ux
{
    void UXApplication::draw()
    {
        target->clear();
        window->draw(target);
        target->display();
    }

    int UXApplication::run()
    {
        Event event ;
        while(1)
        {
            while(target->pollEvent(event))
            {
                //LOG("Got events...");
                if(event.type == Event::Resized)
                {
                    auto w = event.size.width, h = event.size.height ;
                    view.reset(FRect{0, 0, w, h});
                    target->setView(view);
                }
                window->handleEvents(event);

                if(event.type == Event::KeyPressed)
                    if(event.key.code == sf::Keyboard::Escape) {
                        target->close();
                        break;
                    }
            }
            if(GlobalDrawingStates::Redraw)
                draw();
            else
                std::this_thread::sleep_for(std::chrono::milliseconds{30});
            if(window->isClosed())
            {
                target->close();
                break;
            }
        }
        return EXIT_SUCCESS ;
    }
}
