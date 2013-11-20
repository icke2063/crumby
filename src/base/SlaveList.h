/**
 * @file   SlaveList.h
 * @Author icke2063
 * @date   02.06.2013
 * @brief  Brief description of file.
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

#ifndef SLAVELIST_H_
#define SLAVELIST_H_

#include <MBSlaveList.h>
#include <MBVirtualRTUSlave.h>

using namespace icke2063::MB_Framework;

#include <Mutex.h>
#include <ThreadPool.h>

namespace icke2063 {
namespace MB_Gateway {

class SlaveList: public MB_Framework::MBSlaveList {
public:
	SlaveList() {
		m_slavelist_lock.reset(new Mutex);
	}

	virtual ~SlaveList() {}

	virtual bool addSlave(MBVirtualRTUSlave *newSlave) {
		MBVirtualRTUSlave *curSlave = dynamic_cast<MBVirtualRTUSlave*>(newSlave);
		uint8_t index;

		if(curSlave == NULL)return false;
		index = curSlave->getSlaveAddr();
		std::lock_guard<std::mutex> lock(*((Mutex* )m_slavelist_lock.get())->getMutex().get()); //lock slavelist

		map<uint8_t, MBVirtualRTUSlave*>::iterator it = m_slavelist.find(index); //slave already added?
		if (it == m_slavelist.end()) {
			m_slavelist[index] = newSlave;
			return true;
		}

		return false;
	}

	virtual MBVirtualRTUSlave *removeSlave(uint8_t index) {
		MBVirtualRTUSlave* result = NULL;
		std::lock_guard<std::mutex> lock(*((Mutex* )m_slavelist_lock.get())->getMutex().get()); //lock slavelist

		map<uint8_t, MBVirtualRTUSlave*>::iterator it = m_slavelist.find(index); //slave in list?
		if (it != m_slavelist.end()) {
			result = it->second; //get pointer
			m_slavelist.erase(it); //remove from list
		}

		return result;
	}

	virtual void deleteSlave(uint8_t index) {
		MBVirtualRTUSlave* slave = removeSlave(index); //remove slave from list
		if (slave != NULL)
			delete slave; //delete if object exist
	}

	virtual MBVirtualRTUSlave *getSlave(uint8_t index) {
		map<uint8_t, MBVirtualRTUSlave*>::iterator it = m_slavelist.find(index); //slave in list?
		if (it != m_slavelist.end()) {
			return it->second; //get pointer
		}
		return NULL;
	}

	Mutex *getLock(){return (Mutex *)m_slavelist_lock.get();}
};

} /* namespace MB_Gateway */
} /* namespace icke2063 */
#endif /* SLAVELIST_H_ */
