#include "billboard.hpp"

BillboardComponent::BillboardComponent(){};
Element BillboardComponent::OnRender(){
    auto billboard_box = text("Billboard") | size(WIDTH, EQUAL, 25) | yflex | border;
    
    FlexboxConfig flexbox_config;
    flexbox_config.justify_content = ftxui::FlexboxConfig::JustifyContent::FlexStart;
    auto flexbox = ftxui::flexbox({billboard_box}, flexbox_config) | flex;
    return flexbox;
};