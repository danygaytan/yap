#include "input.hpp"
#include <ftxui/component/component.hpp>
#include <ftxui/dom/flexbox_config.hpp>
#include <ftxui/dom/node.hpp>

InputWrapperComponent::InputWrapperComponent():
text_input_component(Input(&this->message_input, "Type something"))
{
    this->Add(this->text_input_component);
};

Element InputWrapperComponent::OnRender() {
        Elements elements{this->text_input_component->Render()};

        FlexboxConfig flexbox_config = FlexboxConfig{};
        flexbox_config.direction = ftxui::FlexboxConfig::Direction::Row;

        Element flexbox = ftxui::flexbox(elements, flexbox_config) | border | size(HEIGHT, EQUAL, 3);
        return flexbox;
    };