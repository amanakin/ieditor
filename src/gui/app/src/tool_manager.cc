// tool.cc

#include <tool_manager.h>
#include <app.h>
#include <button.h>

ToolManager::ToolManager()
{}

ToolManager::~ToolManager() {
    for (auto& tool: tools) {
        delete tool;
    }
}

void ToolManager::addTool(Tool* tool, const std::string& name) {
    App::getApp()->appWidget->subWidgets.push_back(
        new AnimatedButtonRect(
        [this, tool]() {
            this->currTool = tool;
        },
        new FramesText(name, Color(132, 132, 168), Color(182, 182, 218),
                       Color(82, 82, 118), Colors::WHITE, Vector2f(200, 40), 30),
        Vector2f(200, 40),
        Vector2f(10, 700 + tools.size() * 40))
    );
    
    tools.push_back(tool);
}
