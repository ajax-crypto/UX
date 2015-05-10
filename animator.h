#ifndef __UX_ANIMATOR__
#define __UX_ANIMATOR__

namespace ux
{
    template <typename> class Window;

    struct Animator
    {
        template <typename UIType> static bool Animate(Window<UIType>*);

        //static std::map<unsigned int, std::function<void()>> animations ;
    };

    template <typename UIType>
    bool Animator::Animate(Window<UIType>* window)
    {
        for(auto c : window->children)
        {
            for(auto& anim : c->animations)
                if(anim.running)
                    anim();
        }
    }

    class Animation
    {
        std::function<bool(bool)> anim_impl ;

    public:
        bool running, finished ;
        unsigned int duration ;

        Animation(std::function<bool(bool)>&& f)
        : running{false}, finished{false}, anim_impl{f} {}

        void operator()() {
            finished = anim_impl(running);
            running = !finished ;
        }

        void start() { running = true; }
        void stop() { running = false; }

    };
}

#endif // __UX_ANIMATOR__
