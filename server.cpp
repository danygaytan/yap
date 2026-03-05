#include <boost/asio/basic_streambuf_fwd.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/beast/core/flat_buffer.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <ftxui/dom/elements.hpp>
#include <iostream>
#include <queue>
#include <string>
#include <thread>
 
namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

enum status_codes {
  ACTIVE = 0,
  INACTIVE = 1
};

class Server: public std::enable_shared_from_this<Server> {
  private:
  std::queue<std::string> message_send_queue;
  websocket::stream<tcp::socket> ws;
  beast::flat_buffer read_buffer;
  std::string own_service_port;
  std::string own_address;
  int chat_status;

  public:
  Server(std::string& address, std::string& service_port, tcp::socket& socket)
  : ws(std::move(socket)),
    own_address(address),
    own_service_port(service_port),
    chat_status(ACTIVE)
  {}

  void accept_handshake() {
    this->ws.set_option(websocket::stream_base::decorator(
                [](websocket::response_type& res)
                {
                    res.set(http::field::server,
                        std::string(BOOST_BEAST_VERSION_STRING) +
                            " websocket-server-sync");
                }));

    this->ws.accept();
  }

  void run(net::io_context &ioc) {
    this->do_read();
    ioc.run();
  }

  void do_write() {
    try {  
      this->ws.async_write(
      net::buffer(this->message_send_queue.front()), 
      beast::bind_front_handler(
        &Server::on_write,
        shared_from_this()
      ));
    } catch (const std::exception& e){
      std::cout << "Error in async write: " << e.what() << std::endl;
    }

  }

  void on_write( beast::error_code ec, std::size_t bytes_transferred ) {
    try {
      if (ec) std::cout << "Error: " << ec.what() << std::endl;
      this->message_send_queue.pop();
    } catch (const std::exception& e) {
      std::cout << "Error in on_write: " << e.what() << std::endl;
    }
  }

  void do_read() {
    try {
      this->ws.async_read(
        this->read_buffer,
        beast::bind_front_handler(&Server::on_read, shared_from_this())
      );
    } catch (const std::exception& e) {
      std::cout << "Error in do_read: " << e.what() << std::endl;
    }
  }

  void on_read( beast::error_code ec, std::size_t bytes_transferred ) {
    std::string message = boost::beast::buffers_to_string(this->read_buffer.data());
    std::cout << "Message read: " << message << std::endl;
    this->read_buffer.consume(this->read_buffer.size());
    this->do_read();
  }

  void read_user_input(net::io_context& ioc) {
    std::string raw_message;

    while(chat_status == ACTIVE) {
      std::string raw_message;
      std::getline(std::cin, raw_message);
      net::dispatch(ioc, [self = shared_from_this(), msg = std::move(raw_message)]() {
            bool idle = self->message_send_queue.empty();
            self->message_send_queue.push(msg);
            if (idle) {
                self->do_write();
            }
        });
    }
  }
};

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
    auto server = std::make_shared<Server>(ip_address, port_number, socket);
    std::thread t1{[&server, &server_ioc] {
      server->read_user_input(server_ioc);
    } };
    server->accept_handshake();
    server->run(server_ioc);
    t1.join();

  } catch (const std::exception& e ) {

    std::cout << "Error "<< e.what() << std::endl; 

  }
}