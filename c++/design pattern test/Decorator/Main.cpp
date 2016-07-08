/********************************************************************
	created:	2006/07/20
	filename: 	Main.cpp
	author:		�
                http://www.cppblog.com/converse/

	purpose:	Decoratorģʽ�Ĳ��Դ���
*********************************************************************/

#include "Decorator.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

			template <class T, class Y>
			void ConvertTo(T value, T& new_value)
			{
				new_value = value;
			}

			template <class T, class Y>
			void ConvertTo(T value, Y& new_value)
			{
				new_value = (Y)value;
			}


int main()
{


	// ��ʼ��һ��Component����
	Component* pComponent = new ConcreateComponent();
	// �������Component����ȥ��ʼ��һ��Decorator����,
	// �����Ϳ���Ϊ���Component����̬���ְ��
	Decorator* pDecorator = new ConcreateDecorator(pComponent);

	pDecorator->Operation();

	delete pDecorator;

	//system("pause");


       int a = 5, b = 0;

       ConvertTo(a, b);

       cout << "a, b : "<< a << " " << b << endl;


	return 0;
}
