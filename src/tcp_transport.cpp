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

namespace zmq {

tcp_transport::tcp_transport()
{
}

tcp_transport::~tcp_transport() {
}

transport *tcp_transport::tx_create_transport() {
	return new (std::nothrow) tcp_transport();
}

void tcp_transport::tx_destroy_transport(transport *tx_transport_) {
	delete tx_transport_;
}

transport *tcp_transport::tx_copy() {
	tx_increment_use();
	return this;
}

bool tcp_transport::tx_destroy() {
	return tx_decrement_use();
}

int tcp_transport::tx_socket(int domain, int type, int protocol)
{
	int rc;
	rc = socket(domain, type, protocol);

	//P_N_ERR(rc, "tx_socket");

	return rc;
}

int tcp_transport::tx_connect(int sockfd, const struct sockaddr *addr,
		socklen_t addrlen)
{
	int rc;
	rc = connect(sockfd, addr, addrlen);

	//P_Z_ERR(rc, "tx_connect");

	return rc;
}

int tcp_transport::tx_listen(int sockfd, int backlog)
{
	int rc;
	rc = listen(sockfd, backlog);

	//P_Z_ERR(rc, "tx_listen");

	return rc;
}

int tcp_transport::tx_bind(int sockfd, const struct sockaddr *addr,
		socklen_t addrlen)
{
	int rc;
	rc = bind(sockfd, addr, addrlen);

	//P_Z_ERR(rc, "tx_bind");

	return rc;
}

int tcp_transport::tx_accept(int sockfd, struct sockaddr *addr,
		socklen_t *addrlen)
{
	int rc;
	rc = accept(sockfd, addr, addrlen);

	//P_N_ERR(rc, "tx_accept");

	return rc;
}

int tcp_transport::tx_send(int sockfd, const void *buf, size_t len, int flags)
{
	int rc;
	rc = send(sockfd, buf, len, flags);

	//P_N_ERR(rc, "tx_send");

	return rc;
}

int tcp_transport::tx_recv(int sockfd, void *buf, size_t len, int flags)
{
	int rc;
	rc = recv(sockfd, buf, len, flags);

	//P_N_ERR(rc, "tx_recv");

	return rc;
}

int tcp_transport::tx_close(int fd)
{
	int rc;
	rc = close(fd);

	//P_Z_ERR(rc, "tx_close");

	return rc;
}

int tcp_transport::tx_getsockopt(int sockfd, int level, int optname,
		void *optval, socklen_t *optlen)
{
	return getsockopt(sockfd, level, optname, optval, optlen);
}

int tcp_transport::tx_setsockopt(int sockfd, int level, int optname,
		const void *optval, socklen_t optlen)
{
	return setsockopt(sockfd, level, optname, optval, optlen);
}

void tcp_transport::tx_set_receive_buffer(int sockfd, int bufsize)
{
	set_tcp_receive_buffer(sockfd, bufsize);
}

void tcp_transport::tx_set_send_buffer(int sockfd, int bufsize)
{
	set_tcp_send_buffer(sockfd, bufsize);
}

void tcp_transport::tx_set_keepalives(int sockfd, int keepalive, int keepalive_cnt,
		int keepalive_idle, int keepalive_intvl)
{
	tune_tcp_keepalives(sockfd, keepalive, keepalive_cnt, keepalive_idle,
			keepalive_intvl);
}

void tcp_transport::tx_tune_socket(int sockfd)
{
	tune_tcp_socket(sockfd);
}

void tcp_transport::tx_unblock_socket(int sockfd)
{
	unblock_socket(sockfd);
}

void tcp_transport::tx_enable_ipv4_mapping(int sockfd)
{
	enable_ipv4_mapping(sockfd);
}

void tcp_transport::tx_get_peer_ip_address(int sockfd, std::string &ip_addr)
{
	get_peer_ip_address(sockfd, ip_addr);
}

void tcp_transport::tx_set_ip_type_of_service(int sockfd, int iptos)
{
	set_ip_type_of_service(sockfd, iptos);
}

transport_options_t *tcp_transport::tx_get_options()
{
	return NULL;
}

void tcp_transport::tx_set_options(int sockd, transport_options_t *option)
{

}

} /* namespace zmq */
