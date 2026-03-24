#include "include/websocket.hpp"
#include "include/chat.hpp"
#include <boost/smart_ptr/shared_ptr.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/string.hpp>

using namespace ftxui;

int main(int argc, char** argv) {
    // if (argc < 2) return 1;
    // std::string role = argv[1]; // client or server
    // int websocket_role = 0; // server by default
    // std::string ip_address = "127.0.0.1";
    // std::string port_number = "3000";
    // std::string host_address = ip_address + ":" + port_number;
    // auto const server_address = net::ip::make_address(ip_address);
    // auto const server_port = static_cast<unsigned short>(std::stoi(port_number));
    // net::io_context ioc;
    // tcp::socket socket{ioc};

    // if(role == "server"){
    //     tcp::acceptor acceptor{ioc, {server_address, server_port}};
    //     acceptor.accept(socket);
    // } else {
    //     websocket_role = 1;
    // }

    // auto websocket = std::make_shared<Websocket>(ip_address, port_number, socket, websocket_role);
    // std::thread t1{[&websocket, &ioc] {
    //   websocket->read_input_loop(ioc);
    // } };

    // websocket->handshake(ioc);
    // websocket->run(ioc);

    // Create dummy component

    Chat chat("Daniel", "DGServer");
    chat.start();
    
    return 0;
}