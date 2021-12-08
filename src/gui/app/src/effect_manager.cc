// effect_manager.cc

#include <effect_manager.h>
#include <selector.h>

EffectManager::EffectManager()
{}

EffectManager::~EffectManager() {
    for (auto& effect: effects) {
        delete effect;
    }
}

void EffectManager::addEffect(Effect* effect) {
    effects.push_back(effect);
    
    App::getApp()->appWidget->effectsSelector->AddSelectorButton(
        [effect](){
            effect->apply(*App::getApp()->layoutManager.getCurrLayout());
        }, 
        std::string(effect->getName())
    );
}
