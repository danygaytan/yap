#ifndef GLOBAL
#define GLOBAL
#include <string>
#include <vector>

struct Message {
    std::string content;
    std::string sender;
};

struct ConversationContact {
    std::string username;
    std::string status; // Temporary, I will change this type later
};

struct Conversation {
    std::vector<Message> message_list;
    ConversationContact contact;
};

struct User {
    std::string username;
};

struct AppState {
    Conversation active_conversation;
    User app_user;
};
#endif