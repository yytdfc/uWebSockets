#include <uWS/uWS.h>
#include <iostream>


int main()
{
  uWS::Hub h;

  h.onConnection([](uWS::WebSocket<uWS::CLIENT> *ws, uWS::HttpRequest req) {
      auto addr = ws->getAddress();
      auto uri = req.getUrl().toString();
      std::cout<<"CONNECT host " << addr.address << " , port "
      << addr.port << std::endl;
      std::string line;
      getline(std::cin, line);
      ws->send(line.data(), line.size(), uWS::OpCode::TEXT);
      });

  h.onDisconnection([](uWS::WebSocket<uWS::CLIENT> *ws, int code, char *message, size_t length) {
      auto addr = ws->getAddress();
      std::cout<<"DISCONNECT host " << addr.address << " , port "
      << addr.port << std::endl;
      });

  h.onMessage([](uWS::WebSocket<uWS::CLIENT> *ws, char *message, size_t length, uWS::OpCode opCode, std::string url) {
      std::string recv_str(message, length);
      std::cout << "RECV " << recv_str << std::endl;
      std::string line;
      getline(std::cin, line);
      ws->send(line.data(), line.size(), uWS::OpCode::TEXT);
      });

  h.connect("wss://127.0.0.1:3000/any_url");

  h.run();
}
