// tool.cc

#include <tool_manager.h>
#include <app.h>
#include <button.h>
#include <brush.h>
#include <selector.h>

ToolManager::ToolManager() {
    currTool = new Brush;
    addTool(currTool);
}

ToolManager::~ToolManager() {
    for (auto& tool: tools) {
        delete tool;
    }
}

void ToolManager::addTool(Tool* tool) {
    tools.push_back(tool);
    
    App::getApp()->appWidget->toolsSelector->AddSelectorButton(
        [tool](){
            App::getApp()->toolManager->currTool = tool;
        }, 
        std::string(tool->getName())
    );
}
