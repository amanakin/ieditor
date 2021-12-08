#ifndef EFFECT_HEADER
#define EFFECT_HEADER

#include <layout.h>

struct Effect {
    virtual ~Effect();

    virtual void apply(Layout& layout);

    virtual std::string_view getName() const;
};

#endif // EFFECT_HEADER
