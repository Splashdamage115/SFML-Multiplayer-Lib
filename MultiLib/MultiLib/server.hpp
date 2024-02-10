#ifndef SERVER_HPP
#define SERVER_HPP

#include <SFML/Network.hpp>
#include <string>
#include "DEBUG.h"

class ServerConnecter
{
public:
    // connect to the passed in address (cin or input from user)
    bool connectToAddress(std::string t_connectionSocket)
    {
        std::string address = "";
        std::string portString = "";
        int port;

        bool nextHalf = false;
        // convert the ip address from <(ipAddress):(PORT):>
        for (unsigned int i = 0; i < t_connectionSocket.size(); i++)
        {
            if (t_connectionSocket.at(i) == ':' && !(nextHalf)) // check for first ':;
            {
                nextHalf = true;
                continue;
            }
            if (t_connectionSocket.at(i) == ':') // check for second ':' (end of ip address)
                break;
            if (nextHalf)
            {
                portString += t_connectionSocket.at(i);
            }
            else
            {
                address += t_connectionSocket.at(i);
            }
            
        }
        // turn the port string to an int
        port = std::stoi(portString);

        // attempt to connect to socket
        sf::Socket::Status status = m_socket.connect(address, port);
        if (status != sf::Socket::Done)
        {
            DEBUG_MSG("ERROR CONNECTING TO ADDRESS\n");
            return false;
        }
        return true;
    }


    // listen on the available port, print out the current port and ipAddress
    bool listenOnPort()
    {
        sf::TcpListener listener;
        m_host = true;

        int port = 5300; // listen on port 5300 (change this if needed)
        DEBUG_MSG_NO_END(sf::IpAddress::getLocalAddress()); // change this if listening on online address
        DEBUG_MSG(":" + std::to_string(port) + ":");

        // bind the listener to a port
        if (listener.listen(port) != sf::Socket::Done)
        {
            DEBUG_MSG("LISTENING DOESNT WORK\n");
            return false;
        }

        if (listener.accept(m_socket) != sf::Socket::Done)
        {
            DEBUG_MSG("ERROR RECIEVING CONNECTION\n");
            return false;
        }

        DEBUG_MSG("CONNECTED SUCCESSFULLY\n\n");
        return true;
    }

    // send packet
    bool trySendPacket(sf::Packet t_packet)
    {
        while (m_socket.send(t_packet) == sf::Socket::Partial)
            DEBUG_MSG("DIDNT SEND\n");

        return true;
    }

    // read out packet (coords)
    sf::Vector2f tryRecievePacket()
    {
        sf::Packet reciever;
        float xPos{ 0.f };
        float yPos{ 0.f };
        if (m_socket.receive(reciever) == sf::Socket::Done)
        {
            DEBUG_MSG("RECIEVED DATA\n\n");

            

            if (reciever >> xPos >> yPos)
            {
                DEBUG_MSG("SUCCESSFULLY EXTRACTED DATA\n");
                return sf::Vector2f(xPos, yPos);
            }
            DEBUG_MSG("UNSUCCESSFUL\n");
            return sf::Vector2f(0.f, 0.f);
        }
        DEBUG_MSG("NO DATA RECIEVED\n");
        return sf::Vector2f(0.f, 0.f);
    }

private:
    bool m_host = false;
    sf::TcpSocket m_socket;
};


#endif // !SERVER_HPP
