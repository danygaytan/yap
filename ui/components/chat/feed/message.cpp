#include "../../../../include/message.hpp"

MessageComponent::MessageComponent(std::string content, std::string sender):
content(content),
sender(sender)
{};

Element MessageComponent::OnRender() {
    Element message_header = text(this->sender + " says: ") | color(Color::Gold1);
    Element message_content = text(this->content);

    Elements elements{message_header, message_content};
    FlexboxConfig flexbox_config = FlexboxConfig{};
    flexbox_config.direction = ftxui::FlexboxConfig::Direction::Row;

    Element flexbox = ftxui::flexbox(elements, flexbox_config) | size(HEIGHT, EQUAL, 1);
    return flexbox;
};