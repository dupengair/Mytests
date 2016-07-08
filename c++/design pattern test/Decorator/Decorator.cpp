/********************************************************************
	created:	2006/07/20
	filename: 	Decorator.cpp
	author:		�
                http://www.cppblog.com/converse/

	purpose:	Decoratorģʽ����ʾ����
*********************************************************************/

#include "Decorator.h"
#include <iostream>

Decorator::~Decorator()
{
	delete m_pComponent;
	m_pComponent = NULL;
}

void ConcreateComponent::Operation()
{
	std::cout << "Operation of ConcreateComponent\n";
}

void ConcreateDecorator::Operation()
{
	m_pComponent->Operation();
	AddedBehavior();
}

void ConcreateDecorator::AddedBehavior()
{
	std::cout << "AddedBehavior of ConcreateDecorator\n";
}
