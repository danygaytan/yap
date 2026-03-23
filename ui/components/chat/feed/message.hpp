#include <boost/smart_ptr/enable_shared_from_this.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/string.hpp>

using namespace ftxui;

class MessageComponent: public ComponentBase, std::enable_shared_from_this<ComponentBase>{

private:
    std::string content;
    std::string sender;
public:
    MessageComponent(std::string content, std::string sender);
    Element OnRender();
};