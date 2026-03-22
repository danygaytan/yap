#include <boost/smart_ptr/shared_ptr.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/string.hpp>

class MessageComponent {

private:
    std::string content;
    std::string sender_username;
public:
    MessageComponent();
};