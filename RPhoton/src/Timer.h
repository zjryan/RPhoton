#ifndef _TIMER_H_
#define _TIMER_H_

class Timer
{
public:
	Timer();

	float totalTime() const;	//���ض�ʱ���ӿ�ʼ��ʱ�����ڵ���ʱ�䣨��������ͣʱ�䣩����λ����
	float deltaTime() const;	//���ر��μ�ʱ���ϴμ�ʱ֮���ʱ����λ����

	void start();				//��ͣ��ָ���ʱ
	void stop();				//��ͣ
	void reset();				//���ã���ʼ��ʱ����ʱ����ʼ����ʱ����
	void tick();				//��ʱһ�Σ�ÿһ֡����һ��

private:
	float	m_secsPerCount;		//ϵͳ�йأ�����ϵͳ������֮���ʱ���ֵ����λ����
								//��������Ƕ�ʱ����ʱ�䵥λת��Ϊ���롱�Ļ�׼
	float	m_deltaTime;		//�����ϴμ�ʱ֮���ʱ����λ����

	__int64 m_baseTime;			//��ʱ����ʼ��������ʼʱ���
	__int64 m_stopTime;			//�����ǰΪ��ͣ״̬����ָ��ʱ����ʼʱ��
	__int64 m_pausedTime;		//��ͣ����ʱ���ۼ�
	__int64	m_currTime;			//���μ�ʱ��ʱ���
	__int64	m_prevTime;			//�ϴμ�ʱ��ʱ���

	bool	m_stopped;			//�Ƿ���ͣ
};

#endif