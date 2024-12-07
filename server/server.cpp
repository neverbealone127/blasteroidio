#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <iostream>
#include <vector>
#include <cstdint>

typedef websocketpp::server<websocketpp::config::asio> server;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

typedef server::message_ptr message_ptr;

typedef std::vector<uint8_t> ArrayBuffer;

void process_message(ArrayBuffer buffer) {
    const uint8_t OP_PING = 0x00;
    const uint8_t OP_HELLO = 0x01;
    const uint8_t OP_ENTER_GAME = 0X02;
    const uint8_t OP_LEAVE_GAME = 0x03;
    const uint8_t OP_UPDATE_VIEW = 0x04;
    const uint8_t OP_CLICK = 0x05;
    const uint8_t OP_INPUT = 0x06;
    
    uint8_t op = buffer[0];
    
}

void on_message(server* s, websocketpp::connection_hdl hdl, message_ptr msg) {
    std::cout << "on_message called with hdl: " << hdl.lock().get()
              << " and message: " << msg->get_payload()
              << std::endl;    
    if(msg->get_opcode() == websocketpp::frame::opcode::binary) {
    
      ArrayBuffer data(msg->get_payload().begin(), msg->get_payload().end());
      
      std::cout << "Received binary message of size " << data.size() << "bytes" << std::endl;
      
    } else {
      
      std::cout << "Received non-binary message: " << msg->get_payload() << std::endl;
      
    }
}

int main() {
    server ws_server;

    try {
        ws_server.set_access_channels(websocketpp::log::alevel::all);
        ws_server.clear_access_channels(websocketpp::log::alevel::frame_payload);

        ws_server.init_asio();

        ws_server.set_message_handler(bind(&on_message,&ws_server,::_1,::_2));

        ws_server.listen(9002);

        ws_server.start_accept();

        ws_server.run();
    } catch (websocketpp::exception const & e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "other exception" << std::endl;
    }
}
