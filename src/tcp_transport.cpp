/*
 * tcpWrapper.cpp
 *
 *  Created on: 19/03/2014
 *      Author: Michael Holmwood
 */

#include "tcp_transport.hpp"
#include "transport.hpp"
#include "err.hpp"
#include "ip.hpp"
#include "tcp.hpp"
#include "mutex.hpp"
#include "fd.hpp"

#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <iostream>
#include <string>
#include <errno.h>
#include <memory>

int zmq::tcp_transport_options::setsockopt (const void *optval, size_t optvallen_) {
	return 0;
}

int zmq::tcp_transport_options::getsockopt (void *optval, size_t *optvallen_) {
	return 0;
}

zmq::tcp_transport::tcp_transport ()
{
}

zmq::tcp_transport::~tcp_transport () {
}

zmq::transport *zmq::tcp_transport::tx_create_transport () {
	return new (std::nothrow) tcp_transport();
}

int zmq::tcp_transport::tx_socket (int domain, int type, int protocol)
{
	int rc;
	rc = socket(domain, type, protocol);

	//P_N_ERR(rc, "tx_socket");

	return rc;
}

int zmq::tcp_transport::tx_connect (zmq::fd_t fd, const struct sockaddr *addr,
		socklen_t addrlen)
{
	int rc;
	rc = connect(fd, addr, addrlen);

	//P_Z_ERR(rc, "tx_connect");

	return rc;
}

int zmq::tcp_transport::tx_listen (zmq::fd_t fd, int backlog)
{
	int rc;
	rc = listen(fd, backlog);

	//P_Z_ERR(rc, "tx_listen");

	return rc;
}

int zmq::tcp_transport::tx_bind (zmq::fd_t fd, const struct sockaddr *addr,
		socklen_t addrlen)
{
	int rc;
	rc = bind(fd, addr, addrlen);

	//P_Z_ERR(rc, "tx_bind");

	return rc;
}

int zmq::tcp_transport::tx_accept (zmq::fd_t fd, struct sockaddr *addr,
		socklen_t *addrlen)
{
	int rc;
	rc = accept(fd, addr, addrlen);

	//P_N_ERR(rc, "tx_accept");

	return rc;
}

int zmq::tcp_transport::tx_send (zmq::fd_t fd, const void *buf, size_t len, int flags)
{
	int rc;
	rc = send(fd, buf, len, flags);

	//P_N_ERR(rc, "tx_send");

	return rc;
}

int zmq::tcp_transport::tx_recv (zmq::fd_t fd, void *buf, size_t len, int flags)
{
	int rc;
	rc = recv(fd, buf, len, flags);

	//P_N_ERR(rc, "tx_recv");

	return rc;
}

int zmq::tcp_transport::tx_close (int fd)
{
	int rc;
	rc = close(fd);

	//P_Z_ERR(rc, "tx_close");

	return rc;
}

int zmq::tcp_transport::tx_getsockopt (zmq::fd_t fd, int level, int optname,
		void *optval, socklen_t *optlen)
{
	return getsockopt(fd, level, optname, optval, optlen);
}

int zmq::tcp_transport::tx_setsockopt (zmq::fd_t fd, int level, int optname,
		const void *optval, socklen_t optlen)
{
	return setsockopt(fd, level, optname, optval, optlen);
}

void zmq::tcp_transport::tx_set_receive_buffer (zmq::fd_t fd, int bufsize)
{
	set_tcp_receive_buffer(fd, bufsize);
}

void zmq::tcp_transport::tx_set_send_buffer (zmq::fd_t fd, int bufsize)
{
	set_tcp_send_buffer(fd, bufsize);
}

void zmq::tcp_transport::tx_set_keepalives (zmq::fd_t fd, int keepalive, int keepalive_cnt,
		int keepalive_idle, int keepalive_intvl)
{
	tune_tcp_keepalives(fd, keepalive, keepalive_cnt, keepalive_idle,
			keepalive_intvl);
}

void zmq::tcp_transport::tx_tune_socket (zmq::fd_t fd)
{
	tune_tcp_socket(fd);
}

void zmq::tcp_transport::tx_unblock_socket (zmq::fd_t fd)
{
	unblock_socket(fd);
}

void zmq::tcp_transport::tx_enable_ipv4_mapping (zmq::fd_t fd)
{
	enable_ipv4_mapping(fd);
}

void zmq::tcp_transport::tx_get_peer_ip_address (zmq::fd_t fd, std::string &ip_addr)
{
	get_peer_ip_address(fd, ip_addr);
}

void zmq::tcp_transport::tx_set_ip_type_of_service (zmq::fd_t fd, int iptos)
{
	set_ip_type_of_service (fd, iptos);
}

zmq::transport_options_t *zmq::tcp_transport::tx_get_options ()
{
	return new (std::nothrow) tcp_transport_options ();
}

void zmq::tcp_transport::tx_set_options (int sockd, transport_options_t *option)
{

}


