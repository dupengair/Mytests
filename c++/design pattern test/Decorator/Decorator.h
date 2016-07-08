/********************************************************************
	created:	2006/07/20
	filename: 	Decorator.h
	author:		�
                http://www.cppblog.com/converse/

	purpose:	Decoratorģʽ����ʾ����
*********************************************************************/

#ifndef DECORATOR_H
#define DECORATOR_H

// �������,����һ������ӿ�,����Ϊ����ӿڶ�̬�����ְ��.
class Component
{
public:
	Component(){}
	virtual ~Component(){}

	// ���麯��,��������ʵ��
	virtual void Operation() = 0;
};

// �������,ά��һ��ָ��Component�����ָ��
class Decorator
	: public Component
{
public:
	Decorator(Component* pComponent) : m_pComponent(pComponent){}
	virtual ~Decorator();

protected:
	Component* m_pComponent;
};

// ������Component,�������ʾ��Ҫ������̬���ְ�����
class ConcreateComponent
	: public Component
{
public:
	ConcreateComponent(){}
	virtual ~ConcreateComponent(){}

	virtual void Operation();
};

// ������Decorator,�������ΪConcreateComponent��̬���ְ�����
class ConcreateDecorator
	: public Decorator
{
public:
	ConcreateDecorator(Component* pComponent) : Decorator(pComponent){}
	virtual ~ConcreateDecorator(){}

	virtual void Operation();

private:
	void AddedBehavior();
};

#endif
