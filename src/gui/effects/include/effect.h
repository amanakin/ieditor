#ifndef EFFECT_HEADER
#define EFFECT_HEADER

#include <layout.h>

struct Effect {
    virtual ~Effect();

    virtual void apply(Layout& layout);
};

#endif // EFFECT_HEADER
