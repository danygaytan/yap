#include "menu.hpp"
#include <ftxui/dom/direction.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/flexbox_config.hpp>

MenuComponent::MenuComponent(){};

Element MenuComponent::OnRender(){
    auto menu_box = text("Menu") | size(WIDTH, EQUAL, 25) | yflex | border;
    FlexboxConfig flexbox_config;
    flexbox_config.justify_content = ftxui::FlexboxConfig::JustifyContent::FlexEnd;
    auto flexbox = ftxui::flexbox({menu_box}, flexbox_config) | flex;
    return flexbox;
};