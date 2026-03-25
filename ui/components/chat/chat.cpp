#include "../../../../include/chat.hpp"
#include <memory>
#include <vector>

Chat::Chat(std::shared_ptr<AppState> app_state):
    app_state(app_state)
    {};

void Chat::start() {
        // Header
        Component billboard = std::make_shared<BillboardComponent>();
        Component contact = std::make_shared<Contact>(app_state->active_conversation.contact);
        Component menu = std::make_shared<MenuComponent>();
        Component header = Container::Horizontal({
            billboard | flex,
            contact | flex,
            menu | flex
        }) | xflex | border | size(HEIGHT, GREATER_THAN, 5);

        // Body or Chat feed
        auto dummy_message = Message({
            "This is a message",
            "Sender"
        });
        auto active_conversation_input = std::vector<Message>{dummy_message};
        auto active_conversation = std::make_shared<std::vector<Message>>(active_conversation_input);
        auto conversation = std::make_shared<ConversationComponent>(active_conversation);

        // Footer or Input wrapper
        Component footer = std::make_shared<InputWrapperComponent>();

        // Create Main window
        Component chat_window = Container::Vertical({
            header,
            conversation,
            footer
        });

        ScreenInteractive screen = ScreenInteractive::Fullscreen();
        screen.Loop(chat_window);
    };