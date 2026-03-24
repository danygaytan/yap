#include "../../../../include/chat.hpp"
#include <memory>
#include <vector>

Chat::Chat(std::string contact_username, std::string server_handler):
    contact_username(contact_username),
    server_handler(server_handler)
    {};

void Chat::start() {
        // Header
        Component billboard = std::make_shared<BillboardComponent>();
        Component contact = std::make_shared<Contact>(contact_username, 1);
        Component menu = std::make_shared<MenuComponent>();
        Component header = Container::Horizontal({
            billboard | flex,
            contact | flex,
            menu | flex
        }) | xflex | border | size(HEIGHT, GREATER_THAN, 5);

        // Body or Chat feed
        std::vector<std::string> messages{"Hello!!!!", "Friendly ping!"};

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