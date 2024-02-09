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
        m_host = true;

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

        DEBUG_MSG("CONNECTED SUCCESSFULLY\n\n");
        return true;
    }

    bool trySendPacket(sf::Packet t_packet)
    {
        //if(m_socket.)
        float xPos;
        t_packet >> xPos;
        DEBUG_MSG(xPos);

        while (m_socket.send(t_packet) == sf::Socket::Partial)
            DEBUG_MSG("DIDNT SEND\n");

        return true;
    }
    sf::Vector2f tryRecievePacket()
    {
        sf::Packet reciever;
        m_socket.receive(reciever);

        if (!reciever)
            DEBUG_MSG("DIDNT RECIEVE PACKET\n");
        
        float xPos{ 0.f };
        float yPos{ 0.f };

        if (reciever >> xPos >> yPos)
        {
            DEBUG_MSG("SUCCESSFULLY EXTRACTED DATA\n");
            return sf::Vector2f(xPos, yPos);
        }
        DEBUG_MSG("UNSUCCESSFUL\n");
        return sf::Vector2f(0.f, 0.f);
    }

private:
    bool m_host = false;
    sf::TcpSocket m_socket;
};


#endif // !SERVER_HPP
