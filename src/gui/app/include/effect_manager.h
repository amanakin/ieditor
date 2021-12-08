#ifndef EFFECT_MANAGER_HEADER
#define EFFECT_MANAGER_HEADER

#include <effect.h>

struct EffectManager {
    EffectManager();
    ~EffectManager();

    void addEffect(Effect* effect);

private:
    std::vector<Effect*> effects;
};

#endif // EFFECT_MANAGER_HEADER
