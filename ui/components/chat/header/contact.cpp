#include "../../../../include/contact.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/color.hpp"

Contact::Contact(ConversationContact contact):
contact(contact) 
{};

Element Contact::OnRender() {
    std::string username_with_server = contact.username + " @ DGServer"; // placeholder, should be changed for correct server info
    auto username_element = text(username_with_server) | center;
    auto status_element = text(contact.status) | center | color(Color::Green); // placeholder
    auto vertical_box = vbox(username_element, status_element) | size(WIDTH, EQUAL, username_with_server.length() + 10 ) | borderStyled(Color::BlueLight) | center;

    return  vertical_box;
};