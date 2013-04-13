#include "thread.h"
#include <algorithm>
#include <wx/log.h>

#ifdef SL_QT_MODE
Thread::Thread():
//		m_thread_sleep_semaphore( 0, 0 ),
		m_must_exit( false )
{
}

/** TODO this causes a segfault on exit for me (koshi) sometimes
http://docs.wxwidgets.org/stable/wx_wxthread.html#wxthreadwait
says to only call wxThread::Wait from another thread context
**/
Thread::~Thread() {
	if ( isRunning() )
		wait();
}

bool Thread::Sleep( int milliseconds ) {
//	wxSemaError err = m_thread_sleep_semaphore.WaitTimeout( milliseconds );
	usleep( milliseconds );
	return false;//err == wxSEMA_TIMEOUT;
}

void Thread::WakeUp() {
//	m_thread_sleep_semaphore.Post();
}

int Thread::Wait() {
	m_must_exit = true;
//	WakeUp();
//	return wxThread::Wait();
	return wait();
}

wxThreadError Thread::Run() {
	m_must_exit = false;
	start();
	return wxThreadError();
}

void Thread::run()
{
	Entry();
//	exec();
}

bool Thread::TestDestroy() {
	return true;//m_must_exit;//wxThread::TestDestroy() || m_must_exit;
}

wxThreadError Thread::Create()
{
	return wxThreadError();
}

void Thread::SetPriority(int priority)
{

}

void Thread::Yield()
{
	yieldCurrentThread();
}

#else
Thread::Thread():
		wxThread( wxTHREAD_JOINABLE ),
		m_thread_sleep_semaphore( 0, 0 ),
		m_must_exit( false )
{
}

/** TODO this causes a segfault on exit for me (koshi) sometimes
http://docs.wxwidgets.org/stable/wx_wxthread.html#wxthreadwait
says to only call wxThread::Wait from another thread context
**/
Thread::~Thread() {
	if ( IsAlive() )Wait();
}

bool Thread::Sleep( int milliseconds ) {
	wxSemaError err = m_thread_sleep_semaphore.WaitTimeout( milliseconds );
	return err == wxSEMA_TIMEOUT;
}

void Thread::WakeUp() {
	m_thread_sleep_semaphore.Post();
}

Thread::ExitCode Thread::Wait() {
	m_must_exit = true;
	WakeUp();
	return wxThread::Wait();
}

wxThreadError Thread::Run() {
	m_must_exit = false;
	return wxThread::Run();
}

bool Thread::TestDestroy() {
	return wxThread::TestDestroy() || m_must_exit;
}
#endif

