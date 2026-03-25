#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/string.hpp>
#include <ftxui/dom/elements.hpp>
#include "global.hpp"
#include <memory>

using namespace ftxui;

class Contact: public ComponentBase, public std::enable_shared_from_this<ComponentBase> {
private:
    ConversationContact contact;

public:
    Contact(ConversationContact contact);
    Element OnRender();
};