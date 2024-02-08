#ifndef SERVER_HPP
#define SERVER_HPP

#include <SFML/Network.hpp>
#include <string>
#include "DEBUG.h"

class ServerConnecter
{
public:
    bool connectToAddress(std::string t_connectionSocket)
    {
        sf::Socket::Status status = m_socket.connect(t_connectionSocket, 53000);
        if (status != sf::Socket::Done)
        {
            DEBUG_MSG("ERROR CONNECTING TO ADDRESS\n");
            return false;
        }
        return true;
    }

    bool listenOnPort()
    {
        sf::TcpListener listener;

        // bind the listener to a port
        if (listener.listen(53000) != sf::Socket::Done)
        {
            DEBUG_MSG("LISTENING DOESNT WORK\n");
            return false;
        }

        // accept a new connection
        sf::TcpSocket m_socket;
        if (listener.accept(m_socket) != sf::Socket::Done)
        {
            DEBUG_MSG("ERROR RECIEVING CONNECTION\n");
            return false;
        }

        // use "client" to communicate with the connected client
        return true;
    }

private:
    bool m_host = false;
    sf::TcpSocket m_socket;
};





#endif // !SERVER_HPP
