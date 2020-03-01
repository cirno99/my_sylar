#include "stream.hh"
#include <vector>
#include <iostream>

namespace sylar {

    int Stream::readFixSize(void* buffer, size_t length) {
        size_t offset = 0;
        int64_t left = length;
        while (left > 0) {
            int64_t len = read((char*)buffer + offset, left);
            if (len <= 0) {
                return len;
            }
            offset += len;
            left -= len;
        }
        return length;
    }

    int Stream::readFixSize(ByteArray::ptr ba, size_t length) {
        int64_t left = length;
        while (left > 0) {
            int64_t len = read(ba, left); // ba remember the m_postion
            if (len <= 0) {
                return len;
            }
            left -= len;
        }
        return length;
    }

    int Stream::writeFixSize(const char* buffer, size_t length) {
        size_t offset = 0;
        int64_t left = length;
        while (left > 0) {
            int64_t len = write((char*)buffer + offset, left);
            if (len <= 0) {
                return len;
            }
            offset += len;
            left -= len;
        }
        return length;
    }

    int Stream::writeFixSize(const void* buffer, size_t length) {
        return writeFixSize(static_cast<const char*>(buffer), length);
    }

    int Stream::writeFixSize(ByteArray::ptr ba, size_t length) {
        int64_t left = length;
        while (left > 0) {
            int64_t len = write(ba, left);
            if (len <= 0) {
                return len;
            }
            left -= len;
        }
        return length;
    }

    int Stream::readFixSize(Buffer::ptr buf, size_t length) {
        int64_t left = length;
        while (left > 0) {
            int64_t len = read(buf, left);
            if (len <= 0) {
                return len;
            }
            left -= len;
        }
        return length;
    }

    int Stream::writeFixSize(Buffer::ptr buf, size_t length) {
        int64_t left = length;
        while (left > 0) {
            int64_t len = write(buf, left);
            if (len <= 0) {
                return len;
            }
            left -= len;
        }
        return length;
    }

    SocketStream::SocketStream(Socket::ptr sock, bool owner)
    : m_socket(sock),
    m_owner(owner) {
    }

    SocketStream::~SocketStream() {
        if (m_owner && m_socket) {
            m_socket->close();
        }
    }

    bool SocketStream::isConnected() const {
        return m_socket && m_socket->isConnected();
    }

    int SocketStream::read(void* buffer, size_t length) {
        if (!isConnected()) {
            return -1;
        }
        return m_socket->recv(buffer, length);
    }

    int SocketStream::read(ByteArray::ptr ba, size_t length) {
        if (!isConnected()) {
            return -1;
        }
        std::vector<iovec> iovs;
        ba->getWriteBuffers(iovs, length);
        int ret = m_socket->recv(&iovs[0], iovs.size());
        if (ret > 0) {
            ba->setPosition(ba->getPosition() + ret);
        }
        return ret;
    }

    int SocketStream::write(const char* buffer, size_t length) {
        if (!isConnected()) {
            return -1;
        }
        return m_socket->send(buffer, length);
    }

    int SocketStream::write(ByteArray::ptr ba, size_t length) {
        if (!isConnected()) {
            return -1;
        }
        std::vector<iovec> iovs;
        ba->getReadBuffers(iovs, length);
        int ret = m_socket->send(&iovs[0], length);
        if (ret > 0) {
            ba->setPosition(ba->getPosition() + ret);
        }
        if (ret < 0) {
            std::cout<<"errno: " << errno
            << " strerrno: " << strerror(errno) << std::endl;
        }
        return ret;
    }

    int SocketStream::read(Buffer::ptr buf, size_t length) {
        if (!isConnected()) {
            return -1;
        }
        int err;
        int ret = buf->orireadFd(m_socket->getSocket(), length, &err);
        return ret;
    }

    int SocketStream::write(Buffer::ptr buf, size_t length) {
        if (!isConnected()) {
            return -1;
        }
        int err;
        int ret = buf->writeFd(m_socket->getSocket(), length, &err);
        return ret;
    }

    void SocketStream::close() {
        if (m_socket) {
            m_socket->close();
        }
    }
}