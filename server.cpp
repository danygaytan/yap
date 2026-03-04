#include <boost/asio/basic_streambuf_fwd.hpp>
#include <boost/beast/core/flat_buffer.hpp>
#include <boost/beast/websocket.hpp>
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


  // Open SERVER connection listener
  auto const server_address = net::ip::make_address(ip_address);
  auto const server_port = static_cast<unsigned short>(std::stoi(port_number));
  net::io_context server_ioc;
  tcp::acceptor acceptor{server_ioc, {server_address, server_port}};

  tcp::socket socket{server_ioc};

  acceptor.accept(socket);

  try {

    // Accept and reply to handshake
    websocket::stream<tcp::socket> ws{std::move(socket)};

    ws.set_option(websocket::stream_base::decorator(
                [](websocket::response_type& res)
                {
                    res.set(http::field::server,
                        std::string(BOOST_BEAST_VERSION_STRING) +
                            " websocket-server-sync");
                }));

    ws.accept();

    std::string message;
    auto buf = net::dynamic_buffer(message);

    for(;;) {
        buf.consume(buf.size());
        ws.read(buf);
  
        std::cout << "Message received " << message << std::endl;
        ws.write(buf.data());
        
    }

  } catch (const std::exception& e ) {

    std::cout << "Error "<< e.what() << std::endl; 

  }
}