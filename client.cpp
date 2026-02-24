#include <boost/beast/websocket.hpp>
#include <ftxui/screen/screen.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <ftxui/dom/elements.hpp>
#include <iostream>
#include <string>
 
namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;
int main() {
  std::string ip_address = "127.0.0.1";
  std::string port_number = "3000";
  std::string host_address = ip_address + ":" + port_number;

  // Connect from CLIENT
  net::io_context ioc;
  tcp::resolver resolver { ioc };
  websocket::stream<tcp::socket> ws{ ioc };

  auto results = resolver.resolve(ip_address, port_number);

  auto endpoint = net::connect(ws.next_layer(), results);

  ws.set_option(websocket::stream_base::decorator(
            [](websocket::request_type& req)
            {
                req.set(http::field::user_agent,
                    std::string(BOOST_BEAST_VERSION_STRING) +
                        " websocket-client-coro");
            }));
  
  ws.handshake(host_address, "/");
  
  for(;;) {
    std::string outgoing_message;
    std::getline(std::cin, outgoing_message);
    ws.write(net::buffer(outgoing_message));

    std::string incoming_message;
    auto buf = net::dynamic_buffer(incoming_message);
    ws.read(buf);

    std::cout << "Message received: " << incoming_message << std::endl;

    // ws.close(websocket::close_code::normal);
  }

  std::cout << endpoint.address() << std::endl;
}