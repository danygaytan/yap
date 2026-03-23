#include "conversation.hpp"
#include "ftxui/dom/flexbox_config.hpp"

ConversationComponent::ConversationComponent(std::vector<std::string> messages){
    for(int i = 0; i < messages.size(); i++) {
        MessageComponent new_message(messages[i], "Daniel");
        this->messages.push_back(new_message.Render());
    }
};

Element ConversationComponent::OnRender() {
    auto flexbox_config = FlexboxConfig{};
    flexbox_config.direction = ftxui::FlexboxConfig::Direction::Column;
    flexbox_config.justify_content = ftxui::FlexboxConfig::JustifyContent::FlexEnd;
    auto flexbox = ftxui::flexbox(this->messages, flexbox_config) | border | flex;
    return flexbox;   
};