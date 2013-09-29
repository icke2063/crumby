/**
 * @file   Connection.h
 * @Author icke2063
 * @date   01.06.2013
 * @brief	This class can be used for a client connection.
 *
 * Copyright © 2013 icke2063 <icke2063@gmail.com>
 *
 * This framework is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This framework is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef CONNECTION_H_
#define CONNECTION_H_

#include <MBConnection.h>

// libmodbus
#include "modbus-private.h"
#include "modbus.h"

#include <VirtualRTUSlave.h>
#include <Logger.h>
#include <ThreadPool.h>
using namespace icke2063::common_cpp;


using namespace icke2063::MB_Framework;
using namespace icke2063::common_cpp;

namespace icke2063 {
namespace MB_Gateway {

class Connection: public MBConnection,public FunctorInt, public Logger{

	enum handleQuery_mode {
		handleReadAccess = 0x00,
		checkWriteAccess = 0x01,
		handleWriteAccess = 0x02
	};
public:
	Connection(modbus_t *ctx);
	virtual ~Connection();

	modbus_t *getConnInfo (void){return &m_ctx;}

private:
	virtual void functor_function(void);
	bool m_connection_running;

	bool handleQuery(uint8_t* query, VirtualRTUSlave* tmp_slave, enum handleQuery_mode mode);

	/* connection information from libmodbus library */
	modbus_t m_ctx;
};
} /* namespace MB_Gateway */
} /* namespace icke2063 */

#endif /* CONNECTION_H_ */
