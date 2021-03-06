/*
 * transport.hpp
 *
 *  Created on: 19/03/2014
 *      Author: Michael Holmwood
 *
 *      The purpose of this interface is to provide general access to
 *      the network functionality of a protocol, maintaining the same
 *      API as Berkley Sockets.
 */

#ifndef TRANSPORT_HPP_
#define TRANSPORT_HPP_

#include "mutex.hpp"
#include "fd.hpp"

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string>
#include <../include/zmq.h>

#define P_Z_ERR(i, s) if(i != 0 && errno != EAGAIN)  perror(s)
#define P_N_ERR(i, s) if(i == -1 && errno != EAGAIN)  perror(s)

namespace zmq
{

//Passed into setSockOpt to set the specified option
class transport_options_t
{
public:
	virtual ~transport_options_t (){};

	virtual int setsockopt (const void *optval_, size_t optvallen_) = 0;

	virtual int getsockopt (void *optval_, size_t *optvallen_) = 0;
};

/**
 * Interface for transport protocols.
 */
class transport
{
public:
	transport () : use_count(1) {};

	virtual ~transport () {};

	virtual transport *tx_copy ();

	virtual bool tx_destroy ();

	virtual int tx_socket (int domain, int type, int protocol) = 0;

	virtual int tx_connect (fd_t fd, const struct sockaddr *addr,
			socklen_t addrlen) = 0;

	virtual int tx_listen (fd_t fd, int backlog) = 0;

	virtual int tx_bind (fd_t fd, const struct sockaddr *addr,
			socklen_t addrlen) = 0;

	virtual int tx_accept (fd_t fd, struct sockaddr *addr, socklen_t *addrlen) = 0;

	virtual int tx_send (fd_t fd, const void *buf, size_t len, int flags) = 0;

	virtual int tx_recv (fd_t fd, void *buf, size_t len, int flags) = 0;

	virtual int tx_close (int fd) = 0;

	virtual int tx_getsockopt (fd_t fd, int level, int optname,
			void *optval, socklen_t *optlen) = 0;

	virtual int tx_setsockopt (fd_t fd, int level, int optname,
			const void *optval, socklen_t optlen) = 0;

	virtual void tx_set_receive_buffer (fd_t fd, int bufsize) = 0;

	virtual void tx_set_send_buffer (fd_t fd, int bufsize) = 0;

	// This just copies most of the function calls required to set up
	// tcp in zmq. There may be a better way to achieve this, but it
	// currently suffices and has the least impact on existing code.

	virtual void tx_set_keepalives (fd_t fd, int keepalive,
			int keepalive_cnt, int keepalive_idle, int keepalive_intv) = 0;

	virtual void tx_tune_socket (fd_t fd) = 0;

	virtual void tx_unblock_socket (fd_t fd) = 0;

	virtual void tx_enable_ipv4_mapping (fd_t fd) = 0;

	virtual void tx_get_peer_ip_address (fd_t fd, std::string &ip_addr_) = 0;

	virtual void tx_set_ip_type_of_service (fd_t fd, int iptos) = 0;

	// Option factory method - used to set options for the protocol
	virtual transport_options_t *tx_get_options () = 0;

	// Called when options are set for the protocol.
	virtual void tx_set_options (int sockd, transport_options_t *options) = 0;

protected:

	virtual void tx_increment_use ();

	virtual bool tx_decrement_use ();

private:

	int use_count;

	mutex_t lock;
};

// Function definition for transport object factory.
typedef transport *(*transport_factory) ();

// TODO: The functions below will have to be created for protocol
// libraries that cannot use the zmq provided polling functions.
// This is generally the case for application layer protocols.

// Function definition for poller factory.
// typedef void (*tpt_poller_factory)();

// A struct used to pass pointers to functions serving the above functions.
struct transport_func {
	transport_factory factory;
};

} /* namespace zmq */

#endif /* TRANSPORT_HPP_ */
