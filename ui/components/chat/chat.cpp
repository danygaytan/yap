#include "chat.hpp"

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
        Component conversation = std::make_shared<ConversationComponent>();

        // Footer or Input wrapper
        Component footer = std::make_shared<InputWrapperComponent>();

        Component chat_window = Container::Vertical({
            header,
            conversation,
            footer
        });

        ScreenInteractive screen = ScreenInteractive::Fullscreen();
        screen.Loop(chat_window);
    };