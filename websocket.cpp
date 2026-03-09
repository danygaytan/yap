#include <boost/asio/basic_streambuf_fwd.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/beast/core/bind_handler.hpp>
#include <boost/beast/core/buffers_to_string.hpp>
#include <boost/beast/core/flat_buffer.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/rfc6455.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <cstddef>
#include <exception>
#include <ftxui/screen/screen.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <ftxui/dom/elements.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <sys/types.h>
#include <bits/stdc++.h>
#include <utility>
 
namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

struct Message {
  std::string content;
  std::string sender_username;
};

struct Conversation {
  std::queue<Message> messages;
};

enum status_codes {
  ACTIVE = 0,
  INACTIVE = 1
};

enum role_codes {
    SERVER = 0,
    CLIENT = 1
};

class Websocket: public std::enable_shared_from_this<Websocket> {
  
  private:
  std::string host_address;
  std::string host_service_port;
  websocket::stream<tcp::socket> ws;
  std::queue<std::string> message_send_queue;
  boost::beast::flat_buffer read_buffer;
  int status, role;

  public:
  Websocket(std::string& host_address, std::string& host_service_port, tcp::socket socket, int role):
    ws(std::move(socket)),
    host_address(host_address),
    host_service_port(host_service_port),
    status(ACTIVE),
    role(role) {}

  public:
  void handshake(net::io_context& ioc) {
    try {
        if(this->role == CLIENT) {
            tcp::resolver resolver{ioc};
            auto results = resolver.resolve(this->host_address, this->host_service_port);
            std::string address_and_port = this->host_address + ':' + this->host_service_port;

            this->ws.set_option(websocket::stream_base::decorator(
              [](websocket::request_type& req)
              {
                  req.set(http::field::user_agent,
                      std::string(BOOST_BEAST_VERSION_STRING) +
                          " websocket-client-coro");
              }));
    
            this->ws.handshake(address_and_port, "/");
            return;
        }

        this->ws.set_option(websocket::stream_base::decorator(
                [](websocket::response_type& res)
                {
                    res.set(http::field::server,
                        std::string(BOOST_BEAST_VERSION_STRING) +
                            " websocket-server-sync");
                }));

        this->ws.accept();

        return;
    } catch (const std::exception& e) {
        std::cout << "Error in handshake: " << e.what() << std::endl;
    }
  }

  void run(net::io_context& ioc) {
    this->do_read();
    ioc.run();
  }

  void disconnect() {
    this->ws.close(websocket::close_code::normal);
  };

  void do_write() {
    try {
      ws.async_write(
      net::buffer(this->message_send_queue.front()), 
      beast::bind_front_handler(
        &Websocket::on_write,
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
      ws.async_read(
        this->read_buffer,
        beast::bind_front_handler(&Websocket::on_read, shared_from_this())
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

  void read_input_loop(net::io_context& ioc) {
    std::string raw_message;

    while(status == ACTIVE) {
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