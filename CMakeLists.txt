cmake_minimum_required(VERSION 3.14) # A safe version for FetchContent
project(TerminalChat)
include(FetchContent)
 
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
  GIT_TAG v6.1.9
)

FetchContent_Declare(boost
  GIT_REPOSITORY https://github.com/boostorg/beast
  GIT_TAG boost-1.90.0
)
 
FetchContent_MakeAvailable(ftxui)

set(Boost_NO_BOOST_CMAKE ON)
find_package(Boost REQUIRED)
 
add_executable(yap
yap.cpp
websocket.cpp
ui/components/chat/header/billboard.cpp
ui/components/chat/header/contact.cpp
ui/components/chat/header/menu.cpp
ui/components/chat/feed/conversation.cpp
ui/components/chat/footer/input.cpp
ui/components/chat/chat.cpp
)



target_link_libraries(yap
  PRIVATE ftxui::dom
  PRIVATE ftxui::screen
  PRIVATE ftxui::component
  PRIVATE Boost::boost
)

