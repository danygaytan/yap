#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/string.hpp>
#include "message.hpp"
#include <memory>

using namespace ftxui;

class ConversationComponent: public ComponentBase, std::enable_shared_from_this<ComponentBase> {
private:
    Elements messages; // coming from MessageComponent
public:
    ConversationComponent(std::vector<std::string> messages);
    Element OnRender();
    void AddNewMessage();

}; 