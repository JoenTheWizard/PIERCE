#define PIERCE_DLL _declspec(dllexport)
#include <string.h>
#include <ctype.h>
#include <string>

#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif

#define ASIO_STANDALONE
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

using namespace std;
extern "C" {
   PIERCE_DLL int Adds(int a, int b) {
      return a + b;
   }
   PIERCE_DLL void __GetValue__(char* str, int strlen) {
      string result = "W E L C O M E   T O  P I E R C E !";
      result = result.substr(0, strlen);
      copy(result.begin(), result.end(), str);
      str[min(strlen - 1, (int)result.size())] = 0;
   }
   PIERCE_DLL void ParseStringTest(char* st) {
      string str(st);
      //str += " cock ass";
      size_t val = str.length();

      str = str.substr(0, val);
      copy(str.begin(), str.end(), st);

      st[min((int)val, (int)str.size())] = 0;
   }
   PIERCE_DLL void ParseMessage(char* str, string mes) {
      string result = mes;
      size_t val = result.length();

      result = result.substr(0, val);
      copy(result.begin(), result.end(), str);
      str[min((int)val, (int)result.size())] = 0;
   }
   PIERCE_DLL void AsioInit(char* ip, int port, char* result) {
      string ipStr(ip);
      asio::error_code ec;
      asio::io_context context;
      asio::ip::tcp::endpoint endpoint(asio::ip::make_address(ipStr, ec), port);
      //Socket init
      asio::ip::tcp::socket socket(context);

      socket.connect(endpoint, ec);
      if (!ec) {
         string res = "Connected!";
         ParseMessage(result, res);
      }
      else {
         string res = "Failed to connect to address: " + ec.message();
         ParseMessage(result, res);
      }
   }
   PIERCE_DLL void HTTPRequest(char* ip, int port, char* result,
      char* httpreq, char* result1, char* finalRequestResult) {
      string ipStr(ip);
      asio::error_code ec;
      asio::io_context context;
      asio::ip::tcp::endpoint endpoint(asio::ip::make_address(ipStr, ec), port);
      //Socket init
      asio::ip::tcp::socket socket(context);

      socket.connect(endpoint, ec);
      if (!ec) {
         string res = "Connected!";
         ParseMessage(result, res);
      }
      else {
         string res = "Failed to connect to address: " + ec.message();
         ParseMessage(result, res);
      }
      //Check if socket is open
      if (socket.is_open()) {
         string htpre(httpreq);
         socket.write_some(asio::buffer(htpre.data(), htpre.size()), ec);

         //wait for stream
         socket.wait(socket.wait_read);

         size_t bytes = socket.available();
         ParseMessage(result1, "Bytes available: " + to_string(bytes));

         if (bytes > 0) {
            vector<char> vBuffer(bytes);

            socket.read_some(asio::buffer(vBuffer.data(), vBuffer.size()), ec);

            string zxc_;
            for (auto c : vBuffer)
               zxc_ += c;
            ParseMessage(finalRequestResult, zxc_);
         }
      }
   }
}