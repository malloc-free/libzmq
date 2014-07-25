/*
 * tcp_transport.hpp
 *
 *  Created on: 19/03/2014
 *      Author: Michael Holmwood
 */

#ifndef TCP_TRANSPORT_HPP_
#define TCP_TRANSPORT_HPP_

#include "transport.hpp"
#include "fd.hpp"

#include <string>
#include <sys/socket.h>

namespace zmq {

class tcp_transport_options : public transport_options_t{
	int setsockopt (const void *optval_, size_t optvallen_);

	int getsockopt (void *optval_, size_t *optvallen_);
};

class tcp_transport : public transport
{

public:
	tcp_transport ();

	virtual ~tcp_transport ();

	// Create tcp_transport objects.
	static transport *tx_create_transport ();

	// Create tcp_transport objects.
	static transport_options_t *tcp_get_options ();

	// Sockets functions. Basically just call the BSD Sockets API.
	// Other protocols implementing the transport interface will have
	// to do more (an example being SCTP).

	//This function will have to be implemented in some protocols.
	//poller *tx_create_poller ();

	int tx_socket (int domain, int type, int protocol);

	int tx_connect (fd_t fd, const struct sockaddr *addr,
			socklen_t addrlen);

	int tx_listen (fd_t fd, int backlog);

	int tx_bind (fd_t fd, const struct sockaddr *addr,
			socklen_t addrlen);

	int tx_accept (fd_t fd, struct sockaddr *addr, socklen_t *addrlen);

	int tx_send (fd_t fd, const void *buf, size_t len, int flags);

	int tx_recv (fd_t fd, void *buf, size_t len, int flags);

	int tx_close (fd_t fd);

	int tx_getsockopt (fd_t fd, int level, int optname,
			void *optval, socklen_t *optlen);

	int tx_setsockopt (fd_t fd, int level, int optname,
			const void *optval, socklen_t optlen);

	void tx_set_receive_buffer (fd_t fd, int bufsize);

	void tx_set_send_buffer (fd_t fd, int bufsize);

	void tx_set_keepalives (fd_t fd, int keepalive, int keepalive_cnt,
			int keepalive_idle, int keepalive_intv);

	void tx_tune_socket (fd_t fd);

	void tx_unblock_socket (fd_t fd);

	void tx_enable_ipv4_mapping (fd_t fd);

	void tx_get_peer_ip_address (fd_t fd, std::string &ip_addr);

	void tx_set_ip_type_of_service (fd_t fd, int iptos);

	transport_options_t *tx_get_options ();

	void tx_set_options (fd_t fd, transport_options_t *option);
};

} /* namespace zmq */

#endif /* TCP_TRANSPORT_HPP_ */
