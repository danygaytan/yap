#include "ftxui/component/event.hpp"
#include "ftxui/dom/flexbox_config.hpp"
#include "../../../../include/conversation.hpp"

ConversationComponent::ConversationComponent(std::shared_ptr<std::vector<Message>> active_conversation):
active_conversation(active_conversation)
{};

Element ConversationComponent::OnRender() {
    auto flexbox_config = FlexboxConfig{};
    flexbox_config.direction = ftxui::FlexboxConfig::Direction::Column;
    flexbox_config.justify_content = ftxui::FlexboxConfig::JustifyContent::FlexEnd;
    auto flexbox = ftxui::flexbox(this->message_component_list, flexbox_config) | frame | border | flex;
    return flexbox;
};

bool ConversationComponent::OnEvent(Event event){
    if(event == Event::Custom) {
        for(int i = 0; i < active_conversation->size(); i++) {
            MessageComponent new_message(
                active_conversation->at(i).content,
                active_conversation->at(i).sender
            );
            this->message_component_list.push_back(new_message.Render());
        }
        return true;
    }
    return false;
};