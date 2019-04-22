#pragma once
class VECTOR3
{
public:
	VECTOR3();
	VECTOR3(float x, float y);
	~VECTOR3();
	float x;
	float y;
	float image;
	// ������Z�q
	VECTOR3& operator = (const VECTOR3& vec);	//���Z�q�Ƃ��Ďg��Ȃ��ꍇ�擪��"operator"������
												// �Y�������Z�q
	float& operator[](float i);	//����0����1�@����ȊO�͂�

							//��r���Z�q
	bool operator == (const VECTOR3& vec) const;		//true false�̃u�[���^��Ԃ�
	bool operator != (const VECTOR3& vec) const;

	//�P�����Z�q
	VECTOR3& operator += (const VECTOR3& vec);	//�l�������������Ȃ��悤��const������
	VECTOR3& operator -= (const VECTOR3& vec);	//�l�������������Ȃ��悤��const������
	VECTOR3& operator *= (float k);
	VECTOR3& operator /= (float k);
	VECTOR3 operator+()const;
	VECTOR3 operator-()const;
};

//	�x�N�g���̉��Z
// VECTOR3 + VECTOR3
//�Ԃ�l�̌^�@operator�@���Z�q�i����1�A�c�j;
VECTOR3 operator +(const VECTOR3& i, const VECTOR3& j);
// float + VECTOR3
VECTOR3 operator +(float j, const VECTOR3& i);
// VECTOR3 - VECTOR3
VECTOR3 operator -(const VECTOR3& i, const VECTOR3& j);
// float * VECTOR3
VECTOR3 operator *(float j, const VECTOR3& i);
// VECTOR3 *float
VECTOR3 operator *(const VECTOR3& i, float j);
// VECTOR3 / float
VECTOR3 operator /(const VECTOR3& i, float j);

VECTOR3 operator %(const VECTOR3& i, float j);


