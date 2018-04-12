/*
 * @file MessageQueue.cpp 定义文件, 基于boost::interprocess::ipc::message_queue封装消息队列
 * @version 0.2
 * @date 2017-10-02
 */

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>
#include "MessageQueue.h"
#include "GLog.h"

#define MQFUNC_SIZE		1024

MessageQueue::MessageQueue() {
	funcs_.reset(new CallbackFunc[MQFUNC_SIZE]);
}

MessageQueue::~MessageQueue() {
	Stop();
}

bool MessageQueue::RegisterMessage(const long id, const CBSlot& slot) {
	long pos(id - MSG_USER);
	bool rslt = pos >= 0 && pos < MQFUNC_SIZE;

	if (rslt) funcs_[pos].connect(slot);
	return rslt;
}

void MessageQueue::PostMessage(const long id, const long p1, const long p2) {
	if (mq_.unique()) {
		MSG_UNIT msg(id, p1, p2);
		mq_->send(&msg, sizeof(MSG_UNIT), 1);
	}
}

void MessageQueue::SendMessage(const long id, const long p1, const long p2) {
	if (mq_.unique()) {
		MSG_UNIT msg(id, p1, p2);
		mq_->send(&msg, sizeof(MSG_UNIT), 10);
	}
}

bool MessageQueue::Start(const char* name, bool is_create) {
	if (thrdmsg_.unique()) return true;

	try {
		if (is_create) {
			mq_.reset(new message_queue(boost::interprocess::open_or_create, name, 1024, sizeof(MSG_UNIT)));
		}
		else {
			mq_.reset(new message_queue(boost::interprocess::open_only, name));
		}
		thrdmsg_.reset(new boost::thread(boost::bind(&MessageQueue::thread_message, this)));

		return true;
	}
	catch(boost::interprocess::interprocess_exception& ex) {
		g_Log.Write(LOG_FAULT, "MessageQueue::Start", "%s", ex.what());
		return false;
	}
}

void MessageQueue::Stop() {
	if (thrdmsg_.unique()) {
		SendMessage(MSG_QUIT);
		thrdmsg_->join();
	}
}

void MessageQueue::interrupt_thread(threadptr& thrd) {
	if (thrd.unique()) {
		thrd->interrupt();
		thrd->join();
	}
}

void MessageQueue::thread_message() {
	MSG_UNIT msg;
	message_queue::size_type szrcv;
	message_queue::size_type szmsg = sizeof(MSG_UNIT);
	uint32_t priority;
	long pos;

	do {
		mq_->receive(&msg, szmsg, szrcv, priority);
		if ((pos = msg.id - MSG_USER) >= 0 && pos < MQFUNC_SIZE)
			(funcs_[pos])(msg.par1, msg.par2);
	} while(msg.id != MSG_QUIT);
}
