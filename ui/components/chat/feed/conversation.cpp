#include "conversation.hpp"

ConversationComponent::ConversationComponent(){};

Element ConversationComponent::OnRender() {
        auto flexbox_config = FlexboxConfig{};
        flexbox_config.direction = ftxui::FlexboxConfig::Direction::Column;
        auto flexbox = ftxui::flexbox(this->messages, flexbox_config) | border | flex;
        return flexbox;   
    };