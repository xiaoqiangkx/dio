// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//
// This is a public header file, it must only include public header files.

#ifndef DIO_CALLBACKS_H
#define DIO_CALLBACKS_H

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#include <dio/base/Timestamp.h>

namespace dio
{

    class TcpConnection;
// Adapted from google-protobuf stubs/common.h
// see License in muduo/base/Types.h
template<typename To, typename From>
inline ::boost::shared_ptr<To> down_pointer_cast(const ::boost::shared_ptr<From>& f)
{
  if (false)
  {
    dio::implicit_cast<From*, To*>(0);
  }

#ifndef NDEBUG
  assert(f == NULL || dynamic_cast<To*>(get_pointer(f)) != NULL);
#endif
  return ::boost::static_pointer_cast<To>(f);
}

// All client visible callbacks go here.
namespace net {
class Buffer;
typedef boost::shared_ptr<TcpConnection> TcpConnectionPtr;
typedef boost::function<void()> TimerCallback;
typedef boost::function<void(const TcpConnectionPtr &)> ConnectionCallback;
typedef boost::function<void(const TcpConnectionPtr &)> CloseCallback;
typedef boost::function<void(const TcpConnectionPtr &)> WriteCompleteCallback;
typedef boost::function<void(const TcpConnectionPtr &, size_t)> HighWaterMarkCallback;

// the data has been read to (buf, len)
typedef boost::function<void(const TcpConnectionPtr &,
                             dio::net::Buffer *,
                             dio::Timestamp)> MessageCallback;

void defaultConnectionCallback(const TcpConnectionPtr &conn);

void defaultMessageCallback(const TcpConnectionPtr &conn,
                            dio::net::Buffer *buffer,
                            dio::Timestamp receiveTime);
};
}

#endif  // DIO_CALLBACKS_H
