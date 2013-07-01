/**
 * @file   HolRegHandlerRO.h
 * @Author icke
 * @date   15.06.2013
 * @brief  Brief description of file.
 *
 * Detailed description of file.
 */

#ifndef HOLREGHANDLERRO_H_
#define HOLREGHANDLERRO_H_

#include <SingleRegisterHandler.h>

namespace MB_Gateway {
namespace I2C {

class HolRegHandlerRO: public MB_Gateway::I2C::SingleRegisterHandler {
public:
	HolRegHandlerRO(enum address_mode mode = _8bit) :
			SingleRegisterHandler(mode) {
		logger->info("HolRegHandlerRO");
		enableReadInpReg = false;
	} //disable input register support
	virtual ~HolRegHandlerRO() {
	}

	virtual int checkWriteAccess(MBHandlerParam *param) {
		return 0;
	} //disable write support
	virtual int handleWriteAccess(MBHandlerParam *param) {
		return 0;
	} //disable write support
};

} /* namespace I2C */
} /* namespace MB_Gateway */
#endif /* HOLREGHANDLERRO_H_ */
