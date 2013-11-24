/**
 * @file   SummerySlave.h
 * @Author icke
 * @date   03.07.2013
 * @brief  Brief description of file.
 *
 * Detailed description of file.
 */

#ifndef SUMMERYSLAVE_H_
#define SUMMERYSLAVE_H_

//std lib
#include <memory>
#include <thread>
#include <condition_variable>
#include <mutex>
using namespace std;


//own lib
#include <VirtualRTUSlave.h>
#include <Logger.h>

#define SLAVE_TYPE_SUMMERY	0x01

#define DEFAULT_SUMMERY_TIMEOUT_MS	1000
#define DEFAULT_SUMMERY_ADDR	255
#define DEFAULT_SUMMERY_COUNT	256
#define DEFAULT_SUMMERY_VALUE	0

using namespace icke2063::MB_Framework;
using namespace icke2063::common_cpp;

namespace icke2063 {
namespace MB_Gateway {

class SummerySlave: public VirtualRTUSlave, public Logger {
public:
	SummerySlave(uint8_t SlaveAddr = DEFAULT_SUMMERY_ADDR, unsigned int timeout = DEFAULT_SUMMERY_TIMEOUT_MS);
	virtual ~SummerySlave();
	virtual uint8_t getType( void ){return SLAVE_TYPE_SUMMERY;}

private:
	bool init(void);

	unique_ptr<thread> p_scanner_thread;
	bool m_running;

	virtual void thread_function (void);
	
	condition_variable m_Condition;  // Condition variable for timed_wait
	mutex m_Mutex;                   // Mutex
	unsigned int m_timeout;
};

} /* namespace MB_Gateway */
} /* namespace icke2063 */
#endif /* SUMMERYSLAVE_H_ */
