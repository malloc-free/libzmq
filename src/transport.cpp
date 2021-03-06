/*
 * transport.cpp
 *
 *  Created on: 26/07/2014
 *      Author: michael
 */

#include "transport.hpp"
#include "mutex.hpp"

zmq::transport *zmq::transport::tx_copy() {
	tx_increment_use();
	return this;
}

bool zmq::transport::tx_destroy() {
	return tx_decrement_use();
}

void  zmq::transport::tx_increment_use(){
	lock.lock();
	++use_count;
	lock.unlock();
}

bool zmq::transport::tx_decrement_use() {
	bool del_ok = false;
	lock.lock();
	--use_count;

	if(!use_count)
		del_ok = true;

	lock.unlock();

	return del_ok;
}
