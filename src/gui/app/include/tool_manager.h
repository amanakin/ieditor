#ifndef TOOL_MANAGER_HEADER
#define TOOL_MANAGER_HEADER

#include <widget.h>
#include <tool.h>

struct ToolManager {
    ToolManager();
    ~ToolManager();

    void addTool(Tool* tool, const std::string& name);

    Tool* currTool;

private:
    std::vector<Tool*> tools;
};

#endif // TOOL_MANAGER_HEADER
