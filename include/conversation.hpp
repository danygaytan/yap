#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/screen/string.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/dom/elements.hpp>
#include "message.hpp"
#include "global.hpp"
#include <memory>

using namespace ftxui;

class ConversationComponent: public ComponentBase, std::enable_shared_from_this<ConversationComponent> {
private:
    std::shared_ptr<std::vector<Message>> active_conversation; // pointer of global active_conversation
    Elements message_component_list;
public:
    ConversationComponent(std::shared_ptr<std::vector<Message>> active_conversation);
    Element OnRender();
    void AddNewMessage(std::string message);
    virtual bool OnEvent(Event);
}; 