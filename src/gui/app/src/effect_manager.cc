// effect_manager.cc

#include <effect_manager.h>
#include <selector.h>
#include <app.h>

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
            //auto plugin = dynamic_cast<Plugin*>(effect);
            //if (plugin!= nullptr) {
            //    plugin->pPlugin->show_settings();
            //    printf("showing settings\n");
            //    return;
            //}
            effect->apply(*App::getApp()->layoutManager.getCurrLayout());
        }, 
        std::string(effect->getName())
    );
}
