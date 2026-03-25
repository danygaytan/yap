#include "contact.hpp"
#include "menu.hpp"
#include "billboard.hpp"
#include "conversation.hpp"
#include "input.hpp"
#include <boost/smart_ptr/shared_ptr.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/string.hpp>
#include <memory>

class Chat {

private:
    std::shared_ptr<AppState> app_state;
public:
    Chat(std::shared_ptr<AppState> app_state);
    void start();
};