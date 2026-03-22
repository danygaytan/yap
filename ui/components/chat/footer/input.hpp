#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/string.hpp>
#include <memory>

using namespace ftxui;

class InputWrapperComponent: public ComponentBase, std::enable_shared_from_this<ComponentBase> {
private:
    std::string message_input;
    Component text_input_component;
public:
    InputWrapperComponent();
    Element OnRender();
}; 