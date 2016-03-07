#include "Timer.h"
#include <Windows.h>

//���캯������ʼ����������ΪĬ��ֵ
Timer::Timer()
	:	m_deltaTime(0.f),
		m_baseTime(0),
		m_stopTime(0),
		m_pausedTime(0),
		m_currTime(0),
		m_prevTime(0),
		m_stopped(false)
{
	__int64 frequency;
	//�ռ�ϵͳ��Ϣ����ʼ��������֮���ʱ���
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&frequency));
	m_secsPerCount = 1.f/frequency;
}

float Timer::totalTime() const
{
	//�������ͣ״̬������ͼ��ʾ��
	//	��ʼʱ��T0			��ͣ��ʼʱ��S	��ǰʱ��T
	//		|---------------------|------------|
	//�ܵ�ʱ��Ϊ:S - T0 - ��ͣ���ۼ�ʱ��
	//ע��Ѽ���ת��Ϊ��
	if(m_stopped)
	{
		return (m_stopTime-m_baseTime-m_pausedTime)*m_secsPerCount;
	}
	//���������״̬
	//	��ʼʱ��T0							��ǰʱ��T
	//		|----------------------------------|
	//�ܵ�ʱ��Ϊ��T - T0 - ��ͣ���ۼ�ʱ��
	//ע��Ѽ���ת��Ϊ��
	else
	{
		return (m_currTime-m_baseTime-m_pausedTime)*m_secsPerCount;
	}
}

float Timer::deltaTime() const
{
	//�������ϴμ�ʱ�м��ʱ���
	return m_deltaTime;
}

void Timer::start()
{
	//��ͣ�ָ�
	//�����������ͣ״̬���򲻲���
	//���Ϊ��ͣ״̬
	if(m_stopped)
	{
		//�Ȼ�ȡ��ʼʱ��
		__int64 startTime;
		QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&startTime));

		//�ѱ�����ͣʱ���ۼƵ�����ͣʱ����
		m_pausedTime += (startTime-m_stopTime);
		m_prevTime = startTime;
		m_stopTime = 0;
		m_stopped = false;
	}
}

void Timer::stop()
{
	if(!m_stopped)
	{
		__int64 curr;
		QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&curr));
		m_stopTime = curr;
		m_stopped = true;
	}
}

void Timer::reset()
{
	//���ö�ʱ�������빤��״̬
	__int64 curr;
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&curr));
	//ȷ����ʼʱ��
	m_baseTime = curr;
	m_currTime = curr;
	m_prevTime = curr;
	m_deltaTime = 0.f;

	m_stopTime = 0;
	//��ͣ�ۼ�����
	m_pausedTime = 0;
	m_stopped = false;
}

void Timer::tick()
{
	//ÿ֡���õļ�ʱ����
	//���ڸ��¶�ʱ��״̬

	//���Ϊ��ͣ״̬���򲻲���
	if(m_stopped)
	{
		m_deltaTime = 0.f;
		return;
	}

	//�Ȼ�ȡ��ǰʱ��
	__int64 curr;
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&curr));
	m_currTime = curr;
	//���������һ�μ�ʱ��ʱ���
	m_deltaTime = (m_currTime-m_prevTime)*m_secsPerCount;
	//ȷ��Ϊ����(��ʵһ������²�����Ϊ��)
	m_deltaTime = m_deltaTime<0? 0.f : m_deltaTime;

	//���ϴ�ʱ�����Ϊ����ʱ�䣬���´�Tick��
	m_prevTime = m_currTime;
}