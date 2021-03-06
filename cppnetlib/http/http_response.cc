#include "cppnetlib/http/http_response.h"

#include <stdio.h>
#include "cppnetlib/base/buffer.h"

namespace cppnetlib {
namespace net {

void HTTPResponse::AppendToBuffer(Buffer* output) const {
  char buf[32];
  snprintf(buf, sizeof(buf), "HTTP/1.1 %d ", status_code_);
  output->Append(buf);
  output->Append(status_message_);
  output->Append("\r\n");

  if (close_connection_) {
    output->Append("Connection: close\r\n");
  } else {
    snprintf(buf, sizeof(buf), "Content-Length: %zd\r\n", body_.size());
    output->Append(buf);
    output->Append("Connection: Keep-Alive\r\n");
  }

  for (const auto& header : headers_) {
    output->Append(header.first);
    output->Append(": ");
    output->Append(header.second);
    output->Append("\r\n");
  }

  output->Append("\r\n");
  output->Append(body_);
}


} // namespace net
} // namespace cppnetlib
