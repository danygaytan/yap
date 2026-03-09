#ifndef WEBSOCKET
#define WEBSOCKET

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
#include <ftxui/screen/screen.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>
#include <sys/types.h>
#include <bits/stdc++.h>

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

class Websocket {
private:
    std::string host_address;
    std::string host_service_port;
    websocket::stream<tcp::socket> ws;
    std::queue<std::string> message_send_queue;
    boost::beast::flat_buffer read_buffer;
    int status;
    int role;

public:
    Websocket(std::string& host_address, std::string& host_service_port, tcp::socket socket, int role);
    void handshake(net::io_context& ioc);
    void run(net::io_context& ioc);
    void disconnect();
    void do_write();
    void on_write( beast::error_code ec, std::size_t bytes_transferred );
    void do_read();
    void on_read( beast::error_code ec, std::size_t bytes_transferred );
    void read_input_loop(net::io_context& ioc);
};

#endif