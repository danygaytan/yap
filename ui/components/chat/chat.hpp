#include "header/contact.hpp"
#include "header/menu.hpp"
#include "header/billboard.hpp"
#include "feed/conversation.hpp"
#include "footer/input.hpp"
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
    std::string contact_username;
    std::string server_handler;
public:
    Chat(std::string contact_username, std::string server_handler);
    void start();
};