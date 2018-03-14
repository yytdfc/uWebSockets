#include <uWS/uWS.h>
#include <iostream>


int main()
{
  uWS::Hub h;

  uS::TLS::Context ctx = uS::TLS::createContext("./ca/cacert.pem",
      "./ca/private.pem", "");

  h.onConnection([](uWS::WebSocket<uWS::SERVER> *ws, uWS::HttpRequest req) {
      auto addr = ws->getAddress();
      auto uri = req.getUrl().toString();
      std::cout<<"CONNECT host " << addr.address << " , port "
      << addr.port << " , url " << uri << std::endl;
      });

  h.onDisconnection([](uWS::WebSocket<uWS::SERVER> *ws, int code, char *message, size_t length) {
      auto addr = ws->getAddress();
      std::cout<<"DISCONNECT host " << addr.address << " , port "
      << addr.port << std::endl;
      });

  h.onMessage([&h](uWS::WebSocket<uWS::SERVER> *ws, char *message, size_t length, uWS::OpCode opCode, std::string url) {
      std::string recv_str(message, length);
      std::cout << "RECV " << recv_str << " , FROM URL " << url << std::endl;
      // Your message handler function implementation here
      // for example:
      //     string send_str = message_handler(recv_str);
      std::string send_str = recv_str;
      if(recv_str == "quit")
        h.getDefaultGroup<uWS::SERVER>().close();
      std::cout << "SEND " << send_str  << std::endl;
      ws->send(send_str.data(), send_str.size(), opCode);
      });

  if (h.listen(3000, ctx)) {
    std::cout << "LISTENING on " << 3000 << std::endl;
    h.run();
  }
}
