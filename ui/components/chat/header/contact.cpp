#include "contact.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/color.hpp"

Contact::Contact(std::string username, int status):
username(username),
status(status) 
{};

Element Contact::OnRender() {
    std::string username_with_server = username + " @ DGServer";
    auto username_element = text(username_with_server) | center;
    auto status_element = text("Online") | center | color(Color::Green); // placeholder
    auto vertical_box = vbox(username_element, status_element) | size(WIDTH, EQUAL, username_with_server.length() + 10 ) | borderStyled(Color::BlueLight) | center;

    return  vertical_box;
};