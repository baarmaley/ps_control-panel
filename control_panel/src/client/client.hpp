//
// Created by mtsvetkov on 19.07.2020.
//

#pragma once

#include "boost/asio.hpp"

#include "protocol/protocol.hpp"

namespace tsvetkov{
namespace asio = boost::asio;

struct Client : std::enable_shared_from_this<Client>
{
    Client(asio::io_context& io, const std::string& remote_address, std::uint16_t port);

    Client(const Client&) = delete;
    Client(Client&&)      = delete;

    Client& operator=(const Client&) = delete;
    Client& operator=(Client&&) = delete;

    void connect();
    void disconnect();

private:
    void send_hello_request();
    void async_read();

    std::uint32_t next_id();

    asio::ip::tcp::socket socket;
    asio::ip::tcp::endpoint endpoint;

    std::uint32_t counter_id = 0;

    std::array<char, 1024> incoming_buffer;
    std::string accumulate_incoming_buffer;

    protocol::CommandHandler commandHandler;
};
}